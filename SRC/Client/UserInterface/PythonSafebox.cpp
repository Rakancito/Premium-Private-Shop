//Search

DWORD CPythonSafeBox::GetMallSize()
{
	...
}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP

void CPythonSafeBox::SetPremiumPrivateShopMoney(DWORD m_dwMoney)
{
	m_dwMoneyShop = m_dwMoney;
}

DWORD CPythonSafeBox::GetPremiumPrivateShopMoney()
{
	return m_dwMoneyShop;
}

void CPythonSafeBox::OpenPremiumPrivateShop(int iSize)
{
	m_PremiumPrivateShopItemInstanceVector.clear();
	m_PremiumPrivateShopItemInstanceVector.resize(SAFEBOX_SLOT_X_COUNT * (iSize));

	for (DWORD i = 0; i < m_PremiumPrivateShopItemInstanceVector.size(); ++i)
	{
		TItemData& rInstance = m_PremiumPrivateShopItemInstanceVector[i];
		ZeroMemory(&rInstance, sizeof(rInstance));
	}
}

void CPythonSafeBox::SetPremiumPrivateShopItemData(DWORD dwSlotIndex, const TItemData& rItemData)
{
	if (dwSlotIndex >= m_PremiumPrivateShopItemInstanceVector.size())
	{
		TraceError("CPythonSafeBox::SetPremiumPrivateShopItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	m_PremiumPrivateShopItemInstanceVector[dwSlotIndex] = rItemData;
}

void CPythonSafeBox::DelPremiumPrivateShopItemData(DWORD dwSlotIndex)
{
	if (dwSlotIndex >= m_PremiumPrivateShopItemInstanceVector.size())
	{
		TraceError("CPythonSafeBox::DelPremiumPrivateShopItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	TItemData& rInstance = m_PremiumPrivateShopItemInstanceVector[dwSlotIndex];
	ZeroMemory(&rInstance, sizeof(rInstance));
}

BOOL CPythonSafeBox::GetPremiumPrivateShopItemDataPtr(DWORD dwSlotIndex, TItemData** ppInstance)
{
	if (dwSlotIndex >= m_PremiumPrivateShopItemInstanceVector.size())
	{
		TraceError("CPythonSafeBox::GetPremiumPrivateShopSlotItemID(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*ppInstance = &m_PremiumPrivateShopItemInstanceVector[dwSlotIndex];

	return TRUE;
}

BOOL CPythonSafeBox::GetSlotPremiumPrivateShopItemID(DWORD dwSlotIndex, DWORD* pdwItemID)
{
	if (dwSlotIndex >= m_PremiumPrivateShopItemInstanceVector.size())
	{
		TraceError("CPythonSafeBox::GetPremiumPrivateShopSlotItemID(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*pdwItemID = m_PremiumPrivateShopItemInstanceVector[dwSlotIndex].vnum;

	return TRUE;
}
DWORD CPythonSafeBox::GetPremiumPrivateShopSize()
{
	return m_PremiumPrivateShopItemInstanceVector.size();
}
#endif

//Search

CPythonSafeBox::CPythonSafeBox()
{
	m_dwMoney = 0;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	m_dwMoneyShop = 0;
#endif


//Search

PyObject * safeboxGetMallSize(PyObject * poSelf, PyObject * poArgs)
{
	return Py_BuildValue("i", CPythonSafeBox::Instance().GetMallSize());
}

// add after (watch please, if you are using changelook, change transmutation for changelook)


#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
PyObject* safeboxGetPremiumPrivateShopItemID(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->vnum);
}

PyObject* safeboxGetPremiumPrivateShopItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (!CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->count);
}

PyObject* safeboxGetPremiumPrivateShopItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();
	int iSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSocketIndex))
		return Py_BadArgument();

	if (iSocketIndex >= ITEM_SOCKET_SLOT_MAX_NUM)
		return Py_BuildException();

	TItemData* pItemData;
	if (!CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alSockets[iSocketIndex]);
}

PyObject* safeboxGetPremiumPrivateShopItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		TItemData* pItemData;
		if (CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(iSlotIndex, &pItemData))
			return Py_BuildValue("ii", pItemData->aAttr[iAttrSlotIndex].bType, pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

#ifdef ENABLE_TRANSMUTATION
PyObject* safeboxGetPremiumPrivateShopItemTransmutation(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();

	TItemData* pItemData;
	if (CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildValue("i", pItemData->transmutation);

	return Py_BuildValue("i", 0);
}
#endif

PyObject * safeboxGetPremiumPrivateShopItemFlags(PyObject * poSelf, PyObject * poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData * pInstance;
	if (!CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->flags);
}

PyObject* safeboxGetPremiumPrivateShopItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();

	TItemData* pItemData;
	if (CPythonSafeBox::Instance().GetPremiumPrivateShopItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildValue("i", pItemData->dwPrice);

	return Py_BuildValue("i", 0);
}

PyObject* safeboxGetPremiumPrivateShopSize(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonSafeBox::Instance().GetPremiumPrivateShopSize());
}

PyObject* safeboxGetPremiumPrivateShopMoney(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonSafeBox::Instance().GetPremiumPrivateShopMoney());
}
#endif

//Search

{ "GetMallSize",				safeboxGetMallSize,						METH_VARARGS },

//add after


		//PremiumPrivateShop

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		{ "GetPremiumPrivateShopItemID",				safeboxGetPremiumPrivateShopItemID,					METH_VARARGS },
		{ "GetPremiumPrivateShopItemCount",			safeboxGetPremiumPrivateShopItemCount,				METH_VARARGS },
		{ "GetPremiumPrivateShopItemMetinSocket",		safeboxGetPremiumPrivateShopItemMetinSocket,			METH_VARARGS },
		{ "GetPremiumPrivateShopItemAttribute",		safeboxGetPremiumPrivateShopItemAttribute,			METH_VARARGS },
#ifdef ENABLE_TRANSMUTATION
		{ "GetPremiumPrivateShopItemTransmutation",	safeboxGetPremiumPrivateShopItemTransmutation,		METH_VARARGS },
#endif
		{ "GetPremiumPrivateShopSize",				safeboxGetPremiumPrivateShopSize,						METH_VARARGS },

		{ "GetPremiumPrivateShopItemPrice",			safeboxGetPremiumPrivateShopItemPrice,					METH_VARARGS },
		{ "GetPremiumPrivateShopMoney",				safeboxGetPremiumPrivateShopMoney,						METH_VARARGS },
		{ "GetPremiumPrivateShopItemFlags",				safeboxGetPremiumPrivateShopItemFlags,						METH_VARARGS },		
		
#endif

