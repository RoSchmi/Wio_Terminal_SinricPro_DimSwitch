# Wio_Terminal_SinricPro_DimSwitch

This is a modification of this hackster contribution for the Wio Terminal

### WioTerminal-IoTs-Dimmer
https://www.hackster.io/SeeedStudio/wioterminal-iots-dimmer-a106b9


The application is modified to be easily compiled on PlatformIO IDE

The SinricPro_Generic and WebSockets_Generic libraries are not installed through lib_deps
They are installed directly in the lib folder, otherwise there were many compiler errors which couldn't be resolved easily

As an alternative you can use the following settings in platformio.ini (ignore the not needed lobraries)

lib_deps = 
	https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi#v1.0.2
	https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified#v2.1.1
	https://github.com/Seeed-Studio/Seeed_Arduino_FS
	https://github.com/Seeed-Studio/Seeed_Arduino_SFUD
	https://github.com/Seeed-Studio/Seeed_Arduino_mbedtls#dev

	https://github.com/khoih-prog/SinricPro_Generic#v2.8.0
	
	
lib_ignore = 
	STM32Ethernet
	DueFlashStorage
	ESP_AT_Lib
	Ethernet
	Ethernet2
	Ethernet3
	EthernetENC
	EthernetLarge
	EthernetWebServer
	EthernetWebServer_STM32
	STM32duino LwIP
	STM32Ethernet
	UIPEthernet			
	WiFi101
	WiFiEspAT
	WiFiNINA_Generic
	WiFiWebServer


