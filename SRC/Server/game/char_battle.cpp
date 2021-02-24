//Search

	CShopManager::instance().StopShopping(this);
	CloseMyShop();
	CloseSafebox();

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	ClosePremiumPrivateShop();
#endif

