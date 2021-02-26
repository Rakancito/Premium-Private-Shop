//Search

#include "mob_manager.h"
#include "locale_service.h"
#include "../../common/service.h"


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "desc_client.h"
#include "shop_manager.h"
#include "offline_privateshop.h"
#include "safebox.h"
#endif

//Search

CShop::CShop()
	: m_dwVnum(0), m_dwNPCVnum(0), m_pkPC(NULL)

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		, m_bIsPremiumPrivateShop(false)
#endif

//Search

	while (it != m_map_guest.end())
	{
		LPCHARACTER ch = it->first;
		ch->SetShop(NULL);
		++it;
	}

	M2_DELETE(m_pGrid);

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_bIsPremiumPrivateShop)
	{
		for (int i = 0; i < SHOP_HOST_ITEM_MAX_NUM; ++i)
		{
			SHOP_ITEM & item = m_itemVector[i];
			if (!item.pkItem)
				continue;

			item.pkItem->SetSkipSave(true);
			M2_DESTROY_ITEM(item.pkItem);
			item.pkItem = NULL;
		}
	}
#endif

//Search

void CShop::SetShopItems(TShopItemTable * pTable, BYTE bItemCount)

//replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CShop::SetShopItems(TShopItemTable * pTable, BYTE bItemCount, DWORD dwShopVID)
#else
void CShop::SetShopItems(TShopItemTable * pTable, BYTE bItemCount)
#endif

//Search

		char name[36];
		snprintf(name, sizeof(name), "%-20s(#%-5d) (x %d)", item_table->szName, (int) item.vnum, item.count);

		sys_log(0, "SHOP_ITEM: %-36s PRICE %-5d", name, item.price);
		++pTable;

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		if (m_bIsPremiumPrivateShop && pkItem)
		{
			pkItem->SetPremiumPrivateShopPrice(pTable->price);
			pkItem->AddPremiumPrivateShop(iPos, dwShopVID);
		}	
#endif

//Search all

	if (IsPCShop())

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (IsPCShop() && !m_bIsPremiumPrivateShop)
#else
	if (IsPCShop())
#endif


//Search

	if (m_pkPC)

//Replace all with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_pkPC || m_bIsPremiumPrivateShop) 
#else
	if (m_pkPC)
#endif

//Search
	if (!m_pkPC)
	{
		CMonarch::instance().SendtoDBAddMoney(dwTax, ch->GetEmpire(), ch);
	}

	if (m_pkPC)

//Replace if (m_pkPC) with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_bIsPremiumPrivateShop)
	{

		item->SetCell(nullptr, iEmptyPos);
		if (item->IsDragonSoul())
			item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
		else
			item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));

		CShopManager::instance().AddBankPremiumPrivateShop(this, r_item.price);

		//Fix p2p
		LPOFFSHOP pkPremiumPrivateShop = CShopManager::instance().FindPremiumPrivateShop(ch->GetPremiumPrivateShopVid());
		LPCHARACTER ch_owner = CHARACTER_MANAGER::instance().FindByPID(pkPremiumPrivateShop->GetPlayerID());
		if(ch_owner && ch_owner->IsPC() && ch_owner->IsOpenSafebox())
		{
			ch_owner->m_pkPremiumPrivateShop->RemovePrivShop(pos);
			ch_owner->ChatPacket(CHAT_TYPE_INFO, "The player: %s buyed the item %s in this moment", ch->GetName(), item->GetName());
		}


		item->SetPremiumPrivateShopPrice(0);
		item->SetPremiumPrivateShopVid(0);
		item->DelayedSaveFlush();
		memset((void*)&r_item, 0, sizeof(r_item));
		r_item.pkItem = NULL;
		BroadcastUpdateItem(pos);
	}
	else if (m_pkPC)
#else
	if (m_pkPC)
#endif

//Search

    ch->Save();

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_bIsPremiumPrivateShop)
	{
		if (GetItemCount()<=0)
			CShopManager::instance().DestroyPremiumPrivateShop(ch->GetPremiumPrivateShopVid());
	}
#endif


//Search

bool CShop::IsSellingItem(DWORD itemID)
{
	...
}

//Add after
//Please change all transmutation for changelook if you have like changelook

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

bool CShop::IsValidPosition(DWORD dwPos)
{
	if (dwPos >= SHOP_HOST_ITEM_MAX_NUM)
		return false;

	return true;
}

void CShop::SetPremiumPrivateShopItem(LPITEM pkItem)
{
	m_itemVector.resize(SHOP_HOST_ITEM_MAX_NUM);
	//memset(&m_itemVector[0], 0, sizeof(SHOP_ITEM) * m_itemVector.size());

	if (!pkItem)
	{
		sys_err("SetPremiumPrivateShopItem Not Found Item !");
		return;
	}

	int iPos = pkItem->GetCell();

	if (iPos < 0)
	{
		sys_err("not enough shop window");
		return;
	}

	if(!IsValidPosition(iPos))
	{
		sys_err("Not valid position");
		return;
	}

	m_pGrid->Put(iPos, 1, pkItem->GetSize());

	SHOP_ITEM & item = m_itemVector[iPos];
	item.pkItem = pkItem;
	item.vnum = pkItem->GetVnum();
	item.count = pkItem->GetCount();
	item.price = pkItem->GetPremiumPrivateShopPrice();
#ifdef ENABLE_BUY_WITH_ITEM
        item.witemVnum = 0; // We Can Item
#endif
	item.tItem.vnum = pkItem->GetVnum();
	item.tItem.count = pkItem->GetCount();
	item.tItem.price = pkItem->GetPremiumPrivateShopPrice();
	item.tItem.display_pos = iPos;
	item.tItem.transmutation = pkItem->GetTransmutation();

	item.itemid	= pkItem->GetID();
}

void CShop::RemovePremiumPrivateShopItem(DWORD dwPos)
{
	SHOP_ITEM & item = m_itemVector[dwPos];

	LPITEM pkItem = item.pkItem;

	if (!pkItem)
	{
		sys_err("Not found item premium private shop");
		return;
	}

	m_pGrid->Put(dwPos, 0, pkItem->GetSize());

	memset((void*)&item, 0, sizeof(item));
	item.pkItem = NULL;
	BroadcastUpdateItem(dwPos);

	return;
}

void CShop::AddPremiumPrivateShopItem(DWORD dwPos, BYTE bInvenType, DWORD dwSourcePos, DWORD dwPrices, DWORD dwShopVid, LPCHARACTER ch)
{
	if (!ch)
		return;

	LPITEM item = ch->GetItem(TItemPos(bInvenType, dwSourcePos));
	if (!item)
		return;

	if (!m_pGrid->IsEmpty(dwPos, 1, item->GetSize()))
	{
		sys_err("not empty position for npc shop");
		return;
	}
	m_pGrid->Put(dwPos, 1, item->GetSize());

	SHOP_ITEM & r_item = m_itemVector[dwPos];

	r_item.pkItem = item;
	r_item.vnum = item->GetVnum();
	r_item.count = item->GetCount();
	r_item.price = item->GetPremiumPrivateShopPrice();
#ifdef ENABLE_BUY_WITH_ITEM
        r_item.witemVnum = 0; // We Can Item
#endif
	r_item.tItem.vnum = item->GetVnum();
	r_item.tItem.count = item->GetCount();
	r_item.tItem.price = dwPrices;
	r_item.itemid	= item->GetID();
	r_item.tItem.display_pos = dwPos;
#ifdef ENABLE_TRANSMUTATION
	r_item.tItem.transmutation = item->GetTransmutation();
#endif
	item->SetPremiumPrivateShopPrice(dwPrices);
	item->AddPremiumPrivateShop(dwPos, dwShopVid);
	BroadcastUpdateItem(dwPos);
	ch->DelayedSaveFlush();
}

void CShop::RemoveGuests(LPCHARACTER except)
{
	GuestMapType::iterator it = m_map_guest.begin();
	while (it != m_map_guest.end())
	{
		LPCHARACTER ch = it->first;
		if (except && ch == except)
		{
			it++;
			continue;
		}
		if (ch)
		{
			ch->SetShop(NULL);

			TPacketGCShop pack;

			pack.header = HEADER_GC_SHOP;
			pack.subheader = SHOP_SUBHEADER_GC_END;
			pack.size = sizeof(TPacketGCShop);

			ch->GetDesc()->Packet(&pack, sizeof(pack));
		}
		m_map_guest.erase(it++);
	}
}

int CShop::GetItemCount()
{
	int count = 0;
	for (DWORD i = 0; i < m_itemVector.size() && i < SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		if (m_itemVector[i].pkItem)
			count++;
	}
	return count;
}

#endif

