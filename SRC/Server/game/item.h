//Search

	public:
		void SetSIGVnum(DWORD dwSIG)
		{
			m_dwSIGVnum = dwSIG;


//Add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	public:
		void 		AddPremiumPrivateShop(int iPos, DWORD dwShopId);
		void 		SetPremiumPrivateShopVid(DWORD dwVid) { m_dwShopId = dwVid; }
		DWORD 		GetPremiumPrivateShopVid() { return m_dwShopId; }
		void		SetPremiumPrivateShopPrice(DWORD dwPrice) { m_dwPrice = dwPrice; }
		const DWORD		GetPremiumPrivateShopPrice() { return m_dwPrice; }
		void 		SetOwnerPID(DWORD dwVid) { m_dwOwnerPID = dwVid; }
		DWORD	GetOwnerPID() { return m_dwOwnerPID; }
		void		SetOwnerName(const char* szName) { strlcpy(m_szOwnerName, szName, sizeof(m_szOwnerName)); }
		const char*	GetOwnerName() { return m_szOwnerName; }
		void 		DelayedSaveFlush();

	protected:
		DWORD		m_dwShopId;
		DWORD		m_dwPrice;
		DWORD		m_dwOwnerPID;
		char			m_szOwnerName[CHARACTER_NAME_MAX_LEN + 1];
#endif
