//Search

		bool SendMallCheckoutPacket(BYTE byMallPos, TItemPos InventoryPos);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		bool SendPremiumPrivateCheckoutGoldOutPacket();
		bool SendPremiumPrivateShopCheckoutPacket(BYTE bySafeBoxPos, TItemPos InventoryPos);
		bool SendPremiumPrivateShopCheckinPacket(TItemPos InventoryPos, BYTE bySafeBoxPos, DWORD dwPrice);
		bool SendPremiumPrivateShopItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, BYTE byCount);
		bool RecPremiumPrivateShop();
#endif

//Search

		void __PlayMallItemDropSound(UINT uSlotPos);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		void __PlayPremiumPrivateShopItemDropSound(UINT uSlotPos);
#endif


//Search

			RefreshMallWindow = (1 << 16),

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			RefreshPremiumPrivateShopWindow = (1 << 17),
#endif


//Search

		void __RefreshMallWindow();

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		void __RefreshPremiumPrivateShopWindow();
#endif

//Search

		bool RecvSafeBoxMoneyChangePacket();

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		// Premium Private Shop
		bool RecvPremiumPrivateShopOpenPacket();
		bool RecvPremiumPrivateShopItemSetPacket();
		bool RecvPremiumPrivateShopItemDelPacket();
#endif

//search 

		bool m_isRefreshMallWnd;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		bool m_isRefreshPremiumPrivateShopWnd;
#endif
