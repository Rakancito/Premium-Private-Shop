//Search

#include "config.h"

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "shop.h"
#endif


//Search

			m_pkItems[i]->SetSkipSave(true);
			ITEM_MANAGER::instance().FlushDelayedSave(m_pkItems[i]);
			M2_DESTROY_ITEM(m_pkItems[i]->RemoveFromCharacter());

//Replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			if(m_bWindowMode != PRIVATE_SHOP)
			{
				m_pkItems[i]->SetSkipSave(true);
				ITEM_MANAGER::instance().FlushDelayedSave(m_pkItems[i]);
				M2_DESTROY_ITEM(m_pkItems[i]->RemoveFromCharacter());

			}
#else
			m_pkItems[i]->SetSkipSave(true);
			ITEM_MANAGER::instance().FlushDelayedSave(m_pkItems[i]);
			M2_DESTROY_ITEM(m_pkItems[i]->RemoveFromCharacter());
#endif

//Search


bool CSafebox::IsValidPosition(DWORD dwPos)
{
	if (!m_pkGrid)
		return false;

	if (dwPos >= m_pkGrid->GetSize())
		return false;

	return true;
}

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
bool CSafebox::AddPrivShop(DWORD dwPos, LPITEM pkItem, LPSHOP pShop, LPCHARACTER ch, DWORD price, DWORD dwShopVID)
{
	if (!IsValidPosition(dwPos))
	{
		sys_err("PREMIUMpRIVATESHOP: item on wrong position at %d (size of grid = %d)", dwPos, m_pkGrid->GetSize());
		return false;
	}

	if(pShop)
	{
		//Item
		pkItem->SetPremiumPrivateShopPrice(price);
		pkItem->AddPremiumPrivateShop(dwPos, dwShopVID);

		//Shop
		pShop->SetPremiumPrivateShopItem(pkItem);
		pShop->BroadcastUpdateItem(dwPos);

		//Character				
		ch->DelayedSaveFlush();	
	}else{
		pkItem->SetWindow(m_bWindowMode);
		pkItem->SetCell(m_pkChrOwner, dwPos);
	}

	m_pkGrid->Put(dwPos, 1, pkItem->GetSize());
	m_pkItems[dwPos] = pkItem;

	TPacketGCItemSetDelPremiumPrivateShop pack;

	pack.header	= HEADER_GC_PREMIUM_PRIVATE_SHOP_SET;
	pack.Cell	= TItemPos(m_bWindowMode, dwPos);
	pack.vnum	= pkItem->GetVnum();
	pack.count	= pkItem->GetCount();
	pack.flags	= pkItem->GetFlag();
	pack.anti_flags	= pkItem->GetAntiFlag();
	thecore_memcpy(pack.alSockets, pkItem->GetSockets(), sizeof(pack.alSockets));
	thecore_memcpy(pack.aAttr, pkItem->GetAttributes(), sizeof(pack.aAttr));
#ifdef ENABLE_TRANSMUTATION
	pack.transmutation = pkItem->GetTransmutation();
#endif
	pack.dwPrice = pkItem->GetPremiumPrivateShopPrice();
	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));

	sys_log(1, "SAFEBOX PRIVATE SHOP: ADD %s %s count %d", m_pkChrOwner->GetName(), pkItem->GetName(), pkItem->GetCount());
	return true;
}

LPITEM CSafebox::RemovePrivShop(DWORD dwPos)
{
	LPITEM pkItem = Get(dwPos);

	if (!pkItem)
		return NULL;

	if (!m_pkGrid)
		sys_err("SafeboxPrivShop::Remove : nil grid");
	else
		m_pkGrid->Get(dwPos, 1, pkItem->GetSize());

	m_pkItems[dwPos] = NULL;

	TPacketGCItemDel pack;

	pack.header	= HEADER_GC_PREMIUM_PRIVATE_SHOP_DEL;
	pack.pos	= dwPos;

	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));
	sys_log(1, "SAFEBOX PRIVATE SHOP: REMOVE %s %s count %d", m_pkChrOwner->GetName(), pkItem->GetName(), pkItem->GetCount());
	return pkItem;
}


bool CSafebox::MoveItemPremiumPrivateShop(BYTE bCell, BYTE bDestCell, BYTE count, LPSHOP pShop, LPCHARACTER ch)
{
	LPITEM item;

	int max_position = 5 * m_iSize;

	if (bCell >= max_position || bDestCell >= max_position)
		return false;

	if (!(item = GetItem(bCell)))
		return false;

	if (item->IsExchanging())
		return false;

	if (item->GetCount() < count)
		return false;

	{
		LPITEM item2;

		if ((item2 = GetItem(bDestCell)) && item != item2 && item2->IsStackable() &&
				!IS_SET(item2->GetAntiFlag(), ITEM_ANTIFLAG_STACK) &&
				item2->GetVnum() == item->GetVnum())
		{
			sys_log(1, "SAFEBOX: STACK");
			return false;
		}

		if (!IsEmpty(bDestCell, item->GetSize()))
		{
			return false;
		}

		m_pkGrid->Get(bCell, 1, item->GetSize());

		if (!m_pkGrid->Put(bDestCell, 1, item->GetSize()))
		{
			m_pkGrid->Put(bCell, 1, item->GetSize());
			return false;
		}
		else
		{
			m_pkGrid->Get(bDestCell, 1, item->GetSize());
			m_pkGrid->Put(bCell, 1, item->GetSize());
		}

		sys_log(1, "SAFEBOX PREMIUM PRIVATE SHOP: MOVE %s %d -> %d %s count %d", m_pkChrOwner->GetName(), bCell, bDestCell, item->GetName(), item->GetCount());

		RemovePrivShop(bCell);
		AddPrivShop(bDestCell, item, NULL, ch);

		pShop->RemovePremiumPrivateShopItem(bCell);
		pShop->SetPremiumPrivateShopItem(item);
		pShop->BroadcastUpdateItem(bCell);

		item->DelayedSaveFlush();
		ch->DelayedSaveFlush();

	}

	return true;
}
#endif


