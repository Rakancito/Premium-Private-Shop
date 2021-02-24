//Search

void CClientManager::QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket * packet, bool bMall)

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CClientManager::QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket * packet, bool bMall, bool bPrivShop)
#else
void CClientManager::QUERY_SAFEBOX_LOAD(CPeer * pkPeer, DWORD dwHandle, TSafeboxLoadPacket * packet, bool bMall)
#endif


//In the before function search

pi->ip[0] = bMall ? 1 : 0;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if(bPrivShop)
	{
		pi->bIsPrivateShop = true;
		pi->player_id = packet->dwPlayerID;
	}
	else
	{
		pi->bIsPrivateShop = false;
		pi->player_id = 0;
	}
#endif

//Search

void CClientManager::RESULT_SAFEBOX_LOAD(CPeer * pkPeer, SQLMsg * msg)
{
	CQueryInfo * qi = (CQueryInfo *) msg->pvUserData;
	ClientHandleInfo * pi = (ClientHandleInfo *) qi->pvData;
	DWORD dwHandle = pi->dwHandle;

	if (pi->account_index == 0)
	{

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		if(pi->bIsPrivateShop)
		{
			char szSafeboxPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
			strlcpy(szSafeboxPassword, pi->safebox_password, sizeof(szSafeboxPassword));

			TSafeboxTable * pSafebox = new TSafeboxTable;
			memset(pSafebox, 0, sizeof(TSafeboxTable));

			SQLResult * res = msg->Get();

			if (res->uiNumRows == 0)
			{
				if (strcmp("000000", szSafeboxPassword))
				{
					pkPeer->EncodeHeader(HEADER_DG_SAFEBOX_WRONG_PASSWORD, dwHandle, 0);
					delete pi;
					return;
				}
			}
			else
			{
				MYSQL_ROW row = mysql_fetch_row(res->pSQLResult);
				if (((!row[2] || !*row[2]) && strcmp("000000", szSafeboxPassword)) ||
				((row[2] && *row[2]) && strcmp(row[2], szSafeboxPassword)))
				{
					pkPeer->EncodeHeader(HEADER_DG_SAFEBOX_WRONG_PASSWORD, dwHandle, 0);
					delete pi;
					return;
				}

				if (!row[0])
					pSafebox->dwID = 0;
				else
					str_to_number(pSafebox->dwID, row[0]);

				if (!row[1])
					pSafebox->bSize = 0;
				else
					str_to_number(pSafebox->bSize, row[1]);

				sys_log(0, "PRIVATE_SHOP id[%d] size[%d]", pSafebox->dwID, pSafebox->bSize);
			}

			if (0 == pSafebox->dwID)
				pSafebox->dwID = pi->account_id;

			pi->pSafebox = pSafebox;

			char szQuery[1024];
			snprintf(szQuery, sizeof(szQuery), "SELECT id, window+0, pos, count, vnum, socket0, socket1, socket2, attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3, attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6, applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4, applytype5, applyvalue5, applytype6, applyvalue6, applytype7, applyvalue7"
#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					", transmutation, price, shop_id "
#else
#ifdef ENABLE_TRANSMUTATION
					", transmutation "
#else
					" "
#endif
#endif
			"FROM item%s WHERE owner_id=%d AND window='PRIVATE_SHOP'", GetTablePostfix(), pi->player_id);
			
			pi->account_index = 1;

			CDBManager::instance().ReturnQuery(szQuery, QID_SAFEBOX_LOAD, pkPeer->GetHandle(), pi);

		}
		else
		{
#endif
/*
Check if you have my SQL if you don't have you can search in "SELECT id, window+0, and with SQL Syntax you will need add after all syntax
I will give the part and my example.
Ok if you have the transmutation system and if you have like "changelook" just change transmutation for changelook :)
*/
		if (0 == pSafebox->dwID)
			pSafebox->dwID = pi->account_id;

		pi->pSafebox = pSafebox;

		char szQuery[512];
		snprintf(szQuery, sizeof(szQuery), "SELECT id, window+0, pos, count, vnum, socket0, socket1, socket2, attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3, attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6, applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4, applytype5, applyvalue5, applytype6, applyvalue6, applytype7, applyvalue7"
//Add

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					", price, shop_id "
#else
					" "
#endif


//The example for my SQL Syntax it's

		snprintf(szQuery, sizeof(szQuery), "SELECT id, window+0, pos, count, vnum, socket0, socket1, socket2, attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3, attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6, applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4, applytype5, applyvalue5, applytype6, applyvalue6, applytype7, applyvalue7"
#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					", transmutation, price, shop_id "
#else
#ifdef ENABLE_TRANSMUTATION
					", transmutation "
#else
					" "
#endif
#endif
		"FROM item%s WHERE owner_id=%d AND window='%s'", GetTablePostfix(), pi->account_id, pi->ip[0] == 0 ? "SAFEBOX" : "MALL");


//Search

CDBManager::instance().ReturnQuery(szQuery, QID_SAFEBOX_LOAD, pkPeer->GetHandle(), pi);


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		}
#endif

//Search

		CreateItemTableFromRes(msg->Get()->pSQLResult, &s_items, pi->account_id);

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		if(pi->bIsPrivateShop)
			CreateItemTableFromRes(msg->Get()->pSQLResult, &s_items, pi->player_id);
		else
			CreateItemTableFromRes(msg->Get()->pSQLResult, &s_items, pi->account_id);
#else
		CreateItemTableFromRes(msg->Get()->pSQLResult, &s_items, pi->account_id);
#endif


//Search

						snprintf(szQuery, sizeof(szQuery),
								"INSERT INTO item%s (id, owner_id, window, pos, vnum, count, socket0, socket1, socket2) "
								"VALUES(%u, %u, '%s', %d, %u, %u, %u, %u, %u)",
								GetTablePostfix(),
								GainItemID(),
								pi->account_id,
								pi->ip[0] == 0 ? "SAFEBOX" : "MALL",
								iPos,
								pItemAward->dwVnum, pItemAward->dwCount, pItemAward->dwSocket0, pItemAward->dwSocket1, dwSocket2);


//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
						if(pi->bIsPrivateShop)
						{
							snprintf(szQuery, sizeof(szQuery),
								"INSERT INTO item%s (id, owner_id, window, pos, vnum, count, socket0, socket1, socket2) "
								"VALUES(%u, %u, '%s', %d, %u, %u, %u, %u, %u)",
								GetTablePostfix(),
								GainItemID(),
								pi->player_id,
								pi->ip[0] == 0 ? "PRIVATE_SHOP" : "PRIVATE_SHOP",
								iPos,
								pItemAward->dwVnum, pItemAward->dwCount, pItemAward->dwSocket0, pItemAward->dwSocket1, dwSocket2);

						}
						else
						{
							snprintf(szQuery, sizeof(szQuery),
								"INSERT INTO item%s (id, owner_id, window, pos, vnum, count, socket0, socket1, socket2) "
								"VALUES(%u, %u, '%s', %d, %u, %u, %u, %u, %u)",
								GetTablePostfix(),
								GainItemID(),
								pi->account_id,
								pi->ip[0] == 0 ? "SAFEBOX" : "MALL",
								iPos,
								pItemAward->dwVnum, pItemAward->dwCount, pItemAward->dwSocket0, pItemAward->dwSocket1, dwSocket2);
						}
#else
						snprintf(szQuery, sizeof(szQuery),
								"INSERT INTO item%s (id, owner_id, window, pos, vnum, count, socket0, socket1, socket2) "
								"VALUES(%u, %u, '%s', %d, %u, %u, %u, %u, %u)",
								GetTablePostfix(),
								GainItemID(),
								pi->account_id,
								pi->ip[0] == 0 ? "SAFEBOX" : "MALL",
								iPos,
								pItemAward->dwVnum, pItemAward->dwCount, pItemAward->dwSocket0, pItemAward->dwSocket1, dwSocket2);
#endif

//Search

					item.id = pmsg->Get()->uiInsertID;
					item.window = pi->ip[0] == 0 ? SAFEBOX : MALL,
					item.pos = iPos;
					item.count = pItemAward->dwCount;
					item.vnum = pItemAward->dwVnum;
					item.alSockets[0] = pItemAward->dwSocket0;
					item.alSockets[1] = pItemAward->dwSocket1;
					item.alSockets[2] = dwSocket2;
					s_items.push_back(item);

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
					if(pi->bIsPrivateShop)
					{
						item.id = pmsg->Get()->uiInsertID;
						item.window = pi->ip[0] == 0 ? PRIVATE_SHOP : PRIVATE_SHOP,
						item.pos = iPos;
						item.count = pItemAward->dwCount;
						item.vnum = pItemAward->dwVnum;
						item.alSockets[0] = pItemAward->dwSocket0;
						item.alSockets[1] = pItemAward->dwSocket1;
						item.alSockets[2] = dwSocket2;
						s_items.push_back(item);
					}
					else
					{
						item.id = pmsg->Get()->uiInsertID;
						item.window = pi->ip[0] == 0 ? SAFEBOX : MALL,
						item.pos = iPos;
						item.count = pItemAward->dwCount;
						item.vnum = pItemAward->dwVnum;
						item.alSockets[0] = pItemAward->dwSocket0;
						item.alSockets[1] = pItemAward->dwSocket1;
						item.alSockets[2] = dwSocket2;
						s_items.push_back(item);
					}
#else
					item.id = pmsg->Get()->uiInsertID;
					item.window = pi->ip[0] == 0 ? SAFEBOX : MALL,
					item.pos = iPos;
					item.count = pItemAward->dwCount;
					item.vnum = pItemAward->dwVnum;
					item.alSockets[0] = pItemAward->dwSocket0;
					item.alSockets[1] = pItemAward->dwSocket1;
					item.alSockets[2] = dwSocket2;
					s_items.push_back(item);
#endif

//Search

		pkPeer->EncodeHeader(pi->ip[0] == 0 ? HEADER_DG_SAFEBOX_LOAD : HEADER_DG_MALL_LOAD, dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		if(pi->bIsPrivateShop)
			pkPeer->EncodeHeader(HEADER_DG_PREMIUM_PRIVATE_SHOP_LOAD, dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());
		else
			pkPeer->EncodeHeader(pi->ip[0] == 0 ? HEADER_DG_SAFEBOX_LOAD : HEADER_DG_MALL_LOAD, dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());			
#else
		pkPeer->EncodeHeader(pi->ip[0] == 0 ? HEADER_DG_SAFEBOX_LOAD : HEADER_DG_MALL_LOAD, dwHandle, sizeof(TSafeboxTable) + sizeof(TPlayerItem) * s_items.size());
#endif


//Search

		char szQuery[QUERY_MAX_LEN];
		snprintf(szQuery, sizeof(szQuery),
			"REPLACE INTO item%s (id, owner_id, window, pos, count, vnum, socket0, socket1, socket2, "
			"attrtype0, attrvalue0,"
			"attrtype1, attrvalue1,"
			"attrtype2, attrvalue2,"
			"attrtype3, attrvalue3,"
			"attrtype4, attrvalue4,"
			"attrtype5, attrvalue5,"
			"attrtype6, attrvalue6,"
			"applytype0, applyvalue0,"
			"applytype1, applyvalue1,"
			"applytype2, applyvalue2,"
			"applytype3, applyvalue3,"
			"applytype4, applyvalue4,"
			"applytype5, applyvalue5,"
			"applytype6, applyvalue6,"

/*
Ok if you have the transmutation system and if you have like "changelook" just change transmutation for changelook :)
*/

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			"applytype7, applyvalue7,"
			"transmutation, price, shop_id)"
#else
#ifdef ENABLE_TRANSMUTATION
			"applytype7, applyvalue7,"
			"transmutation)"
#else
			"applytype7, applyvalue7)"
#endif
#endif

//Search

			"VALUES(%u, %u, %d, %d, %u, %u, %ld, %ld, %ld, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,"

//Add after
//Ok if you have the transmutation system and if you have like "changelook" just change transmutation for changelook :)

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			" %d, %d, %d, %d)",
#else
#ifdef ENABLE_TRANSMUTATION
			" %d, %d)",
#else
			" %d)",
#endif
#endif

//Search

			p->aAttr[10].bType, p->aAttr[10].sValue,
			p->aAttr[11].bType, p->aAttr[11].sValue,
			p->aAttr[12].bType, p->aAttr[12].sValue,
			p->aAttr[13].bType, p->aAttr[13].sValue,

//Add after
//Ok if you have the transmutation system and if you have like "changelook" just change transmutation for changelook :)

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			p->aAttr[14].bType, p->aAttr[14].sValue,
			p->transmutation, p->price, p->shop_id);
#else
#ifdef ENABLE_TRANSMUTATION
			p->aAttr[14].bType, p->aAttr[14].sValue,
			p->transmutation);
#else
			p->aAttr[14].bType, p->aAttr[14].sValue);
#endif
#endif

//Search

			case HEADER_GD_MALL_LOAD:
				QUERY_SAFEBOX_LOAD(peer, dwHandle, (TSafeboxLoadPacket *) data, 1);
				break;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			case HEADER_GD_PREMIUM_PRIVATE_SHOP_LOAD:
				QUERY_SAFEBOX_LOAD(peer, dwHandle, (TSafeboxLoadPacket *) data, 0, 1);
				break;
#endif
	

