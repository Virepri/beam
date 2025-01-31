// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ManagerStd.h"
#include "../core/serialization_adapters.h"

namespace beam {
namespace bvm2 {

	ManagerStd::ManagerStd()
	{
		m_pOut = &m_Out;
	}

	void ManagerStd::Unfreeze()
	{
		assert(m_Freeze);
		if (!--m_Freeze)
			m_UnfreezeEvt.start();
			//OnUnfreezed();
	}

	void ManagerStd::OnUnfreezed()
	{
		try {
			RunSync();
		}
		catch (const std::exception& exc) {
			OnDone(&exc);
		}
	}

	void ManagerStd::UnfreezeEvt::OnSchedule()
	{
		cancel();
		get_ParentObj().OnUnfreezed();
	}

	void ManagerStd::RemoteRead::Abort()
	{
		if (m_pRequest) {
			m_pRequest->m_pTrg = nullptr;
			m_pRequest.reset();
		}
	}

	void ManagerStd::RemoteRead::Post(proto::FlyClient::Request& r)
	{
		Wasm::Test(get_ParentObj().m_pNetwork != nullptr);

		Abort();
		m_pRequest.reset(&r);

		get_ParentObj().m_Freeze++;
		get_ParentObj().m_pNetwork->PostRequest(r, *this);
	}

	void ManagerStd::RemoteRead::OnComplete(proto::FlyClient::Request&)
	{
		assert(m_pRequest && m_pRequest->m_pTrg);
		get_ParentObj().Unfreeze();
	}

	void ManagerStd::VarsEnum(const Blob& kMin, const Blob& kMax)
	{
		boost::intrusive_ptr<RemoteRead::RequestVars> pReq(new RemoteRead::RequestVars);
		auto& r = *pReq;

		kMin.Export(r.m_Msg.m_KeyMin);
		kMax.Export(r.m_Msg.m_KeyMax);

		m_RemoteRead.Post(r);
	}

	bool ManagerStd::VarsMoveNext(Blob& key, Blob& val)
	{
		if (!m_RemoteRead.m_pRequest || (proto::FlyClient::Request::Type::ContractVars != m_RemoteRead.m_pRequest->get_Type()))
			return false; // enum was not called
		auto& r = Cast::Up<RemoteRead::RequestVars>(*m_RemoteRead.m_pRequest);

		if (r.m_pTrg)
		{
			r.m_pTrg = nullptr;
			r.m_Consumed = 0;
			r.m_Buf = std::move(r.m_Res.m_Result);
			if (r.m_Buf.empty())
				r.m_Res.m_bMore = false;
		}

		if (r.m_Consumed == r.m_Buf.size())
		{
			m_RemoteRead.Abort();
			return false;
		}

		auto* pBuf = &r.m_Buf.front();

		Deserializer der;
		der.reset(pBuf + r.m_Consumed, r.m_Buf.size() - r.m_Consumed);

		der
			& key.n
			& val.n;

		r.m_Consumed = r.m_Buf.size() - der.bytes_left();

		uint32_t nTotal = key.n + val.n;
		Wasm::Test(nTotal >= key.n); // no overflow
		Wasm::Test(nTotal <= der.bytes_left());

		key.p = pBuf + r.m_Consumed;
		r.m_Consumed += key.n;

		val.p = pBuf + r.m_Consumed;
		r.m_Consumed += val.n;

		if ((r.m_Consumed == r.m_Buf.size()) && r.m_Res.m_bMore)
		{
			r.m_Res.m_bMore = false;

			// ask for more
			key.Export(r.m_Msg.m_KeyMin);
			r.m_Msg.m_bSkipMin = true;

			m_Freeze++;
			m_pNetwork->PostRequest(r, m_RemoteRead);
		}

		return true;
	}

	void ManagerStd::LogsEnum(const Blob& kMin, const Blob& kMax, const HeightPos* pPosMin, const HeightPos* pPosMax)
	{
		boost::intrusive_ptr<RemoteRead::RequestLogs> pReq(new RemoteRead::RequestLogs);
		auto& r = *pReq;

		kMin.Export(r.m_Msg.m_KeyMin);
		kMax.Export(r.m_Msg.m_KeyMax);

		if (pPosMin)
			r.m_Msg.m_PosMin = *pPosMin;

		if (pPosMax)
			r.m_Msg.m_PosMax = *pPosMax;
		else
			r.m_Msg.m_PosMax.m_Height = MaxHeight;

		m_RemoteRead.Post(r);
	}

	bool ManagerStd::LogsMoveNext(Blob& key, Blob& val, HeightPos& pos)
	{
		if (!m_RemoteRead.m_pRequest || (proto::FlyClient::Request::Type::ContractLogs != m_RemoteRead.m_pRequest->get_Type()))
			return false; // enum was not called
		auto& r = Cast::Up<RemoteRead::RequestLogs>(*m_RemoteRead.m_pRequest);

		if (r.m_pTrg)
		{
			r.m_pTrg = nullptr;
			r.m_Consumed = 0;
			r.m_Buf = std::move(r.m_Res.m_Result);
			if (r.m_Buf.empty())
				r.m_Res.m_bMore = false;
		}

		if (r.m_Consumed == r.m_Buf.size())
		{
			m_RemoteRead.Abort();
			return false;
		}

		auto* pBuf = &r.m_Buf.front();

		Deserializer der;
		der.reset(pBuf + r.m_Consumed, r.m_Buf.size() - r.m_Consumed);

		der
			& pos
			& key.n
			& val.n;

		if (pos.m_Height)
		{
			r.m_Msg.m_PosMin.m_Height += pos.m_Height;
			r.m_Msg.m_PosMin.m_Pos = 0;
		}

		r.m_Msg.m_PosMin.m_Pos += pos.m_Pos;
		pos = r.m_Msg.m_PosMin;

		r.m_Consumed = r.m_Buf.size() - der.bytes_left();

		uint32_t nTotal = key.n + val.n;
		Wasm::Test(nTotal >= key.n); // no overflow
		Wasm::Test(nTotal <= der.bytes_left());

		key.p = pBuf + r.m_Consumed;
		r.m_Consumed += key.n;

		val.p = pBuf + r.m_Consumed;
		r.m_Consumed += val.n;

		if ((r.m_Consumed == r.m_Buf.size()) && r.m_Res.m_bMore)
		{
			// ask for more
			r.m_Res.m_bMore = false;
			r.m_Msg.m_PosMin.m_Pos++;

			m_Freeze++;
			m_pNetwork->PostRequest(r, m_RemoteRead);
		}

		return true;
	}

	Height ManagerStd::get_Height()
	{
		Wasm::Test(m_pHist);

		Block::SystemState::Full s;
		m_pHist->get_Tip(s); // zero-inits if no tip
		return s.m_Height;
	}

	bool ManagerStd::PerformRequestSync(proto::FlyClient::Request& r)
	{
		Wasm::Test(m_pNetwork != nullptr);

		struct MyHandler
			:public proto::FlyClient::Request::IHandler
		{
			proto::FlyClient::Request* m_pReq = nullptr;

			~MyHandler() {
				m_pReq->m_pTrg = nullptr;
			}

			virtual void OnComplete(proto::FlyClient::Request&) override
			{
				m_pReq->m_pTrg = nullptr;
				io::Reactor::get_Current().stop();
			}

		} myHandler;

		myHandler.m_pReq = &r;
		m_pNetwork->PostRequest(r, myHandler);

		io::Reactor::get_Current().run();

		return !r.m_pTrg;
	}

	bool ManagerStd::get_HdrAt(Block::SystemState::Full& s)
	{
		Wasm::Test(m_pHist);

		Height h = s.m_Height;
		if (m_pHist->get_At(s, h))
			return true;

		proto::FlyClient::RequestEnumHdrs::Ptr pReq(new proto::FlyClient::RequestEnumHdrs);
		auto& r = *pReq;
		r.m_Msg.m_Height = h;

		if (!PerformRequestSync(r))
			return false;

		if (1 != r.m_vStates.size())
			return false;

		s = std::move(r.m_vStates.front());
		return true;
	}

	bool ManagerStd::VarGetProof(Blob& key, ByteBuffer& val, beam::Merkle::Proof& proof)
	{
		proto::FlyClient::RequestContractVar::Ptr pReq(new proto::FlyClient::RequestContractVar);
		auto& r = *pReq;
		key.Export(r.m_Msg.m_Key);

		if (!PerformRequestSync(r))
			return false;

		if (r.m_Res.m_Proof.empty())
			return false;

		r.m_Res.m_Value.swap(val);
		r.m_Res.m_Proof.swap(proof);
		return true;
	}

	bool ManagerStd::LogGetProof(const HeightPos& hp, beam::Merkle::Proof& proof)
	{
		proto::FlyClient::RequestContractLogProof::Ptr pReq(new proto::FlyClient::RequestContractLogProof);
		auto& r = *pReq;
		r.m_Msg.m_Pos = hp;

		if (!PerformRequestSync(r))
			return false;

		if (r.m_Res.m_Proof.empty())
			return false;

		r.m_Res.m_Proof.swap(proof);
		return true;
	}

	void ManagerStd::StartRun(uint32_t iMethod)
	{
		InitMem();
		m_Code = m_BodyManager;
		m_Out.str("");
		m_Out.clear();
		decltype(m_vInvokeData)().swap(m_vInvokeData);

		try {
			CallMethod(iMethod);
			RunSync();
		}
		catch (const std::exception& exc) {
			OnDone(&exc);
		}
	}


	void ManagerStd::RunSync()
	{
		while (!IsDone())
		{
			if (m_Freeze)
				return;

			RunOnce();
		}
		OnDone(nullptr);
	}

	void ManagerStd::DerivePk(ECC::Point& pubKey, const ECC::Hash::Value& hv)
	{
		Wasm::Test(m_pPKdf != nullptr);

		ECC::Point::Native pt;
		m_pPKdf->DerivePKeyG(pt, hv);
		pubKey = pt;
	}

	void ManagerStd::GenerateKernel(const ContractID* pCid, uint32_t iMethod, const Blob& args, const Shaders::FundsChange* pFunds, uint32_t nFunds, const ECC::Hash::Value* pSig, uint32_t nSig, const char* szComment, uint32_t nCharge)
	{
		auto& v = m_vInvokeData.emplace_back();

		if (iMethod)
		{
			assert(pCid);
			v.m_Cid = *pCid;
		}
		else
		{
			v.m_Cid = Zero;
			v.m_Data = m_BodyContract;
		}

		v.m_iMethod = iMethod;
		args.Export(v.m_Args);
		v.m_vSig.assign(pSig, pSig + nSig);
		v.m_sComment = szComment;
		v.m_Charge = nCharge;

		for (uint32_t i = 0; i < nFunds; i++)
		{
			const auto& x = pFunds[i];
			AmountSigned val = x.m_Amount;
			if (!x.m_Consume)
				val = -val;

			v.m_Spend.AddSpend(x.m_Aid, val);
		}
	}

} // namespace bvm2
} // namespace beam
