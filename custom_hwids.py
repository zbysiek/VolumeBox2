Import("env")

board_config = env.BoardConfig()

board_config.update("build.hwids", [
["0x2341", "0x2323"], #VID, PID 1st pair
["0x2365", "0x2355"]  #VID, PID 2nd pair, etc.
])

board_config.update("build.usb_product", "VolumeBox2")