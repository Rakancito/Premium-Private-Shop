//Search

	PyModule_AddIntConstant(poModule, "SLOT_TYPE_DRAGON_SOUL_INVENTORY",	SLOT_TYPE_DRAGON_SOUL_INVENTORY);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	PyModule_AddIntConstant(poModule, "SLOT_TYPE_PREMIUM_PRIVATE_SHOP",						SLOT_TYPE_PREMIUM_PRIVATE_SHOP);
#endif

//Search

	PyModule_AddIntConstant(poModule, "GROUND",								GROUND);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	PyModule_AddIntConstant(poModule, "PRIVATE_SHOP",						PRIVATE_SHOP);
#endif