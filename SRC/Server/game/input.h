//Search

void		SafeboxItemMove(LPCHARACTER ch, const char * data);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		void		PremiumPrivateShop(LPCHARACTER ch, const char * c_pData);
		void		PremiumPrivateShopItemMove(LPCHARACTER ch, const char * data);
#endif

//Search

void		MallLoad(LPDESC d, const char * c_pData);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	void		PremiumPrivateShopLoad(LPDESC d, const char * c_pData);
#endif
