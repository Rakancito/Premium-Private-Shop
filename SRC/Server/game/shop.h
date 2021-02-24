//Search

			LPITEM	pkItem;
			int		itemid;	

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			TShopItemTable	tItem;
#endif

//Search 

			}
		} SHOP_ITEM;


//add before

#ifdef ENABLE_PREMIUM_PRIVATESHOP
				memset(&tItem, 0, sizeof(tItem))
#endif


//Search

		void SetShopItems(TShopItemTable * pTable, BYTE bItemCount);

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		void SetShopItems(TShopItemTable * pTable, BYTE bItemCount, DWORD dwShopVID = 0);
#else
		void SetShopItems(TShopItemTable * pTable, BYTE bItemCount);
#endif

//Search

		LPCHARACTER			m_pkPC;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	public:
		void	SetPremiumPrivateShop(bool bIsPremiumPrivateShop) { m_bIsPremiumPrivateShop = bIsPremiumPrivateShop; }
		void	SetPremiumPrivateShopItem(LPITEM pkItem);
		void	RemovePremiumPrivateShopItem(DWORD dwPos);
		void	AddPremiumPrivateShopItem(DWORD dwPos, BYTE bInvenType, DWORD dwSourcePos, DWORD dwPrices, DWORD dwShopVid, LPCHARACTER ch);
		std::vector<SHOP_ITEM>& GetItemVector() { return m_itemVector; }
		void	RemoveGuests(LPCHARACTER except);
		bool	IsValidPosition(DWORD dwPos);
		int	GetItemCount();
	protected:
		bool m_bIsPremiumPrivateShop;
#endif

