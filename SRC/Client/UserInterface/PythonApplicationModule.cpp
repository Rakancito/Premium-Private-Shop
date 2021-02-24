//Go to end of this file and before the last } add

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	PyModule_AddIntConstant(poModule, "ENABLE_PREMIUM_PRIVATE_SHOP", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PREMIUM_PRIVATE_SHOP", 0);
#endif