//Search

		BYTE		m_bWindowMode;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	public:
		bool	AddPrivShop(DWORD dwPos, LPITEM pkItem, LPSHOP pShop = NULL, LPCHARACTER ch = NULL, DWORD price = 0, DWORD dwShopVID = 0);
		LPITEM	RemovePrivShop(DWORD dwPos);
		bool	MoveItemPremiumPrivateShop(BYTE bCell, BYTE bDestCell, BYTE count, LPSHOP pShop, LPCHARACTER ch);
#endif
