//Search

		void				LoadMall(int iItemCount, TPlayerItem * pItems);
		void				CloseMall();

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		CSafebox *			GetPremiumPrivateShop() const;
		void				ReqPremiumPrivateShopLoad(const char* pszPassword);
		void				LoadPremiumPrivateShop(int iItemCount, TPlayerItem * pItems);
		void				ClosePremiumPrivateShop();
		void				SendPremiumPrivateShopGold();
		int				GetOpenPremiumShopLoadTime() const { return m_iPremiumPrivateShopLoadTime; }
		void				SetOpenPremiumShopLoadTime() { m_iPremiumPrivateShopLoadTime = thecore_pulse(); }
		CSafebox *			m_pkPremiumPrivateShop;
		int				m_iPremiumPrivateShopLoadTime;
#endif


//Search

};

ESex GET_SEX(LPCHARACTER ch);

#endif


//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	public:
		void SetPremiumPrivateShopVid(DWORD dwVid) { m_dwPremiumPrivateShopVid = dwVid; }
		DWORD GetPremiumPrivateShopVid() const { return m_dwPremiumPrivateShopVid; }
		int		GetRenamePulse() const { return m_iRenameTime; }
		void	SetRenamePulse() { m_iRenameTime = thecore_pulse(); }
		void	DelayedSaveFlush();
	protected:
		DWORD m_dwPremiumPrivateShopVid;
		int m_iRenameTime;
#endif
