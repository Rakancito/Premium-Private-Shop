#pragma once
#include "vid.h"
#include "entity.h"
#include "sectree_manager.h"
#include "../common/tables.h"
#include "packet.h"

class CPremiumPrivateShop : public CEntity
{
	public:
		CPremiumPrivateShop(LPSHOP pkShop, DWORD dwTime, DWORD dwRace);
		virtual ~CPremiumPrivateShop(void);

		void Initialize(void);
		void Destroy(void);

		DWORD GetRaceVnum() { return m_dwRaceVnum; }
		DWORD GetVid() { return m_dwVid; }
		DWORD GetTime() { return m_dwEndTime; }
		DWORD GetShopVid() { return m_dwShopVid; }
		DWORD GetPlayerID() { return m_dwPlayerID; }
		std::string GetOwnerName() { return m_strOwnerName; }
		LPSHOP GetShop() { return m_pkShop; }
		void SetShopVid(DWORD dwShopVid) { m_dwShopVid = dwShopVid; }
		void SetSign(const std::string& strSign) { m_strSign = strSign; }
		void SetOwnerName(const std::string& strOwnerName) { m_strOwnerName = strOwnerName; }
		void SetPlayerID(DWORD dwPlayerID) { m_dwPlayerID = dwPlayerID; }

	protected:
		virtual void EncodeInsertPacket(LPENTITY ent);
		virtual void EncodeRemovePacket(LPENTITY ent);

		DWORD m_dwRaceVnum;
		DWORD m_dwVid;
		DWORD m_dwEndTime;
		DWORD m_dwStartTime;
		DWORD m_dwShopVid;
		DWORD m_dwPlayerID;
		LPSHOP m_pkShop;
		std::string m_strSign;
		std::string m_strOwnerName;
};

