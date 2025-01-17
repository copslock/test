/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.48 $ of : mfd-top.m2c,v $
 *
 * $Id: //BBN_Linux/Branch/Branch_for_Rel_CMCC_7526_20161014/tclinux_phoenix/apps/public/net-snmp-5.3.1/agent/mibgroup/ip-mib/ipv4InterfaceTable/ipv4InterfaceTable.h#1 $
 */
#ifndef IPV4INTERFACETABLE_H
#define IPV4INTERFACETABLE_H

#ifdef __cplusplus
extern          "C" {
#endif


/** @addtogroup misc misc: Miscellaneous routines
 *
 * @{
 */
#include <net-snmp/library/asn1.h>
#include <net-snmp/data_access/interface.h>

#include "if-mib/ifTable/ifTable.h"

    /*
     * other required module components 
     */
    /* *INDENT-OFF*  */
config_require(if-mib/ifTable/ifTable)
config_require(ip-mib/ipv4InterfaceTable/ipv4InterfaceTable_interface)
config_require(ip-mib/ipv4InterfaceTable/ipv4InterfaceTable_data_access)
    /* *INDENT-ON*  */

    /*
     * OID, column number and enum definions for ipv4InterfaceTable 
     */
#include "ipv4InterfaceTable_constants.h"

    /*
     *********************************************************************
     * function declarations
     */
    void            init_ipv4InterfaceTable(void);
    void            shutdown_ipv4InterfaceTable(void);

    /*
     *********************************************************************
     * Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ipv4InterfaceTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * IP-MIB::ipv4InterfaceTable is subid 28 of ip.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.4.28, length: 8
     *
     * we share data structures (data too, in fact) with ifTable
     */
    typedef ifTable_registration ipv4InterfaceTable_registration;
    typedef ifTable_data ipv4InterfaceTable_data;
    typedef ifTable_undo_data ipv4InterfaceTable_undo_data;
    typedef ifTable_mib_index ipv4InterfaceTable_mib_index;
    typedef ifTable_rowreq_ctx ipv4InterfaceTable_rowreq_ctx;

    /*
     * ipv4InterfaceReasmMaxSize(2)/INTEGER32/ASN_INTEGER/long(long)//l/A/w/e/R/d/h
     */
#define ipv4InterfaceReasmMaxSize ifentry->reasm_max

    /*
     * ipv4InterfaceEnableStatus(3)/INTEGER/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h
     */
#define ipv4InterfaceEnableStatus ifentry->admin_status

    /*
     * ipv4InterfaceRetransmitTime(4)/UNSIGNED32/ASN_UNSIGNED/u_long(u_long)//l/A/w/e/r/D/h
     */
#define ipv4InterfaceRetransmitTime ifentry->retransmit_v4


    /*
     *********************************************************************
     * function prototypes
     */
    int
        ipv4InterfaceTable_pre_request(ipv4InterfaceTable_registration *
                                       user_context);
    int
        ipv4InterfaceTable_post_request(ipv4InterfaceTable_registration *
                                        user_context, int rc);

    int
        ipv4InterfaceTable_rowreq_ctx_init(ipv4InterfaceTable_rowreq_ctx *
                                           rowreq_ctx,
                                           void *user_init_ctx);
    void
        ipv4InterfaceTable_rowreq_ctx_cleanup(ipv4InterfaceTable_rowreq_ctx
                                              * rowreq_ctx);

    int             ipv4InterfaceTable_commit(ipv4InterfaceTable_rowreq_ctx
                                              * rowreq_ctx);
        ipv4InterfaceTable_rowreq_ctx
        * ipv4InterfaceTable_row_find_by_mib_index
        (ipv4InterfaceTable_mib_index * mib_idx);

    extern oid      ipv4InterfaceTable_oid[];
    extern int      ipv4InterfaceTable_oid_size;


#include "ipv4InterfaceTable_interface.h"
#include "ipv4InterfaceTable_data_access.h"
    /*
     *********************************************************************
     * GET function declarations
     */

    /*
     *********************************************************************
     * GET Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ipv4InterfaceTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * IP-MIB::ipv4InterfaceTable is subid 28 of ip.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.4.28, length: 8
     */
    /*
     * indexes
     */

    int
        ipv4InterfaceReasmMaxSize_get(ipv4InterfaceTable_rowreq_ctx *
                                      rowreq_ctx, long
                                      *ipv4InterfaceReasmMaxSize_val_ptr);
    int
        ipv4InterfaceEnableStatus_get(ipv4InterfaceTable_rowreq_ctx *
                                      rowreq_ctx,
                                      u_long *
                                      ipv4InterfaceEnableStatus_val_ptr);
    int
        ipv4InterfaceRetransmitTime_get(ipv4InterfaceTable_rowreq_ctx *
                                        rowreq_ctx,
                                        u_long *
                                        ipv4InterfaceRetransmitTime_val_ptr);


    int
        ipv4InterfaceTable_indexes_set_tbl_idx(ipv4InterfaceTable_mib_index
                                               * tbl_idx, long
                                               ipv4InterfaceIfIndex_val);
    int
        ipv4InterfaceTable_indexes_set(ipv4InterfaceTable_rowreq_ctx *
                                       rowreq_ctx,
                                       long ipv4InterfaceIfIndex_val);



    /*
     *********************************************************************
     * SET function declarations
     */

    /*
     *********************************************************************
     * SET Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ipv4InterfaceTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * IP-MIB::ipv4InterfaceTable is subid 28 of ip.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.4.28, length: 8
     */


    int
        ipv4InterfaceTable_undo_setup(ipv4InterfaceTable_rowreq_ctx *
                                      rowreq_ctx);
    int
        ipv4InterfaceTable_undo_cleanup(ipv4InterfaceTable_rowreq_ctx *
                                        rowreq_ctx);
    int             ipv4InterfaceTable_undo(ipv4InterfaceTable_rowreq_ctx *
                                            rowreq_ctx);
    int             ipv4InterfaceTable_commit(ipv4InterfaceTable_rowreq_ctx
                                              * rowreq_ctx);
    int
        ipv4InterfaceTable_undo_commit(ipv4InterfaceTable_rowreq_ctx *
                                       rowreq_ctx);


    int
        ipv4InterfaceReasmMaxSize_check_value(ipv4InterfaceTable_rowreq_ctx
                                              * rowreq_ctx, long
                                              ipv4InterfaceReasmMaxSize_val);
    int
        ipv4InterfaceReasmMaxSize_undo_setup(ipv4InterfaceTable_rowreq_ctx
                                             * rowreq_ctx);
    int
        ipv4InterfaceReasmMaxSize_set(ipv4InterfaceTable_rowreq_ctx *
                                      rowreq_ctx,
                                      long ipv4InterfaceReasmMaxSize_val);
    int
        ipv4InterfaceReasmMaxSize_undo(ipv4InterfaceTable_rowreq_ctx *
                                       rowreq_ctx);

    int
        ipv4InterfaceEnableStatus_check_value(ipv4InterfaceTable_rowreq_ctx
                                              * rowreq_ctx,
                                              u_long
                                              ipv4InterfaceEnableStatus_val);
    int
        ipv4InterfaceEnableStatus_undo_setup(ipv4InterfaceTable_rowreq_ctx
                                             * rowreq_ctx);
    int
        ipv4InterfaceEnableStatus_set(ipv4InterfaceTable_rowreq_ctx *
                                      rowreq_ctx,
                                      u_long
                                      ipv4InterfaceEnableStatus_val);
    int
        ipv4InterfaceEnableStatus_undo(ipv4InterfaceTable_rowreq_ctx *
                                       rowreq_ctx);

    int
        ipv4InterfaceRetransmitTime_check_value
        (ipv4InterfaceTable_rowreq_ctx * rowreq_ctx,
         u_long ipv4InterfaceRetransmitTime_val);
    int
        ipv4InterfaceRetransmitTime_undo_setup
        (ipv4InterfaceTable_rowreq_ctx * rowreq_ctx);
    int
        ipv4InterfaceRetransmitTime_set(ipv4InterfaceTable_rowreq_ctx *
                                        rowreq_ctx,
                                        u_long
                                        ipv4InterfaceRetransmitTime_val);
    int
        ipv4InterfaceRetransmitTime_undo(ipv4InterfaceTable_rowreq_ctx *
                                         rowreq_ctx);


    int
        ipv4InterfaceTable_check_dependencies(ipv4InterfaceTable_rowreq_ctx
                                              * ctx);


    /*
     * DUMMY markers, ignore
     *
     * TODO:099:x: *************************************************************
     * TODO:199:x: *************************************************************
     * TODO:299:x: *************************************************************
     * TODO:399:x: *************************************************************
     * TODO:499:x: *************************************************************
     */

#ifdef __cplusplus
}
#endif
#endif                          /* IPV4INTERFACETABLE_H */
/**  @} */

