//Search "Please, if you have TRANSMUTATION like changelook just change transmutation for changelook lol"
//You can search two options if you don't know 

first option:
		for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
		{
			str_to_number(item.aAttr[j].bType, row[cur++]);
			str_to_number(item.aAttr[j].sValue, row[cur++]);
		}
		
#ifdef ENABLE_TRANSMUTATION
		str_to_number(item.transmutation, row[cur++]);
#endif

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		str_to_number(item.price, row[cur++]);
		str_to_number(item.shop_id, row[cur++]);
#endif


//second option:

		item.owner		= dwPID;
	}

	return true;
}

size_t CreatePlayerSaveQuery(char * pszQuery, size_t querySize, TPlayerTable * pkTab)


//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		str_to_number(item.price, row[cur++]);
		str_to_number(item.shop_id, row[cur++]);
#endif

//Search

		/////////////////////////////////////////////
		// 2) DBCache
		/////////////////////////////////////////////
		else
		{
			snprintf(szQuery, sizeof(szQuery),
					"SELECT id,window+0,pos,count,vnum,socket0,socket1,socket2,attrtype0,attrvalue0,attrtype1,attrvalue1,attrtype2,attrvalue2,attrtype3,attrvalue3,attrtype4,attrvalue4,attrtype5,attrvalue5,attrtype6,attrvalue6,applytype0,applyvalue0,applytype1,applyvalue1,applytype2,applyvalue2,applytype3,applyvalue3,applytype4,applyvalue4,applytype5,applyvalue5,applytype6,applyvalue6,applytype7,applyvalue7"


//add after and remember if you have transmutation like changelook you just change for it.

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					", transmutation, price, shop_id "
#else
#ifdef ENABLE_TRANSMUTATION
					", transmutation "
#endif
#endif	

//Search

					"FROM item%s WHERE owner_id=%d AND (window < %d or window = %d)",

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					"FROM item%s WHERE owner_id=%d AND shop_id = 0 AND window != 7 AND (window < %d or window = %d)",
#else
					"FROM item%s WHERE owner_id=%d AND (window < %d or window = %d)",
#endif


//Search

		snprintf(queryStr, sizeof(queryStr),
				"SELECT id,window+0,pos,count,vnum,socket0,socket1,socket2,attrtype0,attrvalue0,attrtype1,attrvalue1,attrtype2,attrvalue2,attrtype3,attrvalue3,attrtype4,attrvalue4,attrtype5,attrvalue5,attrtype6,attrvalue6,applytype0,applyvalue0,applytype1,applyvalue1,applytype2,applyvalue2,applytype3,applyvalue3,applytype4,applyvalue4,applytype5,applyvalue5,applytype6,applyvalue6,applytype7,applyvalue7"


//add after and remember if you have transmutation like changelook you just change for it.

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					", transmutation, price, shop_id "
#else
#ifdef ENABLE_TRANSMUTATION
					", transmutation "
#endif
#endif

//Search

				"FROM item%s WHERE owner_id=%d AND (window < %d or window = %d)",

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
				"FROM item%s WHERE owner_id=%d AND shop_id = 0 AND window != 7 AND (window < %d or window = %d)",
#else
				"FROM item%s WHERE owner_id=%d AND (window < %d or window = %d)",
#endif



