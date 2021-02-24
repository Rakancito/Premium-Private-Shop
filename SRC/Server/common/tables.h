//Search

HEADER_GD_REQUEST_CHANNELSTATUS	= 140,

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	HEADER_GD_PREMIUM_PRIVATE_SHOP_LOAD		= 150,
	HEADER_GD_PREMIUM_PRIVATE_SHOP_SAVE		= 151,
#endif

//Search

HEADER_DG_RESPOND_CHANNELSTATUS		= 181,

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	HEADER_DG_PREMIUM_PRIVATE_SHOP_LOAD		= 185,
#endif

//Search

typedef struct SPlayerItem
{
	...
}
	DWORD	owner;
} TPlayerItem;

//add before 'DWORD owner'

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	DWORD price;
	DWORD shop_id;
#endif


//Search

typedef struct SSafeboxLoadPacket
{
	DWORD	dwID;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	DWORD	dwPlayerID;
#endif
