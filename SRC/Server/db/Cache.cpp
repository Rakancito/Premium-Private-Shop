//On this function

void CItemCache::OnFlush()

//Search the assignments

		int iLen = snprintf(szColumns, sizeof(szColumns), "id, owner_id, window, pos, count, vnum, transmutation");
		int iValueLen = snprintf(szValues, sizeof(szValues), "%u, %u, %d, %d, %u, %u, %u", p->id, p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation);
		int iUpdateLen = snprintf(szUpdate, sizeof(szUpdate), "owner_id=%u, window=%d, pos=%d, count=%u, vnum=%u, transmutation=%u", p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation);

//Replace with and remember I have transmutation like transmutation if you have like changelook just change, if you don't have just remove please "logic"

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
		int iLen = snprintf(szColumns, sizeof(szColumns), "id, owner_id, window, pos, count, vnum, transmutation, price, shop_id");
		int iValueLen = snprintf(szValues, sizeof(szValues), "%u, %u, %d, %d, %u, %u, %u, %llu, %u", p->id, p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation, p->price, p->shop_id);
		int iUpdateLen = snprintf(szUpdate, sizeof(szUpdate), "owner_id=%u, window=%d, pos=%d, count=%u, vnum=%u, transmutation=%u, price=%llu, shop_id=%u", p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation, p->price, p->shop_id);

#else
#ifdef ENABLE_TRANSMUTATION
		int iLen = snprintf(szColumns, sizeof(szColumns), "id, owner_id, window, pos, count, vnum, transmutation");
		int iValueLen = snprintf(szValues, sizeof(szValues), "%u, %u, %d, %d, %u, %u, %u", p->id, p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation);
		int iUpdateLen = snprintf(szUpdate, sizeof(szUpdate), "owner_id=%u, window=%d, pos=%d, count=%u, vnum=%u, transmutation=%u", p->owner, p->window, p->pos, p->count, p->vnum, p->transmutation);
#else
		int iLen = snprintf(szColumns, sizeof(szColumns), "id, owner_id, window, pos, count, vnum");
		int iValueLen = snprintf(szValues, sizeof(szValues), "%u, %u, %d, %d, %u, %u", p->id, p->owner, p->window, p->pos, p->count, p->vnum);
		int iUpdateLen = snprintf(szUpdate, sizeof(szUpdate), "owner_id=%u, window=%d, pos=%d, count=%u, vnum=%u", p->owner, p->window, p->pos, p->count, p->vnum);
#endif
#endif



