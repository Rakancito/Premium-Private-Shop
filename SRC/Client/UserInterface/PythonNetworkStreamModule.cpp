//Search

void initnet()

//add before

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

PyObject* netSendPremiumPrivateCheckoutGoldOutPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendPremiumPrivateCheckoutGoldOutPacket();

	return Py_BuildNone();
}

PyObject* netSendPremiumPrivateShopItemMovePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSourcePos;
	if (!PyTuple_GetInteger(poArgs, 0, &iSourcePos))
		return Py_BuildException();
	int iTargetPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iTargetPos))
		return Py_BuildException();
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 2, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendPremiumPrivateShopItemMovePacket(iSourcePos, iTargetPos, iCount);

	return Py_BuildNone();
}

PyObject* netSendPremiumPrivateShopCheckoutPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSafeBoxPos;
	TItemPos InventoryPos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &iSafeBoxPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &iSafeBoxPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &InventoryPos.cell))
			return Py_BuildException();
		break;
	default:
		break;
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendPremiumPrivateShopCheckoutPacket(iSafeBoxPos, InventoryPos);

	return Py_BuildNone();
}

PyObject* netSendPremiumPrivateShopCheckinPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos InventoryPos;
	int iSafeBoxPos;
	int iPrice;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		InventoryPos.window_type = INVENTORY;
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &iSafeBoxPos))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &iSafeBoxPos))
			return Py_BuildException();
		break;
	case 4:
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &iSafeBoxPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 3, &iPrice))
			return Py_BuildException();
		break;
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendPremiumPrivateShopCheckinPacket(InventoryPos, iSafeBoxPos, iPrice);

	return Py_BuildNone();
}
#endif

//Search

{ "SendSafeboxItemMovePacket",			netSendSafeboxItemMovePacket,			METH_VARARGS },

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		{ "SendPremiumPrivateShopCheckinPacket",			netSendPremiumPrivateShopCheckinPacket,			METH_VARARGS },
		{ "SendPremiumPrivateShopCheckoutPacket",			netSendPremiumPrivateShopCheckoutPacket,			METH_VARARGS },
		{ "SendPremiumPrivateShopItemMovePacket",			netSendPremiumPrivateShopItemMovePacket,			METH_VARARGS },
		{ "SendPremiumPrivateCheckoutGoldOutPacket",		netSendPremiumPrivateCheckoutGoldOutPacket,			METH_VARARGS },
#endif