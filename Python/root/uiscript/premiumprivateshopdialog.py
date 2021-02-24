import uiScriptLocale

ROOT_PATH			= "d:/ymir work/ui/game/premium_private_shop/"

WINDOW_WIDTH		= 196
WINDOW_HEIGHT		= 448


window = {
	"name" : "SafeboxWindow",

	"style" : ("movable", "float",),

	"x" : SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2,
	"y" : SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2,

	"width"		: WINDOW_WIDTH,
	"height"	: WINDOW_HEIGHT,

	"children" :
	(
		{
			"name" : "board",
			"type" : "board",

			"x" : 0,
			"y" : 0,

			"width"		: WINDOW_WIDTH,
			"height"	: WINDOW_HEIGHT,

			"children" :
			(
				## Title
				{
					"name" : "TitleBar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 8,
					"y" : 7,

					"width" : 181,
					"color" : "yellow",

					"children" :
					(
						{ "name":"TitleName", "type":"text", "x":90, "y":3, "text":uiScriptLocale.PREMIUM_PRIVATE_SHOP_TITLE, "text_horizontal_align":"center" },
					),
				},

				## Remain Time Button
				{
					"name"	: "sandglass_icon",
					"type"	: "image",
					"x"		: 10,
					"y"		: 97,
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					"image"	: ROOT_PATH + "sandglass_icon.sub",
				},
					
				## Remain Time Text
				{
					"name" : "remain_time_text_window", "type" : "window", "style" : ("attach",), "x" : 40, "y" : 97, "width" : 137, "height" : 18,
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					"children" :
					(
						{ "name" : "remain_time_text_bg", "type":"image", "x":0, "y":0, "image" : ROOT_PATH + "remain_time_text_bg.sub", },
						{ "name" : "remain_time_text", "type" : "text", "x" : 0, "y" : 0, "all_align" : "center", "text" : "", },
					),
				},
					
				# won icon
				{
					"name":"won_icon",
					"type":"image",
					
					"x": 10,
					"y": 77,
					
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					
					"image":"d:/ymir work/ui/game/windows/cheque_icon.sub",
				},
				
				## won text
				{
					"name" : "won_text_window", "type" : "window", "style" : ("attach",), "x" : 40, "y" : 77, "width" : 24, "height" : 20,
					
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					
					"children" :
					(
						{ "name" : "won_text_bg", "type":"image", "x":0, "y":0, "image" : ROOT_PATH + "won_text_bg.sub", },
						{ "name" : "won_text", "type" : "text", "x" : 0, "y" : 0, "all_align" : "center", "text" : "", },
					),
				},
				
				# yang icon
				{
					"name":"yang_icon",
					"type":"image",
					
					"x": 69,
					"y": 77,
					
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					
					"image":"d:/ymir work/ui/game/windows/money_icon.sub",
				},

				# yang slot
				{
					"name" : "yang_text_window", "type" : "window", "style" : ("attach",), "x" : 87, "y" : 77, "width" : 90, "height" : 20,
		
					"horizontal_align" : "left",
					"vertical_align" : "bottom",
					
					"children" :
					(
						{ "name" : "yang_text_bg", "type":"image", "x":0, "y":0, "image" : ROOT_PATH + "yang_text_bg.sub", },
						{ "name" : "yang_text", "type" : "text", "x" : 0, "y" : 0, "all_align" : "center", "text" : "", },
					),
				},
				
				## Button Close Shop
				{
					"name" : "ExitButton",
					"type" : "button",

					"x" : 65,
					"y" : 37,
					
					"horizontal_align" : "right",
					"vertical_align" : "bottom",

					"default_image" : ROOT_PATH + "shop_close_button_default.sub",
					"over_image" : ROOT_PATH + "shop_close_button_over.sub",
					"down_image" : ROOT_PATH + "shop_close_button_down.sub",
				},
				## Button Refresh Money
				{
					"name" : "RefreshMoney",
					"type" : "button",

					"x" : 0,
					"y" : 37,
					
					"horizontal_align" : "center",
					"vertical_align" : "bottom",

					"default_image" : ROOT_PATH + "tax_adjustment_button_default.sub",
					"over_image" : ROOT_PATH + "tax_adjustment_button_over.sub",
					"down_image" : ROOT_PATH + "tax_adjustment_button_down.sub",
				},
				
				## Button Re Open
				{
					"name" : "ReOpen",
					"type" : "button",

					"x" : 10,
					"y" : 37,
					
					"horizontal_align" : "left",
					"vertical_align" : "bottom",

					"default_image" : ROOT_PATH + "reopen_button_default.sub",
					"over_image" : ROOT_PATH + "reopen_button_over.sub",
					"down_image" : ROOT_PATH + "reopen_button_down.sub",
				},
				
			),
		},
	),
}
