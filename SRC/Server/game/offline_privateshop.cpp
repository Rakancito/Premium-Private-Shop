#include "stdafx.h"
#include "offline_privateshop.h"
#include "char_manager.h"
#include "shop.h"
#include "desc.h"
#include "db.h"

CPremiumPrivateShop::CPremiumPrivateShop(LPSHOP pkShop, DWORD dwTime, DWORD dwRace) : 
			m_pkShop(pkShop), m_dwEndTime(dwTime), m_dwRaceVnum(dwRace), m_dwVid(CHARACTER_MANAGER::instance().AllocVID())
{
	Initialize();
}

CPremiumPrivateShop::~CPremiumPrivateShop(void)
{
	Destroy();
}

void CPremiumPrivateShop::Initialize(void)
{
	CEntity::Initialize(ENTITY_SHOP);
	m_dwShopVid = 0;
	m_dwPlayerID = 0;
	m_strSign = "";
	m_strOwnerName = "";
	m_dwStartTime = time(0);
}

void CPremiumPrivateShop::Destroy(void)
{
	CEntity::Destroy();

	if (GetSectree())
		GetSectree()->RemoveEntity(this);

	m_dwRaceVnum = 0;
	m_dwVid = 0;
	m_dwStartTime = 0;
	m_dwEndTime = 0;
	m_dwShopVid = 0;
	m_dwPlayerID = 0;
	
	M2_DELETE(m_pkShop);
	m_pkShop = NULL;
	m_strSign = "";
	m_strOwnerName = "";
}

void CPremiumPrivateShop::EncodeInsertPacket(LPENTITY ent)
{
	if (ent->GetType() != ENTITY_CHARACTER)
		return;

	LPDESC d;

	if (!(d = ent->GetDesc()))
		return;

	TPacketGCCharacterAdd pack;
	memset(&pack, 0, sizeof(pack));

	pack.header = HEADER_GC_CHARACTER_ADD;
	pack.dwVID = m_dwVid;
	pack.bType = CHAR_TYPE_NPC;
	pack.x = GetX();
	pack.y = GetY();
	pack.z = GetZ();
	pack.wRaceNum = m_dwRaceVnum;
	pack.bStateFlag = ADD_CHARACTER_STATE_GUNGON;

	d->Packet(&pack, sizeof(pack));

	TPacketGCCharacterAdditionalInfo addPacket;
	memset(&addPacket, 0, sizeof(TPacketGCCharacterAdditionalInfo));

	addPacket.header = HEADER_GC_CHAR_ADDITIONAL_INFO;
	addPacket.dwVID = m_dwVid;
	strlcpy(addPacket.name, m_strOwnerName.c_str(), sizeof(addPacket.name));

	d->Packet(&addPacket, sizeof(addPacket));

	TPacketGCShopSign p;

	p.bHeader = HEADER_GC_SHOP_SIGN;
	p.dwVID = m_dwVid;
	strlcpy(p.szSign, m_strSign.c_str(), sizeof(p.szSign));

	d->Packet(&p, sizeof(p));
}

void CPremiumPrivateShop::EncodeRemovePacket(LPENTITY ent)
{
	if (ent->GetType() != ENTITY_CHARACTER)
		return;

	LPDESC d;

	if (!(d = ent->GetDesc()))
		return;

	TPacketGCCharacterDelete pack;

	pack.header	= HEADER_GC_CHARACTER_DEL;
	pack.id	= m_dwVid;

	d->Packet(&pack, sizeof(TPacketGCCharacterDelete));

	TPacketGCShopSign p;

	p.bHeader = HEADER_GC_SHOP_SIGN;
	p.dwVID = m_dwVid;
	p.szSign[0] = '\0';

	d->Packet(&p, sizeof(p));
}
