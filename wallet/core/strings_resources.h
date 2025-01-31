// Copyright 2019 The Beam Team
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

#pragma once

namespace beam
{
    extern const char kDefaultConfigFile[];

    extern const char kBEAM[];
    extern const char kGROTH[];
    extern const char kASSET[];
    extern const char kAGROTH[];
    extern const char kAmountASSET[];
    extern const char kAmountAGROTH[];
    extern const char kNA[];
    // Coin statuses
    extern const char kCoinStatusAvailable[];
    extern const char kCoinStatusUnavailable[];
    extern const char kCoinStatusSpent[];
    extern const char kCoinStatusMaturing[];
    extern const char kCoinStatusOutgoing[];
    extern const char kCoinStatusIncoming[];
    extern const char kCoinStatusConsumed[];

    // Errors
    extern const char kErrorUnknownCoinStatus[];
    extern const char kErrorUnknownTxStatus[];
    extern const char kErrorUnknownTxType[];
    extern const char kErrorUnknownSwapCoin[];
    extern const char kErrorInvalidWID[];
    extern const char kErrorTreasuryBadN[];
    extern const char kErrorTreasuryBadM[];
    extern const char kErrorTreasuryNothingRemains[];
    extern const char kErrorTreasuryPlanNotFound[];
    extern const char kErrorTreasuryInvalidResponse[];
    extern const char kErrorAddrExprTimeInvalid[];
    extern const char kErrorSeedPhraseInvalid[];
    extern const char kErrorSeedPhraseNotProvided[];
    extern const char kErrorTxIdParamReqired[];
    extern const char kErrorTxWithIdNotFound[];
    extern const char kErrorTxIdParamInvalid[];
    extern const char kErrorPpExportFailed[];
    extern const char kErrorPpCannotExportForReceiver[];
    extern const char kErrorPpExportFailedTxNotCompleted[];
    extern const char kErrorPpNotProvided[];
    extern const char kErrorPpInvalid[];
    extern const char kErrorSubkeyNotSpecified[];
    extern const char kErrorExportDataFail[];
    extern const char kErrorReceiverAddrMissing[];
    extern const char kErrorAmountMissing[];
    extern const char kErrorNegativeAmount[];
    extern const char kErrorTooBigAmount[];
    extern const char kErrorZeroAmount[];
    extern const char kErrorFeeToLow[];
    extern const char kErrorFeeForShieldedOutToLow[];
    extern const char kErrorSwapFeeRateMissing[];
    extern const char kErrorSwapWalletAddrNotResolved[];
    extern const char kErrorSwapWalletAddrUnspecified[];
    extern const char kErrorSwapWalletUserNameUnspecified[];
    extern const char kErrorSwapWalletPwdNotProvided[];
    extern const char kErrorCommandNotSpecified[];
    extern const char kErrorCommandUnknown[];
    extern const char kErrorWalletNotInitialized[];
    extern const char kErrorWalletAlreadyInitialized[];
    extern const char kErrorWalletPwdNotProvided[];
    extern const char kErrorWalletPwdNotMatch[];
    extern const char kErrorSeedPhraseFail[];
    extern const char kErrorWalletNotCreated[];
    extern const char kErrorCantOpenWallet[];
    extern const char kErrorNodeAddrNotSpecified[];
    extern const char kErrorNodeAddrUnresolved[];
    extern const char kErrorNodePoolPeriodTooMuch[];
    extern const char kErrorSwapAmountMissing[];
    extern const char kErrorSwapCoinUnknown[];
    extern const char kErrorCantSwapAsset[];
    extern const char kErrorNoBTCNodeCredentials[];
    extern const char kErrorSwapAmountTooLow[];
    extern const char kErrorNoLTCNodeCredentials[];
    extern const char kErrorNoQTUMNodeCredentials[];
    extern const char kErrorAmountTooLow[];
    extern const char kErrorUnableSendZeroCoin[];
    extern const char kErrorTxStatusInvalid[];
    extern const char kErrorCancelTxInInvalidStatus[];
    extern const char kErrorTxIdUnknown[];
    extern const char kErrorImportPathInvalid[];
    extern const char kErrorFileLocationParamReqired[];
    extern const char kErrorConnectionFailed[];
    extern const char kErrorNotEnoughtCoins[];
    extern const char kErrorCantSendMaxPrivacyToOwn[];

    // Swap Tx statuses
    extern const char kSwapTxStatusInitial[];
    extern const char kSwapTxStatusInvitation[];
    extern const char kSwapTxStatusBuildingBeamLockTX[];
    extern const char kSwapTxStatusBuildingBeamRefundTX[];
    extern const char kSwapTxStatusBuildingBeamRedeemTX[];
    extern const char kSwapTxStatusHandlingContractTX[];
    extern const char kSwapTxStatusSendingRefundTX[];
    extern const char kSwapTxStatusSendingRedeemTX[];
    extern const char kSwapTxStatusSendingBeamLockTX[];
    extern const char kSwapTxStatusSendingBeamRefundTX[];
    extern const char kSwapTxStatusSendingBeamRedeemTX[];
    extern const char kSwapTxStatusCompleted[];
    extern const char kSwapTxStatusCancelled[];
    extern const char kSwapTxStatusAborted[];
    extern const char kSwapTxStatusFailed[];
    extern const char kSwapTxStatusExpired[];
    // Coins available for swap
    extern const char kSwapCoinBTC[];
    extern const char kSwapCoinLTC[];
    extern const char kSwapCoinQTUM[];
    extern const char kSwapCoinBCH[];
    extern const char kSwapCoinBSV[];
    extern const char kSwapCoinDOGE[];
    extern const char kSwapCoinDASH[];
    // Treasury messages
    extern const char kTreasuryConsumeRemaining[];
    extern const char kTreasuryDataHash[];
    extern const char kTreasuryRecoveredCoinsTitle[];
    extern const char kTreasuryRecoveredCoin[];
    extern const char kTreasuryBurstsTitle[];
    extern const char kTreasuryBurst[];
    extern const char kTreasuryID[];
    // Address
    extern const char kAllAddrExprChanged[];
    extern const char kAddrExprChanged[];
    extern const char kAddrNewGenerated[];
    extern const char kWalletIdNewGenerated[];
    extern const char kAddrNewGeneratedLabel[];
    extern const char kAddrListTableHead[];
    extern const char kAddrListColumnComment[];
    extern const char kAddrListColumnAddress[];
    extern const char kAddrListColumnIdentity[];
    extern const char kAddrListColumnActive[];
    extern const char kAddrListColumnExprDate[];
    extern const char kAddrListColumnCreated[];
    extern const char kAddrListTableBody[];
    // Seed phrase
    extern const char kSeedPhraseGeneratedTitle[];
    extern const char kSeedPhraseGeneratedMessage[];
    extern const char kSeedPhraseReadTitle[];
    // Wallet info
    extern const char kWalletSummaryFormat[];
    extern const char kWalletAssetSummaryFormat[];
    extern const char kWalletUnreliableAsset[];
    extern const char kWalletNoInfo[];
    extern const char kBeamFee[];
    extern const char kBeamRefund[];
    extern const char kWalletAssetIDFormat[];
    extern const char kWalletAssetNameFormat[];
    extern const char kWalletAssetLockHeightFormat[];
    extern const char kWalletAssetRefreshHeightFormat[];
    extern const char kWalletAssetEmissionFormat[];
    extern const char kWalletAssetOwnerFormat[];
    extern const char kWalletSummaryFieldCurHeight[];
    extern const char kWalletSummaryFieldCurStateID[];
    extern const char kWalletSummaryFieldAvailable[];
    extern const char kWalletSummaryFieldMaturing[];
    extern const char kWalletSummaryFieldInProgress[];
    extern const char kWalletSummaryFieldUnavailable[];
    extern const char kWalletSummaryFieldAvailableCoinbase[];
    extern const char kWalletSummaryFieldTotalCoinbase[];
    extern const char kWalletSummaryFieldAvaliableFee[];
    extern const char kWalletSummaryFieldTotalFee[];
    extern const char kWalletSummaryFieldTotalUnspent[];
    extern const char kCoinsTableHeadFormat[];
    extern const char kCoinColumnId[];
    extern const char kCoinColumnMaturity[];
    extern const char kCoinColumnStatus[];
    extern const char kCoinColumnType[];
    extern const char kCoinsTableFormat[];
    extern const char kCoinConfirmationsCount[];
    // Tx history
    extern const char kTxHistoryTableHead[];
    extern const char kTxHistoryTableFormat[];
    extern const char kTxHistoryColumnDatetTime[];
    extern const char kTxHistoryColumnHeight[];
    extern const char kTxHistoryColumnDirection[];
    extern const char kTxHistoryColumnAmount[];
    extern const char kAssetTxHistoryColumnAmount[];
    extern const char kTxHistoryColumnStatus[];
    extern const char kTxHistoryColumnId[];
    extern const char kTxHistoryColumnKernelId[];
    extern const char kTxDirectionSelf[];
    extern const char kTxDirectionOut[];
    extern const char kTxDirectionIn[];
    extern const char kTxHistoryEmpty[];
    extern const char kTxHistoryUnreliableTxs[];
    extern const char kTxHistoryUnreliableCoins[];
    extern const char kTxAddress[];
    extern const char kNoCoins[];
    extern const char kNoShieldedCoins[];
    extern const char kSwapTxHistoryEmpty[];
    extern const char kSwapTxHistoryTableHead[];
    extern const char kSwapTxHistoryTableFormat[];
    extern const char kTxHistoryColumnSwapAmount[];
    extern const char kTxHistoryColumnSwapType[];
    extern const char kOrphanedAseetTxs[];
    extern const char kNoAssetsInWallet[];
    extern const char kNoAssetTxsInWallet[];

    // Tx Details
    extern const char kTxDetailsFormat[];
    extern const char kTxDetailsFailReason[];

    extern const char kPpExportedFrom[];
    extern const char kSubKeyInfo[];
    extern const char kOwnerKeyInfo[];
    extern const char kDataExportedMessage[];

    extern const char kVersionInfo[];
    extern const char kRulesSignatureInfo[];
    extern const char kStartMessage[];
    extern const char kWalletCreatedMessage[];
    extern const char kDefaultAddrLabel[];
    extern const char kDefaultAddrExpiration[];
    extern const char kWalletOpenedMessage[];

    extern const char kNodePoolPeriod[];
    extern const char kNodePoolPeriodRounded[];

    extern const char kPpRequired[];

    // Assets
    extern const char kErrorAssetIdOrMetaRequired[];
    extern const char kErrorAssetMetadataRequired[];
    extern const char kErrorAssetIDRequired[];
    extern const char kErrorAssetNonSTDMeta[];
    extern const char kErrorAssetNotFound[];
    extern const char kErrorAssetNotOwned[];
    extern const char kErrorAssetLoadMeta[];

    // Laser
#ifdef BEAM_LASER_SUPPORT
    extern const char kLaserWaitPeer[];
    extern const char kLaserOpening[];
    extern const char kLaserOpenFailed[];
    extern const char kLaserOpen[];
    extern const char kLaserUpdating[];
    extern const char kLaserClosing[];
    extern const char kLaserClosed[];
    extern const char kLaserExpired[];
    extern const char kLaserUnknown[];
    extern const char kLaserErrorParamsRead[];
    extern const char kLaserErrorMyAmountMissing[];
    extern const char kLaserErrorTrgAmountMissing[];
    extern const char kLaserErrorChannelIdMissing[];
    extern const char kLaserChannelListTableHead[];
    extern const char kLaserChannelListChannelId[];
    extern const char kLaserChannelListAMy[];
    extern const char kLaserChannelListATrg[];
    extern const char kLaserChannelListState[];
    extern const char kLaserChannelListFee[];
    extern const char kLaserChannelListValidTill[];
    extern const char kLaserChannelTableBody[];
    extern const char kLaserErrorOpenFailed[];
    extern const char kLaserMessageClosed[];
    extern const char kLaserMessageExpired[];
    extern const char kLaserErrorTransferFailed[];
    extern const char kLaserMessageChannelServed[];
    extern const char kLaserMessageUpdateFinished[];
    extern const char kLaserMessageCloseFailed[];

    extern const char kLaserCurrentState[];
#endif  // BEAM_LASER_SUPPORT

    // lelantus
    extern const char kErrorShieldedIDMissing[];
    extern const char kErrorWindowBeginMissing[];
}
