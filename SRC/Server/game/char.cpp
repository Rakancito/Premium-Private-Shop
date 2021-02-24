//Search

extern const BYTE g_aBuffOnAttrPoints;
extern bool RaceToJob(unsigned race, unsigned *ret_job);


//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "offline_privateshop.h"
#endif

//Search

	m_pkMall = NULL;
	m_iMallLoadTime = 0;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	m_pkPremiumPrivateShop = NULL;
	m_iPremiumPrivateShopLoadTime = 0;
#endif

//Search

	m_bIsLoadedAffect = false;
	cannot_dead = false;


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	m_dwPremiumPrivateShopVid = 0;
	m_iRenameTime = 0;
#endif

//Search

	if (m_pkMall)
	{
		M2_DELETE(m_pkMall);
		m_pkMall = NULL;
	}

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_pkPremiumPrivateShop)
	{
		M2_DELETE(m_pkPremiumPrivateShop);
		m_pkPremiumPrivateShop = NULL;
	}
#endif

//Search

void CHARACTER::OpenMyShop(const char * c_pszSign, TShopItemTable * pTable, BYTE bItemCount)
{


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	int iPulse = thecore_pulse();

	if (iPulse - GetOpenPremiumShopLoadTime()  < PASSES_PER_SEC(10))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Wo Wo Wo, Wait you are going so fast, you can't use this for a some seconds."));
		return;
	}

	SetOpenPremiumShopLoadTime();
	
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("SELECT id FROM item%s WHERE window = 'PRIVATE_SHOP' and owner_id=%d",
				get_table_postfix(), GetPlayerID()));

	if (pmsg->Get()->uiNumRows > 0)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "You can't open a new personal shop if you have items into Shop"));
		return;
	}

	if (g_bChannel != 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in channel 1"));
		return;
	}
	if(GetMapIndex() != 1 && GetMapIndex() != 21 && GetMapIndex() != 41)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in your City 1"));
		return;

	}
#endif

//Search

	// MYSHOP_PRICE_LIST
	if (CountSpecifyItem(71049))


//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (bItemCount <= 0)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Wait, you are without items in your Shop, WTF?"));
		return;
	}

	CShopManager::instance().CreatePremiumPrivateShop(this, 30000, szSign, 86400, pTable, bItemCount);
	return;
#else
	// MYSHOP_PRICE_LIST
	if (CountSpecifyItem(71049))
	 {
		TItemPriceListTable header;
		memset(&header, 0, sizeof(TItemPriceListTable));

		header.dwOwnerID = GetPlayerID();
		header.byCount = itemkind.size();

		size_t idx=0;
		for (itertype(itemkind) it = itemkind.begin(); it != itemkind.end(); ++it)
		{
			header.aPriceInfo[idx].dwVnum = it->first;
			header.aPriceInfo[idx].dwPrice = it->second;
			idx++;
		}

		db_clientdesc->DBPacket(HEADER_GD_MYSHOP_PRICELIST_UPDATE, GetDesc()->GetHandle(), &header, sizeof(TItemPriceListTable));
	}
	else if (CountSpecifyItem(50200))
		RemoveSpecifyItem(50200, 1);
	else
	{
		ChatPacket(CHAT_TYPE_INFO, "No puedes construir un mercado.");
		return;
	}
#endif

//Search

	CloseMall();

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	ClosePremiumPrivateShop();
#endif

//Search

void CHARACTER::CloseMall()
{
	...
}

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
CSafebox * CHARACTER::GetPremiumPrivateShop() const
{
	return m_pkPremiumPrivateShop;
}

void CHARACTER::ReqPremiumPrivateShopLoad(const char* pszPassword)
{
	if (!*pszPassword || strlen(pszPassword) > SAFEBOX_PASSWORD_MAX_LEN)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 잘못된 암호를 입력하셨습니다."));
		return;
	}
	else if (m_pkPremiumPrivateShop)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 창고가 이미 열려있습니다."));
		return;
	}

	int iPulse = thecore_pulse();

	if (iPulse - GetSafeboxLoadTime()  < PASSES_PER_SEC(10))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 창고를 닫은지 10초 안에는 열 수 없습니다."));
		return;
	}
	else if (m_bOpeningSafebox)
	{
		sys_log(0, "Overlapped safebox load request from %s", GetName());
		return;
	}

	SetSafeboxLoadTime();
	m_bOpeningSafebox = true;

	TSafeboxLoadPacket p;
	p.dwID = GetDesc()->GetAccountTable().id;
	strlcpy(p.szLogin, GetDesc()->GetAccountTable().login, sizeof(p.szLogin));
	strlcpy(p.szPassword, pszPassword, sizeof(p.szPassword));
	p.dwPlayerID = GetPlayerID();

	db_clientdesc->DBPacket(HEADER_GD_PREMIUM_PRIVATE_SHOP_LOAD, GetDesc()->GetHandle(), &p, sizeof(p));
}

void CHARACTER::LoadPremiumPrivateShop(int iItemCount, TPlayerItem * pItems)
{
	if (g_bChannel != 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in channel 1"));
		return;
	}

	if(GetMapIndex() != 1 && GetMapIndex() != 21 && GetMapIndex() != 41)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in your City 1"));
		return;

	}
	bool bLoaded = false;

	//PREVENT_TRADE_WINDOW
	SetOpenSafebox(true);
	//END_PREVENT_TRADE_WINDOW

	if (m_pkPremiumPrivateShop)
		bLoaded = true;

	if (!m_pkPremiumPrivateShop)
		m_pkPremiumPrivateShop = M2_NEW CSafebox(this, 5 * (SAFEBOX_PAGE_SIZE-1), 0);
	else
		m_pkPremiumPrivateShop->ChangeSize(5*(SAFEBOX_PAGE_SIZE-1));

	m_pkPremiumPrivateShop->SetWindowMode(PRIVATE_SHOP);

	std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT gold, UNIX_TIMESTAMP(date_close) FROM player.player_shop WHERE owner_id = %u", GetPlayerID()));
	SQLResult * pRes = pMsg->Get();
	if (!pRes || !pRes->uiNumRows)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't find Gold in your table shop"));
		return;
	}

	DWORD dwGold = 0, dwTime;
	MYSQL_ROW row = mysql_fetch_row(pRes->pSQLResult);
	str_to_number(dwGold, row[0]);
	str_to_number(dwTime, row[1]);

	TPacketCGPremiumPrivateShopSize p;

	p.bHeader = HEADER_GC_PREMIUM_PRIVATE_SHOP;
	p.bSubHeader = SUB_HEADER_PREMIUM_PRIVATE_SHOP_OPEN;
	p.bSize = 5*(SAFEBOX_PAGE_SIZE-1);
	p.dwGold = dwGold;
	p.dwTime = dwTime;

	GetDesc()->Packet(&p, sizeof(TPacketCGPremiumPrivateShopSize));

	if (!bLoaded)
	{
		for (int i = 0; i < iItemCount; ++i, ++pItems)
		{
			if (!m_pkPremiumPrivateShop->IsValidPosition(pItems->pos))
				continue;

			LPITEM item = ITEM_MANAGER::instance().Find(pItems->id);

			if (!item)
			{
				sys_err("cannot find item vnum %d id %u (name: %s)", pItems->vnum, pItems->id, GetName());
				continue;
			}

			item->SetSkipSave(true);
			item->GetSockets();
			item->GetAttributes();
#ifdef ENABLE_TRANSMUTATION
			item->GetTransmutation();
#endif
			if (!m_pkPremiumPrivateShop->AddPrivShop(pItems->pos, item))
				sys_err("Cannot add pkPremiumitem pos: %d name: %s", pItems->pos, item->GetName());
			else
				item->SetSkipSave(false);
		}
	}
}

void CHARACTER::ClosePremiumPrivateShop()
{
	if (!m_pkPremiumPrivateShop)
		return;

	//PREVENT_TRADE_WINDOW
	SetOpenSafebox(false);
	//END_PREVENT_TRADE_WINDOW

	m_pkPremiumPrivateShop->Save();

	M2_DELETE(m_pkPremiumPrivateShop);
	m_pkPremiumPrivateShop = NULL;
	m_bOpeningSafebox = false;

	SetSafeboxLoadTime();

	ChatPacket(CHAT_TYPE_COMMAND, "ClosePremiumPrivateShop");
}

void CHARACTER::SendPremiumPrivateShopGold()
{
	int iPulse = thecore_pulse();

	if (iPulse - GetOpenPremiumShopLoadTime()  < PASSES_PER_SEC(10))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Wo Wo Wo, Wait you are going so fast, you can't use this for a some seconds."));
		return;
	}

	SetOpenPremiumShopLoadTime();

	if (g_bChannel != 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in channel 1"));
		return;
	}

	if(GetMapIndex() != 1 && GetMapIndex() != 21 && GetMapIndex() != 41)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't open if you don't are in your City 1"));
		return;

	}

	std::auto_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT gold FROM player.player_shop WHERE owner_id = %u", GetPlayerID()));
	if (pMsg->Get()->uiNumRows == 0)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't find Gold in your table shop"));
		return;
	}
	DBManager::instance().DirectQuery("UPDATE player.player_shop SET gold=0 WHERE owner_id =%d", GetPlayerID());

	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	DWORD gold = 0;
	str_to_number( gold, row[0] );

	ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Private Shop> Withdrawn gold!"));
	//SetGold(GetGold() + gold);
	PointChange(POINT_GOLD, gold);

	TPacketCGPremiumPrivateShopSize p;

	p.bHeader = HEADER_GC_PREMIUM_PRIVATE_SHOP;
	p.bSubHeader = SUB_HEADER_PREMIUM_PRIVATE_SHOP_GOLD_DEL;
	p.dwGold = 0;

	GetDesc()->Packet(&p, sizeof(TPacketCGPremiumPrivateShopSize));

}
#endif

//Add anywhere on this file

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CHARACTER::DelayedSaveFlush()
{
	m_bSkipSave = false;
	CHARACTER_MANAGER::instance().DelayedSave(this);
	CHARACTER_MANAGER::instance().FlushDelayedSave(this);
	DWORD dwPID = GetPlayerID();
	db_clientdesc->DBPacketHeader(HEADER_GD_FLUSH_CACHE, 0, sizeof(DWORD));
	db_clientdesc->Packet(&dwPID, sizeof(DWORD));
}
#endif


