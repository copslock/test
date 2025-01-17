/*
** Copyright (c) 2007-2016 by Silicon Laboratories
**
** $Id: proslic.h 5485 2016-01-19 00:47:25Z nizajerk $
**
** Distributed by:
** Silicon Laboratories, Inc
**
** This file contains proprietary information.
** No dissemination allowed without prior written permission from
** Silicon Laboratories, Inc.
**
** File Description:
** This is the header file for the ProSLIC driver.
**
*/

#ifndef PROSLIC_H
#define PROSLIC_H

/*include all the required headers*/
#include "proslic_api_config.h"
#include "si_voice_datatypes.h"
#include "si_voice_ctrl.h"
#include "si_voice_timer_intf.h"
#include "si_voice.h"

#define SILABS_UNREFERENCED_PARAMETER(param) (void)param

/* UNSORTED ADDITIONS - These common parameters have been moved from
   the drivers to here to support simultaneous compile of multiple devices
   */
/* Patch Parameters */
#define PATCH_NUM_LOW_ENTRIES       8
#define PATCH_NUM_HIGH_ENTRIES      8
#define PATCH_MAX_SUPPORT_RAM       128
#define PATCH_MAX_SIZE              1024

#define PROSLIC_RAM_RAM_MADC_VBAT   3
#define PROSLIC_RAM_PATCHID         448
#define PROSLIC_RAM_VERIFY_IO       449
#define PROSLIC_RAM_PD_DCDC         1538
#define PROSLIC_RAM_PRAM_ADDR       1358
#define PROSLIC_RAM_PRAM_DATA       1359
#define PATCH_JMPTBL_HIGH_ADDR      1597

/* Common register values for 17x, 26x, 18x & 28x */
#define PROSLIC_REG_ID              0
#define PROSLIC_REG_RESET           1
#define PROSLIC_REG_MSTRSTAT        3
#define PROSLIC_REG_RAM_ADDR_HI     5
#define PROSLIC_REG_PCMMODE         11
#define PROSLIC_REG_PCMTXLO         12
#define PROSLIC_REG_PCMTXHI         13
#define PROSLIC_REG_PCMRXLO         14
#define PROSLIC_REG_PCMRXHI         15
#define PROSLIC_REG_IRQEN1          22
#define PROSLIC_REG_IRQEN4          25
#define PROSLIC_REG_CALR0           26
#define PROSLIC_REG_CALR3           29
#define PROSLIC_REG_IRQ             16
#define PROSLIC_REG_IRQ0            17
#define PROSLIC_REG_IRQ1            18
#define PROSLIC_REG_IRQ4            21
#define PROSLIC_REG_LINEFEED        30
#define PROSLIC_REG_POLREV          31
#define PROSLIC_REG_LCRRTP          34
#define PROSLIC_REG_RINGCON         38
#define PROSLIC_REG_RINGTALO        39
#define PROSLIC_REG_RINGTAHI        40
#define PROSLIC_REG_RINGTILO        41
#define PROSLIC_REG_RINGTIHI        42
#define PROSLIC_REG_LOOPBACK        43
#define PROSLIC_REG_DIGCON          44
#define PROSLIC_REG_ZCAL_EN         46
#define PROSLIC_REG_ENHANCE         47
#define PROSLIC_REG_OMODE           48
#define PROSLIC_REG_OCON            49
#define PROSLIC_REG_O1TALO          50
#define PROSLIC_REG_O1TAHI          51
#define PROSLIC_REG_O1TILO          52
#define PROSLIC_REG_O1TIHI          53
#define PROSLIC_REG_O2TALO          54
#define PROSLIC_REG_O2TAHI          55
#define PROSLIC_REG_O2TILO          56
#define PROSLIC_REG_O2TIHI          57
#define PROSLIC_REG_FSKDAT          58
#define PROSLIC_REG_FSKDEPTH        59
#define PROSLIC_REG_TONDTMF         60
#define PROSLIC_REG_USERSTAT        66
#define PROSLIC_REG_GPIO            67
#define PROSLIC_REG_PMCON           75
#define PROSLIC_REG_AUTORD          80
#define PROSLIC_REG_JMPEN           81
#define PATCH_JMPTBL_START_ADDR     82
#define PATCH_JMPTBL_LOW_ADDR       82
#define PROSLIC_REG_USERMODE_ENABLE 126

/* Common RAM locations for most ProSLICs */
#define PROSLIC_RAM_OSC1FREQ        26
#define PROSLIC_RAM_OSC1AMP         27
#define PROSLIC_RAM_OSC1PHAS        28
#define PROSLIC_RAM_OSC2FREQ        29
#define PROSLIC_RAM_OSC2AMP         30
#define PROSLIC_RAM_OSC2PHAS        31
#define PROSLIC_RAM_FSKFREQ0        834
#define PROSLIC_RAM_FSKFREQ1        835
#define PROSLIC_RAM_FSKAMP0         836
#define PROSLIC_RAM_FSKAMP1         837
#define PROSLIC_RAM_FSK01           838
#define PROSLIC_RAM_FSK10           839
#define PROSLIC_RAM_CMDAC_FWD       1476
#define PROSLIC_RAM_CMDAC_REV       1477
#define PROSLIC_RAM_CAL_TRNRD_DACT  1458
#define PROSLIC_RAM_CAL_TRNRD_DACR  1459
#define PROSLIC_RAM_RDC_SUM         1499
#define PROSLIC_RAM_DCDC_STATUS     1551

#define PROSLIC_CHAN_BROADCAST      0xFF

/* BOM Constants */
#define BOM_KAUDIO_PM               0x8000000L
#define BOM_KAUDIO_NO_PM            0x3A2E8BAL
#define BOM_AC_ADC_GAIN_PM          0x151EB80L
#define BOM_AC_ADC_GAIN_NO_PM       0x99999AL
#define FIXRL_VDC_SCALE             0xAE924B9L  /** vdc sense scale when using fixed-rail */

/* Generic Constants */
#define COMP_5V                     0x51EB82L
#define VBATL_13V                   0xF00000L
#define COMP_10V                    0xA3D705L
#define ZCAL_V_RASUM_IDEAL_VAL      0x8F00000L
#define ZCAL_DC_DAC_OS_VAL          0x1FFE0000L

/* MADC Constants */
#define SCALE_V_MADC                1074      /* 1/(1000*931.32e-9)  mV */
#define SCALE_I_MADC                597       /* 1/(1e6*1.676e-9)    uA */
#define SCALE_P_MADC				2386	  /* 1/(1e3*419.095e-9)  mW */

/* Calibration Constants */
#define CAL_LB_CMDAC                0x0C
#define CAL_LB_TRNRD                0x03
#define CAL_LB_ALL                  0x0F
#define TIMEOUT_MADC_CAL            100
#define TIMEOUT_GEN_CAL             300
#define TIMEOUT_LB_CAL              2410

/* MWI Constants */
#define SIL_MWI_USTAT_SET           0x04
#define SIL_MWI_USTAT_CLEAR         0xFB
#define SIL_MWI_TOGGLE_HIGH         0x0F
#define SIL_MWI_TOGGLE_LOW          0x00
#define SIL_MWI_VPK_MAX             110
#define SIL_MWI_VPK_MIN             80
#define SIL_MWI_LCRMASK_MAX         2000
#define SIL_MWI_LCRMASK_MIN         5
#define SIL_MWI_LCRMASK_SCALE       65536
#define SIL_MWI_FLASH_OFF           0
#define SIL_MWI_FLASH_ON            1

/* Depricated functions now mapped directly to SiVoice versions... */

#define ProSLIC_clearErrorFlag                   SiVoice_clearErrorFlag
#define ProSLIC_createChannel                    SiVoice_createChannel
#define ProSLIC_createControlInterface           SiVoice_createControlInterface
#define ProSLIC_createDevice                     SiVoice_createDevice
#define ProSLIC_destroyChannel                   SiVoice_destroyChannel
#define ProSLIC_destroyControlInterface          SiVoice_destroyControlInterface
#define ProSLIC_destroyDevice                    SiVoice_destroyDevice
#define ProSLIC_getChannelEnable                 SiVoice_getChannelEnable
#define ProSLIC_getErrorFlag                     SiVoice_getErrorFlag
#define ProSLIC_Reset                            SiVoice_Reset
#define ProSLIC_setChannelEnable                 SiVoice_setChannelEnable
#define ProSLIC_setControlInterfaceCtrlObj       SiVoice_setControlInterfaceCtrlObj
#define ProSLIC_setControlInterfaceDelay         SiVoice_setControlInterfaceDelay
#define ProSLIC_setControlInterfaceGetTime       SiVoice_setControlInterfaceGetTime
#define ProSLIC_setControlInterfaceReadRAM       SiVoice_setControlInterfaceReadRAM
#define ProSLIC_setControlInterfaceReadRegister  SiVoice_setControlInterfaceReadRegister
#define ProSLIC_setControlInterfaceReset         SiVoice_setControlInterfaceReset
#define ProSLIC_setControlInterfaceSemaphore     SiVoice_setControlInterfaceSemaphore
#define ProSLIC_setControlInterfaceTimeElapsed   SiVoice_setControlInterfaceTimeElapsed
#define ProSLIC_setControlInterfaceTimerObj      SiVoice_setControlInterfaceTimerObj
#define ProSLIC_setControlInterfaceWriteRAM      SiVoice_setControlInterfaceWriteRAM
#define ProSLIC_setControlInterfaceWriteRegister SiVoice_setControlInterfaceWriteRegister
#define ProSLIC_setSWDebugMode                   SiVoice_setSWDebugMode
#define ProSLIC_SWInitChan                       SiVoice_SWInitChan
#define ProSLIC_Version                          SiVoice_Version
#define ProSLIC_ReadReg                          SiVoice_ReadReg
#define ProSLIC_WriteReg                         SiVoice_WriteReg
#define ProSLIC_ShutdownChannel                  ProSLIC_PowerDownConverter
#define SI_MAX_INTERRUPTS 4

#define PROSLIC_EXTENDED_GAIN_MAX 9
#define PROSLIC_GAIN_MAX 6
#define PROSLIC_GAIN_MIN -30
/*
** Initialization Sequence Location - Used by 18x & 17x
*/
typedef enum
{
  INIT_SEQ_BEGINNING,
  INIT_SEQ_READ_ID,
  INIT_SEQ_PRE_PATCH_LOAD,
  INIT_SEQ_POST_PATCH_LOAD,
  INIT_SEQ_PRE_CAL,
  INIT_SEQ_POST_CAL,
  INIT_SEQ_END
} initSeqType;

/** @mainpage
 * This document is a supplement to the ProSLIC API Specification.  It has most
 * of the APIs documented and hyperlinked.
 *
 * This document has the following tabs:
 *
 * - Main Page (this page) - introduction to the document.
 * - Related pages - mainly the deprecated list is located here.
 *  Although these identifiers are present in the current release, they are
 *  targeted for deletion in a future release.  Any existing customer code
 *  using deprecated identifiers should be modified as indicated.
 * - Modules - this is the meat of the document - this has each functional group in outline format listed here.
 * - Data Structures - This has every data structure listed in in the ProSLIC API in alphabetical order.
 * - Files - this has the source files in hyperlink format.  @note In some cases the hyperlink generator will not properly
 *  generate the correct reference or not be able to find it.  In this case please use an alternative method.
 *
 */

/** @defgroup PROSLIC_TYPES ProSLIC General Datatypes/Function Definitions
 * This section documents functions and data structures related to the
 * ProSLIC/FXS chipsets.
 * @{
 */

/*
* ----------------ProSLIC Generic DataTypes/Function Definitions----
**********************************************************************
*/

#define MAX_PROSLIC_IRQS 32 /**< How many interrupts are supported in the ProSLIC */

#ifdef ENABLE_DEBUG
#define PROSLIC_PRINT_ERROR(CHAN, ERROR)\
  LOGPRINT("%sError encountered on channel: %d fault code: %d\n",\
    LOGPRINT_PREFIX, (CHAN)->channel, (ERROR))
#else
#define PROSLIC_PRINT_ERROR(CHAN, ERROR)
#endif

/**********************************************************************/
/**
* Map Proslic types to SiVoice types
*/
typedef SiVoiceControlInterfaceType
controlInterfaceType; /**< Map ProSLIC to SiVoice type */
typedef SiVoiceControlInterfaceType
proslicControlInterfaceType; /**< Map ProSLIC to SiVoice type */
typedef SiVoiceDeviceType ProslicDeviceType; /**< Map ProSLIC to SiVoice type */
typedef SiVoiceChanType proslicChanType; /**< Map ProSLIC to SiVoice type */

/**
* Define channel and device type pointers
*/
typedef ProslicDeviceType
*proslicDeviceType_ptr; /**< Shortcut for pointer to a ProSLIC device type */
typedef proslicChanType
*proslicChanType_ptr; /**< Shortcut for pointer to a ProSLIC channel type */

/** @} PROSLIC_TYPES */

/** @addtogroup HC_DETECT
 * @{
 */

/**
* This is structure used to store pulse dial information
*/
#define SI_HC_NO_ACTIVITY     0x10
#define SI_HC_NEED_MORE_POLLS 0x20
#define SI_HC_ONHOOK_TIMEOUT  0x41
#define SI_HC_OFFHOOK_TIMEOUT 0x42
#define SI_HC_HOOKFLASH       0x43

#define SI_HC_NONDIGIT_DONE(X) ((X) & 0x40)
#define SI_HC_DIGIT_DONE(X)    ((X) && ((X) < 11))

typedef struct
{
  uInt8 currentPulseDigit;
  uInt8 last_hook_state;
  uInt8 lookingForTimeout;
  uInt8 last_state_reported;
  void *hookTime; /**< Timestamp for when the onhook detection occurred */
} hookChangeType;

/**
* Defines structure for configuring hook change detection.  Times are in mSec.
*/
typedef struct
{
  uInt16 minOnHook; /**< Min mSec for onhook/break time  */
  uInt16 maxOnHook; /**< Max mSec for onhook/break time  */
  uInt16 minOffHook; /**< Min mSec for offhook/make time */
  uInt16 maxOffHook; /**< Max mSec for offhook/make time */
  uInt16 minInterDigit; /**< Minimum interdigit time */
  uInt16 minHookFlash; /**< minimum hook flash time */
  uInt16 maxHookFlash; /**< maximum hook flash time */
  uInt16 minHook; /**< Minimum hook time, which should be >> than maxHookFlash */
} hookChange_Cfg;
/** @} HC_DETECT*/


/** @addtogroup PROSLIC_INTERRUPTS
 * @{
 */
/**
* Interrupt tags
*/

typedef enum
{
  IRQ_OSC1_T1,
  IRQ_OSC1_T2,
  IRQ_OSC2_T1,
  IRQ_OSC2_T2,
  IRQ_RING_T1,
  IRQ_RING_T2,
  IRQ_PM_T1,
  IRQ_PM_T2,
  IRQ_FSKBUF_AVAIL, /**< FSK FIFO depth reached */
  IRQ_VBAT,
  IRQ_RING_TRIP, /**< Ring Trip detected */
  IRQ_LOOP_STATUS,  /**< Loop Current changed */
  IRQ_LONG_STAT,
  IRQ_VOC_TRACK,
  IRQ_DTMF,         /**< DTMF Detected - call @ref ProSLIC_DTMFReadDigit to decode the value */
  IRQ_INDIRECT,     /**< Indirect/RAM access completed */
  IRQ_TXMDM,
  IRQ_RXMDM,
  IRQ_PQ1,          /**< Power alarm 1 */
  IRQ_PQ2,          /**< Power alarm 2 */
  IRQ_PQ3,          /**< Power alarm 3 */
  IRQ_PQ4,          /**< Power alarm 4 */
  IRQ_PQ5,          /**< Power alarm 5 */
  IRQ_PQ6,          /**< Power alarm 6 */
  IRQ_RING_FAIL,
  IRQ_CM_BAL,
  IRQ_USER_0,
  IRQ_USER_1,
  IRQ_USER_2,
  IRQ_USER_3,
  IRQ_USER_4,
  IRQ_USER_5,
  IRQ_USER_6,
  IRQ_USER_7,
  IRQ_DSP,
  IRQ_MADC_FS,
  IRQ_P_HVIC,
  IRQ_P_THERM, /**< Thermal alarm */
  IRQ_P_OFFLD
} ProslicInt;

/**
* Defines structure of interrupt data - used by @ref ProSLIC_GetInterrupts
*/
typedef struct
{
  ProslicInt
  *irqs; /**< Pointer of an array of size MAX_PROSLIC_IRQS (this is to be allocated by the caller) */
  uInt8 number; /**< Number of IRQs detected/pending */
} proslicIntType;


/** @} PROSLIC_INTERRUPTS */

/** @addtogroup TONE_GEN
 * @{
 */
/**
* Defines structure for configuring 1 oscillator - see your data sheet for specifics or use the configuration
* tool to have this filled in for you.
*/
typedef struct
{
  ramData freq;
  ramData amp;
  ramData phas;
  uInt8 talo;
  uInt8 tahi;
  uInt8 tilo;
  uInt8 tihi;
} Oscillator_Cfg;

/**
 * Defines structure for tone configuration.
 */
typedef struct
{
  Oscillator_Cfg osc1;
  Oscillator_Cfg osc2;
  uInt8 omode;
} ProSLIC_Tone_Cfg;

typedef struct
{
  ramData fsk[2];
  ramData fskamp[2];
  ramData fskfreq[2];
  uInt8 eightBit;
  uInt8 fskdepth;
} ProSLIC_FSK_Cfg;
/** @} TONE_GEN */

/*****************************************************************************/
/** @addtogroup SIGNALING
 * @{
 */
/**
* Hook states - returned by @ref ProSLIC_ReadHookStatus()
*/
enum
{
  PROSLIC_ONHOOK, /**< Hook state is onhook */
  PROSLIC_OFFHOOK /**< Hook state is offhook */
};

//PROSLIC_PORTING   #ifndef SIVOICE_CFG_NEWTYPES_ONLY
enum
{
  ONHOOK = PROSLIC_ONHOOK, /**< @deprecated- Please use PROSLIC_ONHOOK and PROSLIC_OFFHOOK for future code development */
  OFFHOOK = PROSLIC_OFFHOOK
};
//PROSLIC_PORTING   #endif

/** @} SIGNALING */

/*****************************************************************************/
/** @addtogroup PCM_CONTROL
 * @{
* Loopback modes
*/
typedef enum
{
  PROSLIC_LOOPBACK_NONE, /**< Loopback disabled */
  PROSLIC_LOOPBACK_DIG,  /**< Loopback is toward the PCM side */
  PROSLIC_LOOPBACK_ANA   /**< Loopback is toward the analog side */
} ProslicLoopbackModes;

/**
* Mute options - which direction to mute
*/
typedef enum
{
  PROSLIC_MUTE_NONE = 0,  /**< Don't mute */
  PROSLIC_MUTE_RX = 0x1,  /**< Mute toward the RX side */
  PROSLIC_MUTE_TX = 0x2,  /**< Mute toward the TX side */
  PROSLIC_MUTE_ALL = 0x3  /**< Mute both directions */
} ProslicMuteModes;

/** @} PCM_CONTROL */

/*****************************************************************************/
/** @addtogroup GAIN_CONTROL
 * @{
* Path Selector
*/
enum
{
  TXACGAIN_SEL = 0,
  RXACGAIN_SEL = 1
};


/*
** Defines structure for configuring audio gain on the fly
*/
typedef struct
{
  ramData acgain;
  uInt8 mute;
  ramData aceq_c0;
  ramData aceq_c1;
  ramData aceq_c2;
  ramData aceq_c3;
} ProSLIC_audioGain_Cfg;

/** @} GAIN_CONTROL */

/*****************************************************************************/
/** @addtogroup LINESTATUS
 * @{
 */
/**
* enumeration of the Proslic polarity reversal states - used by ProSLIC_PolRev API
*/
enum
{
  POLREV_STOP, /**< Stop Polarity reversal */
  POLREV_START, /**< Start Polarity reversal */
  WINK_START, /**< Start Wink */
  WINK_STOP /**< Stop Wink */
};

/**
* Defines initialization data structures
* Linefeed states - used in @ref ProSLIC_SetLinefeedStatus and @ref ProSLIC_SetLinefeedStatusBroadcast
*/
enum
{
  LF_OPEN,          /**< Open circuit */
  LF_FWD_ACTIVE,    /**< Forward active */
  LF_FWD_OHT,       /**< Forward active, onhook transmission (used for CID/VMWI) */
  LF_TIP_OPEN,      /**< Tip open */
  LF_RINGING,       /**< Ringing */
  LF_REV_ACTIVE,    /**< Reverse battery/polarity reversed, active */
  LF_REV_OHT,       /**< Reverse battery/polarity reversed, active, onhook transmission (used for CID/VMWI) */
  LF_RING_OPEN      /**< Ring open */
} ;
/** @} LINESTATUS */




/*****************************************************************************/
/** @addtogroup GEN_CFG
 * @{
 */

/**
* Defines initialization data structures
*/
typedef struct
{
  uInt8 address;
  uInt8 initValue;
} ProslicRegInit;

typedef struct
{
  uInt16 address;
  ramData initValue;
} ProslicRAMInit;

//PROSLIC_PORTING
typedef struct {
	int32 amplitudeSlab;
	int32 profileID;
} ProfileRing;/* added by mtk08176_20150627  */

typedef struct {
	int32 ilaSlab;
	int32 profileID;
} ProfileDCFeed;/* added by mtk08176_20150627  */


/**
* ProSLIC patch object
*/
typedef struct
{
  const ramData *patchData; /**< 1024 max*/
  const uInt16 *patchEntries; /**< 8 max */
  const uInt32 patchSerial;
  const uInt16 *psRamAddr;  /**< 128 max */
  const ramData *psRamData; /**< 128 max */
} proslicPatch;

/** @} GEN_CFG */


/*****************************************************************************/
/** @addtogroup RING_CONTROL
 * @{
 */
/**
* Ringing type options
* Ringing type options - Trapezoidal w/ a Crest factor CF11= Crest factor 1.1 or sinusoidal.
*/
typedef enum
{
  ProSLIC_RING_TRAP_CF11,
  ProSLIC_RING_TRAP_CF12,
  ProSLIC_RING_TRAP_CF13,
  ProSLIC_RING_TRAP_CF14,
  ProSLIC_RING_TRAP_CF15,
  ProSLIC_RING_TRAP_CF16,
  ProSLIC_RING_SINE /***< Plain old sinusoidal ringing */
} ProSLIC_RINGTYPE_T;

/**
* Ringing (provisioned) object
*/
typedef struct
{
  ProSLIC_RINGTYPE_T
  ringtype;  /**< Is this a sinusoid or a trapezoidal ring shape? */
  uInt8 freq;                   /**< In terms of Hz */
  uInt8 amp;                    /**< in terms of 1 volt units */
  uInt8 offset;                 /**< In terms of 1 volt units */
} ProSLIC_dbgRingCfg;


/** @} RING_CONTROL */

/*****************************************************************************/
/**
* Line Monitor - returned by @ref ProSLIC_LineMonitor
*/
typedef struct
{
  int32  vtr;		/**< Voltage, tip-ring in mV */
  int32  vtip;	/**< Voltage, tip-ground in mV */
  int32  vring;	/**< Voltage, ring-ground in mV */
  int32  vbat;	/**< Voltage, battery in mV */
  int32  vdc;		/**< Voltage, Vdc in mV */
  int32  vlong;	/**< Voltage, longitudinal in mV */
  int32  itr;		/**< Loop current, in uA tip-ring */
  int32  itip;	/**< Loop current, in uA tip */
  int32  iring;	/**< Loop current, in uA ring */
  int32  ilong;	/**< Loop current, in uA longitudinal */
  int32  p_hvic;  /**< On-chip Power Calculation in mw */
} proslicMonitorType;

/*****************************************************************************/
/** @addtogroup PROSLIC_DCFEED
 * @{
 */
/**
* Powersave
*/
enum
{
  PWRSAVE_DISABLE = 0, /**< Disable power savings mode */
  PWRSAVE_ENABLE  = 1   /**< Enable power savings mode */
};

/**
** DC Feed Preset
*/
typedef struct
{
  ramData slope_vlim;
  ramData slope_rfeed;
  ramData slope_ilim;
  ramData delta1;
  ramData delta2;
  ramData v_vlim;
  ramData v_rfeed;
  ramData v_ilim;
  ramData const_rfeed;
  ramData const_ilim;
  ramData i_vlim;
  ramData lcronhk;
  ramData lcroffhk;
  ramData lcrdbi;
  ramData longhith;
  ramData longloth;
  ramData longdbi;
  ramData lcrmask;
  ramData lcrmask_polrev;
  ramData lcrmask_state;
  ramData lcrmask_linecap;
  ramData vcm_oh;
  ramData vov_bat;
  ramData vov_gnd;
} ProSLIC_DCfeed_Cfg;

/** @} PROSLIC_DCFEED */

/*****************************************************************************/
/** @defgroup ProSLIC_API ProSLIC API
* proslic.c function declarations
* @{
*/

/*****************************************************************************/
/** @defgroup DIAGNOSTICS Diagnostics
 * The functions in this group allow one to monitor the line state for abnormal
 * situations.
 * @{
 */

/**
* Test State - used in polled tests (such as PSTN Check)
*/
typedef struct
{
  int32 stage;               /**< What state is the test in */
  int32 waitIterations;      /**< How many iterations to stay in a particular state */
  int32 sampleIterations;    /**< How many  samples have been collected */
} proslicTestStateType;

/**
 * @brief
 *  This function allows one to monitor the instantaneous voltage and
 *  loop current values seen on tip/ring.
 *
 *  @param[in] pProslic - which channel should the data be collected from
 *  @param[in,out] *monitor -  the data collected
 *  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_LineMonitor(proslicChanType_ptr pProslic,
                        proslicMonitorType *monitor);

/**
 * @brief
 *  This function reads the MADC a scaled value
 *
 *  @param[in] pProslic - which channel should the data be collected from
 *  @param[in] addr  - address to read from (MADC_ILOOP, MADC_ITIP, etc).
 *  @param[in] scale  - scale to use (0 = determine based upon MADC address)
 *  @retval int32 - scaled value requested or -1 if not supported.
 *
 */

int32 ProSLIC_ReadMADCScaled(proslicChanType_ptr pProslic, uInt16 addr,
                             int32 scale);

/** @defgroup PSTN_CHECK PSTN Check
 * Monitor for excessive longitudinal current, which
 * would be present if a live pstn line was connected
 * to the port.  To operate these sets of functions:
 *
 * - Iniitalize the PSTN object by calling @ref ProSLIC_InitPSTNCheckObj
 * - Poll at a constant rate and call @ref ProSLIC_PSTNCheck.  Check the return code of this function.
 *
 * Alternatively, you can call the DiffPSTNCheck versions of the above two functions.
 *
 * @note These functions may be disabled by doing a undef of @ref PSTN_DET_ENABLE in the configuration file.
 * @{
*/
#define MAX_ILONG_SAMPLES 32 /**< How many samples to collect for PSTN check */
#define MAX_PSTN_SAMPLES 16 /**< Used in the PSTN check status code to indicate the number of samples to collect */

/**
* FEMF OPEN voltage test enable
*/
enum
{
  FEMF_MEAS_DISABLE, /**< Do not measure FEMF as part of PSTN Check */
  FEMF_MEAS_ENABLE   /**< Do measure FEMF as part of PSTN Check */
};

/** Standard line interfaces */
typedef struct
{
  int32   avgThresh;
  int32   singleThresh;
  int32   ilong[MAX_ILONG_SAMPLES];
  uInt8   count;
  uInt8   samples;
  int32   avgIlong;
  BOOLEAN buffFull;
} proslicPSTNCheckObjType;

typedef proslicPSTNCheckObjType *proslicPSTNCheckObjType_ptr;


/** Re-Injection line interfaces (differential) */
typedef struct
{
  proslicTestStateType pState;
  int dcfPreset1;
  int dcfPreset2;
  int entryDCFeedPreset;
  uInt8 lfstate_entry;
  uInt8 enhanceRegSave;
  uInt8 samples;
  int32 vdiff1[MAX_PSTN_SAMPLES];
  int32 vdiff2[MAX_PSTN_SAMPLES];
  int32 iloop1[MAX_PSTN_SAMPLES];
  int32 iloop2[MAX_PSTN_SAMPLES];
  int32 vdiff1_avg;
  int32 vdiff2_avg;
  int32 iloop1_avg;
  int32 iloop2_avg;
  int32 rl1;
  int32 rl2;
  int32 rl_ratio;
  int femf_enable;
  int32 vdiff_open;
  int32 max_femf_vopen;
  int return_status;
} proslicDiffPSTNCheckObjType;

typedef proslicDiffPSTNCheckObjType *proslicDiffPSTNCheckObjType_ptr;

/** @}PSTN_CHECK */
/** @}DIAGNOSTICS */
/*****************************************************************************/
/*
** proslic.c function declarations
*/

/*****************************************************************************/
/** @defgroup GEN_CFG General configuration
 * @{
 */

/**
 * @brief
 *  Loads patch and initializes all ProSLIC devices. Performs all calibrations except
 *  longitudinal balance.
 *
 * @param[in] hProslic - which channel(s) to initialize, if size > 1, then the start of the array
 * of channels to be initialized.
 * @param[in] size - the number of channels to initialize.
 * @param[in] preset - general configuration preset to apply
 *
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_Init
 */

int ProSLIC_Init_MultiBOM (proslicChanType_ptr *hProslic, int size, int preset);

/**
 * @brief
 *  Loads patch and initializes all ProSLIC devices. Performs all calibrations except
 *  longitudinal balance.
 *
 * @param[in] hProslic - which channel(s) to initialize, if size > 1, then the start of the array
 * of channels to be initialized.
 * @param[in] size - the number of channels to initialize.
 *
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_Init (proslicChanType_ptr *hProslic, int size);

/**
 * @brief
 *  Loads patch and initializes all ProSLIC devices. NOTE: not all chipsets support this API.
 *
 * @param[in] hProslic - which channel(s) to initialize, if size > 1, then the start of the array
 * of channels to be initialized.
 * @param[in] size - the number of channels to initialize.
 * @param[in] option - see initOptionsType
 *
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_Init_with_Options (proslicChanType_ptr *hProslic, int size,
                               int option);

/**
 * @brief
 *  Performs soft reset then calls ProSLIC_Init()
 *
 * @param[in] hProslic - which channel(s) to initialize, if size > 1, then the start of the array
 * of channels to be initialized.
 * @param[in] size - the number of channels to initialize.
 *
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_Reinit (proslicChanType_ptr *hProslic, int size);

/**
 * @brief
 * Loads registers and RAM in the ProSLICs specified.
 *
 * @param[in] pProslic - array of channels
 * @param[in] pRamTable - array of RAM locations and values to write
 * @param[in] pRegTable - array of register locations and values to write
 * @param[in] size - number of ProSLICS to write to.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @deprecated This function should NOT be used since it can bypass the standard initialization/operational state of the
 * ProSLIC.
 */

int ProSLIC_LoadRegTables (proslicChanType_ptr *pProslic,
                           ProslicRAMInit *pRamTable, ProslicRegInit *pRegTable, int size);

/**
 * @brief
 *  Configure impedance synthesis
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - which impedance configuration to load from the constants file.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be disabled by @ref DISABLE_ZSYNTH_SETUP
 */

int ProSLIC_ZsynthSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  This function configures the CI bits (GCI mode)
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - which GCI preset to use from the constants file
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be disabled by @ref DISABLE_CI_SETUP
 */

int ProSLIC_GciCISetup (proslicChanType_ptr hProslic,int preset);

/*****************************************************************************/
/** @defgroup PROSLIC_DEBUG Debug
 * This group of functions enables/disables debug messages as well as dump
 * register contents.
 * @{
 */


/**
 * @brief
 * This function allows access to SPI read RAM function pointer from interface
 *
 * @param[in] pProslic - pointer to channel structure
 * @param[in] addr - address to read
 * @retval ramData - RAM contents
 *
 */
ramData ProSLIC_ReadRAM (proslicChanType *pProslic, uInt16 addr);

/**
 * @brief
 * This function allows access to SPI write RAM function pointer from interface
 *
 * @param[in] pProslic - pointer to channel structure
 * @param[in] addr - address to write
 * @param[in] data to be written
 * @retval int - @ref RC_NONE
 *
 */
int ProSLIC_WriteRAM (proslicChanType *pProslic, uInt16 addr, ramData data);

/**
 * @brief
 * This function dumps to console the register contents of several
 * registers and RAM locations.
 *
 * @param[in] pProslic - which channel to dump the register contents of.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */
int ProSLIC_PrintDebugData (proslicChanType *pProslic);

/**
 * @brief
 * This function dumps the registers to the console using whatever
 * I/O method is defined by LOGPRINT
 *
 * @param[in] pProslic - which channel to dump the register contents of.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */
int ProSLIC_PrintDebugReg (proslicChanType *pProslic);

/**
 * @brief
 * This function dumps the RAM to the console using whatever
 * I/O method is defined by LOGPRINT
 *
 * @param[in] pProslic - which channel to dump the RAM contents of.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */
int ProSLIC_PrintDebugRAM (proslicChanType *pProslic);

/** @} PROSLIC_DEBUG */
/*****************************************************************************/
/** @defgroup PROSLIC_ENABLE Enable/disable channels (for init)
 * @{
 */

/**
 * @brief
 *  This function sets the channel enable status of the FXO channel on ProSLIC devices
 *  with integrated FXO.  If NOT set, then when
 *  the various initialization routines such as @ref SiVoice_SWInitChan is called,
 *  then this particular channel will NOT be initialized.
 *
 *  This function does not access the chipset directly, so SPI/GCI
 *  does not need to be up during this function call.
 *
 * @param[in,out] pProslic - which channel to return the status.
 * @param[in] enable - The new value of the channel enable field. 0 = NOT enabled, 1 = enabled.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_getChannelEnable
 */

int ProSLIC_SetDAAEnable(proslicChanType *pProslic, int enable);

/** @} PROSLIC_ENABLE */

/*****************************************************************************/
/** @defgroup PROSLIC_PATCH Patch management.
 * This group of functions write and verify the patch data needed by the
 * ProSLIC chipset.
 * @{
 */

/**
 * @brief
 * Calls patch loading function for a particular channel/ProSLIC
 *
 * @param[in] hProslic - which channel/ProSLIC should be patched
 * @param[in] pPatch - the patch data
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function should not be called directly under normal circumstances since the initialization function should
 *       perform this operation.
 *
 * @sa ProSLIC_Init
 */

int ProSLIC_LoadPatch (proslicChanType_ptr hProslic,const proslicPatch *pPatch);

/**
 * @brief
 *  Verifies patch loading function for a particular channel/ProSLIC
 *
 * @param[in] hProslic - which channel/ProSLIC should be patched
 * @param[in] pPatch - the patch data to verify was written to.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function should not be called directly under normal circumstances since the initialization function should
 *       perform this operation, unless @ref DISABLE_VERIFY_PATCH is defined.
 *
 * @sa ProSLIC_Init
 */

int ProSLIC_VerifyPatch (proslicChanType_ptr hProslic,proslicPatch *pPatch);

/** @} PROSLIC_PATCH */

/*****************************************************************************/
/** @defgroup PROSLIC_GPIO GPIO Control
 * This group of functions configure, read and write the GPIO status pins.
 * @{
 */

/**
 * @brief
 *  This function configures the ProSLIC GPIOs by loading a gpio preset that was
 *  set in the configuration tool.
 * @param[in] hProslic - which channel to configure the GPIO pins.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_GPIOControl
 */

int ProSLIC_GPIOSetup (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function controls the GPIOs of the ProSLIC.
 *
 * @param[in] hProslic - which channel to modify
 * @param[in,out] pGpioData  - pointer to GPIO status (typically 1 byte)
 * @param[in] read - 1 = Read the status, 0 = write the status
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_GPIOSetup
 */

int ProSLIC_GPIOControl (proslicChanType_ptr hProslic,uInt8 *pGpioData,
                         uInt8 read);

/** @} PROSLIC_GPIO */
/** @} GEN_CFG */

/*****************************************************************************/
/** @defgroup PROSLIC_PULSE_METER Pulse Metering
 *
 * This group contains functions related to pulse metering.
 * @{
 */

/**
* @brief
*  This function configures the ProSLIC pulse metering by loading a pulse metering preset.
*
* @param[in] hProslic - which channel should be configured
* @param[in] preset - which preset to load from the defined settings made in the configuration tool.
* @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
* @sa ProSLIC_PulseMeterStart ProSLIC_PulseMeterStop
*/

int ProSLIC_PulseMeterSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  This function enables the pulse metering generator.
 *
 * @param[in] hProslic - which channel should play the tone.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_PulseMeterSetup ProSLIC_PulseMeterStop ProSLIC_PulseMeterDisable
 *
 */
int ProSLIC_PulseMeterEnable (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function disables the pulse metering generator..
 *
 * @param[in] hProslic - which channel should play the tone.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_PulseMeterSetup ProSLIC_PulseMeterStop ProSLIC_PulseMeterEnable
 *
 */

int ProSLIC_PulseMeterDisable (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function starts the pulse metering tone.
 *
 * @param[in] hProslic - which channel should play the tone.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_PulseMeterSetup ProSLIC_PulseMeterStop
 *
 */

int ProSLIC_PulseMeterStart (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function stops the pulse metering tone.
 *
 * @param[in] hProslic - which channel should play the tone.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa PProSLIC_PulseMeterStart ProSLIC_PulseMeterSetup
 *
 */

int ProSLIC_PulseMeterStop (proslicChanType_ptr hProslic);

/** @} PROSLIC_PULSE_METER */

/*****************************************************************************/
/** @defgroup PROSLIC_INTERRUPTS Interrupt control and decode
 * @{
 */

/**
 * @brief
 *  Enables interrupts configured in the general configuration data structure.
 *
 * @param[in]  hProslic - which channel to enable the interrupts.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_EnableInterrupts (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function reads the interrupts from the ProSLIC and places them into
 *  a @ref proslicIntType structure which contains up to @ref MAX_PROSLIC_IRQS
 *  interrupts.
 *
 * @param[in] hProslic - which channel to enable the interrupts.
 * @param[in,out] pIntData - this structure contains the interrupts pending and the number of interrupts.
 * @retval int - number of interrupts pending or RC_CHANNEL_TYPE_ERR if wrong chip type or 0 for no interrupts.
 *
 */

int ProSLIC_GetInterrupts (proslicChanType_ptr hProslic,
                           proslicIntType *pIntData);

/**
 * @brief
 *  This function disables and clears interrupts on the given channel.
 *
 *  @param[in] hProslic - which channel to disable
 *  @retval int - error from @ref errorCodeType @ref RC_NONE indicates no error.
 */

int ProSLIC_DisableInterrupts (proslicChanType_ptr hProslic);

/** @} PROSLIC_INTERRUPTS */

/*****************************************************************************/
/** @defgroup SIGNALING Signaling - ring & line state, and hook state
 * @{
 */

/**
* Function: PROSLIC_ReadHookStatus
*
* @brief
* Determine hook status
* @param[in] hProslic - which channel to read from.
* @param[out] *pHookStat - will contain either @ref PROSLIC_ONHOOK or @ref PROSLIC_OFFHOOK
*
*/

int ProSLIC_ReadHookStatus (proslicChanType_ptr hProslic,uInt8 *pHookStat);

/*****************************************************************************/
/** @defgroup LINESTATUS Line Feed status
 * @{
 */

/**
 * @brief
 *  This function sets the linefeed state.
 *
 * @param[in] hProslic - which channel to modify
 * @param[in] newLinefeed - new line feed state  - examples: LF_OPEN, LF_FWD_ACTIVE
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_SetLinefeedStatus (proslicChanType_ptr hProslic,uInt8 newLinefeed);

/**
 * @brief
 *  This function sets the linefeed state for all channels on the same daisychain.
 *
 * @param[in] hProslic - which channel to modify
 * @param[in] newLinefeed - new line feed state  - examples: LF_OPEN, LF_FWD_ACTIVE
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_SetLinefeedStatusBroadcast (proslicChanType_ptr hProslic,
                                        uInt8 newLinefeed);

/**
 * @brief
 *  This function sets the polarity/wink state of the channel.
 *
 * @param[in] hProslic - which channel to modify
 * @param[in] abrupt  - to change the state immediately
 * @param[in] newPolRevState - new polarity state  - examples: POLREV_STOP, POLREV_START and WINK_START
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_PolRev (proslicChanType_ptr hProslic,uInt8 abrupt,
                    uInt8 newPolRevState);

/** @} LINESTATUS */

/*****************************************************************************/
/** @defgroup RING_CONTROL Ring generation
 * @{
 */

/**
 * @brief
 *  Configure the ringer to the given preset (see your constants header file for exact value to use).
 *  This includes timing, cadence, OHT mode, voltage levels, etc.
 *
 * @param[in]  hProslic - which channel to configure
 * @param[in]  preset - which of the xxxx_Ring_Cfg structures to use to configure the channel.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining @ref DISABLE_RING_SETUP
 *
 * @sa ProSLIC_dbgSetRinging ProSLIC_RingStart ProSLIC_RingStop
 */

int ProSLIC_RingSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Starts the ringer as confgured by @ref ProSLIC_RingSetup .  If the active and inactive timers are enabled,
 *  the ProSLIC will automatically turn on/off the ringer as programmed, else one will need to
 *  manually implement the ring cadence.  In either case, one will need to call ProSLIC_RingStop to
 *  stop the ringer or one may call @ref ProSLIC_SetLinefeedStatus to change the state directly.
 *
 * @param[in]  hProslic - which channel to enable ringing.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining @ref DISABLE_RING_SETUP
 * @deprecated - Will become a macro in a future release and later removed.  Customers should just call ProSLIC_SetLinefeedStatus w/ LF_RINGING.
 *
 * @sa ProSLIC_dbgSetRinging ProSLIC_RingStop ProSLIC_RingSetup
 */

int ProSLIC_RingStart (proslicChanType_ptr hProslic);

/**
 * @brief
 *  Stop the ringer on the given channel and set the line state to forward active.
 * @deprecated  - Will become a macro in a future release.  Customers should just call ProSLIC_SetLinefeedStatus w/ LF_FWD_ACTIVE.
 *
 * @param[in] hProslic - which channel to modify.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 * @sa ProSLIC_RingSetup ProSLIC_RingStart
 *
 * @deprecated customers are encouraged to use ProSLIC_SetLinefeedStatus
 */

int ProSLIC_RingStop (proslicChanType_ptr hProslic);

/**
 * @brief
 *  Provision function for setting up Ring type, frequency, amplitude and dc offset and
 *  to store them in the given preset.
 *
 * @note: This function calculates the values, it does not set them.
 *
 * @param[in] pProslic - which channel to modify
 * @param[in] ringCfg - how to configure the channel's ringer
 * @param[in] preset - where to store the new configuration.
 * @sa ProSLIC_RingSetup ProSLIC_RingStart ProSLIC_RingStop
 */

int ProSLIC_dbgSetRinging (proslicChanType *pProslic,
                           ProSLIC_dbgRingCfg *ringCfg, int preset);

/** @} RING_CONTROL */
/** @} SIGNALING */

/*****************************************************************************/
/** @defgroup PROSLIC_AUDIO Audio
 * This group of functions contains routines to configure the PCM bus, to generate tones, and to send FSK data.
 *
 * In order to start using the PCM bus, you would typically initialize the PCM bus with code similar to
 * the following:
 *
 * @code
 * if( (ProSLIC_PCMSetup(myProSLIC, MY_COMPANDING) != RC_NONE)
 * 	|| (ProSLIC_PCMTimeSlotSetup(myProSLIC, pcm_ts, pcm_ts) != RC_NONE)
 * 	|| (ProSLIC_PCMStart(myProSLIC) != RC_NONE))
 * {
 * 	return MY_PCM_INIT_ERROR;
 * }
 * @endcode
 *
 * @{
 * @defgroup TONE_GEN Tone generation
 * This group of functions is related to playing out general tones - such as dial tone, busy tone, etc.  One would
 * typically call @ref ProSLIC_ToneGenSetup first followed by @ref ProSLIC_ToneGenStart and after some time, a call to
 * @ref ProSLIC_ToneGenStop to stop the tone.  The direction of the tone and cadence (if any) are configured using the
 * GUI configuration tool's TONE dialog box and then saved in the constants file.
 *
 * @{
 */
/**
 * @brief
 *  Configure the tone generator to the given preset (see your constants header file for exact value to use).  It does NOT
 *  play a particular tone out.
 *
 * @warning If @ref ProSLIC_FSKSetup was called earlier, this function will need to be called again.
 *
 * @param[in]  hProslic - which channel to configure
 * @param[in]  preset - which of the xxxx_Tone_Cfg structures to use to configure the channel.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining @ref DISABLE_TONE_SETUP.
 *
 * @note Typically, if one is using the ProSLIC for tone generation, you will be calling this function prior to each call
 *       into @ref ProSLIC_ToneGenStart so that the correct tone is played out.
 */

int ProSLIC_ToneGenSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Configure the tone generator to the given preset (see your constants header file for exact value to use).  It does NOT
 *  play a particular tone out.
 *
 * @warning If @ref ProSLIC_FSKSetup was called earlier, this function will need to be called again.
 *
 * @param[in]  pProslic - which channel to configure
 * @param[in]  cfg - which of the xxxx_Tone_Cfg structures to use to configure the channel.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining @ref DISABLE_TONE_SETUP.
 *
 * @note Typically, if one is using the ProSLIC for tone generation, you will be calling this function prior to each call
 *       into @ref ProSLIC_ToneGenStart so that the correct tone is played out.
 */

int ProSLIC_ToneGenSetupPtr(proslicChanType_ptr pProslic,
                            ProSLIC_Tone_Cfg *cfg);

/**
 * @brief
 *  This function starts the tone configured by @ref ProSLIC_ToneGenSetup.
 *  It is assumed that the @ref PROSLIC_AUDIO setup was performed
 *  prior to calling this function.  Also, it is suggested that
 *  @ref ProSLIC_ToneGenSetup be called if @ref FSK_CONTROL
 *  functions were used.
 *
 *  @param[in] hProslic - which channel should play the tone.
 *  @param[in] timerEn - are the timers to be enabled?  1 = Yes, 0 = No. When in doubt, set to 1.
 *  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_ToneGenSetup ProSLIC_ToneGenStop
 */

int ProSLIC_ToneGenStart (proslicChanType_ptr hProslic, uInt8 timerEn);

/**
 * @brief
 *  This function turns off tone generation initiated by @ref ProSLIC_ToneGenStart.
 *
 * @param[in] hProslic - which channel should stop playing the tone.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_ToneGenStart ProSLIC_ToneGenSetup
 */

int ProSLIC_ToneGenStop (proslicChanType_ptr hProslic);

/** @} TONE_GEN */

/*****************************************************************************/
/** @defgroup FSK_CONTROL FSK/Caller ID generation
 * This group of functions is related to FSK generation, typically used with Caller ID/Call Waiting
 * functionality. To set the frequencies, the data rate, and the FSK FIFO depth, please use the configuration
 * GUI FSK dialog box.
 *
 * Here's a simple example code fragment to send data via FSK:
 *
 * @code
 * if( ProSLIC_FSKSetup(myProSLICChan, PROSLIC_NORTH_AMERICA_FSK) == RC_NONE)
 * {
 *
 *  // This should be called every time since it is likely a tone was played
 *  // earlier which reprograms the oscillators...
 *  ProSLIC_FSKSetup(myProSLICChan, FSK_TIA777A);
 *
 *  // Enable the CID block, at this point no tones other than the FSK ones
 *  // should be played out...
 * 	ProSLIC_EnableCID(myProSLICChan);
 *
 *	bytes_left_to_send = bufsz;
 *
 * 	do
 * 	{
 * 		if(bytes_left_to_send < FIFO_DEPTH)
 * 		{
 * 			bytes_to_send = bytes_left_to_send;
 * 		}
 * 		else
 * 		{
 * 			bytes_to_send = FIFO_DEPTH;
 *		}
 *
 * 		if( ProSLIC_SendCID(myProSLICChan,buf,bytes_to_send) != RC_NONE)
 * 		{
 * 			ProSLIC_DisableCID(myProSLICChan);
 * 			return MY_FSK_ERROR;
 * 		}
 *
 *		bytes_left_to_send -= bytes_to_send;
 *
 *		if(bytes_left_to_send)
 *		{
 *			do
 *			{
 *				ProSLIC_CheckCIDBuffer(myProSLICChan, &is_fifo_empty);
 *
 *			} while( is_fifo_empty != 1 );
 *		}
 *
 * 	}while( bytes_left_to_send > 0);
 *
 * 	ProSLIC_DisableCID(myProSLICChan);
 * @endcode
 *
 * @note The above code fragment is sub-optimal since it does constantly poll the CID buffer
 * state - one may want to implement the actual code using interrupts.
 * @{
 */

/**
 * @brief
 *  Configures the FSK generator from a configuration generated by the config tool.
 *
 * @warning If @ref ProSLIC_ToneGenSetup was called earlier, this function will need to be called again.
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - which FSK configuration to use.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining DISABLE_FSK_SETUP
 */

int ProSLIC_FSKSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Configures the FSK generator from a configuration generated by the config tool.
 *
 * @warning If @ref ProSLIC_ToneGenSetup was called earlier, this function will need to be called again.
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] cfg - which FSK configuration to use.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be compiled out by defining DISABLE_FSK_SETUP
 */

int ProSLIC_FSKSetupPtr (proslicChanType_ptr pProslic, ProSLIC_FSK_Cfg *cfg);

/**
 * @brief
 *  This function enables FSK mode and clears the FSK FIFO.  It is assumed that PCM has been enabled and that @ref ProSLIC_FSKSetup
 *  has been called at some point.
 *
 * @warning If @ref ProSLIC_ToneGenSetup was called earlier, @ref ProSLIC_FSKSetup will need to be called again.
 *
 * @param[in] hProslic - which channel to check upon.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_EnableCID (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function disables FSK mode.
 *
 * @param[in] hProslic - which channel to disable FSK mode.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_DisableCID (proslicChanType_ptr hProslic);

/**
 * @brief
 *  Check if the FSK FIFO is empty or not.
 *
 * @param[in] hProslic - which channel to check upon.
 * @param[out] fsk_buf_avail - is the buffer available? 1 = Yes, 0  = No.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note - This modifies the IRQ1 register contents, so some other interrupts may be lost. An alternative is to enable the
 *         FSK FIFO interrupt and trigger off of it when it does occur in your interrupt service routine.
 */

int ProSLIC_CheckCIDBuffer (proslicChanType_ptr hProslic, uInt8 *fsk_buf_avail);

/**
 * @brief
 *  Send numBytes as FSK encoded data.  It is assumed that numBytes <= FIFO Depth (typically 8) and that the FIFO
 *  is free. It is also assumed that @ref ProSLIC_PCMStart has been called and that we're in
 *  @ref LF_FWD_OHT or @ref LF_REV_OHT mode for Type-1 or  @ref LF_REV_ACTIVE or @ref LF_FWD_ACTIVE
 *  if we're in Type-2 caller ID.
 *
 * @param[in] hProslic - which channel to send the data through.
 * @param[in] buffer - byte array of data to send.
 * @param[in] numBytes - number of bytes to send. MUST be less than or equal to the FIFO size
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_CheckCIDBuffer ProSLIC_FSKSetup ProSLIC_EnableCID ProSLIC_DisableCID
 */

int ProSLIC_SendCID (proslicChanType_ptr hProslic, uInt8 *buffer,
                     uInt8 numBytes);

/**
 * @brief Control if the start/stop bits are enabled.
 *
 * @param[in] hProslic - which channel to adjust
 * @param[in] enable_startStop - TRUE - start/stop bits are enabled, FALSE - disabled
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note: This does not replace @ref ProSLIC_FSKSetup, but is a supplement that toggles
 * one of the registers that the preset modifies.  It is assumed that @ref ProSLIC_FSKSetup
 * was called at some point earlier in the code flow.
 */

int ProSLIC_ModifyCIDStartBits(proslicChanType_ptr hProslic,
                               uInt8 enable_startStop);


/** @} FSK_CONTROL */

/*****************************************************************************/
/** @defgroup AUDIO_CONTROL Audio control/configuration
 * @{
 */
/** @defgroup PCM_CONTROL PCM control
 * This group of functions is used to configure and control the PCM bus.  It is essential that @ref ProSLIC_PCMSetup,
 * @ref ProSLIC_PCMTimeSlotSetup and @ref ProSLIC_PCMStart are called prior to any tone or FSK generation.
 *
 * See @ref PROSLIC_AUDIO code fragment on how the functions relate during initialization.
 *
 * @{
 */

/**
 * @brief
 *  This configures the PCM bus with parameters such as companding and data latching timing.
 *
 * @param[in] hProslic - which channel should be configured
 * @param[in] preset - which preset to use from the constants file (see configuration tool, PCM dialog box)
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_PCMTimeSlotSetup ProSLIC_PCMStart
 */

int ProSLIC_PCMSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  This configures the ProSLIC to latch and send the PCM data at a particular timeslot in terms of PCM clocks (PCLK).
 *
 *  Typically, for aLaw and uLaw, one can use the following calculation to set the rxcount and txcount parameters:
 *
 *  rxcount = txcount = (channel_number)*8;
 *
 *  For 16 bit linear, one can do the following:
 *
 *  rxcount = txcount = (channel_number)*16;
 *
 * where channel_number = which ProSLIC channel on the PCM bus.  For example, if one were to have 2 dual channel
 * ProSLIC's on the same PCM bus, this value would range from 0 to 3.
 *
 * @param[in] hProslic - which channel should be configured
 * @param[in] rxcount -  how many clocks until reading data from the PCM bus
 * @param[in] txcount -  how many clocks until writing data to the PCM bus.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_PCMSetup ProSLIC_PCMStart
 */

int ProSLIC_PCMTimeSlotSetup (proslicChanType_ptr hProslic, uInt16 rxcount,
                              uInt16 txcount);

/**
 * @brief
 *  This enables PCM transfer on the given ProSLIC channel.
 *
 * @param[in] hProslic - - which channel should be enabled
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_PCMSetup ProSLIC_PCMTimeSlotSetup ProSLIC_PCMStop
 */

int ProSLIC_PCMStart (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This disables PCM transfer on the given ProSLIC channel. Typically, this is called for debugging
 *  purposes only.
 *
 * @param[in] hProslic - - which channel should be disabled
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_PCMSetup ProSLIC_PCMTimeSlotSetup ProSLIC_PCMStart
 */

int ProSLIC_PCMStop (proslicChanType_ptr hProslic);

/**
 * @brief
 * Program desired loopback test mode for the given channel.
 *
 * @param[in] hProslic -  which channel should be modified
 * @param[in] newMode - what is the desired loopback mode.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_SetLoopbackMode (proslicChanType_ptr hProslic,
                             ProslicLoopbackModes newMode);

/**
 * @brief
 * Program desired mute test mode for the given channel.
 *
 * @param[in] hProslic - which channel should be modified
 * @param[in] muteEn - what is the desired mode.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_SetMuteStatus (proslicChanType_ptr hProslic,
                           ProslicMuteModes muteEn);

/** @} PCM_CONTROL */

/*****************************************************************************/
/** @defgroup GAIN_CONTROL Gain control
 * @{
 */

/**
 * @brief
 *  Sets the TX audio gain (toward the network). This funcion DOES NOT actually calculate the values for the preset.
 *  To dynamically calculate the values, you would need to call @ref ProSLIC_dbgSetTXGain .
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - which preset to use (this may be from the constants file)
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note One can use this in conjunction with @ref ProSLIC_dbgSetTXGain to dynamically
 * change the audio gain. It is important to have the presets of both routines match.
 *
 * The following code * fragment will set the TX audio gain to -5 dB:
 *
 * @code
 * ProSLIC_dbgSetTXGain(myChannel, -5, MY_IMPEDENCE,0);
 * ProSLIC_TXAudioGainSetup(myChannel,0);
 * @endcode
 *
 * @sa ProSLIC_RXAudioGainSetup ProSLIC_dbgSetTXGain ProSLIC_AudioGainSetup
 */

int ProSLIC_TXAudioGainSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Adjusts gain of TX audio path by scaling the PGA and Equalizer coefficients by the supplied values.
 *
 * @param[in] hProslic   - which channel to configure
 * @param[in] preset     - which preset to use (this may be from the constants file)
 * @param[in] pga_scale  - scale factor which pga coefficients are to be multiplied
 * @param[in] eq_scale   - scale factor which equalizer coefficients are to be multiplied
 * @retval int           - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be used in lieu of @ref ProSLIC_dbgSetTXGain to dynamically
 * change the audio gain when gain steps of 0.1dB do not suffice, or if an attenuation
 * > 30dB is required.
 *
 * The following code * fragment will scale the TX audio gain by a factor of (0.707)*(0.500)
 *
 * @code
 * uInt32  pga_gain_scale = 707;
 * uInt32  eq_gain_scale  = 500;
 * ProSLIC_TXAudioGainScale(pProslic,DEFAULT_PRESET,pga_gain_scale,eq_gain_scale);
 * @endcode
 *
 * @sa ProSLIC_RXAudioGainScale
 */
int ProSLIC_TXAudioGainScale (proslicChanType_ptr hProslic,int preset,
                              uInt32 pga_scale,uInt32 eq_scale);

/**
 * @brief
 *  Configures the RX audio gain (toward the telephone). This function DOES NOT actually calculate the values for the preset.
 *  To dynamically calculate the values, you would need to call @ref ProSLIC_dbgSetRXGain .
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - which preset to use (this may be from the constants file)
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note One can use this in conjunction with @ref ProSLIC_dbgSetRXGain to dynamically
 * change the audio gain. It is important to have the presets of both routines match.
 *
 * The following code * fragment will set the RX audio gain to -1 dB:
 *
 * @code
 * ProSLIC_dbgSetRXGain(myChannel, -1, MY_IMPEDENCE,0);
 * ProSLIC_RXAudioGainSetup(myChannel,0);
 * @endcode
 *
 * @sa ProSLIC_TXAudioGainSetup ProSLIC_dbgSetRXGain ProSLIC_AudioGainSetup
 */

int ProSLIC_RXAudioGainSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Adjusts gain of RX audio path by scaling the PGA and Equalizer coefficients by the supplied values.
 *
 * @param[in] hProslic   - which channel to configure
 * @param[in] preset     - which preset to use (this may be from the constants file)
 * @param[in] pga_scale  - scale factor which pga coefficients are to be multiplied
 * @param[in] eq_scale   - scale factor which equalizer coefficients are to be multiplied
 * @retval int           - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be used in lieu of @ref ProSLIC_dbgSetRXGain to dynamically
 * change the audio gain when gain steps of 0.1dB do not suffice, or if an attenuation
 * > 30dB is required.
 *
 * The following code * fragment will scale the TX audio gain by a factor of (0.707)*(0.500)
 *
 * @code
 * uInt32  pga_gain_scale = 707;
 * uInt32  eq_gain_scale  = 500;
 * ProSLIC_RXAudioGainScale(pProslic,DEFAULT_PRESET,pga_gain_scale,eq_gain_scale);
 * @endcode
 *
 * @sa ProSLIC_TXAudioGainScale
 */
int ProSLIC_RXAudioGainScale (proslicChanType_ptr hProslic,int preset,
                              uInt32 pga_scale,uInt32 eq_scale);

/**
 * @brief
 *  Configures and sets the audio gains - for both RX (toward the phone) and the TX (toward the network). Unlike
 *  the @ref ProSLIC_RXAudioGainSetup and @ref ProSLIC_TXAudioGainSetup this does both the calculations and then
 *  configures the given channel in one step.  It is assumed that the preset gain array is at least 2 elements in size.
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] rxgain - what is the gain/loss of the RX transmit path in 1 dB units (negative = attenuation)
 * @param[in] txgain - what is the gain/loss of the TX transmit path in 1 dB units (negative = attenuation)
 * @param[in] preset - what is the impedance preset value
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * The following code * fragment will set the RX audio gain to -1 dB snd TX audio gain to -5 dB:
 *
 * @code
 * ProSLIC_AudioGain(myChannel, -1, -5,  MY_IMPEDENCE);
 * @endcode
 *
 * @sa ProSLIC_TXAudioGainSetup ProSLIC_dbgSetRXGain ProSLIC_dbgSetRXGain ProSLIC_dbgSetTXGain
 */

int ProSLIC_AudioGainSetup (proslicChanType_ptr hProslic,int32 rxgain,
                            int32 txgain,int preset);

/**
 * @brief
 *  This function calculates the preset values for the RX audio (toward the telephone) - it does NOT set the
 *  actual register values.  For that, please use @ref ProSLIC_RXAudioGainSetup .
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] gain - gain to set the preset values to.
 * @param[in] impedance_preset - impedence preset in the constants file.
 * @param[in] audio_gain_preset - index to the audio gain preset to store the value.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_RXAudioGainSetup ProSLIC_AudioGainSetup ProSLIC_dbgSetTXGain
 */

int ProSLIC_dbgSetRXGain (proslicChanType *pProslic, int32 gain,
                          int impedance_preset, int audio_gain_preset);

/**
 * @brief
 *  This function calculates the preset values for the TX audio (toward the network) - it does NOT set the
 *  actual register values.  For that, please use @ref ProSLIC_TXAudioGainSetup .
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] gain - gain to set the preset values to.
 * @param[in] impedance_preset - impedance preset in the constants file.
 * @param[in] audio_gain_preset - index to the audio gain preset to store the value.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_TXAudioGainSetup ProSLIC_AudioGainSetup ProSLIC_dbgSetRXGain
 */

int ProSLIC_dbgSetTXGain (proslicChanType *pProslic, int32 gain,
                          int impedance_preset, int audio_gain_preset);

/** @} GAIN_CONTROL */
/** @} AUDIO_CONTROL */
/** @} PROSLIC_AUDIO */

/*****************************************************************************/
/** @defgroup HC_DETECT Hook Change detection
 *
 * This function group has routines used to implement a pulse dial, hook flash
 * and general hook change detection. The outline of how to use these
 * functions is as follows:
 *
 * - Initialize the data structure w/ @ref ProSLIC_InitializeHookChangeDetect
 * - When hook change is detected or if there has been no activity for a minimum
 *   of the interdigit time, call @ref ProSLIC_HookChangeDetect. Keep on calling
 *   the function until we have a return code not equal to SI_HC_NEED_MORE_POLLS.
 *   Again, the function should be called, when no hook activity is detected at
 *   minimum of the interdigit time.
 *
 *   General theory (pulse digit):
 *
 *   ---|___|-----|__|---------
 *
 *   A    B    C    B   D
 *
 *   A - Offhook (time unknown)
 *   B - Onhook (break time)
 *   C - Offhook (make time)
 *   D - Interdigit delay
 *
 *   We report after D occurs a pulse digit as long as the duration for B
 *   is met.
 *
 *   For hook flash, we are looking at
 *
 *   ----|________________|-----------
 *
 *
 *  Here we're looking for the pulse width meets a certain min/max time.  If the
 *  time is exceeded, then we have likely a onhook or offhook event.
 *
 *   @note This set of functions require that the elapsed timer functions
 *   documented in @ref PROSLIC_CUSTOMER_TIMER are implemented.
 *
 * @{
 */

/**
 * @brief
 *  Initialize pulse dial/hook detection parameters.
 *
 * @param[in,out] pPulse - the structure that is to be initialized.  Refer to your target market's pulse dial standard for exact values.
 * @param[in] hookTime - a timer object suitable to be passed to a function of type @ref system_timeElapsed_fptr
 *
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_InitializeHookChangeDetect(hookChangeType *pPulse,void *hookTime);

/**
 * @brief
 *  Implements pulse dial detection and should be called at every hook transition and after the minimum interdigit delay time (should continue calling until
 *  the function returns back with a value other than SI_HC_NEED_MORE_POLLS.
 *
 * @param[in] pProslic - which channel had a hook transition.
 * @param[in] pPulsedialCfg - what is the criteria to determine on/off hook states.
 * @param[in,out] pPulseDialData - contians the timer information that was set in
 * @ref ProSLIC_InitializeHookChangeDetect as well as the pulse digit detected
 *
 * @retval int - either SI_HC_xxx values or a value between 1-10 for the number of pulses detected.  In most cases, a 0 is 10 pulses.  Please refer to
 * your country's pulse dial standard for exact encoding.
 */

uInt8 ProSLIC_HookChangeDetect (proslicChanType *pProslic,
                                hookChange_Cfg *pPulsedialCfg, hookChangeType *pPulseDialData);

/** @} HC_DETECT */

/*****************************************************************************/
/**  @addtogroup PROSLIC_AUDIO
 * @{
 * @defgroup PROSLIC_DTMF_DECODE DTMF Decode
 * This section covers DTMF decoding.
 *
 * @note Not all chipsets support this capability.  Please review your chipset
 * documentation to confirm this capability is supported.
 * @{
 */

/**
 * @brief
 *  Read/Decode DTMF digits.  The "raw" hexcode is returned in this function and would require
 *  further processing.  For example, on the Si3217x chipset, the following mapping exists:
 *
 * DTMF Digit | API output value
 * :-|:---
 * 0 | 0xA
 * 1 | 1
 * 2 | 2
 * 3 | 3
 * 4 | 4
 * 5 | 5
 * 6 | 6
 * 7 | 7
 * 8 | 8
 * 9 | 9
 * A | 0xD
 * B | 0xE
 * C | 0xF
 * D | 0
 * \*| 0xB
 * \# |0xC
 *
 * @note This function is only valid after @ref IRQ_DTMF occurred and should be called shortly
 * thereafter.
 *
 * @warning Not all ProSLIC chipsets have a DTMF decoder.  Please review your chipset to make
 * sure this capability exists.
 *
 * @param[in] hProslic - which channel is to be decoded.
 * @param[out] pDigit - "raw" DTMF value (see comments in description)
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 *
 */

int ProSLIC_DTMFReadDigit (proslicChanType_ptr hProslic,uInt8 *pDigit);

/** @} PROSLIC_DTMF_DECODE */
/** @} PROSLIC_AUDIO */

/*****************************************************************************/
/** @defgroup PROSLIC_POWER_CONVERTER Power Converter control
 * @{
 */
/**
* @brief
* Powers all DC/DC converters sequentially with delay to minimize peak power draw on VDC.
* @param[in] hProslic - which channel to change state.
* @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
* @sa ProSLIC_PowerDownConverter
*
*/

int ProSLIC_PowerUpConverter(proslicChanType_ptr hProslic);

/**
* @brief
*  Safely power down dcdc converter after ensuring linefeed
*  is in the open state.  Test power down by setting error
*  flag if detected voltage does no fall below 5v.
*
* @param[in] hProslic - which channel to change state.
* @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
* @sa ProSLIC_PowerUpConverter
*
*/

int ProSLIC_PowerDownConverter(proslicChanType_ptr hProslic);

/**
* @brief
*  Set channel flag to indicate that the polarity of the
*  DC-DC converter drive signal is to be inverted from what
*  is indicated in the General Parameters. This inversion is
*  relative to the polarity established by the General Parameters,
*  not an absolute polarity.
*
*
* @param[in] hProslic - which channel to change state.
* @param[in] flag - inversion flag (1 - inverted, 0 - no inversion)
* @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
* @sa ProSLIC_PowerUpConverter
*
*/
int ProSLIC_SetDCDCInversionFlag(proslicChanType_ptr hProslic, uInt8 flag);


/** @} PROSLIC_POWER_CONVERTER */
/*****************************************************************************/
/** @defgroup PROSLIC_LB_CALIBRATION LB Calibration
 * @{
 */

/**
 * @brief
 *  Run canned longitudinal balance calibration.
 *
 * @param[in] pProslic - start channel to start from for calibration.
 * @param[in] size - number of channels to calibrate
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note
 * Use the @ref ProSLIC_Init function to perform all calibrations except Longitudinal Balance (LB).
 * Use the @ref ProSLIC_LBCal function to perform LB calibration. LB Calibration typically needs
 * to execute LB calibration once per system setup without a load connected.  The LB calibration
 * results can be stored in non-volatile storage (flash, eeprom) and retrieved during your normal
 * ProSLIC initialization.
 *
*  @sa ProSLIC_GetLBCalResult ProSLIC_LoadPreviousLBCal ProSLIC_LoadPreviousLBCalPacked ProSLIC_GetLBCalResultPacked
 */

int ProSLIC_LBCal (proslicChanType_ptr *pProslic, int size);

/**
 * @brief
 *  This function returns the coefficient results of the last LB calibration.
 *
 * @param[in] pProslic - which channel to retrieve the values from.
 * @param[out] result1 - results read from the last calibration
 * @param[out] result2 - results read from the last calibration
 * @param[out] result3 - results read from the last calibration
 * @param[out] result4 - results read from the last calibration
*  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
*  @sa ProSLIC_LBCal ProSLIC_LoadPreviousLBCal ProSLIC_LoadPreviousLBCalPacked ProSLIC_LBCal ProSLIC_GetLBCalResultPacked
*/

int ProSLIC_GetLBCalResult (proslicChanType *pProslic,int32 *result1,
                            int32 *result2,int32 *result3,int32 *result4);

/**
 * @brief
 *  This function loads previously stored LB calibration results to the appropriate ProSLIC
 *  RAM locations.
 *
 * @param[in] pProslic - which channel to program the values
 * @param[in] result1 - values to be written
 * @param[in] result2 - values to be written
 * @param[in] result3 - values to be written
 * @param[in] result4 - values to be written
*  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
*  @sa ProSLIC_LBCal ProSLIC_LoadPreviousLBCalPacked ProSLIC_LBCal ProSLIC_GetLBCalResult ProSLIC_GetLBCalResultPacked
*/

int ProSLIC_LoadPreviousLBCal (proslicChanType *pProslic,int32 result1,
                               int32 result2,int32 result3,int32 result4);

/**
 * @brief
 *  This function returns the results of the last LB calibration packed into single int32.
 *
 * @param[in] pProslic - which channel to retrieve the values from.
 * @param[out] result - results - where to store the value
*  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
*  @sa ProSLIC_LBCal ProSLIC_LoadPreviousLBCal ProSLIC_LoadPreviousLBCalPacked ProSLIC_LBCal
*/

int ProSLIC_GetLBCalResultPacked (proslicChanType *pProslic,int32 *result);

/**
 * @brief
 *  This function loads previously stored LB calibration results that are in the packed format.
 *
 * @param[in] pProslic - which channel to retrieve the values from.
 * @param[in] result - results read from @ref ProSLIC_GetLBCalResultPacked
*  @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
*
*  @sa ProSLIC_LBCal ProSLIC_LoadPreviousLBCal ProSLIC_LBCal ProSLIC_GetLBCalResultPacked
*
*/

int ProSLIC_LoadPreviousLBCalPacked (proslicChanType *pProslic,int32 *result);

/** @} PROSLIC_LB_CALIBRATION */


/*****************************************************************************/
/** @addtogroup DIAGNOSTICS
 * @{
 */

/**
 * @brief
 *  This function can be used to verify that the SPI interface is functioning
 *  properly by performing a series of read back tests.  This test DOES modify
 *  certain registers, so a reinitialization will be required.  This test is
 *  recommended only for development use.
 *
 * @param[in] pProslic - This should point to the channel that is to be verified.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error amd will typically return back
 * @ref RC_SPI_FAIL if a SPI failure occured.
 */

int ProSLIC_VerifyControlInterface (proslicChanType_ptr pProslic);

/** @addtogroup PSTN_CHECK PSTN Check
 * @{
 */

/**
 * @brief
 * Allocates memory for a PSTN check object. One channel object is needed per
 * ProSLIC channel.
 *
 *  @param[in,out] pstnCheckObj - pointer to the object that is to be initialized.
 *  @param[in] num_objs - number of objects to allocate
 *
 *  @retval 0 = OK
 */

int ProSLIC_CreatePSTNCheckObjs(proslicPSTNCheckObjType_ptr *pstnCheckObj,
                                unsigned int num_objs);
#define ProSLIC_CreatePSTNCheckObj(PTRPTR) ProSLIC_CreatePSTNCheckObjs((PTRPTR), 1)

/**
 * @brief
 * Allocates memory for a differential PSTN check object. One channel object is needed per
 * ProSLIC channel.
 *
 *  @param[in,out] pstnCheckObj - pointer to the object that is to be initialized.
 *  @param[in] num_objs - number of objects to allocate
 *
 *  @retval 0 = OK
 */

int ProSLIC_CreateDiffPSTNCheckObjs(proslicDiffPSTNCheckObjType_ptr
                                    *pstnCheckObj, unsigned int num_objs);
#define ProSLIC_CreateDiffPSTNCheckObj(PTRPTR) ProSLIC_CreateDiffPSTNCheckObjs((PTRPTR), 1)

/**
 * @brief
 * Destroys a PSTN check object and deallocates memory.
 *
 * @param[in] pstnCheckObj - object to deallocate.
 *
 * @retval 0 = OK
 */

#define ProSLIC_DestroyPSTNCheckObj ProSLIC_DestroyPSTNCheckObjs
int ProSLIC_DestroyPSTNCheckObjs(proslicPSTNCheckObjType_ptr *pstnCheckObj);

/**
 * @brief
 *  Destroys a differential PSTN check object and deallocates memory.
 *
 * @param[in] pstnCheckObj - object to deallocate.
 *
 * @retval 0 = OK
 */

#define ProSLIC_DestroyDiffPSTNCheckObj ProSLIC_DestroyDiffPSTNCheckObjs
int ProSLIC_DestroyDiffPSTNCheckObjs(proslicDiffPSTNCheckObjType_ptr
                                     *pstnCheckObj);

/**
 * @brief
 *  Initialize pstnCheckObj structure members
 *
 * @param[in] pstnCheckObj - which object to initialize
 * @param[in] avgThresh - Average current threshold that indicates a PSTN is present (uA).
 * @param[in] singleThresh - Single current threshold that indicates a PSTN is present (uA).
 * @param[in] samples - number of samples to collect
 * @retval 0 = OK
 */

int ProSLIC_InitPSTNCheckObj(proslicPSTNCheckObjType_ptr pstnCheckObj,
                             int32 avgThresh, int32 singleThresh, uInt8 samples);

/**
 * @brief
 *  This function initializes a differential PSTN detection object.
 *
 *  @param[in,out] pstnDiffCheckObj - object to be initialized
 *  @param[in] preset1 - DC Feed preset to be used for first loop I/V measurement
 *  @param[in] preset2 - DC Feed preset to be used for second loop I/V measurement
 *  @param[in] entry_preset - restore_preset DC Feed preset that is restored after PSTN check is complete.
 *  @param[in] femf_enable - Flag to enable OPEN state hazardous voltage measurement (0 = disabled, 1 = enabled)
 *  @retval 0 = OK
 */

int ProSLIC_InitDiffPSTNCheckObj(proslicDiffPSTNCheckObjType_ptr
                                 pstnDiffCheckObj, int preset1, int preset2, int entry_preset, int femf_enable);

/**
 * @brief
 * This function monitors longitudinal current (average and single sample) to quickly identify
 * the presence of a live PSTN line. Sufficient polling needs to occur in order to quickly determine
 * if a PSTN line is preset or not.
 *
 *  @param[in] pProslic - which channel to run this test on.
 *  @param[in] pPSTNCheck - the initialized data structure that contains the intermediate results of this test.
 *  @retval 0 = no PSTN detected/thresholds have not been exceeded, 1 = PSTN detected, state machine reset.
 *
 *  @note
 *   If wanting to restart the test, one will need to call @ref ProSLIC_InitPSTNCheckObj again. However, if the
 *   number of samples exceeds the buffer then the function will "wrap".
 */

int ProSLIC_PSTNCheck(proslicChanType *pProslic,
                      proslicPSTNCheckObjType *pPSTNCheck);

/**
 * @brief
 *  This function monitors for a foreign voltage (if enabled) and measures the differential I/V
 *  characteristics of the loop at 2 unique settings to detect a foreign PSTN.  It is assumed that polling will
 *  occur at the configured value found in @ref PSTN_DET_POLL_RATE.
 *
 *  @param[in] pProslic - channel to be monitored
 *  @param[in,out] pPSTNCheck - pointer to an initialized structure that is used by the function to
 *  store state information.
 *  @retval @ref RC_NONE - test is in progress, @ref RC_COMPLETE_NO_ERR - test complete, no errors, @ref RC_PSTN_OPEN_FEMF - detected foreign voltage, RC_CHANNEL_TYPE_ERR = a non-ProSLIC device was called to perform this function
 */
int ProSLIC_DiffPSTNCheck(proslicChanType *pProslic,
                          proslicDiffPSTNCheckObjType *pPSTNCheck);

/** @} PSTN_CHECK */
/** @} DIAGNOSTICS*/

/*****************************************************************************/
/** @defgroup PROSLIC_DCFEED DC Feed Setup and control
 * @{
 */

/**
 * @brief
 *  Configures the DC feed from a preset.
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] preset - the preset to use
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be disabled by @ref DISABLE_DCFEED_SETUP
 */

int ProSLIC_DCFeedSetup (proslicChanType_ptr hProslic,int preset);

/**
 * @brief
 *  Configures the DC feed from a preset.
 *
 * @param[in] hProslic - which channel to configure
 * @param[in] cfg - pointer to preset storage structure
 * @param[in] preset - the preset to use
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @note This function can be disabled by @ref DISABLE_DCFEED_SETUP
 */
int ProSLIC_DCFeedSetupCfg (proslicChanType_ptr hProslic,
                            ProSLIC_DCfeed_Cfg *cfg, int preset);

/**
 * @brief
 *  This function allows one to adjust the DC open circuit voltage level dynamically. Boundary checking is done.
 *
 * @note This function does NOT modify the register sets needed, it calculates the correct values and stores
 * them in the correct preset.  Use @ref ProSLIC_DCFeedSetup to program the device with the new values.
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] v_vlim_val - absolute voltage level
 * @param[in] preset - DC Feed preset to be modified.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_dbgSetDCFeedIloop ProSLIC_DCFeedSetup
 */

int ProSLIC_dbgSetDCFeedVopen (proslicChanType *pProslic, uInt32 v_vlim_val,
                               int32 preset);

/**
 * @brief
 *  This function allows one to adjust the loop current level dynamically. Boundary checking is done.
 *
 * @note This function does NOT modify the register sets needed, it calculates the correct values and stores
 * them in the correct preset.  Use @ref ProSLIC_DCFeedSetup to program the device with the new values.
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] i_ilim_val - loop current level
 * @param[in] preset - DC Feed preset to be modified.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @sa ProSLIC_dbgSetDCFeedVopen ProSLIC_DCFeedSetup
 */

int ProSLIC_dbgSetDCFeedIloop (proslicChanType *pProslic, uInt32 i_ilim_val,
                               int32 preset);

/**
 * @brief
 *  This function allows one to enable/disable power savings mode found on some of the chipsets.  This allows one
 *  to change the default value set in the GUI config tool.
 *
 * @param[in] pProslic - which channel to configure
 * @param[in] pwrsave -  power savings mode enabled or disabled - value expected: @ref PWRSAVE_DISABLE or @ref PWRSAVE_ENABLE
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 */

int ProSLIC_SetPowersaveMode(proslicChanType *pProslic, int pwrsave);

/** @} PROSLIC_DCFEED */

/*****************************************************************************/
/** @defgroup MESSAGE_WAITING Message Waiting Indicator routines
 * @{
 */

/**
 * @brief
 *  Configure optional MWI feature settings.  Default values are 95v and 50ms.
 *
 * @details
 *  Set MWI flashing voltage level (Vpk), and duration that LCR is masked when
 *  MWI toggles.
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @param[in] vpk_mag - MWI voltage level (vpk) (no change is made if 0)
 * @param[in] lcrmask_mwi - LCR mask duration (ms) (no change is made if 0)
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */
int ProSLIC_MWISetup (proslicChanType_ptr hProslic,uInt16 vpk_mag,
                      uInt16 lcrmask_mwi);

/**
 * @brief
 *  Enables message waiting indicator feature
 *
 * @details
 *  Message waiting (neon flashing) enabled if device is in the onhook state.
 *  Otherwise, function will not execute and return RC_MWI_ENABLE_FAIL.  This
 *  function must be called to ENABLE MWI prior to calling ProSLIC_MWI to toggle
 *  the voltage level on TIP-RING.
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */
int ProSLIC_MWIEnable (proslicChanType_ptr hProslic);

/**
 * @brief
 *  Disables message waiting indicator feature
 *
 * @details
 *  Message waiting (neon flashing) disable.  Turns off flashing and disabled
 *  MWI feature.
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */
int ProSLIC_MWIDisable (proslicChanType_ptr hProslic);


/**
 * @brief
 *  Implements message waiting indicator
 *
 * @details
 *  Message waiting (neon flashing) state toggling.  If MWI feature has not been
 *  enabled by calling ProSLIC_SetMWIEnable(), then this function will return
 *  RC_MWI_NOT_ENABLED
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @param[in] flash_on - 0 = lamp off, 1 = lamp on.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_SetMWIState(proslicChanType_ptr hProslic,uInt8 flash_on);

/**
 * @brief
 *  Implements message waiting indicator with ramp configurability
 *
 * @details
 *  Message waiting (neon flashing) state toggling.  If MWI feature has not been
 *  enabled by calling ProSLIC_SetMWIEnable(), then this function will return
 *  RC_MWI_NOT_ENABLED
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @param[in] flash_on - 0 = lamp off, 1 = lamp on.
 * @param[in] step_delay - delay between VBATH steps (ms)
 * @param[in] step_num - number of steps between low and high states
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_SetMWIState_ramp(proslicChanType_ptr hProslic,uInt8 flash_on,
                             uInt8 step_delay,uInt8 step_num);


/**
 * @brief
 *  Read MWI output state
 *
 * @details
 *  Message waiting (neon flashing) state read.  If MWI feature has not been
 *  enabled by calling ProSLIC_SetMWIEnable(), then this function will return
 *  RC_MWI_NOT_ENABLED
 *
 * @note
 *  Proper patch must be loaded for this feature to work properly.  Code does not
 *  automatically verify that this patch is loaded.
 *
 * @param[in] hProslic - channel to modify
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_GetMWIState(proslicChanType_ptr hProslic);


/**
 * @brief
 *  Implements message waiting indicator
 *
 * @details
 *  Message waiting (neon flashing) requires modifications to vbath_expect and slope_vlim.
 *  The old values are restored to turn off the lamp. The function assumes the channels
 *  are all configured the same. During off-hook event lamp must be disabled manually.
 *
 * @param[in] hProslic - channel to modify
 * @param[in] lampOn - 0 = lamp is off, 1 = lamp is on.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 *
 * @deprecated Use @ref ProSLIC_SetMWIState
 */

int ProSLIC_MWI (proslicChanType_ptr hProslic,uInt8 lampOn);

/** @} MESSAGE_WAITING */

/*****************************************************************************/
/** @defgroup MISC MISC. routines
 * @{
 */

/**
 * @brief
 *  This function initiates PLL free run mode.
 *
 * @param[in] hProslic - which channel to modify
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_PLLFreeRunStart (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function terminates PLL free run mode.
 *
 * @param[in] hProslic - which channel to modify
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_PLLFreeRunStop (proslicChanType_ptr hProslic);

/**
 * @brief
 *  This function returns PLL free run status.
 *
 * @param[in] hProslic - which channel to report upon.
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */

int ProSLIC_GetPLLFreeRunStatus (proslicChanType_ptr hProslic);

/**
 *
 * @brief
 * Sets the ProSLIC into User Access Mode (UAM) on parts that support this. This is mainly
 * used internally within the API.
 *
 * @param[in] pProslic - which channel to modify
 * @param[in] isEnabled - is the User Access Mode enabled (NOTE: once enabled, it can not be disabled)
 * @param[in] isBcast   - is this a broadcast on the daisychain
 * @retval int - error from @ref errorCodeType  @ref RC_NONE indicates no error.
 */
int ProSLIC_SetUserMode(proslicChanType *pProslic,BOOLEAN isEnabled,
                        BOOLEAN isBcast);

/*
** @brief
** Checks for improper ring exit (this is used internally by the API) and
** not all chipsets need to call this.
**
** @param[in] pProslic - which ProSLIC to check.
** Returns:
** RC_NONE                -  Reinit not required
** RC_REINIT_REQUIRED     -  Corrupted state machine - reinit required
**
*/
int ProSLIC_isReinitRequired(proslicChanType *pProslic);

/** @} MISC */
/** @} */

/* Hopefully customer's code will never call this function... */
int ProSLIC_UnsupportedFeatureNoArg(proslicChanType_ptr pProslic,
                                    const char *function_name);

/* Helper function used by PSTN routines */
#ifdef PSTN_DET_ENABLE
void ProSLIC_PSTN_delay_poll(proslicTestStateType *pState, uInt16 delay);
#endif

#if defined(SI3218X) || defined(SI3226X) || defined(SI3228X) || defined(SI3217X)
int ProSLIC_Calibrate(proslicChanType_ptr *hProslic, int maxChan, uInt8 *calr,
                      int maxTime);
#endif
/**
 * @brief determine if the given channel is a ProSLIC or DAA
 *
 * @param[in,out] pProslic - channel to be probed.
 * @retval PROSLIC | DAA | UNKNOWN
 */
int ProSLIC_identifyChannelType(proslicChanType *pProslic);

/* The following functions are used as part of the chipset init functions, not meant to be called
   outside this scope.
*/
int ProSLIC_ReInit_helper(proslicChanType_ptr *pProslic, int size,
                          initOptionsType init_option, int numChanPerDevice);
int ProSLIC_VerifyMasterStat(proslicChanType_ptr);

#endif /*end ifdef PROSLIC_H*/

