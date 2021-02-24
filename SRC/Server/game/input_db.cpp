//Search

	building::CManager::instance().FinalizeBoot();

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if(g_bChannel == 1)
	{
		CShopManager::instance().BuildPremiumPrivateShop();
	}
#endif

//Search

void CInputDB::MallLoad(LPDESC d, const char * c_pData)
{
	...
}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CInputDB::PremiumPrivateShopLoad(LPDESC d, const char * c_pData)
{
	if (!d)
		return;

	TSafeboxTable * p = (TSafeboxTable *) c_pData;

	if (d->GetAccountTable().id != p->dwID)
	{
		sys_err("safebox has different id %u != %u", d->GetAccountTable().id, p->dwID);
		return;
	}

	if (!d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();

	//PREVENT_TRADE_WINDOW
#ifdef ENABLE_TRANSMUTATION
	if (ch->GetShopOwner() || ch->GetExchange() || ch->GetMyShop() || ch->IsCubeOpen() || ch->IsAcceOpen() || ch->IsTransmutationOpen() || ch->IsAuraOpen()
#if defined(__BL_SOUL_ROULETTE__)
			|| ch->GetSoulRoulette()
#endif
	)
#else
	if (ch->GetShopOwner() || ch->GetExchange() || ch->GetMyShop() || ch->IsCubeOpen() || ch->IsAcceOpen()
#if defined(__BL_SOUL_ROULETTE__)
			|| ch->GetSoulRoulette()
#endif
	)
#endif
	{
		d->GetCharacter()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "다른거래창이 열린상태에서는 창고를 열수가 없습니다." ) );
		d->GetCharacter()->CancelSafeboxLoad();
		return;
	}
	//END_PREVENT_TRADE_WINDOW


	d->GetCharacter()->LoadPremiumPrivateShop(p->wItemCount, (TPlayerItem *) (c_pData + sizeof(TSafeboxTable)));
}

#endif

//Search

if ((p->window == INVENTORY && ch->GetInventoryItem(p->pos)) ||

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		item->SetPremiumPrivateShopPrice(p->price);
		item->SetPremiumPrivateShopVid(p->shop_id);
#endif

//Search

	case HEADER_DG_MALL_LOAD:
		MallLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;


//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	case HEADER_DG_PREMIUM_PRIVATE_SHOP_LOAD:
		PremiumPrivateShopLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif


