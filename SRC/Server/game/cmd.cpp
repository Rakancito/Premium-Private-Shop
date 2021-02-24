//Search

ACMD(do_mall_password);
ACMD(do_mall_close);

//add after
#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
ACMD(do_premium_private_shop_password);
ACMD(do_premium_private_shop_close);
ACMD(do_click_premium_private_shop);
#endif

//Search

	{ "mall_passwor",	do_inputall,		0,			POS_DEAD,	GM_PLAYER	},
	{ "mall_password",	do_mall_password,	0,			POS_DEAD,	GM_PLAYER	},
	{ "mall_close",	do_mall_close,		0,			POS_DEAD,	GM_PLAYER	},

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	{ "premium_private_shop_passwor",	do_inputall,		0,			POS_DEAD,	GM_PLAYER	},
	{ "premium_private_shop_password",	do_premium_private_shop_password,	0,			POS_DEAD,	GM_PLAYER	},
	{ "premium_private_shop_close",	do_premium_private_shop_close,		0,			POS_DEAD,	GM_PLAYER	},
	{ "click_premium_private_shop",		do_click_premium_private_shop,			0,			POS_DEAD,	GM_IMPLEMENTOR	},
#endif

