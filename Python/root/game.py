#Search

import uiprivateshopbuilder

#Add

if app.ENABLE_PREMIUM_PRIVATE_SHOP:
	import uiSafebox

#Search

	def RefreshMall(self):
		self.interface.RefreshMall()
	# END_OF_ITEM_MALL


#add after

	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		# PREMIUMPRIVATESHOPWINDOW
		def OpenPremiumPrivateShopWindow(self, size, gold, time):
			self.interface.OpenPremiumPrivateShopWindow(size, gold, time)

		def RefreshPremiumPrivateShop(self):
			self.interface.RefreshPremiumPrivateShop()
			
		def RefreshGoldPremiumPrivateShopWindow(self, gold):
			self.interface.RefreshGoldPremiumPrivateShopWindow(gold)
		# PREMIUMPRIVATESHOPWINDOW

#Search all

		if uiPrivateShopBuilder.IsBuildingPrivateShop():			
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
			return

#add before or after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			if uiSafebox.IsBuildingPremiumPrivateShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
				return

#Search

			# ITEM_MALL
			"CloseMall"				: self.CommandCloseMall,
			"ShowMeMallPassword"	: self.AskMallPassword,
			"item_mall"				: self.__ItemMall_Open,
			# END_OF_ITEM_MALL

#add after

			# ENABLE_PREMIUM_PRIVATE_SHOP
			"ShowMePremiumPrivateShopPassword"		: self.AskPremiumPrivateShopPassword,
			"ClosePremiumPrivateShop"				: self.CommandClosePremiumPrivateShop,	

#Search 

	def CommandCloseMall(self):
		self.interface.CommandCloseMall()
	# END_OF_ITEM_MALL

#add after

	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		def AskPremiumPrivateShopPassword(self):
			self.interface.AskPremiumPrivateShopPassword()

		def CommandClosePremiumPrivateShop(self):
			self.interface.CommandClosePremiumPrivateShop()