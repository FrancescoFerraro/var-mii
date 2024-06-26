#ifndef _PHY_ADIN_H
#define _PHY_ADIN_H

#include "phylib.h"

#define ADIN1300_PHY_ID_1               0x283
#define ADIN1300_EXT_REG_PTR            0x10
#define ADIN1300_EXT_REG_DATA           0x11

/* Clock Configuration */
#define ADIN1300_GE_CLK_CFG             0xff1f
#define   ADIN1300_GE_CLK_RCVR_125_EN	BIT(5)

/* RGMII internal delay settings for rx and tx for ADIN1300 */
#define ADIN1300_GE_RGMII_CFG           0xff23
#define   ADIN1300_GE_RGMII_RXID_EN     BIT(2)
#define   ADIN1300_GE_RGMII_TXID_EN     BIT(1)
#define   ADIN1300_GE_RGMII_EN          BIT(0)
#define   ADIN1300_RGMII_1_60_NS        0x0001
#define   ADIN1300_RGMII_1_80_NS        0x0002
#define   ADIN1300_RGMII_2_00_NS        0x0000
#define   ADIN1300_RGMII_2_20_NS        0x0006
#define   ADIN1300_RGMII_2_40_NS        0x0007

int adin1300_verify_phy_mode(const phy_t * phy, const char * mode);
int adin1300_verify_clk_rcvr_125(const phy_t * phy, const int clk_rcvr_125_en);

#endif
