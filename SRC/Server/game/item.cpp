//Search

#include "war_map.h"

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "desc_client.h"
#include "db.h"
#endif

//Search

CItem::CItem(DWORD dwVnum)
	: m_dwVnum(dwVnum), m_bWindow(0), m_dwID(0), m_bEquipped(false), m_dwVID(0), m_wCell(0), m_dwCount(0), m_lFlag(0), m_dwLastOwnerPID(0),
	m_bExchanging(false), m_pkDestroyEvent(NULL), m_pkExpireEvent(NULL), m_pkUniqueExpireEvent(NULL),
	m_pkTimerBasedOnWearExpireEvent(NULL), m_pkRealTimeExpireEvent(NULL),
   	m_pkAccessorySocketExpireEvent(NULL), m_pkOwnershipEvent(NULL), m_dwOwnershipPID(0), m_bSkipSave(false), m_isLocked(false),
	m_dwMaskVnum(0), m_dwSIGVnum (0)

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	, m_dwShopId(0), m_dwPrice(0), m_dwOwnerPID(0)
#endif

//Search

	m_pkDestroyEvent = NULL;
	m_pkOwnershipEvent = NULL;
	m_dwOwnershipPID = 0;
	m_pkUniqueExpireEvent = NULL;
	m_pkTimerBasedOnWearExpireEvent = NULL;
	m_pkRealTimeExpireEvent = NULL;

	m_pkAccessorySocketExpireEvent = NULL;

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	m_dwShopId = 0;
#endif

//add anywhere of this file

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CItem::AddPremiumPrivateShop(int iPos, DWORD dwShopId)
{
	if (!m_pOwner)
	{
		sys_err("Item::AddPremiumPrivateShop owner null");
		return;
	}

	if (GetWindow() != SAFEBOX && GetWindow() != MALL && GetWindow() != PRIVATE_SHOP)
	{
		if (IsDragonSoul())
		{
			if (m_wCell >= DRAGON_SOUL_INVENTORY_MAX_NUM)
				sys_err("CItem::AddPremiumPrivateShop: pos >= DRAGON_SOUL_INVENTORY_MAX_NUM");
			else
				m_pOwner->SetItem(TItemPos(m_bWindow, m_wCell), nullptr);
		}
		else
		{
			TItemPos cell(INVENTORY, m_wCell);

			if (false == cell.IsDefaultInventoryPosition() && false == cell.IsBeltInventoryPosition())
				sys_err("CItem::AddPremiumPrivateShop: Invalid Item Position");
			else
				m_pOwner->SetItem(cell, NULL);
		}
	}

	m_dwShopId = dwShopId;
	m_wCell = iPos;
	SetWindow(PRIVATE_SHOP);
	DelayedSaveFlush();
}

void CItem::DelayedSaveFlush()
{
	ITEM_MANAGER::instance().DelayedSave(this);
	ITEM_MANAGER::instance().FlushDelayedSave(this);
	DWORD dwID = GetID();
	db_clientdesc->DBPacketHeader(HEADER_GD_ITEM_FLUSH, 0, sizeof(DWORD));
	db_clientdesc->Packet(&dwID, sizeof(DWORD));
}

#endif
