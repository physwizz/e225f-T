/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __S6E3FC3_PARAM_H__
#define __S6E3FC3_PARAM_H__

#include <linux/types.h>
#include <linux/kernel.h>

#define LCD_TYPE_VENDOR		"SDC"

#define EXTEND_BRIGHTNESS	486
#define UI_MAX_BRIGHTNESS	255
#define UI_DEFAULT_BRIGHTNESS	128

#define NORMAL_TEMPERATURE	0	/* 25 degrees Celsius */

#define ACL_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_ACL_OFF))
#define HBM_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_HBM_OFF))
#define ELVSS_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_ELVSS_SET))
#define DIM_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_DIM_SET))
#define SYNC_CMD_CNT			((u16)ARRAY_SIZE(SEQ_S6E3FC3_SMOOTH_SYNC_CONTROL_SET))
#define VINT_CMD_CNT			((u16)ARRAY_SIZE(SEQ_S6E3FC3_HBM_VINT_PRE_SET))



#define LDI_REG_BRIGHTNESS			0x51
#define LDI_REG_ID				0x04
#define LDI_REG_COORDINATE			0xA1
#define LDI_REG_DATE				LDI_REG_COORDINATE
#define LDI_REG_MANUFACTURE_INFO		LDI_REG_COORDINATE
#define LDI_REG_MANUFACTURE_INFO_CELL_ID	0x92
#define LDI_REG_CHIP_ID				0xD6

/* len is read length */
#define LDI_LEN_ID				3
#define LDI_LEN_COORDINATE			4	/* A1h 1st ... 4th */
#define LDI_LEN_DATE				7	/* A1h 5th ... 11th */
#define LDI_LEN_MANUFACTURE_INFO		4	/* A1h 12th ... 15th */
#define LDI_LEN_MANUFACTURE_INFO_CELL_ID	16	/* 92h 3rd ... 18th */
#define LDI_LEN_CHIP_ID				5

/* offset is position including addr, not only para */
#define LDI_OFFSET_ACL		1			/* 55h 1st para */
#define LDI_OFFSET_HBM		1			/* 53h 1st para */
#define LDI_OFFSET_ELVSS_1	3			/* B5h 3rd para ELVSS interpolation */
#define LDI_OFFSET_ELVSS_2	1			/* B5h 1st para TSET */

#define LDI_GPARA_COORDINATE			0	/* A1h 1st ... 4th */
#define LDI_GPARA_DATE				4	/* A1h 5th ... 11th */
#define LDI_GPARA_MANUFACTURE_INFO		11	/* A1h 12th ... 15th */
#define LDI_GPARA_MANUFACTURE_INFO_CELL_ID	2	/* 92h 3rd ... 18th */

#define FPS_60							0
#define FPS_90							1

struct bit_info {
	unsigned int reg;
	unsigned int len;
	char **print;
	unsigned int expect;
	unsigned int offset;
	unsigned int g_para;
	unsigned int invert;
	unsigned int mask;
	unsigned int result;
};

enum {
	LDI_BIT_ENUM_05,	LDI_BIT_ENUM_RDNUMPE = LDI_BIT_ENUM_05,
	LDI_BIT_ENUM_0A,	LDI_BIT_ENUM_RDDPM = LDI_BIT_ENUM_0A,
	LDI_BIT_ENUM_0E,	LDI_BIT_ENUM_RDDSM = LDI_BIT_ENUM_0E,
	LDI_BIT_ENUM_0F,	LDI_BIT_ENUM_RDDSDR = LDI_BIT_ENUM_0F,
	LDI_BIT_ENUM_EE,	LDI_BIT_ENUM_ESDERR = LDI_BIT_ENUM_EE,
	LDI_BIT_ENUM_E9,	LDI_BIT_ENUM_DSIERR = LDI_BIT_ENUM_E9,
	LDI_BIT_ENUM_MAX
};

static char *LDI_BIT_DESC_05[BITS_PER_BYTE] = {
	[0 ... 6] = "number of corrupted packets",
	[7] = "overflow on number of corrupted packets",
};

static char *LDI_BIT_DESC_0A[BITS_PER_BYTE] = {
	[2] = "Display is Off",
	[7] = "Booster has a fault",
};

static char *LDI_BIT_DESC_0E[BITS_PER_BYTE] = {
	[0] = "Error on DSI",
};

static char *LDI_BIT_DESC_0F[BITS_PER_BYTE] = {
	[7] = "Register Loading Detection",
};

static char *LDI_BIT_DESC_EE[BITS_PER_BYTE] = {
	[2] = "VLIN3 error",
	[3] = "ELVDD error",
	[6] = "VLIN1 error",
};

static char *LDI_BIT_DESC_E9[BITS_PER_BYTE * 2] = {
	[0] = "SoT Error",
	[1] = "SoT Sync Error",
	[2] = "EoT Sync Error",
	[3] = "Escape Mode Entry Command Error",
	[4] = "Low-Power Transmit Sync Error",
	[5] = "HS RX Timeout",
	[6] = "False Control Error",
	[7] = "Data Lane Contention Detection",
	[8] = "ECC Error, single-bit (detected and corrected)",
	[9] = "ECC Error, multi-bit (detected, not corrected)",
	[10] = "Checksum Error",
	[11] = "DSI Data Type Not Recognized",
	[12] = "DSI VC ID Invalid",
	[13] = "Data P Lane Contention Detetion",
	[14] = "Data Lane Contention Detection",
	[15] = "DSI Protocol Violation",
};

static struct bit_info ldi_bit_info_list[LDI_BIT_ENUM_MAX] = {
	[LDI_BIT_ENUM_05] = {0x05, 1, LDI_BIT_DESC_05, 0x00, },
	[LDI_BIT_ENUM_0A] = {0x0A, 1, LDI_BIT_DESC_0A, 0x9C, .invert = (BIT(2) | BIT(7)), },
	[LDI_BIT_ENUM_0E] = {0x0E, 1, LDI_BIT_DESC_0E, 0x80, },
	[LDI_BIT_ENUM_0F] = {0x0F, 1, LDI_BIT_DESC_0F, 0xC0, .invert = (BIT(7)), },
	[LDI_BIT_ENUM_EE] = {0xEE, 1, LDI_BIT_DESC_EE, 0xC0, },
	[LDI_BIT_ENUM_E9] = {0xE9, 2, LDI_BIT_DESC_E9, 0x00, },
};

#if defined(CONFIG_SMCDSD_DPUI)
#define LDI_LEN_RDNUMPE		1		/* DPUI_KEY_PNDSIE: Read Number of the Errors on DSI */
#define LDI_PNDSIE_MASK		(GENMASK(7, 0))

/*
 * ESD_ERROR[0] = MIPI DSI error is occurred by ESD.
 * ESD_ERROR[1] = HS CLK lane error is occurred by ESD.
 * ESD_ERROR[2] = VLIN3 error is occurred by ESD.
 * ESD_ERROR[3] = ELVDD error is occurred by ESD.
 * ESD_ERROR[4] = CHECK_SUM error is occurred by ESD.
 * ESD_ERROR[5] = Internal HSYNC error is occurred by ESD.
 * ESD_ERROR[6] = VLIN1 error is occurred by ESD
 */
#define LDI_LEN_ESDERR		1		/* DPUI_KEY_PNELVDE, DPUI_KEY_PNVLI1E, DPUI_KEY_PNVLO3E, DPUI_KEY_PNESDE */
#define LDI_PNELVDE_MASK	(BIT(3))	/* ELVDD error */
#define LDI_PNVLI1E_MASK	(BIT(6))	/* VLIN1 error */
#define LDI_PNVLO3E_MASK	(BIT(2))	/* VLIN3 error */
#define LDI_PNESDE_MASK		(BIT(2) | BIT(3) | BIT(6))

#define LDI_LEN_RDDSDR		1		/* DPUI_KEY_PNSDRE: Read Display Self-Diagnostic Result */
#define LDI_PNSDRE_MASK		(BIT(7))	/* D7: REG_DET: Register Loading Detection */
#endif

struct lcd_seq_info {
	unsigned char	*cmd;
	unsigned int	len;
	unsigned int	sleep;
};


static unsigned char SEQ_S6E3FC3_SLEEP_OUT[] = { 0x11 };
static unsigned char SEQ_S6E3FC3_SLEEP_IN[] = { 0x10 };
static unsigned char SEQ_S6E3FC3_DISPLAY_OFF[] = { 0x28 };
static unsigned char SEQ_S6E3FC3_DISPLAY_ON[] = { 0x29 };

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_F0[] = {
	0xF0,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_F0[] = {
	0xF0,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_FC[] = {
	0xFC,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_FC[] = {
	0xFC,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_9F[] = {
	0x9F,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_9F[] = {
	0x9F,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_BRIGHTNESS[] = {
	0x51,
	0x01, 0xC7,
};

static unsigned char SEQ_S6E3FC3_WRCTRD_NORMAL[] = {
	0x53,
	0x20,
};

static unsigned char SEQ_S6E3FC3_GLOBAL_PARA_SET[] = {
	0xF2,
	0x00, 0x05, 0x0E, 0x58, 0x50, 0x00, 0x0C, 0x00,
	0x04, 0x30, 0xB1, 0x30, 0xB1, 0x0C, 0x04, 0xBC,
	0x26, 0xE9, 0x0C, 0x00, 0x04, 0x10, 0x00, 0x10,
	0x26, 0xA8, 0x10, 0x00, 0x10, 0x10, 0x34, 0x10,
	0x00, 0x40, 0x30, 0xC8, 0x00, 0xC8, 0x00, 0x00,
	0xCE
};

static unsigned char SEQ_S6E3FC3_LTPS_UPDATE[] = {
	0xF7,
	0x0F
};

static unsigned char SEQ_S6E3FC3_TE_ON[] = {
	0x35,
	0x00
};

static unsigned char SEQ_S6E3FC3_CASET[] = {
	0x2A,
	0x00, 0x00, 0x04, 0x37
};

static unsigned char SEQ_S6E3FC3_PASET[] = {
	0x2B,
	0x00, 0x00, 0x09, 0x5F
};

#if defined(CONFIG_SMCDSD_DYNAMIC_MIPI)

enum {
	FFC_OFF,
	FFC_UPDATE,
};

enum {
	DYNAMIC_MIPI_INDEX_0,
	DYNAMIC_MIPI_INDEX_1,
	DYNAMIC_MIPI_INDEX_2,
	DYNAMIC_MIPI_INDEX_MAX,
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_GPARA[] = {
	0xB0,
	0x00, 0x2A, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1710[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x45
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1730[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x45
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1680[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x45
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_GPARA[] = {
	0xB0,
	0x00, 0x3E, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1710[] = {
	0xC5,
	0x32, 0xB1
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1730[] = {
	0xC5,
	0x32, 0x22
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1680[] = {
	0xC5,
	0x33, 0xA0
};
static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_OFF[] = {
	0xC5,
	0x0D, 0x0C
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_OFF[] = {
	0xFE,
	0xB0
};

static unsigned char SEQ_S6E3FC3_FFC_SET_3RD_OFF[] = {
	0xFE,
	0x30
};

static struct lcd_seq_info LCD_SEQ_FFC_1710[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1710, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1710) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1710, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1710) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1730[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1730, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1730) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1730, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1730) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1680[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1680, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1680) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1680, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1680) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_OFF[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_OFF) },
	{SEQ_S6E3FC3_FFC_SET_2ND_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_OFF) },
	{SEQ_S6E3FC3_FFC_SET_3RD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_3RD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

#else
// 1660
static unsigned char SEQ_S6E3FC3_FFC1_GPARA[] = {
	0xB0,
	0x00, 0x2A, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC1_SET[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x45
};

static unsigned char SEQ_S6E3FC3_FFC2_GPARA[] = {
	0xB0,
	0x00, 0x3E, 0xC5
};
static unsigned char SEQ_S6E3FC3_FFC2_SET[] = {
	0xC5,
	0x34, 0x40
};
#endif

static unsigned char SEQ_S6E3FC3_ERR_FG_ENABLE[] = {
	0xE5,
	0x15		// 0x05:disable, 0x15:enable
};

static unsigned char SEQ_S6E3FC3_ERR_FG_SET[] = {
	0xED,
	0x44, 0x4C, 0x20		// vlin1, elvdd, vlin3
};

static unsigned char SEQ_S6E3FC3_PCD[] = {
	0xCC,
	0x5C, 0x51		// default high, enable sw reset
};

static unsigned char SEQ_S6E3FC3_ACL_GPARA[] = {
	0xB0,
	0x03, 0xB3, 0x65
};

static unsigned char SEQ_S6E3FC3_ACL_DEFAULT[] = {
	0x65,
	0x55, 0x00, 0xB0, 0x51, 0x66, 0x98, 0x15, 0x55,
	0x55, 0x55, 0x08, 0xF1, 0xC6, 0x48, 0x40, 0x00,
	0x20, 0x10, 0x09
};

static unsigned char SEQ_S6E3FC3_FREQ_GPARA[] = {
	0xB0,
	0x00, 0x27, 0xF2
};

static unsigned char SEQ_S6E3FC3_FREQ_SET[] = {
	0xF2,
	0x00
};

static unsigned char SEQ_S6E3FC3_FPS_60HZ[] = {
	0x60,
	0x00, 0x00
};

static unsigned char SEQ_S6E3FC3_FPS_90HZ[] = {
	0x60,
	0x08, 0x00
};

static unsigned char SEQ_S6E3FC3_ELVSS_SET[] = {
	0xB5,
	0x19,	/* 1st: TSET */
};

static unsigned char SEQ_S6E3FC3_HBM_ON[] = {
	0x53,
	0xE8,
};

static unsigned char SEQ_S6E3FC3_HBM_OFF[] = {
	0x53,
	0x28,
};

static unsigned char SEQ_S6E3FC3_HBM_ON_DIMMING_OFF[] = {
	0x53,
	0xE0,
};

static unsigned char SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF[] = {
	0x53,
	0x20,
};

static unsigned char SEQ_S6E3FC3_DIM_GPARA[] = {
	0xB0,
	0x00, 0x02, 0x90
};

static unsigned char SEQ_S6E3FC3_NORMAL_DIM_SET[] = {
	0x90,
	0x1C,
};

static unsigned char SEQ_S6E3FC3_HBM_DIM_SET[] = {
	0x90,
	0x14,
};

static unsigned char SEQ_S6E3FC3_VINT_GPARA[] = {
	0xB0,
	0x02, 0x03, 0x63
};

/* normal -> hbm */
static unsigned char SEQ_S6E3FC3_HBM_VINT_PRE_SET[] = {
	0x63,
	0xF1, 0x00
};

static unsigned char SEQ_S6E3FC3_HBM_VINT_POST_SET[] = {
	0x63,
	0xF0, 0x07
};

/* hbm -> normal */
static unsigned char SEQ_S6E3FC3_NORMAL_VINT_PRE_SET[] = {
	0x63,
	0xF1, 0x07
};

static unsigned char SEQ_S6E3FC3_NORMAL_VINT_POST_SET[] = {
	0x63,
	0xF0, 0x00
};

static unsigned char SEQ_S6E3FC3_SYNC_CONTROL_GPARA[] = {
	0xB0,
	0x00, 0x91, 0x63
};

static unsigned char SEQ_S6E3FC3_SMOOTH_SYNC_CONTROL_SET[] = {
	0x63,
	0x60,
};

static unsigned char SEQ_S6E3FC3_NORMAL_SYNC_CONTROL_SET[] = {
	0x63,
	0x20,
};

static unsigned char SEQ_S6E3FC3_ACL_OFF[] = {
	0x55,
	0x00
};

static unsigned char SEQ_S6E3FC3_ACL_08P[] = {
	0x55,
	0x01
};

static unsigned char SEQ_S6E3FC3_ACL_15P[] = {
	0x55,
	0x03
};

static unsigned char SEQ_S6E3FC3_AOR_GPARA[] = {
	0xB0,
	0x00, 0x76, 0x63
};

#if defined(CONFIG_SMCDSD_DOZE)
enum {
	ALPM_OFF,
	ALPM_ON_LOW,	/* ALPM 2 NIT */
	HLPM_ON_LOW,	/* HLPM 2 NIT */
	ALPM_ON_HIGH,	/* ALPM 60 NIT */
	HLPM_ON_HIGH,	/* HLPM 60 NIT */
	ALPM_MODE_MAX
};

enum {
	AOD_MODE_OFF,
	AOD_MODE_ALPM,
	AOD_MODE_HLPM,
	AOD_MODE_MAX
};

enum {
	AOD_HLPM_OFF,
	AOD_HLPM_02_NIT,
	AOD_HLPM_10_NIT,
	AOD_HLPM_30_NIT,
	AOD_HLPM_60_NIT,
	AOD_HLPM_STATE_MAX
};

static const char *AOD_HLPM_STATE_NAME[AOD_HLPM_STATE_MAX] = {
	"HLPM_OFF",
	"HLPM_02_NIT",
	"HLPM_10_NIT",
	"HLPM_30_NIT",
	"HLPM_60_NIT",
};

static unsigned int lpm_old_table[ALPM_MODE_MAX] = {
	AOD_HLPM_OFF,
	AOD_HLPM_02_NIT,
	AOD_HLPM_02_NIT,
	AOD_HLPM_60_NIT,
	AOD_HLPM_60_NIT,
};

static unsigned int lpm_brightness_table[EXTEND_BRIGHTNESS + 1] = {
	[0 ... 11]			= AOD_HLPM_02_NIT,
	[12 ... 31]			= AOD_HLPM_10_NIT,
	[32 ... 54]			= AOD_HLPM_30_NIT,
	[55 ... EXTEND_BRIGHTNESS]	= AOD_HLPM_60_NIT,
};

static unsigned char SEQ_S6E3FC3_HLPM_60NIT[] = {
	0x53,
	0x24
};

static unsigned char SEQ_S6E3FC3_HLPM_30NIT[] = {
	0x53,
	0x25
};

static unsigned char SEQ_S6E3FC3_HLPM_10NIT[] = {
	0x53,
	0x26
};

static unsigned char SEQ_S6E3FC3_HLPM_2NIT[] = {
	0x53,
	0x27
};

static unsigned char SEQ_S6E3FC3_AOD_ON[] = {
	0x91,
	0x01, 0x01
};

static unsigned char SEQ_S6E3FC3_AOD_OFF[] = {
	0x91,
	0x02, 0x01
};

static unsigned char SEQ_S6E3FC3_SWIRE_GPARA[] = {
	0xB0,
	0x00, 0x07, 0xB5
};

static unsigned char SEQ_S6E3FC3_SWIRE_NO_PULSE[] = {
	0xB5,
	0x00, 0x00, 0x00
};

static unsigned char SEQ_S6E3FC3_AOD_HFP_GPARA1[] = {
	0xB0,
	0x01, 0x88, 0xCB
};
static unsigned char SEQ_S6E3FC3_AOD_HFP_SET1[] = {
	0xCB,
	0x30, 0x19, 0x00, 0x00, 0x00, 0x00, 0x30
};

static unsigned char SEQ_S6E3FC3_AOD_HFP_GPARA2[] = {
	0xB0,
	0x01, 0xC0, 0xCB
};
static unsigned char SEQ_S6E3FC3_AOD_HFP_SET2[] = {
	0xCB,
	0x38, 0x00, 0x00, 0x00, 0x18, 0x03, 0x38
};

static unsigned char SEQ_S6E3FC3_AOD_HFP_GPARA3[] = {
	0xB0,
	0x00, 0x10, 0xF2
};
static unsigned char SEQ_S6E3FC3_AOD_HFP_SET3[] = {
	0xF2,
	0x24, 0xA0
};

static unsigned char SEQ_S6E3FC3_NORMAL_HFP_GPARA1[] = {
	0xB0,
	0x01, 0x88, 0xCB
};
static unsigned char SEQ_S6E3FC3_NORMAL_HFP_SET1[] = {
	0xCB,
	0x35, 0x19, 0x00, 0x00, 0x00, 0x00, 0x35
};

static unsigned char SEQ_S6E3FC3_NORMAL_HFP_GPARA2[] = {
	0xB0,
	0x01, 0xC0, 0xCB
};
static unsigned char SEQ_S6E3FC3_NORMAL_HFP_SET2[] = {
	0xCB,
	0x3D, 0x00, 0x00, 0x00, 0x18, 0x03, 0x3D
};

static unsigned char SEQ_S6E3FC3_NORMAL_HFP_GPARA3[] = {
	0xB0,
	0x00, 0x10, 0xF2
};
static unsigned char SEQ_S6E3FC3_NORMAL_HFP_SET3[] = {
	0xF2,
	0x26, 0xE9
};


static struct lcd_seq_info LCD_SEQ_HLPM_60_NIT_00_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_60NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_60NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_30_NIT_00_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_30NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_30NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_10_NIT_00_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_10NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_10NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_02_NIT_00_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_2NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_2NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_OFF_00_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_SWIRE_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_SWIRE_GPARA) },
	{SEQ_S6E3FC3_SWIRE_NO_PULSE, ARRAY_SIZE(SEQ_S6E3FC3_SWIRE_NO_PULSE) },
	{SEQ_S6E3FC3_AOD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_AOD_OFF) },
	{SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF, ARRAY_SIZE(SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_60_NIT_04[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_60NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_60NIT) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA1) },
	{SEQ_S6E3FC3_AOD_HFP_SET1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET1) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA2) },
	{SEQ_S6E3FC3_AOD_HFP_SET2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET2) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA3) },
	{SEQ_S6E3FC3_AOD_HFP_SET3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET3) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_30_NIT_04[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_30NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_30NIT) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA1) },
	{SEQ_S6E3FC3_AOD_HFP_SET1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET1) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA2) },
	{SEQ_S6E3FC3_AOD_HFP_SET2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET2) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA3) },
	{SEQ_S6E3FC3_AOD_HFP_SET3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET3) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_10_NIT_04[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_10NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_10NIT) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA1) },
	{SEQ_S6E3FC3_AOD_HFP_SET1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET1) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA2) },
	{SEQ_S6E3FC3_AOD_HFP_SET2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET2) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA3) },
	{SEQ_S6E3FC3_AOD_HFP_SET3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET3) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_02_NIT_04[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_ON, ARRAY_SIZE(SEQ_S6E3FC3_AOD_ON) },
	{SEQ_S6E3FC3_HLPM_2NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_2NIT) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA1) },
	{SEQ_S6E3FC3_AOD_HFP_SET1, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET1) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA2) },
	{SEQ_S6E3FC3_AOD_HFP_SET2, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET2) },
	{SEQ_S6E3FC3_AOD_HFP_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_GPARA3) },
	{SEQ_S6E3FC3_AOD_HFP_SET3, ARRAY_SIZE(SEQ_S6E3FC3_AOD_HFP_SET3) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_OFF_04[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_SWIRE_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_SWIRE_GPARA) },
	{SEQ_S6E3FC3_SWIRE_NO_PULSE, ARRAY_SIZE(SEQ_S6E3FC3_SWIRE_NO_PULSE) },
	{SEQ_S6E3FC3_NORMAL_HFP_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_GPARA1) },
	{SEQ_S6E3FC3_NORMAL_HFP_SET1, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_SET1) },
	{SEQ_S6E3FC3_NORMAL_HFP_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_GPARA2) },
	{SEQ_S6E3FC3_NORMAL_HFP_SET2, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_SET2) },
	{SEQ_S6E3FC3_NORMAL_HFP_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_GPARA3) },
	{SEQ_S6E3FC3_NORMAL_HFP_SET3, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_HFP_SET3) },
	{SEQ_S6E3FC3_AOD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_AOD_OFF) },
	{SEQ_S6E3FC3_SYNC_CONTROL_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_SYNC_CONTROL_GPARA) },
	{SEQ_S6E3FC3_NORMAL_SYNC_CONTROL_SET, ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_SYNC_CONTROL_SET) },
	{SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF, ARRAY_SIZE(SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

#endif

static unsigned char SEQ_S6E3FC3_FD_ON[] = {
	0xB5,
	0x40, 0x40	/* FD enable */
};

static unsigned char SEQ_S6E3FC3_FD_OFF[] = {
	0xB5,
	0x80, 0x40	/* FD disable */
};

static unsigned char SEQ_S6E3FC3_FD_GPARA[] = {
	0xB0,
	0x00, 0x0A, 0xB5
};

enum {
	ACL_STATUS_OFF,
	ACL_STATUS_08P,
	ACL_STATUS_15P,
	ACL_STATUS_MAX,
};

enum {
	TEMP_ABOVE_MINUS_00_DEGREE,	/* T > 0 */
	TEMP_ABOVE_MINUS_15_DEGREE,	/* -15 < T <= 0 */
	TEMP_BELOW_MINUS_15_DEGREE,	/* T <= -15 */
	TEMP_MAX
};

enum {
	HBM_STATUS_OFF,
	HBM_STATUS_ON,
	HBM_STATUS_MAX
};

enum {
	TRANS_DIMMING_OFF,
	TRANS_DIMMING_ON,
	TRANS_DIMMING_MAX
};


enum {
	ACL_DIMMING_OFF,
	ACL_DIMMING_ON,
	ACL_DIMMING_MAX
};

static unsigned char *HBM_TABLE[TRANS_DIMMING_MAX][HBM_STATUS_MAX] = {
	{SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF, SEQ_S6E3FC3_HBM_ON_DIMMING_OFF},
	{SEQ_S6E3FC3_HBM_OFF, SEQ_S6E3FC3_HBM_ON}
};

static unsigned char *ACL_TABLE[ACL_STATUS_MAX] = {SEQ_S6E3FC3_ACL_OFF, SEQ_S6E3FC3_ACL_08P, SEQ_S6E3FC3_ACL_15P};
static unsigned char *DIM_TABLE[HBM_STATUS_MAX] = {SEQ_S6E3FC3_NORMAL_DIM_SET, SEQ_S6E3FC3_HBM_DIM_SET};
static unsigned char *SYNC_TABLE[HBM_STATUS_MAX] = {SEQ_S6E3FC3_SMOOTH_SYNC_CONTROL_SET, SEQ_S6E3FC3_NORMAL_SYNC_CONTROL_SET};
static unsigned char *PRE_VINT_TABLE[HBM_STATUS_MAX] = {SEQ_S6E3FC3_NORMAL_VINT_PRE_SET, SEQ_S6E3FC3_HBM_VINT_PRE_SET};
static unsigned char *POST_VINT_TABLE[HBM_STATUS_MAX] = {SEQ_S6E3FC3_NORMAL_VINT_POST_SET, SEQ_S6E3FC3_HBM_VINT_POST_SET};


/* platform brightness <-> acl opr and percent */
static unsigned int brightness_opr_table[ACL_STATUS_MAX][EXTEND_BRIGHTNESS + 1] = {
	{
		[0 ... EXTEND_BRIGHTNESS]			= ACL_STATUS_OFF,
	}, {
		[0 ... UI_MAX_BRIGHTNESS]			= ACL_STATUS_15P,
		[UI_MAX_BRIGHTNESS + 1 ... EXTEND_BRIGHTNESS]	= ACL_STATUS_08P
	}
};

/* platform brightness <-> gamma level */
static unsigned int brightness_table_id_00_02[EXTEND_BRIGHTNESS + 1] = {
	2, 3, 4, 5, 7, 8, 10, 12, 13, 15, 17,
	19, 21, 24, 26, 28, 30, 32, 35, 37, 40,
	42, 45, 47, 50, 52, 55, 58, 60, 63, 66,
	69, 71, 74, 77, 80, 83, 86, 89, 92, 95,
	98, 101, 104, 107, 110, 113, 116, 119, 123, 126,
	129, 132, 136, 139, 142, 146, 149, 152, 156, 159,
	162, 166, 169, 173, 176, 180, 183, 187, 190, 194,
	197, 201, 205, 208, 212, 215, 219, 223, 227, 230,
	234, 238, 241, 245, 249, 253, 257, 260, 264, 268,
	272, 276, 280, 283, 287, 291, 295, 299, 303, 307,
	311, 315, 319, 323, 327, 331, 335, 339, 343, 347,
	351, 355, 360, 364, 368, 372, 376, 380, 384, 389,
	393, 397, 401, 405, 410, 414, 418, 422, 427, 431,	// 128 = 173nit = 422
	435, 440, 444, 448, 453, 457, 461, 465, 470, 474,
	478, 483, 487, 491, 496, 500, 504, 509, 513, 518,
	522, 526, 531, 535, 540, 544, 549, 553, 558, 562,
	567, 571, 576, 580, 585, 589, 594, 598, 603, 608,
	612, 617, 621, 626, 631, 635, 640, 644, 649, 654,
	658, 663, 668, 672, 677, 682, 686, 691, 696, 701,
	705, 710, 715, 720, 724, 729, 734, 739, 744, 748,
	753, 758, 763, 768, 772, 777, 782, 787, 792, 797,
	802, 807, 811, 816, 821, 826, 831, 836, 841, 846,
	851, 856, 861, 866, 871, 876, 881, 886, 891, 896,
	901, 906, 911, 916, 921, 926, 931, 936, 941, 946,
	951, 956, 961, 967, 972, 977, 982, 987, 992, 997,
	1002, 1008, 1013, 1018, 1023,						// 255 = 420nit = 1023
	// hbm
	0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30,
	33, 36, 39, 42, 45, 48, 51, 54, 57, 60,
	63, 66, 69, 72, 75, 78, 81, 84, 86, 88,
	90, 92, 94, 96, 98, 100, 102, 104, 106, 108,
	110, 112, 114, 116, 118, 120, 122, 124, 126, 128,
	130, 132, 134, 136, 138, 140, 142, 144, 146, 148,
	150, 152, 154, 156, 158, 160, 162, 164, 166, 168,
	170, 172, 174, 176, 178, 182, 186, 190, 194, 198,
	203, 208, 213, 218, 223, 228, 233, 238, 243, 248,
	253, 258, 263, 268, 273, 278, 283, 288, 293, 298,
	303, 308, 313, 318, 323, 328, 333, 338, 343, 348,
	353, 358, 363, 368, 373, 378, 383, 388, 393, 398,
	403, 408, 413, 418, 423, 428, 433, 438, 443, 448,
	453, 458, 463, 468, 473, 478, 483, 488, 493, 498,
	503, 508, 513, 518, 523, 528, 533, 538, 543, 548,
	553, 558, 563, 568, 573, 578, 583, 589, 595, 601,
	607, 613, 619, 625, 631, 637, 643, 649, 655, 661,
	667, 673, 679, 685, 691, 697, 703, 709, 715, 721,
	727, 733, 739, 745, 751, 757, 763, 769, 775, 781,
	787, 793, 799, 805, 811, 817, 823, 829, 835, 841,
	847, 853, 859, 865, 871, 877, 883, 889, 895, 901,
	907, 913, 919, 925, 931, 937, 943, 949, 955, 961,
	967, 973, 979, 985, 991, 997, 1003, 1009, 1015, 1023,	// 486 = 800nit = 1023
};

/* platform brightness <-> gamma level */
static unsigned int brightness_table_id_03[EXTEND_BRIGHTNESS + 1] = {
	2, 3, 4, 5, 7, 8, 10, 12, 13, 15, 17,
	19, 21, 24, 26, 28, 30, 32, 35, 37, 40,
	42, 45, 47, 50, 52, 55, 58, 60, 63, 66,
	69, 71, 74, 77, 80, 83, 86, 89, 92, 95,
	98, 101, 104, 107, 110, 113, 116, 119, 123, 126,
	129, 132, 136, 139, 142, 146, 149, 152, 156, 159,
	162, 166, 169, 173, 176, 180, 183, 187, 190, 194,
	197, 201, 205, 208, 212, 215, 219, 223, 227, 230,
	234, 238, 241, 245, 249, 253, 257, 260, 264, 268,
	272, 276, 280, 283, 287, 291, 295, 299, 303, 307,
	311, 315, 319, 323, 327, 331, 335, 339, 343, 347,
	351, 355, 360, 364, 368, 372, 376, 380, 384, 389,
	393, 397, 401, 405, 410, 414, 418, 422, 427, 431,	// 128 = 173nit = 422
	435, 440, 444, 448, 453, 457, 461, 465, 470, 474,
	478, 483, 487, 491, 496, 500, 504, 509, 513, 518,
	522, 526, 531, 535, 540, 544, 549, 553, 558, 562,
	567, 571, 576, 580, 585, 589, 594, 598, 603, 608,
	612, 617, 621, 626, 631, 635, 640, 644, 649, 654,
	658, 663, 668, 672, 677, 682, 686, 691, 696, 701,
	705, 710, 715, 720, 724, 729, 734, 739, 744, 748,
	753, 758, 763, 768, 772, 777, 782, 787, 792, 797,
	802, 807, 811, 816, 821, 826, 831, 836, 841, 846,
	851, 856, 861, 866, 871, 876, 881, 886, 891, 896,
	901, 906, 911, 916, 921, 926, 931, 936, 941, 946,
	951, 956, 961, 967, 972, 977, 982, 987, 992, 997,
	1002, 1008, 1013, 1018, 1023,						// 255 = 420nit = 1023
	// hbm
	0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
	22, 24, 26, 28, 30, 32, 34, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
	69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
	79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
	89, 90, 91, 92, 93, 95, 97, 99, 101, 103,
	105, 107, 109, 111, 113, 115, 117, 119, 121, 123,
	125, 127, 129, 131, 133, 135, 137, 139, 141, 143,
	145, 147, 149, 151, 154, 157, 160, 163, 166, 168,
	171, 174, 177, 180, 183, 186, 189, 192, 195, 198,
	201, 204, 207, 210, 213, 216, 219, 222, 225, 228,
	231, 234, 237, 240, 243, 246, 249, 252, 255, 258,
	261, 264, 267, 270, 273, 276, 279, 282, 285, 288,
	291, 294, 297, 300, 303, 306, 309, 312, 315, 318,
	321, 324, 327, 330, 333, 336, 339, 342, 345, 348,
	351, 354, 357, 360, 363, 366, 369, 372, 375, 378,
	381, 384, 387, 390, 393, 396, 399, 402, 405, 408,
	411, 414, 417, 420, 423, 426, 429, 432, 435, 438,
	441, 444, 447, 450, 453, 456, 459, 462, 465, 468,
	471, 474, 477, 480, 483, 486, 489, 492, 495, 498,
	501, 504, 507, 510, 513, 516, 519, 522, 525, 528,	// 486 = 800nit = 1023
};

static unsigned char aor_table[EXTEND_BRIGHTNESS + 1][4] = {
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },
	{ 0x63, 0x00, 0x00, 0x18, },		// normal max 255

	{ 0x63, 0x01, 0x01, 0x90, },
	{ 0x63, 0x01, 0x01, 0x8B, },
	{ 0x63, 0x01, 0x01, 0x86, },
	{ 0x63, 0x01, 0x01, 0x81, },
	{ 0x63, 0x01, 0x01, 0x7C, },
	{ 0x63, 0x01, 0x01, 0x77, },
	{ 0x63, 0x01, 0x01, 0x72, },
	{ 0x63, 0x01, 0x01, 0x6D, },
	{ 0x63, 0x01, 0x01, 0x68, },
	{ 0x63, 0x01, 0x01, 0x63, },
	{ 0x63, 0x01, 0x01, 0x5E, },
	{ 0x63, 0x01, 0x01, 0x59, },
	{ 0x63, 0x01, 0x01, 0x54, },
	{ 0x63, 0x01, 0x01, 0x4F, },
	{ 0x63, 0x01, 0x01, 0x4A, },
	{ 0x63, 0x01, 0x01, 0x45, },
	{ 0x63, 0x01, 0x01, 0x40, },
	{ 0x63, 0x01, 0x01, 0x3B, },
	{ 0x63, 0x01, 0x01, 0x36, },
	{ 0x63, 0x01, 0x01, 0x31, },
	{ 0x63, 0x01, 0x01, 0x2C, },
	{ 0x63, 0x01, 0x01, 0x27, },
	{ 0x63, 0x01, 0x01, 0x22, },
	{ 0x63, 0x01, 0x01, 0x1D, },
	{ 0x63, 0x01, 0x01, 0x18, },
	{ 0x63, 0x01, 0x01, 0x13, },
	{ 0x63, 0x01, 0x01, 0x0E, },
	{ 0x63, 0x01, 0x01, 0x09, },
	{ 0x63, 0x01, 0x01, 0x04, },
	{ 0x63, 0x01, 0x00, 0xFF, },
	{ 0x63, 0x01, 0x00, 0xFA, },
	{ 0x63, 0x01, 0x00, 0xF5, },
	{ 0x63, 0x01, 0x00, 0xF0, },
	{ 0x63, 0x01, 0x00, 0xEB, },
	{ 0x63, 0x01, 0x00, 0xE6, },
	{ 0x63, 0x01, 0x00, 0xE1, },
	{ 0x63, 0x01, 0x00, 0xDC, },
	{ 0x63, 0x01, 0x00, 0xD7, },
	{ 0x63, 0x01, 0x00, 0xD2, },
	{ 0x63, 0x01, 0x00, 0xCD, },
	{ 0x63, 0x01, 0x00, 0xC8, },
	{ 0x63, 0x01, 0x00, 0xC3, },
	{ 0x63, 0x01, 0x00, 0xBE, },
	{ 0x63, 0x01, 0x00, 0xB9, },
	{ 0x63, 0x01, 0x00, 0xB4, },
	{ 0x63, 0x01, 0x00, 0xAF, },
	{ 0x63, 0x01, 0x00, 0xAA, },
	{ 0x63, 0x01, 0x00, 0xA5, },
	{ 0x63, 0x01, 0x00, 0xA0, },
	{ 0x63, 0x01, 0x00, 0x9B, },
	{ 0x63, 0x01, 0x00, 0x96, },
	{ 0x63, 0x01, 0x00, 0x91, },
	{ 0x63, 0x01, 0x00, 0x8C, },
	{ 0x63, 0x01, 0x00, 0x87, },
	{ 0x63, 0x01, 0x00, 0x82, },
	{ 0x63, 0x01, 0x00, 0x7D, },
	{ 0x63, 0x01, 0x00, 0x78, },
	{ 0x63, 0x01, 0x00, 0x73, },
	{ 0x63, 0x01, 0x00, 0x6E, },
	{ 0x63, 0x01, 0x00, 0x69, },
	{ 0x63, 0x01, 0x00, 0x64, },
	{ 0x63, 0x01, 0x00, 0x5F, },
	{ 0x63, 0x01, 0x00, 0x5A, },
	{ 0x63, 0x01, 0x00, 0x55, },
	{ 0x63, 0x01, 0x00, 0x50, },
	{ 0x63, 0x01, 0x00, 0x4B, },
	{ 0x63, 0x01, 0x00, 0x46, },
	{ 0x63, 0x01, 0x00, 0x41, },
	{ 0x63, 0x01, 0x00, 0x3C, },
	{ 0x63, 0x01, 0x00, 0x37, },
	{ 0x63, 0x01, 0x00, 0x32, },
	{ 0x63, 0x01, 0x00, 0x2D, },
	{ 0x63, 0x01, 0x00, 0x28, },
	{ 0x63, 0x01, 0x00, 0x23, },
	{ 0x63, 0x01, 0x00, 0x1E, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },
	{ 0x63, 0x01, 0x00, 0x18, },		// hbm max 486
};

static struct lcd_seq_info LCD_SEQ_INIT_00_02[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0), 0, },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC), 0, },
	{SEQ_S6E3FC3_GLOBAL_PARA_SET, ARRAY_SIZE(SEQ_S6E3FC3_GLOBAL_PARA_SET), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
#if defined(CONFIG_SEC_FACTORY)
	{SEQ_S6E3FC3_FD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FD_GPARA), 0, },
	{SEQ_S6E3FC3_FD_ON, ARRAY_SIZE(SEQ_S6E3FC3_FD_ON), 0, },
#endif
	{SEQ_S6E3FC3_CASET, ARRAY_SIZE(SEQ_S6E3FC3_CASET), 0, },
	{SEQ_S6E3FC3_PASET, ARRAY_SIZE(SEQ_S6E3FC3_PASET), 0, },
#if !defined(CONFIG_SMCDSD_DYNAMIC_MIPI)
	{SEQ_S6E3FC3_FFC1_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC1_GPARA), 0, },
	{SEQ_S6E3FC3_FFC1_SET, ARRAY_SIZE(SEQ_S6E3FC3_FFC1_SET), 0, },
	{SEQ_S6E3FC3_FFC2_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC2_GPARA), 0, },
	{SEQ_S6E3FC3_FFC2_SET, ARRAY_SIZE(SEQ_S6E3FC3_FFC2_SET), 0, },
#endif
	{SEQ_S6E3FC3_ERR_FG_ENABLE, ARRAY_SIZE(SEQ_S6E3FC3_ERR_FG_ENABLE), 0, },
	{SEQ_S6E3FC3_ERR_FG_SET, ARRAY_SIZE(SEQ_S6E3FC3_ERR_FG_SET), 0, },
	{SEQ_S6E3FC3_PCD, ARRAY_SIZE(SEQ_S6E3FC3_PCD), 0, },
	{SEQ_S6E3FC3_ACL_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_ACL_GPARA), 0, },
	{SEQ_S6E3FC3_ACL_DEFAULT, ARRAY_SIZE(SEQ_S6E3FC3_ACL_DEFAULT), 0, },
	{SEQ_S6E3FC3_FREQ_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_GPARA), 0, },
	{SEQ_S6E3FC3_FREQ_SET, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_SET), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0), 0, },
	{SEQ_S6E3FC3_TE_ON, ARRAY_SIZE(SEQ_S6E3FC3_TE_ON), 0, },
};

static struct lcd_seq_info LCD_SEQ_INIT_03[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0), 0, },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC), 0, },
	{SEQ_S6E3FC3_GLOBAL_PARA_SET, ARRAY_SIZE(SEQ_S6E3FC3_GLOBAL_PARA_SET), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
#if defined(CONFIG_SEC_FACTORY)
	{SEQ_S6E3FC3_FD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FD_GPARA), 0, },
	{SEQ_S6E3FC3_FD_ON, ARRAY_SIZE(SEQ_S6E3FC3_FD_ON), 0, },
#endif
	{SEQ_S6E3FC3_CASET, ARRAY_SIZE(SEQ_S6E3FC3_CASET), 0, },
	{SEQ_S6E3FC3_PASET, ARRAY_SIZE(SEQ_S6E3FC3_PASET), 0, },
#if !defined(CONFIG_SMCDSD_DYNAMIC_MIPI)
	{SEQ_S6E3FC3_FFC1_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC1_GPARA), 0, },
	{SEQ_S6E3FC3_FFC1_SET, ARRAY_SIZE(SEQ_S6E3FC3_FFC1_SET), 0, },
	{SEQ_S6E3FC3_FFC2_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC2_GPARA), 0, },
	{SEQ_S6E3FC3_FFC2_SET, ARRAY_SIZE(SEQ_S6E3FC3_FFC2_SET), 0, },
#endif
	{SEQ_S6E3FC3_ERR_FG_ENABLE, ARRAY_SIZE(SEQ_S6E3FC3_ERR_FG_ENABLE), 0, },
	{SEQ_S6E3FC3_ERR_FG_SET, ARRAY_SIZE(SEQ_S6E3FC3_ERR_FG_SET), 0, },
	{SEQ_S6E3FC3_PCD, ARRAY_SIZE(SEQ_S6E3FC3_PCD), 0, },
	{SEQ_S6E3FC3_ACL_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_ACL_GPARA), 0, },
	{SEQ_S6E3FC3_ACL_DEFAULT, ARRAY_SIZE(SEQ_S6E3FC3_ACL_DEFAULT), 0, },
	{SEQ_S6E3FC3_FREQ_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_GPARA), 0, },
	{SEQ_S6E3FC3_FREQ_SET, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_SET), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0), 0, },
	{SEQ_S6E3FC3_TE_ON, ARRAY_SIZE(SEQ_S6E3FC3_TE_ON), 0, },
};

#endif /* __S6E3FC3_PARAM_H__ */
