//Search

		BOOL GetMallItemDataPtr(DWORD dwSlotIndex, TItemData ** ppInstance);
		BOOL GetSlotMallItemID(DWORD dwSlotIndex, DWORD * pdwItemID);
		DWORD GetMallSize();

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		void OpenPremiumPrivateShop(int iSize);
		void SetPremiumPrivateShopItemData(DWORD dwSlotIndex, const TItemData & rItemData);
		void DelPremiumPrivateShopItemData(DWORD dwSlotIndex);
		BOOL GetPremiumPrivateShopItemDataPtr(DWORD dwSlotIndex, TItemData** ppInstance);
		BOOL GetSlotPremiumPrivateShopItemID(DWORD dwSlotIndex, DWORD* pdwItemID);
		DWORD GetPremiumPrivateShopSize();

		void SetPremiumPrivateShopMoney(DWORD m_dwMoney);
		DWORD GetPremiumPrivateShopMoney();
#endif

//Search

		TItemInstanceVector m_ItemInstanceVector;
		TItemInstanceVector m_MallItemInstanceVector;
		DWORD m_dwMoney;

//add after


#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		TItemInstanceVector m_PremiumPrivateShopItemInstanceVector;
		DWORD m_dwMoneyShop;
#endif