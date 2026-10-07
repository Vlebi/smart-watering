import network


wifi = network.WLAN(network.STA_IF)
wifi.active(True)

print("Boot folyamat kész, Wi-Fi aktív az ESP-NOW-hoz.")