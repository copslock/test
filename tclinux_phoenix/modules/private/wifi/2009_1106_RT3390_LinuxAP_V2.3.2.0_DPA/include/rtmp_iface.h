/****************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ****************************************************************************

    Module Name:
	rt_iface.h

    Abstract:

    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------
 */

#ifndef __RTMP_IFACE_H__
#define __RTMP_IFACE_H__


#ifdef RTMP_PCI_SUPPORT
#include "iface/rtmp_pci.h"
#endif // RTMP_PCI_SUPPORT //




typedef struct _INF_PCI_CONFIG_
{
	unsigned long	CSRBaseAddress;     // PCI MMIO Base Address, all access will use
	unsigned int	irq_num;
}INF_PCI_CONFIG;


typedef struct _INF_USB_CONFIG_
{
	UINT8                BulkInEpAddr;		// bulk-in endpoint address
	UINT8                BulkOutEpAddr[6];	// bulk-out endpoint address
}INF_USB_CONFIG;


typedef struct _INF_RBUS_CONFIG_
{
	unsigned long		csr_addr;
	unsigned int		irq;
}INF_RBUS_CONFIG;


typedef enum _RTMP_INF_TYPE_
{	
	RTMP_DEV_INF_UNKNOWN = 0,
	RTMP_DEV_INF_PCI = 1,
	RTMP_DEV_INF_USB = 2,
	RTMP_DEV_INF_RBUS = 4,
	RTMP_DEV_INF_PCIE = 5,
}RTMP_INF_TYPE;


typedef union _RTMP_INF_CONFIG_{
	struct _INF_PCI_CONFIG_ 		pciConfig;
	struct _INF_USB_CONFIG_ 		usbConfig;
	struct _INF_RBUS_CONFIG_		rbusConfig;
}RTMP_INF_CONFIG;

#endif // __RTMP_IFACE_H__ //
