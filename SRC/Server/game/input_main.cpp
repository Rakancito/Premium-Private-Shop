//Search 
#include "shop_manager.h"

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
#include "offline_privateshop.h"
#endif

//Search

void CInputMain::OnClick(LPCHARACTER ch, const char * data)
{
	struct command_on_click *	pinfo = (struct command_on_click *) data;
	LPCHARACTER			victim;

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	LPOFFSHOP			victimShop;
#endif


//Search

	else if (test_server)
	{
		sys_err("CInputMain::OnClick %s.Click.NOT_EXIST_VID[%d]", ch->GetName(), pinfo->vid);
	}


//Replace with 

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	else if((victimShop = CShopManager::instance().FindPremiumPrivateShopByShopVID(pinfo->vid)))
		CShopManager::instance().StartPremiumPrivateShop(ch, pinfo->vid);
	else
		sys_err("CInputMain::OnClick %s.Click.NOT_EXIST_VID[%d]", ch->GetName(), pinfo->vid);
#else
	else if (test_server)
	{
		sys_err("CInputMain::OnClick %s.Click.NOT_EXIST_VID[%d]", ch->GetName(), pinfo->vid);
	}
#endif

//Search

void CInputMain::SafeboxItemMove(LPCHARACTER ch, const char * data)
{
	...
}

//add after


#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

void CInputMain::PremiumPrivateShopItemMove(LPCHARACTER ch, const char * data)
{
	struct command_item_move * pinfo = (struct command_item_move *) data;

	if (!ch->CanHandleItem())
		return;

	if (!ch->GetPremiumPrivateShop())
		return;

	CSafebox * pkSafebox = ch->GetPremiumPrivateShop();

	if (!pkSafebox)
		return;

	LPITEM pkItem = pkSafebox->Get(pinfo->Cell.cell);

	if (!pkItem)
		return;

	DWORD dwPID = ch->GetPlayerID();
		
	LPOFFSHOP pkShop = CShopManager::instance().FindPremiumPrivateShopByPlayerID(dwPID);

	if (!pkShop)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Safebox Private Shop> Private Shop not Found by PID"));
		return;
	}

	LPSHOP pShop = pkShop->GetShop();
			
	if (!pShop)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Safebox Private Shop> Private Shop not Found by Shop"));
		return;
	}

	if(!pkSafebox->MoveItemPremiumPrivateShop(pinfo->Cell.cell, pinfo->CellTo.cell, pinfo->count, pShop, ch))
	{
		//sys_err("Fail moving item");
		return;
	}
}

void CInputMain::PremiumPrivateShop(LPCHARACTER ch, const char * c_pData)
{
	struct packet_premium_private_shop * pinfo = (struct packet_premium_private_shop *) c_pData;
	switch (pinfo->subheader)
	{
		//For Gold
		case SUB_HEADER_PREMIUM_PRIVATE_SHOP_GOLD_DEL:
		{
			if (quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID())->IsRunning() == true)
				return;

			if (!ch->CanHandleItem())
				return;

			CSafebox * pkSafebox = ch->GetPremiumPrivateShop();

			if (!pkSafebox)
			{
			    ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Premium Private Shop> Error no Safebox Private Shop detect"));
			    return;				
			}

			ch->SendPremiumPrivateShopGold();
		}
		break;
		//For add items.
		case SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_ADD:
		{

			if (quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID())->IsRunning() == true)
				return;

			TPacketCGPremiumPrivateShopCheck * p = (TPacketCGPremiumPrivateShopCheck *) c_pData;

			if (!ch->CanHandleItem())
				return;

			CSafebox * pkSafebox = ch->GetPremiumPrivateShop();

			if (!pkSafebox)
			{
			    ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Premium Private Shop> Error no Safebox Private Shop detect"));
			    return;				
			}

			LPITEM pkItem = ch->GetItem(p->ItemPos);

			if (!pkItem)
			{
			    ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Premium Private Shop> Error no Item position %d to %d detect."), p->ItemPos, p->bSafePos);
			    return;				
			}

			if (pkItem->GetCell() >= INVENTORY_MAX_NUM && IS_SET(pkItem->GetFlag(), ITEM_FLAG_IRREMOVABLE))
			{
			    ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 창고로 옮길 수 없는 아이템 입니다."));
			    return;
			}

			if (!pkSafebox->IsEmpty(p->bSafePos, pkItem->GetSize()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 옮길 수 없는 위치입니다."));
				return;
			}

			if (pkItem->GetVnum() == UNIQUE_ITEM_SAFEBOX_EXPAND)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 이 아이템은 넣을 수 없습니다."));
				return;
			}

			if (true == pkItem->isLocked())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 이 아이템은 넣을 수 없습니다."));
				return;
			}

#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
			if (pkItem->IsEquipped())
			{
				int iWearCell = pkItem->FindEquipCell(ch);
				if (iWearCell == WEAR_WEAPON)
				{
					LPITEM costumeWeapon = ch->GetWear(WEAR_COSTUME_WEAPON);
					if (costumeWeapon && !ch->UnequipItem(costumeWeapon))
					{
						ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "You cannot unequip the costume weapon. Not enough space."));
						return;
					}
				}
			}
#endif
			if (ITEM_BELT == pkItem->GetType() && CBeltInventoryHelper::IsExistItemInBeltInventory(ch))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "벨트 인벤토리에 아이템이 존재하면 해제할 수 없습니다."));
				return;
			}

			//pkItem->RemoveFromCharacter();
			//if (!pkItem->IsDragonSoul())
			//	ch->SyncQuickslot(QUICKSLOT_TYPE_ITEM, p->ItemPos.cell, 255);
			
			DWORD dwPID = ch->GetPlayerID();
			
			LPOFFSHOP pkShop = CShopManager::instance().FindPremiumPrivateShopByPlayerID(dwPID);

			if (pkShop)
			{
				LPSHOP pShop = pkShop->GetShop();
				if(pShop)
				{
					//Safebox
					if(!pkSafebox->AddPrivShop(p->bSafePos, pkItem, pShop, ch, p->dwPrice, pkShop->GetShopVid()))
					{
						sys_err("Fail addying the item");
						return;
					}
				}
			}
			else
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "Can't find your shop, maybe you will need re open or contact any admin"));
			}	
		}
		break;
		//For delete items.
		case SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_DEL:
		{
			TPacketCGPremiumPrivateShopCheck * p = (TPacketCGPremiumPrivateShopCheck *) c_pData;

			if (!ch->CanHandleItem())
				return;

			CSafebox * pkSafebox;

			pkSafebox = ch->GetPremiumPrivateShop();

			if (!pkSafebox)
				return;

			LPITEM pkItem = pkSafebox->Get(p->bSafePos);

			if (!pkItem)
				return;

			if (!ch->IsEmptyItemGrid(p->ItemPos, pkItem->GetSize()))
				return;

			DWORD dwPID = ch->GetPlayerID();
			
			LPOFFSHOP pkShop = CShopManager::instance().FindPremiumPrivateShopByPlayerID(dwPID);

			if (!pkShop)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Safebox Private Shop> Private Shop not Found by PID"));
				return;
			}

			LPSHOP pShop = pkShop->GetShop();
			
			if (!pShop)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<Safebox Private Shop> Private Shop not Found by Shop"));
				return;
			}

			if (pkItem->IsDragonSoul())
			{
				if (DRAGON_SOUL_INVENTORY != p->ItemPos.window_type)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 옮길 수 없는 위치입니다."));
					return;
				}

				TItemPos DestPos = p->ItemPos;
				if (!DSManager::instance().IsValidCellForThisItem(pkItem, DestPos))
				{
					int iCell = ch->GetEmptyDragonSoulInventory(pkItem);
					if (iCell < 0)
					{
						ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 옮길 수 없는 위치입니다."));
						return ;
					}
					DestPos = TItemPos (DRAGON_SOUL_INVENTORY, iCell);
				}

				//Player
				pkItem->AddToCharacter(ch, DestPos);
				//Item
				pkItem->SetPremiumPrivateShopVid(0);
				pkItem->SetPremiumPrivateShopPrice(0);
				pkItem->DelayedSaveFlush();

				//Shop and Safebox
				pShop->RemovePremiumPrivateShopItem(p->bSafePos);
				pShop->BroadcastUpdateItem(p->bSafePos);
				pkSafebox->RemovePrivShop(p->bSafePos);
				ch->DelayedSaveFlush();

				if(pShop->GetItemCount() <= 0)
					CShopManager::instance().DestroyPremiumPrivateShop(pkShop->GetShopVid());					

			}
			else
			{
				if (DRAGON_SOUL_INVENTORY == p->ItemPos.window_type)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "<창고> 옮길 수 없는 위치입니다."));
					return;
				}
				// @fixme119
				if (p->ItemPos.IsBeltInventoryPosition() && false == CBeltInventoryHelper::CanMoveIntoBeltInventory(pkItem))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "이 아이템은 벨트 인벤토리로 옮길 수 없습니다."));
					return;
				}

				//Player
				pkItem->AddToCharacter(ch, p->ItemPos);

				//Item
				pkItem->SetPremiumPrivateShopVid(0);
				pkItem->SetPremiumPrivateShopPrice(0);
				pkItem->DelayedSaveFlush();

				//Shop and Safebox
				pShop->RemovePremiumPrivateShopItem(p->bSafePos);
				pShop->BroadcastUpdateItem(p->bSafePos);
				pkSafebox->RemovePrivShop(p->bSafePos);
				ch->DelayedSaveFlush();

				if(pShop->GetItemCount() <= 0)
					CShopManager::instance().DestroyPremiumPrivateShop(pkShop->GetShopVid());
			}

			char szHint[128];
			snprintf(szHint, sizeof(szHint), "%s %u", pkItem->GetName(), pkItem->GetCount());
			LogManager::instance().ItemLog(ch, pkItem, "SAFEBOX PREMIUM PRIVATE SHOP GET", szHint);

		}
		break;
	}
}
#endif

//Search

	}
	return (iExtraLen);


//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		case HEADER_CG_PREMIUM_PRIVATE_SHOP:
			PremiumPrivateShop(ch, c_pData);
			break;
		case HEADER_CG_PREMIUM_PRIVATE_SHOP_ITEM_MOVE:
			PremiumPrivateShopItemMove(ch, c_pData);
			break;
#endif
