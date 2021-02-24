#Search

class PasswordDialog(ui.ScriptWindow):

#add before

if app.ENABLE_PREMIUM_PRIVATE_SHOP:
	import uiInventory
	import uiCommon
	import interfaceModule
	
	g_isBuildingPremiumPrivateShop = False

	def IsBuildingPremiumPrivateShop():
		global g_isBuildingPremiumPrivateShop
		if g_isBuildingPremiumPrivateShop:
			return True
		else:
			return False


#Search

if __name__ == "__main__":

#add before

if app.ENABLE_PREMIUM_PRIVATE_SHOP:
	class PremiumPrivateShopWindow(ui.ScriptWindow):

		BOX_WIDTH = 176
		
		def __init__(self):
			ui.ScriptWindow.__init__(self)
			self.tooltipItem = None
			self.sellingSlotNumber = -1
			self.pageButtonList = []
			self.curPageIndex = 0
			self.isLoaded = 0
			self.xSafeBoxStart = 0
			self.ySafeBoxStart = 0

			self.priceInputBoard = None
			self.wndMoney = 0
			self.wndWon = 0
			
			self.wndTime = 0
			
			if app.WJ_ENABLE_TRADABLE_ICON:
				self.interface = None
				self.wndInventory = uiInventory.InventoryWindow()
				
				self.lockedItems = {i:(-1,-1) for i in range(safebox.SAFEBOX_SLOT_X_COUNT*(safebox.SAFEBOX_SLOT_Y_COUNT-1))}
			
			self.__LoadWindow()

		def __del__(self):
			ui.ScriptWindow.__del__(self)

		def Show(self):
			self.__LoadWindow()

			ui.ScriptWindow.Show(self)		

		def Destroy(self):
			self.ClearDictionary()

			self.tooltipItem = None
			self.wndBoard = None
			self.wndItem = None

			self.priceInputBoard = None
			self.pageButtonList = []
			
			self.wndMoney = 0
			self.wndWon = 0
			
			self.wndTime = 0
			
			if app.WJ_ENABLE_TRADABLE_ICON:
				self.interface = None
				self.wndInventory = None
				
				self.lockedItems = {i:(-1,-1) for i in range(safebox.SAFEBOX_SLOT_X_COUNT*(safebox.SAFEBOX_SLOT_Y_COUNT-1))}
					
		def __LoadWindow(self):
			if self.isLoaded == 1:
				return

			self.isLoaded = 1

			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/premiumprivateshopdialog.py")

			from _weakref import proxy

			## Item
			wndItem = ui.GridSlotWindow()
			wndItem.SetParent(self)
			wndItem.SetPosition(8, 35)
			wndItem.SetSelectEmptySlotEvent(ui.__mem_func__(self.SelectEmptySlot))
			wndItem.SetSelectItemSlotEvent(ui.__mem_func__(self.SelectItemSlot))
			wndItem.SetUnselectItemSlotEvent(ui.__mem_func__(self.UseItemSlot))
			wndItem.SetUseSlotEvent(ui.__mem_func__(self.UseItemSlot))
			wndItem.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
			wndItem.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))
			wndItem.Show()

			## Close Button
			self.GetChild("TitleBar").SetCloseEvent(ui.__mem_func__(self.Close))
			self.GetChild("ExitButton").SetEvent(ui.__mem_func__(self.Close))
			self.GetChild("RefreshMoney").SetEvent(ui.__mem_func__(self.RefreshMoney))
			
			self.wndMoney = self.GetChild("yang_text")
			self.wndWon = self.GetChild("won_text")
			
			self.wndTime = self.GetChild("remain_time_text")
			
			self.wndItem = wndItem
			self.wndBoard = self.GetChild("board")

			## Initialize
			self.SetTableSize(3)
			
		def ShowWindow(self, size, gold, time):

			(self.xSafeBoxStart, self.ySafeBoxStart, z) = player.GetMainCharacterPosition()

			if app.WJ_ENABLE_TRADABLE_ICON:
				self.interface.SetOnTopWindow(player.ON_TOP_WND_PRIVATE_SHOP)
				self.wndInventory.RefreshMarkSlots()
			#	self.interface.RefreshMarkInventoryBag()
			
			self.wndTime.SetText(localeInfo.SecondToDHM(time - app.GetGlobalTimeStamp()))
			
				
			self.wndMoney.SetText(localeInfo.NumberToMoneyString(gold))
			self.wndWon.SetText(0)

			global g_isBuildingPremiumPrivateShop
			g_isBuildingPremiumPrivateShop = True
			
			self.SetTableSize(size)
			self.Show()
			
		def SetTableSize(self, size):

			pageCount = max(1, size / safebox.SAFEBOX_SLOT_Y_COUNT-1)
			pageCount = min(3, pageCount)
			size = safebox.SAFEBOX_SLOT_Y_COUNT-1

			self.wndItem.SetPosition(17, 35)
			self.wndItem.ArrangeSlot(0, safebox.SAFEBOX_SLOT_X_COUNT, size, 32, 32, 0, 0)
			self.wndItem.RefreshSlot()
			self.wndItem.SetSlotBaseImage("d:/ymir work/ui/public/Slot_Base.sub", 1.0, 1.0, 1.0, 1.0)

			self.wndBoard.SetSize(self.BOX_WIDTH + 20, 150 + 32*size)
			self.SetSize(self.BOX_WIDTH + 20, 150 + 32*size)
			self.UpdateRect()
			
		def RefreshPremiumPrivateShop(self):
			getItemID=safebox.GetPremiumPrivateShopItemID
			getItemCount=safebox.GetPremiumPrivateShopItemCount
			setItemID=self.wndItem.SetItemSlot

			for i in xrange(safebox.GetPremiumPrivateShopSize()):
				itemID = getItemID(i)
				itemCount = getItemCount(i)
				if app.ENABLE_TRANSMUTATION:
					self.wndItem.SetCoverButton(i, "d:/ymir work/ui/game/quest/slot_button_00.sub", "d:/ymir work/ui/game/quest/slot_button_00.sub", "d:/ymir work/ui/game/quest/slot_button_00.sub", "icon/item/ingame_convert_mark.tga", FALSE, FALSE)
					itemTransmutation = safebox.GetPremiumPrivateShopItemTransmutation(i)
					if itemTransmutation > 0:
						self.wndItem.DisableCoverButton(i)
					else:
						self.wndItem.EnableCoverButton(i)
				if itemCount <= 1:
					itemCount = 0
				setItemID(i, itemID, itemCount)

			self.wndItem.RefreshSlot()

			if app.WJ_ENABLE_TRADABLE_ICON:
				self.RefreshLockedSlot()
		
		def RefreshMoney(self):
			net.SendPremiumPrivateCheckoutGoldOutPacket()
			
		def RefreshGoldMoney(self, gold):
			self.wndMoney.SetText(localeInfo.NumberToMoneyString(gold))
			
		def SetItemToolTip(self, tooltip):
			self.tooltipItem = tooltip

		def Close(self):
			if self.priceInputBoard:
				return
			net.SendChatPacket("/premium_private_shop_close")

			global g_isBuildingPremiumPrivateShop
			g_isBuildingPremiumPrivateShop = False
			
			if app.WJ_ENABLE_TRADABLE_ICON:
				for privatePos, (itemInvenPage, itemSlotPos) in self.lockedItems.items():
					if itemInvenPage == self.wndInventory.GetInventoryPageIndex():
						self.wndInventory.wndItem.SetCanMouseEventSlot(itemSlotPos)
				
				self.lockedItems = {i:(-1,-1) for i in range(safebox.SAFEBOX_SLOT_X_COUNT*(safebox.SAFEBOX_SLOT_Y_COUNT-1))}
					
				self.interface.SetOnTopWindow(player.ON_TOP_WND_NONE)
				self.wndInventory.RefreshMarkSlots()
				
				#self.interface = interfaceModule.Interface()
				#self.interface.SetOnTopWindow(player.ON_TOP_WND_NONE)
				#self.wndInventory.RefreshMarkSlots()
				
		def CommandClosePremiumPrivateShop(self):
			if self.tooltipItem:
				self.tooltipItem.HideToolTip()

			if app.WJ_ENABLE_TRADABLE_ICON:
				if self.interface:
					self.interface.SetOnTopWindow(player.ON_TOP_WND_NONE)
					self.wndInventory.RefreshMarkSlots()
			#		self.interface.RefreshMarkInventoryBag()

			global g_isBuildingPremiumPrivateShop
			g_isBuildingPremiumPrivateShop = False
			
			self.Hide()

			
		## Slot Event
		def SelectEmptySlot(self, selectedSlotPos):
			if app.ENABLE_PREMIUM_PRIVATE_SHOP:

				if mouseModule.mouseController.isAttached():

					attachedSlotType = mouseModule.mouseController.GetAttachedType()
					attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()

					if player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP == attachedSlotType:
						net.SendPremiumPrivateShopItemMovePacket(attachedSlotPos, selectedSlotPos, 0)
					else:
						attachedInvenType = player.SlotTypeToInvenType(attachedSlotType)
						if player.RESERVED_WINDOW == attachedInvenType:
							return
							
						if player.ITEM_MONEY == mouseModule.mouseController.GetAttachedItemIndex():
							return

						else:
						
							itemVNum = player.GetItemIndex(attachedInvenType, attachedSlotPos)
							item.SelectItem(itemVNum)

							if item.IsAntiFlag(item.ANTIFLAG_GIVE) or item.IsAntiFlag(item.ANTIFLAG_MYSHOP):
								chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATE_SHOP_CANNOT_SELL_ITEM)
								return
							if app.WJ_ENABLE_TRADABLE_ICON and player.SLOT_TYPE_INVENTORY == attachedSlotType:
								self.CantTradableItem(selectedSlotPos, attachedSlotPos)
							priceInputBoard = uiCommon.MoneyInputDialog()
							priceInputBoard.SetTitle(localeInfo.PRIVATE_SHOP_INPUT_PRICE_DIALOG_TITLE)
							priceInputBoard.SetAcceptEvent(ui.__mem_func__(self.AcceptInputPrice))
							priceInputBoard.SetCancelEvent(ui.__mem_func__(self.CancelInputPrice))
							priceInputBoard.Open()

							#itemPrice=GetPrivateShopItemPrice(itemVNum)

							#if itemPrice>0:
							#	priceInputBoard.SetValue(itemPrice)

							self.priceInputBoard = priceInputBoard
							self.priceInputBoard.itemVNum = itemVNum
							self.priceInputBoard.sourceWindowType = attachedInvenType
							self.priceInputBoard.sourceSlotPos = attachedSlotPos
							self.priceInputBoard.targetSlotPos = selectedSlotPos
							
					mouseModule.mouseController.DeattachObject()		
			else:
				if mouseModule.mouseController.isAttached():

					chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MALL_CANNOT_INSERT)
					mouseModule.mouseController.DeattachObject()

		def SelectItemSlot(self, selectedSlotPos):
			if mouseModule.mouseController.isAttached():

				attachedSlotType = mouseModule.mouseController.GetAttachedType()

				if player.SLOT_TYPE_INVENTORY == attachedSlotType:

					if player.ITEM_MONEY == mouseModule.mouseController.GetAttachedItemIndex():
						net.SendSafeboxSaveMoneyPacket(mouseModule.mouseController.GetAttachedItemCount())
						snd.PlaySound("sound/ui/money.wav")

					else:
						attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
				mouseModule.mouseController.DeattachObject()

			else:

				curCursorNum = app.GetCursor()
				if app.SELL == curCursorNum:
					chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SAFEBOX_SELL_DISABLE_SAFEITEM)

				elif app.BUY == curCursorNum:
					chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SHOP_BUY_INFO)

				else:
					selectedItemID = safebox.GetPremiumPrivateShopItemID(selectedSlotPos)
					mouseModule.mouseController.AttachObject(self, player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP, selectedSlotPos, selectedItemID)
					snd.PlaySound("sound/ui/pick.wav")


		def AcceptInputPrice(self):
			if not self.priceInputBoard:
				return True

			text = self.priceInputBoard.GetText()

			if not text:
				return True

			if not text.isdigit():
				return True

			if int(text) <= 0:
				return True
					
			attachedInvenType = self.priceInputBoard.sourceWindowType
			sourceSlotPos = self.priceInputBoard.sourceSlotPos
			targetSlotPos = self.priceInputBoard.targetSlotPos

			price = int(self.priceInputBoard.GetText())

			net.SendPremiumPrivateShopCheckinPacket(attachedInvenType, sourceSlotPos, targetSlotPos, price)
			snd.PlaySound("sound/ui/drop.wav")
			self.RefreshPremiumPrivateShop()

			#####
			if app.WJ_ENABLE_TRADABLE_ICON:
				for privatePos, (itemInvenPage, itemSlotPos) in self.lockedItems.items():
					if itemInvenPage == self.wndInventory.GetInventoryPageIndex():
						self.wndInventory.wndItem.SetCanMouseEventSlot(itemSlotPos)
				
				self.lockedItems = {i:(-1,-1) for i in range(safebox.SAFEBOX_SLOT_X_COUNT*(safebox.SAFEBOX_SLOT_Y_COUNT-1))}
					
			self.priceInputBoard = None
			return True

		def CancelInputPrice(self):
			if app.WJ_ENABLE_TRADABLE_ICON:
				itemInvenPage = self.priceInputBoard.sourceSlotPos / player.INVENTORY_PAGE_SIZE
				itemSlotPos = self.priceInputBoard.sourceSlotPos - (itemInvenPage * player.INVENTORY_PAGE_SIZE)
				if self.wndInventory.GetInventoryPageIndex() == itemInvenPage:
					self.wndInventory.wndItem.SetCanMouseEventSlot(itemSlotPos)

				self.lockedItems[self.priceInputBoard.targetSlotPos] = (-1, -1)
			self.priceInputBoard = None
			return True
			
		def UseItemSlot(self, slotIndex):
			if mouseModule.mouseController.isAttached():
				mouseModule.mouseController.DeattachObject()

		def __ShowToolTip(self, slotIndex):
			if self.tooltipItem:
				self.tooltipItem.SetPremiumPrivateShopItem(slotIndex)

		def OverInItem(self, slotIndex):
			self.__ShowToolTip(slotIndex)

		def OverOutItem(self):
			self.wndItem.SetUsableItem(FALSE)
			if self.tooltipItem:
				self.tooltipItem.HideToolTip()

		def OnPressEscapeKey(self):
			if self.priceInputBoard:
				return
			self.Close()
			return TRUE

		def OnUpdate(self):

			USE_SAFEBOX_LIMIT_RANGE = 1000

			(x, y, z) = player.GetMainCharacterPosition()
			if abs(x - self.xSafeBoxStart) > USE_SAFEBOX_LIMIT_RANGE or abs(y - self.ySafeBoxStart) > USE_SAFEBOX_LIMIT_RANGE:
				self.Close()

		if app.WJ_ENABLE_TRADABLE_ICON:				
			def CantTradableItem(self, destSlotIndex, srcSlotIndex):
				itemInvenPage = srcSlotIndex / player.INVENTORY_PAGE_SIZE
				localSlotPos = srcSlotIndex - (itemInvenPage * player.INVENTORY_PAGE_SIZE)
				self.lockedItems[destSlotIndex] = (itemInvenPage, localSlotPos)
				if self.wndInventory.GetInventoryPageIndex() == itemInvenPage:
					self.wndInventory.wndItem.SetCantMouseEventSlot(localSlotPos)

			def RefreshLockedSlot(self):
				if self.wndInventory:
					for privatePos, (itemInvenPage, itemSlotPos) in self.lockedItems.items():
						if self.wndInventory.GetInventoryPageIndex() == itemInvenPage:
							self.wndInventory.wndItem.SetCantMouseEventSlot(itemSlotPos)

					self.wndInventory.wndItem.RefreshSlot()

			def BindInterface(self, interface):
				self.interface = interface

			def OnTop(self):
				if self.interface:
					self.interface.SetOnTopWindow(player.ON_TOP_WND_PRIVATE_SHOP)
					self.wndInventory.RefreshMarkSlots()
					#self.interface.RefreshMarkInventoryBag()

			def SetInven(self, wndInventory):
				from _weakref import proxy
				self.wndInventory = proxy(wndInventory)	