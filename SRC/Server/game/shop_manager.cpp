//Search 

#include "shop.h"

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "offline_privateshop.h"
#include "sectree_manager.h"
#endif

//Search
	if (!(shop = ch->GetShop()))
		return;

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	LPOFFSHOP pkPremiumPrivateShop = FindPremiumPrivateShop(ch->GetPremiumPrivateShopVid());

	if (!(shop = ch->GetShop()) || (pkPremiumPrivateShop && !(shop = pkPremiumPrivateShop->GetShop())))
		return;

	ch->SetPremiumPrivateShopVid(0);

#else
	if (!(shop = ch->GetShop()))
		return;
#endif

//in void CShopManager::Buy(LPCHARACTER ch, BYTE pos) Search

	if (!ch->GetShopOwner())

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (!ch->GetShopOwner() && !ch->GetPremiumPrivateShopVid())
#else
	if (!ch->GetShopOwner())
#endif

//Search

if (DISTANCE_APPROX(ch->GetX() - ch->GetShopOwner()->GetX(), ch->GetY() - ch->GetShopOwner()->GetY()) > 2000)

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (!ch->GetPremiumPrivateShopVid() &&DISTANCE_APPROX(ch->GetX() - ch->GetShopOwner()->GetX(), ch->GetY() - ch->GetShopOwner()->GetY()) > 2000)
#else
	if (DISTANCE_APPROX(ch->GetX() - ch->GetShopOwner()->GetX(), ch->GetY() - ch->GetShopOwner()->GetY()) > 2000)
#endif

//add anywhere on this file

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

void CShopManager::CreatePremiumPrivateShop(LPCHARACTER ch, DWORD dwNPCVnum, const char* szSign, DWORD dwTime, TShopItemTable * pTable, BYTE bItemCount)
{
	LPSECTREE sectree = SECTREE_MANAGER::instance().Get(ch->GetMapIndex(), ch->GetX(), ch->GetY());

	if (!sectree)
		return;

	LPOFFSHOP pkFindShop = FindPremiumPrivateShopByPlayerID(ch->GetPlayerID());

	if(pkFindShop)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "You are with a offline Shop in this moment, maybe you will need Open the panel Edition or close your shop."));
		return;
	}

	LPSHOP pkShop = M2_NEW CShop;
	pkShop->SetPremiumPrivateShop(true);
	pkShop->SetPCShop(ch);
	dwTime += time(nullptr);

	LPOFFSHOP pkPremiumPrivateShop = M2_NEW CPremiumPrivateShop(pkShop, dwTime, dwNPCVnum);
	if(!pkPremiumPrivateShop)
	{
		sys_err("Fail to create Premium Private Shop: %s", ch->GetName());
		return;
	}

	pkPremiumPrivateShop->SetMapIndex(ch->GetMapIndex());
	pkPremiumPrivateShop->SetXYZ(ch->GetXYZ());
	pkPremiumPrivateShop->SetOwnerName(ch->GetName());
	pkPremiumPrivateShop->SetSign(szSign);
	pkPremiumPrivateShop->SetPlayerID(ch->GetPlayerID());
	sectree->InsertEntity(pkPremiumPrivateShop);
	pkPremiumPrivateShop->UpdateSectree();
	
	DWORD dwShopVID = 0;
	std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_id FROM player.player_shop WHERE status = 0 and owner_id = %d", ch->GetPlayerID()));
	if (pMsg->Get()->uiNumRows > 0)
	{
		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
		str_to_number(dwShopVID, row[0]);
		std::auto_ptr<SQLMsg> pMsg2(DBManager::instance().DirectQuery("UPDATE player.player_shop SET map_index=%d, x=%d, y=%d, z=%d, date_close=FROM_UNIXTIME(%d), race=%d, count=%d, name='%s', status=1 WHERE shop_id=%d", ch->GetMapIndex(), ch->GetX(), ch->GetY(), ch->GetZ(), dwTime, dwNPCVnum, bItemCount, szSign, dwShopVID));
		if(pMsg2->Get()->uiAffectedRows == 0)
		{
			sys_err("Update Bank Fail Premium Private Shop %d", dwShopVID);
		}
	}
	else
	{
		std::auto_ptr<SQLMsg> pMsg2(DBManager::instance().DirectQuery("INSERT INTO player.player_shop SET owner_id=%d, owner_name='%s', map_index=%d, x=%d, y=%d, z=%d, date_close=FROM_UNIXTIME(%d), race=%d, count=%d, name='%s'", 
		ch->GetPlayerID(), ch->GetName(), ch->GetMapIndex(), ch->GetX(), ch->GetY(), ch->GetZ(), dwTime, dwNPCVnum, bItemCount, szSign));
		SQLResult * pRes2 = pMsg2->Get();

		dwShopVID = pRes2->uiInsertID;
	}


	pkPremiumPrivateShop->SetShopVid(dwShopVID);

	ch->SaveAndFlush();

	pkShop->SetShopItems(pTable, bItemCount, dwShopVID);
	m_map_pkPrivateOfflineShop.insert(TOfflinePrivateShopMap::value_type(pkPremiumPrivateShop->GetShopVid(), pkPremiumPrivateShop));
}

LPOFFSHOP CShopManager::FindPremiumPrivateShop(DWORD dwShopVid)
{
	for (auto& it : m_map_pkPrivateOfflineShop)
		if (it.second->GetShopVid() == dwShopVid)
			return it.second;

	return NULL;
}

LPOFFSHOP CShopManager::FindPremiumPrivateShopByShopVID(DWORD dwVid)
{
	for (auto& it : m_map_pkPrivateOfflineShop)
		if (it.second->GetVid() == dwVid)
			return it.second;

	return NULL;
}

LPOFFSHOP CShopManager::FindPremiumPrivateShopByPlayerID(DWORD dwVid)
{
	for (auto& it : m_map_pkPrivateOfflineShop)
		if (it.second->GetPlayerID() == dwVid)
			return it.second;
	return NULL;
}

void CShopManager::CheckPremiumPrivateShop()
{
	for (auto& it : m_map_pkPrivateOfflineShop)
	{
		if (it.second->GetTime() <= get_global_time())
		{
			DestroyPremiumPrivateShop(it.second->GetShopVid());
		}
	}
}

EVENTFUNC(shop_event)
{
	CShopManager::instance().CheckPremiumPrivateShop();
	return passes_per_sec;
}

void CShopManager::DestroyPremiumPrivateShop(DWORD dwShopVid)
{
	LPOFFSHOP pkPremiumPrivateShop = FindPremiumPrivateShop(dwShopVid);

	if (!pkPremiumPrivateShop)
	{
		sys_err("Can't find the Shop %d", dwShopVid);
		return;
	}

	std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("UPDATE player.player_shop SET status = 0 WHERE shop_id = %d and owner_id = %d", pkPremiumPrivateShop->GetShopVid(), pkPremiumPrivateShop->GetPlayerID()));
	if(pMsg->Get()->uiAffectedRows == 0)
	{
		sys_err("Update Fail Premium Private Shop %d", dwShopVid);
		return;
	}

	for (auto& it : m_map_pkPrivateOfflineShop)
		if (it.second->GetShopVid() == dwShopVid)
			m_map_pkPrivateOfflineShop.erase(it.first);

	M2_DELETE(pkPremiumPrivateShop);
}

bool CreateItemTableFromRes(MYSQL_RES * res, std::vector<TPlayerItem> * pVec)
{
	if (!res)
	{
		pVec->clear();
		return true;
	}

	int rows;

	if ((rows = mysql_num_rows(res)) <= 0)
	{
		pVec->clear();
		return true;
	}

	pVec->resize(rows);

	for (int i = 0; i < rows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		TPlayerItem & item = pVec->at(i);

		int cur = 0;

		str_to_number(item.id, row[cur++]);
		str_to_number(item.owner, row[cur++]);
		str_to_number(item.window, row[cur++]);
		str_to_number(item.pos, row[cur++]);
		str_to_number(item.count, row[cur++]);
		str_to_number(item.vnum, row[cur++]);
		str_to_number(item.alSockets[0], row[cur++]);
		str_to_number(item.alSockets[1], row[cur++]);
		str_to_number(item.alSockets[2], row[cur++]);

		for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
		{
			str_to_number(item.aAttr[j].bType, row[cur++]);
			str_to_number(item.aAttr[j].sValue, row[cur++]);
		}
		
#ifdef ENABLE_TRANSMUTATION
		str_to_number(item.transmutation, row[cur++]);
#endif
#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		str_to_number(item.price, row[cur++]);
		str_to_number(item.shop_id, row[cur++]);
#endif
	}

	return true;
}

void CShopManager::BuildPremiumPrivateShop()
{
	std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_id, owner_id, owner_name, map_index, x, y, z, UNIX_TIMESTAMP(date_close), race, count, name FROM player.player_shop WHERE status = 1"));
	SQLResult * pRes = pMsg->Get();
	MYSQL_ROW row;
	if (!pRes || !pRes->uiNumRows)
		return;

	while ((row = mysql_fetch_row(pRes->pSQLResult)))
	{
		DWORD dwShopVid = 0, dwPlayerId = 0, dwRace = 0, dwEndTime;
		int map_index = 0, x = 0, y = 0, z = 0;
		BYTE bItemCount = 0;
		str_to_number(dwShopVid, row[0]);
		str_to_number(dwPlayerId, row[1]);
		//owner_name = 2
		str_to_number(map_index, row[3]);
		str_to_number(x, row[4]);
		str_to_number(y, row[5]);
		str_to_number(z, row[6]);
		str_to_number(dwEndTime, row[7]);
		str_to_number(dwRace, row[8]);
		str_to_number(bItemCount, row[9]);
		//name = 10
		LPSECTREE sectree = SECTREE_MANAGER::instance().Get(map_index, x, y);

		if (!sectree)
		{
			sys_log(0, "cannot find sectree by %dx%d mapindex %d", x, y, map_index);
			return;
		}

		LPSHOP pkShop = NULL;
		char queryStr[1024];
		snprintf(queryStr, sizeof(queryStr), 
			"SELECT id, owner_id, window+0,pos,count,vnum,socket0,socket1,socket2,attrtype0,attrvalue0,attrtype1,attrvalue1,attrtype2,attrvalue2,attrtype3,attrvalue3,attrtype4,attrvalue4,attrtype5,attrvalue5,attrtype6,attrvalue6,applytype0,applyvalue0,applytype1,applyvalue1,applytype2,applyvalue2,applytype3,applyvalue3,applytype4,applyvalue4,applytype5,applyvalue5,applytype6,applyvalue6,applytype7,applyvalue7"
			", transmutation, price, shop_id "
			"FROM player.item WHERE shop_id=%u", dwShopVid);

		std::auto_ptr<SQLMsg> pMsg2(DBManager::instance().DirectQuery(queryStr));
		SQLResult * pRes2 = pMsg2->Get();
		if (pRes2->uiNumRows > 0)
		{
			pkShop = M2_NEW CShop;
			pkShop->SetPremiumPrivateShop(true);

			static std::vector<TPlayerItem> s_items;
			CreateItemTableFromRes(pRes2->pSQLResult, &s_items);
			for (size_t i = 0; i < s_items.size(); ++i)
			{
				TPlayerItem & p = s_items.at(i);
				LPITEM item = ITEM_MANAGER::instance().CreateItem(p.vnum, p.count, p.id);
				if (!item)
				{
					sys_err("cannot create item by vnum %u id %u", p.vnum, p.id);
					continue;
				}

				item->SetSkipSave(true);
				item->SetOwnerPID(p.owner);
				item->SetOwnerName(row[2]);
				item->SetCell(nullptr, p.pos);
				item->SetSockets(p.alSockets);
				item->SetAttributes(p.aAttr);
				item->SetTransmutation(p.transmutation);
				item->SetPremiumPrivateShopVid(p.shop_id);
				item->SetPremiumPrivateShopPrice(p.price);
				item->SetSkipSave(false);
				if (!p.owner && !p.pos)
				{
					item->SetOwnerPID(dwPlayerId);
				}
				pkShop->SetPremiumPrivateShopItem(item);
			}
		}
		else
		{
			std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("UPDATE player.player_shop SET status = 0 WHERE shop_id = %d and owner_id = %d", dwShopVid, dwPlayerId));
			if(pMsg->Get()->uiAffectedRows == 0)
			{
				sys_err("Update Fail Build Premium Private Shop");
				return;
			}
		}

		if(pkShop)
		{
			LPOFFSHOP pkPremiumPrivateShop = M2_NEW CPremiumPrivateShop(pkShop, dwEndTime, dwRace);

			if(!pkPremiumPrivateShop)
			{
				sys_err("Fail to create Build Premium Private Shop: %d", dwShopVid);
				return;
			}

			pkPremiumPrivateShop->SetMapIndex(map_index);
			pkPremiumPrivateShop->SetXYZ(x, y, z);
			pkPremiumPrivateShop->SetOwnerName(row[2]);
			pkPremiumPrivateShop->SetSign(row[10]);
			pkPremiumPrivateShop->SetPlayerID(dwPlayerId);
			sectree->InsertEntity(pkPremiumPrivateShop);
			pkPremiumPrivateShop->UpdateSectree();
			pkPremiumPrivateShop->SetShopVid(dwShopVid);
			m_map_pkPrivateOfflineShop.insert(TOfflinePrivateShopMap::value_type(pkPremiumPrivateShop->GetShopVid(), pkPremiumPrivateShop));
		}
	}

	shop_event_info* info = AllocEventInfo<shop_event_info>();
	m_pkShopEvent = event_create(shop_event, info, passes_per_sec);
}

void CShopManager::StartPremiumPrivateShop(LPCHARACTER ch, DWORD dwVid)
{
	if (!ch || !ch->IsPC())
		return;

	if (ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen() || ch->IsTransmutationOpen() || ch->GetSoulRoulette())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "You can't open this if you have other window open."));
		return;
	}

	LPOFFSHOP pkPremiumPrivateShop = FindPremiumPrivateShopByShopVID(dwVid);

	if (!pkPremiumPrivateShop)
		return;

	int distance = DISTANCE_APPROX(pkPremiumPrivateShop->GetX() - ch->GetX(), pkPremiumPrivateShop->GetY() - ch->GetY());

	if (distance >= SHOP_MAX_DISTANCE)
	{
		sys_log(1, "SHOP: TOO_FAR: %s distance %d", ch->GetName(), distance);
		return;
	}

	LPSHOP pkShop = pkPremiumPrivateShop->GetShop();

	if (!pkShop)
		return;

	pkShop->AddGuest(ch, pkPremiumPrivateShop->GetVid(), false);
	ch->SetPremiumPrivateShopVid(pkPremiumPrivateShop->GetShopVid());
}

DWORD CShopManager::GetPremiumPrivateShopCount(DWORD dwVid)
{
	BYTE bCount = 0;
	TOfflinePrivateShopMap::iterator it;

	for (it = m_map_pkPrivateOfflineShop.begin(); it != m_map_pkPrivateOfflineShop.end(); ++it)
		if (it->second->GetPlayerID() == dwVid)
			++bCount;

	return bCount;
}

void CShopManager::SetPremiumPrivateShops(LPOFFSHOP pkPremiumPrivateShops[], BYTE bCount, DWORD dwVid)
{
	BYTE bTotalCount = 0;
	TOfflinePrivateShopMap::iterator it;
	for (it = m_map_pkPrivateOfflineShop.begin(); it != m_map_pkPrivateOfflineShop.end(); ++it)
	{
		if (it->second->GetPlayerID() == dwVid && bTotalCount < bCount)
		{
			pkPremiumPrivateShops[bTotalCount] = it->second;
			++bTotalCount;
		}
	}
}

void CShopManager::AddBankPremiumPrivateShop(LPSHOP pkShop, long long dwPrices)
{
	TOfflinePrivateShopMap::iterator it;

	for (it = m_map_pkPrivateOfflineShop.begin(); it != m_map_pkPrivateOfflineShop.end(); ++it)
	{
		if (it->second->GetShop() == pkShop)
		{
			std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("UPDATE player.player_shop SET gold = gold + %llu WHERE shop_id = %d and owner_id = %d", dwPrices, it->second->GetShopVid(), it->second->GetPlayerID()));
			if(pMsg->Get()->uiAffectedRows == 0)
			{
				sys_err("Update Bank Fail Premium Private Shop %d", it->second->GetShopVid());
			}
		}
	}
}

#endif




//Search all transmutation and replace for changelook if you use changelook