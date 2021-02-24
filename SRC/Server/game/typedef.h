//Search

class CParty;
#ifdef USE_DEBUG_PTR
typedef DebugPtr<CParty> LPPARTY;
#else
typedef CParty* LPPARTY;
#endif


//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
class CShop;
typedef class CShop * LPSHOP;

class CPremiumPrivateShop;
#ifdef USE_DEBUG_PTR
typedef DebugPtr<CPremiumPrivateShop> LPOFFSHOP;
#else
typedef CPremiumPrivateShop * LPOFFSHOP;
#endif
#endif


//Search

	ENTITY_CHARACTER,
	ENTITY_ITEM,
	ENTITY_OBJECT,


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	ENTITY_SHOP,
#endif
