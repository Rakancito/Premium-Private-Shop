//Search

void ITEM_MANAGER::SaveSingleItem(LPITEM item)
{
	if (!item)
		return;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (!item->GetOwner() && item->GetPremiumPrivateShopVid())
	{
		TPlayerItem t;
		t.id = item->GetID();
		t.window = item->GetWindow();
		t.owner =item->GetOwnerPID();
		t.pos = item->GetCell();
		t.count = item->GetCount();
		t.vnum = item->GetOriginalVnum();
#ifdef ENABLE_TRANSMUTATION
		t.transmutation = item->GetTransmutation(); //Just remember change for changelook if you have like changelook
#endif
		t.shop_id = item->GetPremiumPrivateShopVid();
		t.price = item->GetPremiumPrivateShopPrice();

		memcpy(t.alSockets, item->GetSockets(), sizeof(t.alSockets));
		memcpy(t.aAttr, item->GetAttributes(), sizeof(t.aAttr));
		db_clientdesc->DBPacketHeader(HEADER_GD_ITEM_SAVE, 0, sizeof(TPlayerItem));
		db_clientdesc->Packet(&t, sizeof(TPlayerItem));
		return;
	}
#endif


//Search

	db_clientdesc->DBPacketHeader(HEADER_GD_ITEM_SAVE, 0, sizeof(TPlayerItem));
	db_clientdesc->Packet(&t, sizeof(TPlayerItem));
}


//Add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	t.shop_id = item->GetPremiumPrivateShopVid();
	t.price = item->GetPremiumPrivateShopPrice();
#endif


