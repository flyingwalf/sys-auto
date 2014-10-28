#include    <stdio.h>
#include    <unistd.h>
#include    <string.h>
#include    <stdlib.h>
#include    <ctype.h>
#include    <sys/socket.h>
#include    <sys/ioctl.h>
#include    <errno.h>
#include    <linux/if.h>
#include    <linux/wireless.h>
#include    <sys/types.h>
#include    <sys/time.h>
#include    <cutils/properties.h>

/** Character, 1 byte */
typedef signed char t_s8;
/** Unsigned character, 1 byte */
typedef unsigned char t_u8;

/** Short integer */
typedef signed short t_s16;
/** Unsigned short integer */
typedef unsigned short t_u16;

/** Integer */
typedef signed int t_s32;
/** Unsigned integer */
typedef unsigned int t_u32;

/** Long long integer */
typedef signed long long t_s64;
/** Unsigned long long integer */
typedef unsigned long long t_u64;

/** Void pointer (4-bytes) */
typedef void t_void;

#ifndef __ATTRIB_PACK__
#define __ATTRIB_PACK__  __attribute__((packed))
#endif

/** 16 bits byte swap */
#define swap_byte_16(x) \
((t_u16)((((t_u16)(x) & 0x00ffU) << 8) | \
		(((t_u16)(x) & 0xff00U) >> 8)))

/** 32 bits byte swap */
#define swap_byte_32(x) \
((t_u32)((((t_u32)(x) & 0x000000ffUL) << 24) | \
		 (((t_u32)(x) & 0x0000ff00UL) <<  8) | \
		 (((t_u32)(x) & 0x00ff0000UL) >>  8) | \
		 (((t_u32)(x) & 0xff000000UL) >> 24)))

//#define BIG_ENDIAN_SUPPORT
/** Convert to correct endian format */
#ifdef BIG_ENDIAN_SUPPORT
/** CPU to little-endian convert for 16-bit */
#define     cpu_to_le16(x)  swap_byte_16(x)
/** CPU to little-endian convert for 32-bit */
#define     cpu_to_le32(x)  swap_byte_32(x)
/** Little-endian to CPU convert for 16-bit */
#define     le16_to_cpu(x)  swap_byte_16(x)
/** Little-endian to CPU convert for 32-bit */
#define     le32_to_cpu(x)  swap_byte_32(x)
#else
/** Do nothing */
#define     cpu_to_le16(x)  (x)
/** Do nothing */
#define     cpu_to_le32(x)  (x)
/** Do nothing */
#define     le16_to_cpu(x)  (x)
/** Do nothing */
#define     le32_to_cpu(x)  (x)
#endif

/** Type definition: boolean */
//typedef enum { FALSE, TRUE } boolean;

/** Marvell private command identifier */
#define CMD_MARVELL         "MRVL_CMD"

/** Defaule mef.conf file location */
#define DEFAULT_MEM_CONF_FILE "/data/system/mef.conf"

/** IOCTL number */
#define MLAN_ETH_PRIV               (SIOCDEVPRIVATE + 14)

/** Command buffer max length */
#define BUFFER_LENGTH       (2 * 1024)

/** Find number of elements */
#define NELEMENTS(x) (sizeof(x)/sizeof(x[0]))

struct eth_priv_cmd {
    /** Command buffer */
	t_u8 *buf;
    /** Used length */
	int used_len;
    /** Total length */
	int total_len;
};

/** HostCmd_DS_REG */
typedef struct MAPP_HostCmd_DS_REG {
    /** Read or write */
	t_u16 action;
    /** Register offset */
	t_u16 offset;
    /** Value */
	t_u32 value;
} __ATTRIB_PACK__ HostCmd_DS_REG;

/** HostCmd_DS_MEM */
typedef struct MAPP_HostCmd_DS_MEM {
    /** Read or write */
	t_u16 action;
    /** Reserved */
	t_u16 reserved;
    /** Address */
	t_u32 addr;
    /** Value */
	t_u32 value;
} __ATTRIB_PACK__ HostCmd_DS_MEM;

typedef struct _HostCmd_DS_MEF_CFG {
    /** Criteria */
	t_u32 Criteria;
    /** Number of entries */
	t_u16 NumEntries;
} __ATTRIB_PACK__ HostCmd_DS_MEF_CFG;

typedef struct _MEF_CFG_DATA {
    /** Size */
	t_u16 size;
    /** Data */
	HostCmd_DS_MEF_CFG data;
} __ATTRIB_PACK__ MEF_CFG_DATA;

/** HostCmd_DS_GEN */
typedef struct MAPP_HostCmd_DS_GEN {
    /** Command */
	t_u16 command;
    /** Size */
	t_u16 size;
    /** Sequence number */
	t_u16 seq_num;
    /** Result */
	t_u16 result;
} __ATTRIB_PACK__ HostCmd_DS_GEN;

/** Size of HostCmd_DS_GEN */
#define S_DS_GEN    sizeof(HostCmd_DS_GEN)


/** Success */
#define MLAN_STATUS_SUCCESS         (0)
/** Failure */
#define MLAN_STATUS_FAILURE         (-1)
/** Not found */
#define MLAN_STATUS_NOTFOUND        (1)

#define WIFI_WAKEUP_GPIO_PROP "wifi.wakeup.gpio"

#define NAME_MODE	1	/**< Field name 'mode' */
#define NAME_ACTION	2	/**< Field name 'action' */
#define NAME_FILTER_NUM	3   /**< Field name 'filter_num' */
#define NAME_RPN	4	/**< Field name 'RPN' */
static struct mef_entry_fields {
	char *name;
	      /**< Name */
	t_s8 nameid;
		/**< Name id */
} mef_entry_fields[] = {
	{
	"mode", NAME_MODE}, {
	"action", NAME_ACTION}, {
	"filter_num", NAME_FILTER_NUM}, {
"RPN", NAME_RPN},};

typedef struct _MEF_ENTRY {
    /** Mode */
	t_u8 Mode;
    /** Size */
	t_u8 Action;
    /** Size of expression */
	t_u16 ExprSize;
} MEF_ENTRY;


#define COUNTRY_CODE_LEN                3
/** Type definition of eth_priv_countrycode for CMD_COUNTRYCODE */
struct eth_priv_countrycode {
    /** Country Code */
	t_u8 country_code[COUNTRY_CODE_LEN];
};

/** Type definition of mlan_ds_hs_cfg for MLAN_OID_PM_CFG_HS_CFG */
struct eth_priv_hs_cfg {
    /** MTRUE to invoke the HostCmd, MFALSE otherwise */
	t_u32 is_invoke_hostcmd;
    /** Host sleep config condition */
    /** Bit0: broadcast data
     *  Bit1: unicast data
     *  Bit2: mac event
     *  Bit3: multicast data
     */
	t_u32 conditions;
    /** GPIO pin or 0xff for interface */
	t_u32 gpio;
    /** Gap in milliseconds or or 0xff for special setting when GPIO is used to wakeup host */
	t_u32 gap;
};
#define STACK_NBYTES            	100	/**< Number of bytes in stack */
#define MAX_BYTESEQ 		       	6	/**< Maximum byte sequence */
#define TYPE_DNUM           		1 /**< decimal number */
#define TYPE_BYTESEQ        		2 /**< byte sequence */
#define MAX_OPERAND         		0x40	/**< Maximum operands */
#define TYPE_EQ         		(MAX_OPERAND+1)	/**< byte comparison:    == operator */
#define TYPE_EQ_DNUM    		(MAX_OPERAND+2)	/**< decimal comparison: =d operator */
#define TYPE_EQ_BIT     		(MAX_OPERAND+3)	/**< bit comparison:     =b operator */
#define TYPE_AND        		(MAX_OPERAND+4)	/**< && operator */
#define TYPE_OR         		(MAX_OPERAND+5)	/**< || operator */
typedef struct {
	t_u16 sp;		      /**< Stack pointer */
	t_u8 byte[STACK_NBYTES];      /**< Stack */
} mstack_t;

int config_wifi_wakeup();

