#Search

import player


#add after

if app.ENABLE_PREMIUM_PRIVATE_SHOP:
	import uiSafebox

#search

			self.mallButton = self.GetChild2("MallButton")

#add after


			if app.ENABLE_PREMIUM_PRIVATE_SHOP:
				self.premiumPrivateShopButton = self.GetChild("premium_private_shop_button")

#Search

		if self.mallButton:
			self.mallButton.SetEvent(ui.__mem_func__(self.ClickMallButton))

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			if self.premiumPrivateShopButton:
				self.premiumPrivateShopButton.SetEvent(ui.__mem_func__(self.ClickPremiumPrivateShopButton))

#Search

		self.mallButton = None
		self.DSSButton = None

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			self.premiumPrivateShopButton = None

#Search

	def _Shop2(self):
		print "click_offline_shop_button"
		#self.interface.ToggleOfflineShopAdminPanelWindow()

#add after

	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		def ClickPremiumPrivateShopButton(self):
			print "click_premium_private_shop_button"
			net.SendChatPacket("/click_premium_private_shop")

#Search

			elif player.SLOT_TYPE_MALL == attachedSlotType:
				net.SendMallCheckoutPacket(attachedSlotPos, selectedSlotPos)

#Add after

			elif player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP == attachedSlotType and app.ENABLE_PREMIUM_PRIVATE_SHOP:
				net.SendPremiumPrivateShopCheckoutPacket(attachedSlotPos, selectedSlotPos)

#Search

		if uiPrivateShopBuilder.IsBuildingPrivateShop():
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.USE_ITEM_FAILURE_PRIVATE_SHOP)
			return

#add before or after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			if uiSafebox.IsBuildingPremiumPrivateShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
				return

#Search

		if uiPrivateShopBuilder.IsBuildingPrivateShop():
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
			return

#add before or after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			if uiSafebox.IsBuildingPremiumPrivateShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
				return