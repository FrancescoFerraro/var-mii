#include <linux/types.h>
#include <include/utils.h>
#include <string.h>
#include <stdio.h>
#include "phy_adin1300.h"
#include "phylib.h"

int adin1300_read_extended(const phy_t * phy, const int phy_reg, __u16 * value) {
	mii_write_reg(phy, ADIN1300_EXT_REG_PTR, phy_reg);
	return mii_read_reg(phy, ADIN1300_EXT_REG_DATA, value);
}

int adin1300_write_extended(const phy_t * phy, const int phy_reg, __u16 value) {
	mii_write_reg(phy, ADIN1300_EXT_REG_PTR, phy_reg);
	return mii_write_reg(phy, ADIN1300_EXT_REG_DATA, value);
}

int adin1300_verify_phy_mode(const phy_t * phy, const char * mode) {
	__u16 value;
	int ret = 0;

	/* read rgmii regsiter */
	adin1300_read_extended(phy, ADIN1300_GE_RGMII_CFG, &value);

	if (!(value & ADIN1300_GE_RGMII_EN)) {
		printf("%s:\tError: ADIN1300_GE_RGMII_EN is disabled\n", __func__);
		ret = -1;
	}

	if (strcmp(mode, "rgmii") == 0) {
		if ((value & ADIN1300_GE_RGMII_TXID_EN)) {
			printf("%s:\tError: GE_RGMII_TX_ID_EN is enabled\n", __func__);
			ret = -1;
		}
		if ((value & ADIN1300_GE_RGMII_RXID_EN)) {
			printf("%s:\tError: GE_RGMII_RX_ID_EN is enabled\n", __func__);
			ret = -1;
		}
	} else if (strcmp(mode, "rgmii-id") == 0) {
		if (!(value & ADIN1300_GE_RGMII_TXID_EN)) {
			printf("%s:\tError: GE_RGMII_TX_ID_EN is disabled\n", __func__);
			ret = -1;
		}
		if (!(value & ADIN1300_GE_RGMII_RXID_EN)) {
			printf("%s:\tError: GE_RGMII_RX_ID_EN is disabled\n", __func__);
			ret = -1;
		}
	} else if (strcmp(mode, "rgmii-txid") == 0) {
		if (!(value & ADIN1300_GE_RGMII_TXID_EN)) {
			printf("%s:\tError: GE_RGMII_TX_ID_EN is disabled\n", __func__);
			ret = -1;
		}
		if ((value & ADIN1300_GE_RGMII_RXID_EN)) {
			printf("%s:\tError: GE_RGMII_RX_ID_EN is enabled\n", __func__);
			ret = -1;
		}
	} else if (strcmp(mode, "rgmii-rxid") == 0) {
		if ((value & ADIN1300_GE_RGMII_TXID_EN)) {
			printf("%s:\tError: GE_RGMII_TX_ID_EN is enabled\n", __func__);
			ret = -1;
		}
		if (!(value & ADIN1300_GE_RGMII_RXID_EN)) {
			printf("%s:\tError: GE_RGMII_RX_ID_EN is disabled\n", __func__);
			ret = -1;
		}
	} else {
		printf("%s:\tError: unknown phy mode '%s'\n", __func__, mode);
		ret = -1;
	}

	if (!ret) {
		printf("%s:\tPASS: RGMII Mode = '%s' \n", __func__, mode);
	} else {
		printf("%s:\tFAIL: RGMII Mode != '%s' \n", __func__, mode);
	}

	return ret;
}
