//Search

void CPythonNetworkStream::__RefreshMallWindow()
{
	m_isRefreshMallWnd=true;
}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
void CPythonNetworkStream::__RefreshPremiumPrivateShopWindow()
{
	m_isRefreshPremiumPrivateShopWnd =true;
}
#endif

//Search

			case HEADER_GC_MALL_DEL:

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
			case HEADER_GC_PREMIUM_PRIVATE_SHOP:
				ret = RecPremiumPrivateShop();
				break;

			case HEADER_GC_PREMIUM_PRIVATE_SHOP_SET:
				ret = RecvPremiumPrivateShopItemSetPacket();
				break;

			case HEADER_GC_PREMIUM_PRIVATE_SHOP_DEL:
				ret = RecvPremiumPrivateShopItemDelPacket();
				break;
#endif

//Search

	if (m_isRefreshMallWnd)
	{
		m_isRefreshMallWnd=false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshMall", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	if (m_isRefreshPremiumPrivateShopWnd)
	{
		m_isRefreshMallWnd=false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshPremiumPrivateShop", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}

#endif

//Search

	m_isRefreshMallWnd=false;

//add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
	m_isRefreshPremiumPrivateShopWnd =false;
#endif
