#Search

			elif player.SLOT_TYPE_MALL == attachedSlotType:
				net.SendMallCheckoutPacket(attachedSlotPos, player.DRAGON_SOUL_INVENTORY, selectedSlotPos)

#add after

			elif player.SLOT_TYPE_PREMIUM_PRIVATE_SHOP == attachedSlotType and app.ENABLE_PREMIUM_PRIVATE_SHOP:
				net.SendPremiumPrivateShopCheckoutPacket(attachedSlotPos, player.DRAGON_SOUL_INVENTORY, selectedSlotPos)