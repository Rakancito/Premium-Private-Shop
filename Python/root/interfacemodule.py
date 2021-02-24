#Search 

		# ITEM_MALL
		wndMall = uiSafebox.MallWindow()
		self.wndMall = wndMall
		# END_OF_ITEM_MALL

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			wndPremiumPrivateShop = uiSafebox.PremiumPrivateShopWindow()
			self.wndPremiumPrivateShop = wndPremiumPrivateShop
			wndPremiumPrivateShop.BindInterface(self)

#Search

		self.privateShopBuilder = uiPrivateShopBuilder.PrivateShopBuilder()
		if app.WJ_ENABLE_TRADABLE_ICON:
			self.privateShopBuilder.BindInterface(self)
			self.privateShopBuilder.SetInven(self.wndInventory)
			self.wndInventory.BindWindow(self.privateShopBuilder)
		self.privateShopBuilder.Hide()

#Add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			self.wndPremiumPrivateShop = uiSafebox.PremiumPrivateShopWindow()
			if app.WJ_ENABLE_TRADABLE_ICON:		
				self.wndPremiumPrivateShop.BindInterface(self)
				self.wndPremiumPrivateShop.SetInven(self.wndInventory)
				self.wndInventory.BindWindow(self.wndPremiumPrivateShop)
			self.wndPremiumPrivateShop.Hide()

#Search

		# ITEM_MALL
		self.wndMall.SetItemToolTip(self.tooltipItem)
		# END_OF_ITEM_MALL

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			self.wndPremiumPrivateShop.SetItemToolTip(self.tooltipItem)

#Search

		if self.wndMall:
			self.wndMall.Destroy()

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			if self.wndPremiumPrivateShop:
				self.wndPremiumPrivateShop.Destroy()

#Search

		del self.wndMall

#add after

		if app.ENABLE_PREMIUM_PRIVATE_SHOP:
			del self.wndPremiumPrivateShop

#Search

	def OpenItemMall(self):
		if constInfo.IN_GAME_SHOP_ENABLE:
			import event
			constInfo.ITEMSHOP["questCMD"] = 'LOAD#'+str(constInfo.ITEMSHOP['tableUpdate'])
			event.QuestButtonClick(int(constInfo.ITEMSHOP["qid"]))

		self.mallPageDlg.Open()
	# END_OF_ITEM_MALL

#add after

	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		def RefreshPremiumPrivateShop(self):
			self.wndPremiumPrivateShop.RefreshPremiumPrivateShop()

#Search

	def CommandCloseMall(self):
		self.wndMall.CommandCloseMall()
	# END_OF_ITEM_MALL

#add after

	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		def AskPremiumPrivateShopPassword(self):
			if self.wndPremiumPrivateShop.IsShow():
				return
			self.dlgPassword.SetTitle(localeInfo.MALL_PASSWORD_TITLE)
			self.dlgPassword.SetSendMessage("/premium_private_shop_password ")
			self.dlgPassword.ShowDialog()

		def OpenPremiumPrivateShopWindow(self, size, gold, time):
			self.dlgPassword.CloseDialog()
			self.wndPremiumPrivateShop.ShowWindow(size, gold, time)
			
		def RefreshGoldPremiumPrivateShopWindow(self, gold):
			self.wndPremiumPrivateShop.RefreshGoldMoney(gold)

		def CommandClosePremiumPrivateShop(self):
			self.wndPremiumPrivateShop.CommandClosePremiumPrivateShop()

