//Search

	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	Set(HEADER_CG_PREMIUM_PRIVATE_SHOP, sizeof(TPacketCGPremiumPrivateShopCheck), "PremiumPrivateShop", true);
	Set(HEADER_CG_PREMIUM_PRIVATE_SHOP_ITEM_MOVE, sizeof(TPacketCGItemMove), "PremiumPrivateShopItemMove", true);
#endif

