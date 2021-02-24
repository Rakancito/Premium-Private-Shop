//Search

void CHARACTER::SetItem(TItemPos Cell, LPITEM pItem, bool bWereMine)
{
	WORD wCell = Cell.cell;
	BYTE window_type = Cell.window_type;
	if ((unsigned long)((CItem*)pItem) == 0xff || (unsigned long)((CItem*)pItem) == 0xffffffff)
	{
		sys_err("!!! FATAL ERROR !!! item == 0xff (char: %s cell: %u)", GetName(), wCell);
		core_dump();
		return;
	}

	if (pItem && pItem->GetOwner())

//and the conditional if (pItem && pItem->GetOwner()) replace with

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (pItem && pItem->GetOwner() && !pItem->GetPremiumPrivateShopVid())
#else
	if (pItem && pItem->GetOwner())
#endif

//Search

	case MALL:
		if (NULL != m_pkMall)
			return m_pkMall->IsValidPosition(cell);
		else
			return false;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	case PRIVATE_SHOP:
		if (NULL != m_pkPremiumPrivateShop)
			return m_pkPremiumPrivateShop->IsValidPosition(cell);
		else
			return false;
#endif

