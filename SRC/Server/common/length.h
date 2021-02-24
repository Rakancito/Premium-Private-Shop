//Search

enum EWindows
{
	RESERVED_WINDOW,
	INVENTORY,
	EQUIPMENT,
	SAFEBOX,
	MALL,
	DRAGON_SOUL_INVENTORY,
	BELT_INVENTORY,

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP	
	PRIVATE_SHOP,
#endif

//Search

	bool IsValidItemPosition() const
	{
		...
		case SAFEBOX:
		case MALL:

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		case PRIVATE_SHOP:
#endif

