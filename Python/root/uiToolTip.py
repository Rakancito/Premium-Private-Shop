#Search

	def SetMallItem(self, slotIndex):
		...
			self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetItemFlags(slotIndex))

#add after


	if app.ENABLE_PREMIUM_PRIVATE_SHOP:
		def SetPremiumPrivateShopItem(self, slotIndex):
			itemVnum = safebox.GetPremiumPrivateShopItemID(slotIndex)
			if 0 == itemVnum:
				return

			self.ClearToolTip()
			
			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(safebox.GetPremiumPrivateShopItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(safebox.GetPremiumPrivateShopItemAttribute(slotIndex, i))

			if app.ENABLE_TRANSMUTATION:
				itemTransmutation = safebox.GetPremiumPrivateShopItemTransmutation(slotIndex)
				if itemTransmutation > 0:
					item.SelectItem(itemTransmutation)
					nameTransmutation = item.GetItemName()
					self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetPremiumPrivateShopItemFlags(slotIndex), 0, nameTransmutation)
				else:
					self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetPremiumPrivateShopItemFlags(slotIndex))
			else:
				self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetPremiumPrivateShopItemFlags(slotIndex))
				
			self.AppendPrice(safebox.GetPremiumPrivateShopItemPrice(slotIndex))

