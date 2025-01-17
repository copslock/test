/*
 * ATM connection 
 *
 * $Id: //BBN_Linux/Branch/Branch_for_Rel_CMCC_7526_20161014/tclinux_phoenix/apps/public/linux-atm/lane/atm.h#1 $
 *
 */
#ifndef ATM_H
#define ATM_H

/* System includes needed for types */
#include <sys/types.h>
 
/* Local includes needed for types */
#include "units.h"
#include "lane.h" 
#include "connect.h"

/* Type definitions */

/* Codepoints */
#define CONFIGURATION_DIRECT    0x01
#define CONTROL_DIRECT          0x01
#define CONTROL_DISTRIBUTE      0x01
#define DATA_DIRECT_802_3       0x02
#define DATA_DIRECT_802_5       0x03
#define MULTICAST_SEND_802_3    0x04
#define MULTICAST_FORWARD_802_3 0x04
#define MULTICAST_SEND_802_5    0x05
#define MULTICAST_FORWARD_802_5 0x05

/* Global function prototypes */
int atm_create_socket(unsigned char codepoint, const AtmAddr_t *our_addr);
int atm_connect_back(const AtmAddr_t *our_addr, const Conn_t *conn,
		     unsigned char codepoint);

/* Global data */
extern const Unit_t atm_unit;

#endif

