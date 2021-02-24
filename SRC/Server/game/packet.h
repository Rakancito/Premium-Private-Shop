//Search

HEADER_CG_ROULETTE				= 90,

//add after (watch, if you are using 94,95 change for other number)

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	HEADER_CG_PREMIUM_PRIVATE_SHOP			= 94,
	HEADER_CG_PREMIUM_PRIVATE_SHOP_ITEM_MOVE	= 95,
#endif

//and for GC search HEADER_GC_KEY_AGREEMENT_COMPLETED = 0xfa, // and add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	HEADER_GC_PREMIUM_PRIVATE_SHOP			= 138,
	HEADER_GC_PREMIUM_PRIVATE_SHOP_SET		= 139,
	HEADER_GC_PREMIUM_PRIVATE_SHOP_DEL		= 140,
#endif


//Search


#pragma pack()
#endif


//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

enum
{
	SUB_HEADER_PREMIUM_PRIVATE_SHOP_OPEN,
	SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_ADD,
	SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_DEL,
	SUB_HEADER_PREMIUM_PRIVATE_SHOP_MOVE_ITEM,
	SUB_HEADER_PREMIUM_PRIVATE_SHOP_GOLD_DEL,
};

typedef struct packet_premium_private_shop_size
{
	BYTE bHeader;
	BYTE bSubHeader;
	BYTE bSize;
	DWORD dwGold;
	DWORD dwTime;
} TPacketCGPremiumPrivateShopSize;

typedef struct packet_premium_private_shop
{
	BYTE bheader;
	BYTE subheader;
	DWORD	dwPrice;
} TPacketCGPremiumPrivateShop;

typedef struct command_premium_private_shop_check
{
	BYTE	bHeader;
	BYTE	bSubHeader;
	BYTE	bSafePos;
	TItemPos	ItemPos;
	DWORD dwPrice;
} TPacketCGPremiumPrivateShopCheck;


typedef struct packet_item_set_premium_private_shop
{
	BYTE	header;
	TItemPos Cell;
	DWORD	vnum;
	BYTE	count;
	DWORD	flags;
	DWORD	anti_flags;
	bool	highlight;
	long	alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
#ifdef ENABLE_TRANSMUTATION
	DWORD	transmutation; //change for changelook if you have like changelook
#endif
	DWORD	dwPrice;
} TPacketGCItemSetDelPremiumPrivateShop;

#endif
