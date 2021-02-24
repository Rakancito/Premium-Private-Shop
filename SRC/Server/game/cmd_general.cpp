//Search

ACMD(do_mall_close)
{
	if (ch->GetMall())
	{
		ch->SetMallLoadTime(thecore_pulse());
		ch->CloseMall();
		ch->Save();
	}
}

//Add after

#ifdef ENABLE_PREMIUM_PRIVATE_SHOP
ACMD(do_premium_private_shop_password)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	ch->ReqPremiumPrivateShopLoad(arg1);
}

ACMD(do_premium_private_shop_close)
{
	ch->ClosePremiumPrivateShop();
}

ACMD(do_click_premium_private_shop)
{
	if ((ch->GetGMLevel() <= GM_PLAYER) && (ch->GetDungeon() || ch->GetWarMap()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT( "You cannot open the safebox in dungeon or at war."));
		return;
	}

	ch->SetSafeboxOpenPosition();
	ch->ChatPacket(CHAT_TYPE_COMMAND, "ShowMePremiumPrivateShopPassword");
}
#endif
