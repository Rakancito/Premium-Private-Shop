//Search

public:
	typedef std::map<DWORD, CShop *> TShopMap;

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	typedef std::map<DWORD, CPremiumPrivateShop*> TOfflinePrivateShopMap;
#endif

//Search

	void	DestroyPCShop(LPCHARACTER ch);

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	void	CreatePremiumPrivateShop(LPCHARACTER ch, DWORD dwNPCVnum, const char* szSign, DWORD dwTime, TShopItemTable * pTable, BYTE bItemCount);
	LPOFFSHOP	FindPremiumPrivateShop(DWORD dwShopVid);
	LPOFFSHOP	FindPremiumPrivateShopByShopVID(DWORD dwVid);
	LPOFFSHOP	FindPremiumPrivateShopByPlayerID(DWORD dwVid);
	void	CheckPremiumPrivateShop();
	void	CheckPremiumPrivateShop();
	void	DestroyPremiumPrivateShop(DWORD dwShopVid);
	void	BuildPremiumPrivateShop();
	void	StartPremiumPrivateShop(LPCHARACTER ch, DWORD dwVid);
	DWORD	GetPremiumPrivateShopCount(DWORD dwVid);
	void	SetPremiumPrivateShops(LPOFFSHOP pkPremiumPrivateShops[], BYTE bCount, DWORD dwVid);
	void	AddBankPremiumPrivateShop(LPSHOP pkShop, long long dwPrices);
#endif

//Search

	bool	ReadShopTableEx(const char* stFileName);

//Add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	TOfflinePrivateShopMap m_map_pkPrivateOfflineShop;
#endif

//Search the last 

};

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
public:
	LPEVENT m_pkShopEvent;

	EVENTINFO(shop_event_info)
	{
		DWORD empty;
	};
#endif