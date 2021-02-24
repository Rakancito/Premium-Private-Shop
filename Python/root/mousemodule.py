#Search

			if Type == player.SLOT_TYPE_INVENTORY or\
				Type == player.SLOT_TYPE_PRIVATE_SHOP or\
				Type == player.SLOT_TYPE_SHOP or\
				Type == player.SLOT_TYPE_SAFEBOX or\
				Type == player.SLOT_TYPE_MALL or\
				Type == player.SLOT_TYPE_DRAGON_SOUL_INVENTORY:

				item.SelectItem(self.AttachedItemIndex)
				self.AttachedIconHandle = item.GetIconInstance()

				if not self.AttachedIconHandle:
					self.AttachedIconHandle = 0
					self.DeattachObject()
					return

				(width, height) = item.GetItemSize()

#add after

			elif Type == player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP and app.ENABLE_PREMIUM_PRIVATE_SHOP:
				item.SelectItem(self.AttachedItemIndex)
				self.AttachedIconHandle = item.GetIconInstance()

				if not self.AttachedIconHandle:
					self.AttachedIconHandle = 0
					self.DeattachObject()
					return

				(width, height) = item.GetItemSize()

#Search

			elif self.AttachedType == player.SLOT_TYPE_EMOTION:
				grpImage.Delete(self.AttachedIconHandle)
#add after

			elif self.AttachedType == player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP and app.ENABLE_PREMIUM_PRIVATE_SHOP:
				item.DeleteIconInstance(self.AttachedIconHandle)