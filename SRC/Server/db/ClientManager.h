//Search

		DWORD	dwHandle;
		DWORD	account_id;
		DWORD	player_id;
		BYTE	account_index;
		char	login[LOGIN_MAX_LEN + 1];
		char	safebox_password[SAFEBOX_PASSWORD_MAX_LEN + 1];
		char	ip[MAX_HOST_LENGTH + 1];

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		bool	bIsPrivateShop;
#endif


//Search

void		QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket *, bool bMall);

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	void		QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket *, bool bMall, bool bPrivShop = false);
#else
	void		QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket *, bool bMall);
#endif
