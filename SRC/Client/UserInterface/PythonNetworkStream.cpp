//Under this

	public:
		CMainPacketHeaderMap()
		{

// add in a some part


#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			Set(HEADER_GC_PREMIUM_PRIVATE_SHOP, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketCGPremiumPrivateShopSize), STATIC_SIZE_PACKET));
			Set(HEADER_GC_PREMIUM_PRIVATE_SHOP_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemSetDelPremiumPrivateShop), STATIC_SIZE_PACKET));			
			Set(HEADER_GC_PREMIUM_PRIVATE_SHOP_DEL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCItemDel), STATIC_SIZE_PACKET));
#endif
