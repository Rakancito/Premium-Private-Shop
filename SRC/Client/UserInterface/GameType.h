//Search

	SLOT_TYPE_DRAGON_SOUL_INVENTORY,

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	SLOT_TYPE_PREMIUM_PRIVATE_SHOP,
#endif

//Search

	WINDOW_TYPE_MAX,
};

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	PRIVATE_SHOP,
#endif

//Search

typedef struct packet_item
{
    DWORD       vnum;
    BYTE        count;
	DWORD		flags;
	DWORD		anti_flags;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	DWORD		dwPrice;
#endif