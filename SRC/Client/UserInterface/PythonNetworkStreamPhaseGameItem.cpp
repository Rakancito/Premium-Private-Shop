//Search

bool CPythonNetworkStream::SendSafeBoxItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, BYTE byCount)
{
	...
}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

bool CPythonNetworkStream::RecvPremiumPrivateShopItemDelPacket()
{
	TPacketGCItemDel kItemDel;
	if (!Recv(sizeof(kItemDel), &kItemDel))
		return false;

	CPythonSafeBox::Instance().DelPremiumPrivateShopItemData(kItemDel.pos);

	__RefreshPremiumPrivateShopWindow();
	Tracef(" >> CPythonNetworkStream::RecvMallItemDelPacket\n");

	return true;
}

bool CPythonNetworkStream::RecvPremiumPrivateShopItemSetPacket()
{
	TPacketGCItemSetDelPremiumPrivateShop kItemSet;
	
	if (!Recv(sizeof(kItemSet), &kItemSet))
	{
		TraceError("Error Packet Premium Private Shop Size");
		return false;
	}

	TItemData kItemData;
	kItemData.vnum = kItemSet.vnum;
	kItemData.count = kItemSet.count;
	kItemData.flags = kItemSet.flags;
	kItemData.anti_flags = kItemSet.anti_flags;
	for (int isocket = 0; isocket < ITEM_SOCKET_SLOT_MAX_NUM; ++isocket)
		kItemData.alSockets[isocket] = kItemSet.alSockets[isocket];
	for (int iattr = 0; iattr < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++iattr)
		kItemData.aAttr[iattr] = kItemSet.aAttr[iattr];
#ifdef ENABLE_TRANSMUTATION
	kItemData.transmutation = kItemSet.transmutation;
#endif
	kItemData.dwPrice = kItemSet.dwPrice;

	CPythonSafeBox::Instance().SetPremiumPrivateShopItemData(kItemSet.Cell.cell, kItemData);

	__RefreshPremiumPrivateShopWindow();

	return true;
}

bool CPythonNetworkStream::SendPremiumPrivateShopItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, BYTE byCount)
{
	__PlayPremiumPrivateShopItemDropSound(bySourcePos);

	TPacketCGItemMove kItemMove;
	kItemMove.header = HEADER_CG_PREMIUM_PRIVATE_SHOP_ITEM_MOVE;
	kItemMove.pos = TItemPos(INVENTORY, bySourcePos);
	kItemMove.num = byCount;
	kItemMove.change_pos = TItemPos(INVENTORY, byTargetPos);
	if (!Send(sizeof(kItemMove), &kItemMove))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendPremiumPrivateCheckoutGoldOutPacket()
{
	TPacketCGPremiumPrivateShopCheck kPremiumCheckout;
	kPremiumCheckout.bHeader = HEADER_CG_PREMIUM_PRIVATE_SHOP;
	kPremiumCheckout.bSubHeader = SUB_HEADER_PREMIUM_PRIVATE_SHOP_GOLD_DEL;
	if (!Send(sizeof(kPremiumCheckout), &kPremiumCheckout))
		return false;
	return SendSequence();
}

bool CPythonNetworkStream::SendPremiumPrivateShopCheckoutPacket(BYTE bySafeBoxPos, TItemPos InventoryPos)
{
	__PlayPremiumPrivateShopItemDropSound(bySafeBoxPos);
	TPacketCGPremiumPrivateShopCheck kPremiumCheckout;
	kPremiumCheckout.bHeader = HEADER_CG_PREMIUM_PRIVATE_SHOP;
	kPremiumCheckout.bSubHeader = SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_DEL;
	kPremiumCheckout.bSafePos = bySafeBoxPos;
	kPremiumCheckout.ItemPos = InventoryPos;
	if (!Send(sizeof(kPremiumCheckout), &kPremiumCheckout))
		return false;
	return SendSequence();
}

bool CPythonNetworkStream::SendPremiumPrivateShopCheckinPacket(TItemPos InventoryPos, BYTE bySafeBoxPos, DWORD dwPrice)
{
	__PlayPremiumPrivateShopItemDropSound(bySafeBoxPos);

	TPacketCGPremiumPrivateShopCheck kPremiumCheckout;
	kPremiumCheckout.bHeader = HEADER_CG_PREMIUM_PRIVATE_SHOP;
	kPremiumCheckout.bSubHeader = SUB_HEADER_PREMIUM_PRIVATE_SHOP_ITEM_ADD;
	kPremiumCheckout.bSafePos = bySafeBoxPos;
	kPremiumCheckout.ItemPos = InventoryPos;
	kPremiumCheckout.dwPrice = dwPrice;
	if (!Send(sizeof(kPremiumCheckout), &kPremiumCheckout))
		return false;

	return SendSequence();
}
#endif

//Search

// Mall
//////////////////////////////////////////////////////////////////////////

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

//PremiumPrivateShop
//////////////////////////////////////////////////////////////////////////

bool CPythonNetworkStream::RecPremiumPrivateShop() 
{
	TPacketCGPremiumPrivateShopSize PremiumPrivateShop;

	if (!Recv(sizeof(PremiumPrivateShop), &PremiumPrivateShop))
	{
		TraceError("Fail to size Packet PremiumPrivateShop");
		return false;
	}

	switch (PremiumPrivateShop.bSubHeader)
	{
		case SUB_HEADER_PREMIUM_PRIVATE_SHOP_OPEN:
			{
				CPythonSafeBox::Instance().OpenPremiumPrivateShop(PremiumPrivateShop.bSize);
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenPremiumPrivateShopWindow", Py_BuildValue("(iii)", PremiumPrivateShop.bSize, PremiumPrivateShop.dwGold, PremiumPrivateShop.dwTime));
			}
			break;
		case SUB_HEADER_PREMIUM_PRIVATE_SHOP_GOLD_DEL:
			{
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGoldPremiumPrivateShopWindow", Py_BuildValue("(i)", PremiumPrivateShop.dwGold));
			}
			break;
		default:
			{
				TraceError("Error! not found sub header %d packet in PremiumprivateShop", PremiumPrivateShop.bSubHeader);
			}
			break;
	}

	return true;
}

//PremiumPrivateShop
//////////////////////////////////////////////////////////////////////////
#endif


//Search

void CPythonNetworkStream::__PlayMallItemDropSound(UINT uSlotPos)
{
	...
}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CPythonNetworkStream::__PlayPremiumPrivateShopItemDropSound(UINT uSlotPos)
{
	DWORD dwItemID;
	CPythonSafeBox& rkSafeBox=CPythonSafeBox::Instance();
	if (!rkSafeBox.GetSlotPremiumPrivateShopItemID(uSlotPos, &dwItemID))
		return;

	CPythonItem& rkItem=CPythonItem::Instance();
	rkItem.PlayDropSound(dwItemID);
}
#endif
