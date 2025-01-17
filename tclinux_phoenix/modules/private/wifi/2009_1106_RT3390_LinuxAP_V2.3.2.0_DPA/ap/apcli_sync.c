/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2006, Ralink Technology, Inc.
 *
 * All rights reserved.	Ralink's source	code is	an unpublished work	and	the
 * use of a	copyright notice does not imply	otherwise. This	source code
 * contains	confidential trade secret material of Ralink Tech. Any attemp
 * or participation	in deciphering,	decoding, reverse engineering or in	any
 * way altering	the	source code	is stricitly prohibited, unless	the	prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	sta_sync.c

	Abstract:

	Revision History:
	Who			When			What
	--------	----------		----------------------------------------------
	Fonchi		2006-06-23      modified for rt61-APClinent
*/

#ifdef APCLI_SUPPORT

#include "rt_config.h"

static VOID ApCliProbeTimeout(
	IN PVOID SystemSpecific1, 
	IN PVOID FunctionContext, 
	IN PVOID SystemSpecific2, 
	IN PVOID SystemSpecific3);

static VOID ApCliMlmeProbeReqAction(
	IN PRTMP_ADAPTER pAd,
	IN MLME_QUEUE_ELEM *Elem);

static VOID ApCliPeerProbeRspAtJoinAction(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem);

static VOID ApCliProbeTimeoutAtJoinAction(
	IN PRTMP_ADAPTER pAd,
	IN MLME_QUEUE_ELEM *Elem);

static VOID ApCliInvalidStateWhenJoin(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem);

static VOID ApCliEnqueueProbeRequest(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR SsidLen,
	OUT PCHAR Ssid,
	IN USHORT ifIndex);

DECLARE_TIMER_FUNCTION(ApCliProbeTimeout);
BUILD_TIMER_FUNCTION(ApCliProbeTimeout);

/*
    ==========================================================================
    Description:
        The sync state machine, 
    Parameters:
        Sm - pointer to the state machine
    Note:
        the state machine looks like the following
    ==========================================================================
 */
VOID ApCliSyncStateMachineInit(
	IN PRTMP_ADAPTER pAd,
	IN STATE_MACHINE *Sm,
	OUT STATE_MACHINE_FUNC Trans[])
{
	UCHAR i;

	StateMachineInit(Sm, (STATE_MACHINE_FUNC*)Trans,
		APCLI_MAX_SYNC_STATE, APCLI_MAX_SYNC_MSG,
		(STATE_MACHINE_FUNC)Drop, APCLI_SYNC_IDLE,
		APCLI_SYNC_MACHINE_BASE);

	// column 1
	StateMachineSetAction(Sm, APCLI_SYNC_IDLE, APCLI_MT2_MLME_PROBE_REQ, (STATE_MACHINE_FUNC)ApCliMlmeProbeReqAction);

	//column 2
	StateMachineSetAction(Sm, APCLI_JOIN_WAIT_PROBE_RSP, APCLI_MT2_MLME_PROBE_REQ, (STATE_MACHINE_FUNC)ApCliInvalidStateWhenJoin);
	StateMachineSetAction(Sm, APCLI_JOIN_WAIT_PROBE_RSP, APCLI_MT2_PEER_PROBE_RSP, (STATE_MACHINE_FUNC)ApCliPeerProbeRspAtJoinAction);
	StateMachineSetAction(Sm, APCLI_JOIN_WAIT_PROBE_RSP, APCLI_MT2_PROBE_TIMEOUT, (STATE_MACHINE_FUNC)ApCliProbeTimeoutAtJoinAction);

	// timer init
	RTMPInitTimer(pAd, &pAd->MlmeAux.ProbeTimer, GET_TIMER_FUNCTION(ApCliProbeTimeout), pAd, FALSE);

	for (i = 0; i < MAX_APCLI_NUM; i++)
		pAd->ApCfg.ApCliTab[i].SyncCurrState = APCLI_SYNC_IDLE;

	return;
}

/* 
    ==========================================================================
    Description:
        Becaon timeout handler, executed in timer thread
    ==========================================================================
 */
static VOID ApCliProbeTimeout(
	IN PVOID SystemSpecific1, 
	IN PVOID FunctionContext, 
	IN PVOID SystemSpecific2, 
	IN PVOID SystemSpecific3)
{
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *)FunctionContext;

	DBGPRINT(RT_DEBUG_TRACE, ("ApCli_SYNC - ProbeReqTimeout\n"));

	MlmeEnqueue(pAd, APCLI_SYNC_STATE_MACHINE, APCLI_MT2_PROBE_TIMEOUT, 0, NULL, 0);
	RTMP_MLME_HANDLER(pAd);

	return;
}

/* 
    ==========================================================================
    Description:
        MLME PROBE req state machine procedure
    ==========================================================================
 */
static VOID ApCliMlmeProbeReqAction(
	IN PRTMP_ADAPTER pAd,
	IN MLME_QUEUE_ELEM *Elem)
{
	BOOLEAN Cancelled;
	APCLI_MLME_JOIN_REQ_STRUCT *Info = (APCLI_MLME_JOIN_REQ_STRUCT *)(Elem->Msg);
	USHORT ifIndex = (USHORT)(Elem->Priv);
	PULONG pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].SyncCurrState;


	DBGPRINT(RT_DEBUG_TRACE, ("ApCli SYNC - ApCliMlmeProbeReqAction(Ssid %s)\n", Info->Ssid));

	// reset all the timers
	RTMPCancelTimer(&pAd->MlmeAux.ProbeTimer, &Cancelled);

	pAd->MlmeAux.Rssi = -9999;
	pAd->MlmeAux.Channel = pAd->CommonCfg.Channel;
	pAd->MlmeAux.SupRateLen = pAd->CommonCfg.SupRateLen;
	NdisMoveMemory(pAd->MlmeAux.SupRate, pAd->CommonCfg.SupRate, pAd->CommonCfg.SupRateLen);

	RTMPSetTimer(&pAd->MlmeAux.ProbeTimer, PROBE_TIMEOUT);

	ApCliEnqueueProbeRequest(pAd, Info->SsidLen, (PCHAR) Info->Ssid, ifIndex);

	DBGPRINT(RT_DEBUG_TRACE, ("ApCli SYNC - Start Probe the SSID %s on channel =%d\n", pAd->MlmeAux.Ssid, pAd->MlmeAux.Channel));

	*pCurrState = APCLI_JOIN_WAIT_PROBE_RSP;

	return;
}

/* 
    ==========================================================================
    Description:
        When waiting joining the (I)BSS, beacon received from external
    ==========================================================================
 */
static VOID ApCliPeerProbeRspAtJoinAction(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem) 
{
	UCHAR Bssid[MAC_ADDR_LEN], Addr2[MAC_ADDR_LEN];
	UCHAR Ssid[MAX_LEN_OF_SSID], SsidLen, BssType, Channel, MessageToMe, 
		DtimCount, DtimPeriod, BcastFlag; 
	LARGE_INTEGER TimeStamp;
	USHORT BeaconPeriod, AtimWin, CapabilityInfo;
//	UINT FrameLen = 0;
	CF_PARM Cf;
	UCHAR Erp;
	UCHAR SupRate[MAX_LEN_OF_SUPPORTED_RATES], ExtRate[MAX_LEN_OF_SUPPORTED_RATES];
	UCHAR SupRateLen, ExtRateLen;
	UCHAR CkipFlag;
	USHORT LenVIE;
	UCHAR AironetCellPowerLimit;
	EDCA_PARM EdcaParm;
	QBSS_LOAD_PARM QbssLoad;
	QOS_CAPABILITY_PARM QosCapability;
	UCHAR VarIE[MAX_VIE_LEN];		// Total VIE length = MAX_VIE_LEN - -5
	NDIS_802_11_VARIABLE_IEs *pVIE = NULL;
	ULONG RalinkIe;
	APCLI_CTRL_MSG_STRUCT ApCliCtrlMsg;
	HT_CAPABILITY_IE HtCapability;
	ADD_HT_INFO_IE AddHtInfo;	// AP might use this additional ht info IE 
	UCHAR HtCapabilityLen;
	UCHAR AddHtInfoLen;
	UCHAR NewChannel;
	UCHAR NewExtChannelOffset = 0xff;
	PAPCLI_STRUCT pApCliEntry = NULL;
#ifdef DOT11_N_SUPPORT
        UCHAR CentralChannel;
#endif // DOT11_N_SUPPORT //
	EXT_CAP_INFO_ELEMENT	ExtCapInfo;

	USHORT ifIndex = (USHORT)(Elem->Priv);
	PULONG pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].SyncCurrState;


	// Init Variable IE structure
	pVIE = (PNDIS_802_11_VARIABLE_IEs) VarIE;
	pVIE->Length = 0;
	RTMPZeroMemory(&HtCapability, sizeof(HT_CAPABILITY_IE));
	RTMPZeroMemory(&AddHtInfo, sizeof(ADD_HT_INFO_IE));

	if (PeerBeaconAndProbeRspSanity(pAd, 
								Elem->Msg, 
								Elem->MsgLen, 
								Elem->Channel,
								Addr2, 
								Bssid, 
								(PCHAR) Ssid, 
								&SsidLen, 
								&BssType, 
								&BeaconPeriod, 
								&Channel, 
								&NewChannel,
								&TimeStamp, 
								&Cf, 
								&AtimWin, 
								&CapabilityInfo, 
								&Erp,
								&DtimCount, 
								&DtimPeriod, 
								&BcastFlag, 
								&MessageToMe, 
								SupRate,
								&SupRateLen,
								ExtRate,
								&ExtRateLen,
								&CkipFlag,
								&AironetCellPowerLimit,
								&EdcaParm,
								&QbssLoad,
								&QosCapability,
								&RalinkIe,
								&HtCapabilityLen,
								&HtCapability,
								&ExtCapInfo,
								&AddHtInfoLen,
								&AddHtInfo,
								&NewExtChannelOffset,
								&LenVIE,
								pVIE))
	{
		// BEACON from desired BSS/IBSS found. We should be able to decide most
		// BSS parameters here.
		// Q. But what happen if this JOIN doesn't conclude a successful ASSOCIATEION?
		//    Do we need to receover back all parameters belonging to previous BSS?
		// A. Should be not. There's no back-door recover to previous AP. It still need
		//    a new JOIN-AUTH-ASSOC sequence.
		INT ssidEqualFlag = FALSE;
		INT ssidEmptyFlag = FALSE;
		INT bssidEqualFlag = FALSE;
		INT bssidEmptyFlag = FALSE;
		INT matchFlag = FALSE;

		pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

		// Check the Probe-Rsp's Bssid.
		if(!MAC_ADDR_EQUAL(pApCliEntry->CfgApCliBssid, ZERO_MAC_ADDR))
			bssidEqualFlag = MAC_ADDR_EQUAL(pApCliEntry->CfgApCliBssid, Bssid);
		else
			bssidEmptyFlag = TRUE;

		// Check the Probe-Rsp's Ssid.
		if(pApCliEntry->CfgSsidLen != 0)
			ssidEqualFlag = SSID_EQUAL(pApCliEntry->CfgSsid, pApCliEntry->CfgSsidLen, Ssid, SsidLen);
		else
			ssidEmptyFlag = TRUE;


		// bssid and ssid, Both match.
		if (bssidEqualFlag && ssidEqualFlag)
			matchFlag = TRUE;

		// ssid match but bssid doesn't be indicate.
		else if(ssidEqualFlag && bssidEmptyFlag)
			matchFlag = TRUE;

		// user doesn't indicate any bssid or ssid. AP-Clinet will auto pick a AP to join by most strong siganl strength.
		else if (bssidEmptyFlag && ssidEmptyFlag)
			matchFlag = TRUE;


		DBGPRINT(RT_DEBUG_TRACE, ("SYNC - bssidEqualFlag=%d, ssidEqualFlag=%d, matchFlag=%d\n", bssidEqualFlag, ssidEqualFlag, matchFlag));
		if (matchFlag)
		{
			// Validate RSN IE if necessary, then copy store this information
			if (LenVIE > 0 
#ifdef WSC_AP_SUPPORT
                && pAd->ApCfg.ApCliTab[ifIndex].WscControl.WscConfMode == WSC_DISABLE
#endif // WSC_AP_SUPPORT //
                )
			{
				if (ApCliValidateRSNIE(pAd, (PEID_STRUCT)pVIE, LenVIE, ifIndex))
				{
					pAd->MlmeAux.VarIELen = LenVIE;
					NdisMoveMemory(pAd->MlmeAux.VarIEs, pVIE, pAd->MlmeAux.VarIELen);
				}
				else
				{
					// ignore this response
					pAd->MlmeAux.VarIELen = 0;
					if (pAd->ApCfg.ApCliTab[ifIndex].AuthMode >= Ndis802_11AuthModeWPA)
					{
						DBGPRINT(RT_DEBUG_ERROR, ("ERROR: The RSN IE of this received Probe-resp is dis-match !!!!!!!!!! \n"));
						return;
					}
				}
			}
			else
			{
				if (pApCliEntry->AuthMode >= Ndis802_11AuthModeWPA
#ifdef WSC_AP_SUPPORT
                    && pAd->ApCfg.ApCliTab[ifIndex].WscControl.WscConfMode == WSC_DISABLE
#endif // WSC_AP_SUPPORT //
                    )
				{
					// ignore this response
					DBGPRINT(RT_DEBUG_ERROR, ("ERROR: The received Probe-resp has empty RSN IE !!!!!!!!!! \n"));
					return;
				}	
				
				pAd->MlmeAux.VarIELen = 0;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("SYNC - receive desired PROBE_RSP at JoinWaitProbeRsp... Channel = %d\n", Channel));

			// if the Bssid doesn't be indicated then you need to decide which AP to connect by most strong Rssi signal strength.
			if (bssidEqualFlag == FALSE)
			{
				// caculate real rssi value.
				CHAR Rssi0 = ConvertToRssi(pAd, Elem->Rssi0, RSSI_0);
				CHAR Rssi1 = ConvertToRssi(pAd, Elem->Rssi1, RSSI_1);
				CHAR Rssi2 = ConvertToRssi(pAd, Elem->Rssi2, RSSI_2);
				LONG RealRssi = (LONG)(RTMPMaxRssi(pAd, Rssi0, Rssi1, Rssi2));

				DBGPRINT(RT_DEBUG_TRACE, ("SYNC - previous Rssi = %ld current Rssi=%ld\n", pAd->MlmeAux.Rssi, (LONG)RealRssi));
				if (pAd->MlmeAux.Rssi > (LONG)RealRssi)
					return;
				else
					pAd->MlmeAux.Rssi = RealRssi;
			} else
			{
				BOOLEAN Cancelled;
				RTMPCancelTimer(&pAd->MlmeAux.ProbeTimer, &Cancelled);
			}

			NdisMoveMemory(pAd->MlmeAux.Ssid, Ssid, SsidLen);
			pAd->MlmeAux.SsidLen = SsidLen;

			NdisMoveMemory(pAd->MlmeAux.Bssid, Bssid, MAC_ADDR_LEN);			
			pAd->MlmeAux.CapabilityInfo = CapabilityInfo & SUPPORTED_CAPABILITY_INFO;
			pAd->MlmeAux.BssType = BssType;
			pAd->MlmeAux.BeaconPeriod = BeaconPeriod;
			pAd->MlmeAux.Channel = Channel;
			pAd->MlmeAux.AtimWin = AtimWin;
			pAd->MlmeAux.CfpPeriod = Cf.CfpPeriod;
			pAd->MlmeAux.CfpMaxDuration = Cf.CfpMaxDuration;
			pAd->MlmeAux.APRalinkIe = RalinkIe;

			// Copy AP's supported rate to MlmeAux for creating assoication request
			// Also filter out not supported rate
			pAd->MlmeAux.SupRateLen = SupRateLen;
			NdisMoveMemory(pAd->MlmeAux.SupRate, SupRate, SupRateLen);
			RTMPCheckRates(pAd, pAd->MlmeAux.SupRate, &pAd->MlmeAux.SupRateLen);
			pAd->MlmeAux.ExtRateLen = ExtRateLen;
			NdisMoveMemory(pAd->MlmeAux.ExtRate, ExtRate, ExtRateLen);
			RTMPCheckRates(pAd, pAd->MlmeAux.ExtRate, &pAd->MlmeAux.ExtRateLen);

#ifdef DOT11_N_SUPPORT
			NdisZeroMemory(pAd->ApCfg.ApCliTab[ifIndex].RxMcsSet,sizeof(pAd->ApCfg.ApCliTab[ifIndex].RxMcsSet));
			// filter out un-supported ht rates
			if ((HtCapabilityLen > 0) && 
				(pApCliEntry->DesiredHtPhyInfo.bHtEnable) &&
				(pAd->CommonCfg.PhyMode >= PHY_11ABGN_MIXED))
			{
				RTMPZeroMemory(&pAd->MlmeAux.HtCapability, SIZE_HT_CAP_IE);
				pAd->MlmeAux.NewExtChannelOffset = NewExtChannelOffset;
				pAd->MlmeAux.HtCapabilityLen = HtCapabilityLen;
				ApCliCheckHt(pAd, ifIndex, &HtCapability, &AddHtInfo);

				if (AddHtInfoLen > 0)
				{
					CentralChannel = AddHtInfo.ControlChan;
		 			// Check again the Bandwidth capability of this AP.
		 			if ((AddHtInfo.ControlChan > 2)&& (AddHtInfo.AddHtInfo.ExtChanOffset == EXTCHA_BELOW) && (HtCapability.HtCapInfo.ChannelWidth == BW_40))
		 			{
		 				CentralChannel = AddHtInfo.ControlChan - 2;
		 			}
		 			else if ((AddHtInfo.AddHtInfo.ExtChanOffset == EXTCHA_ABOVE) && (HtCapability.HtCapInfo.ChannelWidth == BW_40))
		 			{
		 				CentralChannel = AddHtInfo.ControlChan + 2;
		 			}
		 			DBGPRINT(RT_DEBUG_TRACE, ("PeerBeaconAtJoinAction HT===>Central Channel = %d, Control Channel = %d,  .\n", CentralChannel, AddHtInfo.ControlChan));

				}
				
			}
			else
#endif // DOT11_N_SUPPORT //
			{
				RTMPZeroMemory(&pAd->MlmeAux.HtCapability, SIZE_HT_CAP_IE);
				RTMPZeroMemory(&pAd->MlmeAux.AddHtInfo, SIZE_ADD_HT_INFO_IE);
				pAd->MlmeAux.HtCapabilityLen = 0;
			}
			RTMPUpdateMlmeRate(pAd);

#ifdef DOT11_N_SUPPORT
			// copy QOS related information
			if (pAd->CommonCfg.PhyMode >= PHY_11ABGN_MIXED)
			{
				NdisMoveMemory(&pAd->MlmeAux.APEdcaParm, &EdcaParm, sizeof(EDCA_PARM));
				NdisMoveMemory(&pAd->MlmeAux.APQbssLoad, &QbssLoad, sizeof(QBSS_LOAD_PARM));
				NdisMoveMemory(&pAd->MlmeAux.APQosCapability, &QosCapability, sizeof(QOS_CAPABILITY_PARM));
			}
			else
#endif // DOT11_N_SUPPORT //
			{
				NdisZeroMemory(&pAd->MlmeAux.APEdcaParm, sizeof(EDCA_PARM));
				NdisZeroMemory(&pAd->MlmeAux.APQbssLoad, sizeof(QBSS_LOAD_PARM));
				NdisZeroMemory(&pAd->MlmeAux.APQosCapability, sizeof(QOS_CAPABILITY_PARM));
			}

			DBGPRINT(RT_DEBUG_TRACE, ("APCLI SYNC - after JOIN, SupRateLen=%d, ExtRateLen=%d\n", 
				pAd->MlmeAux.SupRateLen, pAd->MlmeAux.ExtRateLen));

			if (AironetCellPowerLimit != 0xFF)
			{
				//We need to change our TxPower for CCX 2.0 AP Control of Client Transmit Power
				ChangeToCellPowerLimit(pAd, AironetCellPowerLimit);
			}
			else  //Used the default TX Power Percentage.
				pAd->CommonCfg.TxPowerPercentage = pAd->CommonCfg.TxPowerDefault;

			if(bssidEqualFlag == TRUE)
			{
				*pCurrState = APCLI_SYNC_IDLE;

				ApCliCtrlMsg.Status = MLME_SUCCESS;
				MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_PROBE_RSP,
					sizeof(APCLI_CTRL_MSG_STRUCT), &ApCliCtrlMsg, ifIndex);
			}
		}
		// not to me BEACON, ignored
	}
	// sanity check fail, ignore this frame

	return;
}

static VOID ApCliProbeTimeoutAtJoinAction(
	IN PRTMP_ADAPTER pAd,
	IN MLME_QUEUE_ELEM *Elem) 
{
	APCLI_CTRL_MSG_STRUCT ApCliCtrlMsg;
	USHORT ifIndex = (USHORT)(Elem->Priv);
	PULONG pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].SyncCurrState;


	DBGPRINT(RT_DEBUG_TRACE, ("APCLI_SYNC - ProbeTimeoutAtJoinAction\n"));
	*pCurrState = SYNC_IDLE;

	DBGPRINT(RT_DEBUG_TRACE, ("APCLI_SYNC - MlmeAux.Bssid=%02x:%02x:%02x:%02x:%02x:%02x\n",
		pAd->MlmeAux.Bssid[0], pAd->MlmeAux.Bssid[1], pAd->MlmeAux.Bssid[2], pAd->MlmeAux.Bssid[3], pAd->MlmeAux.Bssid[4], pAd->MlmeAux.Bssid[5]));

	if(!MAC_ADDR_EQUAL(pAd->MlmeAux.Bssid, ZERO_MAC_ADDR))
	{
		ApCliCtrlMsg.Status = MLME_SUCCESS;
		MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_PROBE_RSP,
			sizeof(APCLI_CTRL_MSG_STRUCT), &ApCliCtrlMsg, ifIndex);
	} else
	{
		MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_JOIN_REQ_TIMEOUT, 0, NULL, ifIndex);
	}

	return;
}

/* 
    ==========================================================================
    Description:
    ==========================================================================
 */
static VOID ApCliInvalidStateWhenJoin(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem) 
{
	APCLI_CTRL_MSG_STRUCT ApCliCtrlMsg;
	USHORT ifIndex = (USHORT)(Elem->Priv);
	PULONG pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].SyncCurrState;


	ApCliCtrlMsg.Status = MLME_STATE_MACHINE_REJECT;
	MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_PROBE_RSP,
		sizeof(APCLI_CTRL_MSG_STRUCT), &ApCliCtrlMsg, ifIndex);

	DBGPRINT(RT_DEBUG_TRACE, ("APCLI_AYNC - ApCliInvalidStateWhenJoin(state=%ld). Reset SYNC machine\n", *pCurrState));

	return;
}

/* 
	==========================================================================
	Description:
	==========================================================================
 */
static VOID ApCliEnqueueProbeRequest(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR SsidLen,
	OUT PCHAR Ssid,
	IN USHORT ifIndex)
{
	NDIS_STATUS     NState;
	PUCHAR          pOutBuffer;
	ULONG           FrameLen = 0;
	HEADER_802_11   Hdr80211;
	UCHAR           SsidIe    = IE_SSID;
	UCHAR           SupRateIe = IE_SUPP_RATES;
	UCHAR ssidLen;
	CHAR ssid[MAX_LEN_OF_SSID];

	DBGPRINT(RT_DEBUG_TRACE, ("force out a ProbeRequest ...\n"));

	
	NState = MlmeAllocateMemory(pAd, &pOutBuffer);  //Get an unused nonpaged memory
	if(NState != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("EnqueueProbeRequest() allocate memory fail\n"));
		return;
	} else
	{
		if(MAC_ADDR_EQUAL(pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid, ZERO_MAC_ADDR))
			ApCliMgtMacHeaderInit(pAd, &Hdr80211, SUBTYPE_PROBE_REQ, 0,
				BROADCAST_ADDR, BROADCAST_ADDR, ifIndex);
		else
			ApCliMgtMacHeaderInit(pAd, &Hdr80211, SUBTYPE_PROBE_REQ, 0,
				pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid, pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid, ifIndex);

		ssidLen = SsidLen;
		NdisZeroMemory(ssid, MAX_LEN_OF_SSID);
		NdisMoveMemory(ssid, Ssid, ssidLen);

		// this ProbeRequest explicitly specify SSID to reduce unwanted ProbeResponse
		MakeOutgoingFrame(pOutBuffer,		&FrameLen,
			sizeof(HEADER_802_11),			&Hdr80211,
			1,								&SsidIe,
			1,								&ssidLen,
			ssidLen,						ssid,
			1,								&SupRateIe,
			1,								&pAd->MlmeAux.SupRateLen,
			pAd->MlmeAux.SupRateLen,		pAd->MlmeAux.SupRate,
			END_OF_ARGS);

		MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);
		MlmeFreeMemory(pAd, pOutBuffer);
	}

	return;
}

#endif // APCLI_SUPPORT //

