// This is a modification of the hackster contribution

// WioTerminal-IoTs-Dimmer
// https://www.hackster.io/SeeedStudio/wioterminal-iots-dimmer-a106b9


// The application is modified to be easily compiled on PlatformIO IDE

// SinricPro library is not installed through the PlatformIO library manager
// It is installed directly in the lib folder

#include <Arduino.h>

#include "SinricPro_Generic.h"

#include "defines.h"

#include "SinricProDimSwitch.h"

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite

int LED_PIN = 0;
int val = 0;
bool powerState = false;


const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

// we use a struct to store all states and values for our dimmable switch
struct
{
  int LED_PIN = 0;
  bool powerState = false;
  int powerLevel = 0;
} device_state;

bool onPowerState(const String &deviceId, bool &state)
{
  Serial.println("Device " + deviceId + " power turned " + String(state ? "on" : "off"));
  powerState = state;
  digitalWrite(LED_PIN, powerState ? HIGH : LOW);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.fillRect(0, 0, 320, 45, TFT_BLUE); //Drawing rectangle with blue fill
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.drawString("LED Dimmer", 80, 10); //Drawing text string
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("WIFI :", 10 , 55);
  spr.setTextColor(TFT_GREEN, TFT_BLACK);
  spr.drawString("conneted", 100 , 55);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("Dimmer Power: ", 10, 95);
  spr.drawString("brightness: ", 10, 135);
  spr.drawString("%", 200, 135);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString(String(state ? "on" : "off"), 195, 95, 4);

  if (powerState == HIGH) {
    val = 1;
  } else {
    val = 0;
  }
  return true; // request handled properly
}

bool onPowerLevel(const String &deviceId, int &powerLevel)
{
  device_state.powerLevel = powerLevel;
  analogWrite(LED_PIN, device_state.powerLevel);
  Serial.println("Device " + deviceId + " power level level changed to " + String(device_state.powerLevel));
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.fillRect(0, 0, 320, 45, TFT_BLUE); //Drawing rectangle with blue fill
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.drawString("LED Dimmer", 80, 10); //Drawing text string
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("WIFI :", 10 , 55);
  spr.setTextColor(TFT_GREEN, TFT_BLACK);
  spr.drawString("conneted", 100 , 55);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("Dimmer Power: ", 10, 95);
  spr.drawString("brightness: ", 10, 135);
  spr.drawString("%", 200, 135);

  if (val == 1) {
    if (device_state.powerLevel < 100 && device_state.powerLevel >= 10) {
      analogWrite(LED_PIN, powerLevel);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.drawNumber(device_state.powerLevel, 150, 140, 4);
      tft.drawString("     ", 178, 140, 4);
    } else if (device_state.powerLevel < 10) {
      analogWrite(LED_PIN, powerLevel);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.drawNumber(device_state.powerLevel, 150, 140, 4);
      tft.drawString("     ", 165, 140, 4);
    } else {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.drawString("100", 150, 140, 4);
    }
  } else {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("0", 150, 140, 4);
  }
  return true;
}


// setup function for WiFi connection
void setupWiFi()
{
//Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  Serial.println((char *)"First disconnecting.");
  while (WiFi.status() != WL_DISCONNECTED)
  {
    WiFi.disconnect();
    delay(200); 
  }
  
  delay(500);
  Serial.println((char *)"First disconnecting.");
  char buf[100];
  sprintf(buf, "Connecting to SSID: %s", ssid);
  Serial.println(buf);
  
  if (!ssid || *ssid == 0x00 || strlen(ssid) > 31)
  {
    Serial.println((char *)"Invalid: SSID or PWD, Stop");
    // Stay in endless loop
      while (true)
      {         
        delay(1000);
      }
  }

  Serial.print("\n[Wifi]: Connecting");
  WiFi.begin(ssid, password);   // put your WIFI 

  if (!WiFi.enableSTA(true))
{
  
  while (true)
  {
    // Stay in endless loop to reboot through Watchdog
    Serial.println((char *)"Connect failed.");
    delay(1000);
    }
}

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
    WiFi.begin(ssid, password);
  }
  Serial.print("[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
  spr.fillSprite(TFT_BLACK);
  spr.createSprite(320, 175);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.fillRect(0, 0, 320, 45, TFT_BLUE); //Drawing rectangle with blue fill
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.drawString("LED Dimmer", 80, 10); //Drawing text string
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("WIFI :", 10 , 55);
  spr.setTextColor(TFT_GREEN, TFT_BLACK);
  spr.drawString("conneted", 100 , 55);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("Dimmer Power: ", 10, 95);
  spr.drawString("brightness: ", 10, 135);
  spr.drawString("%", 200, 135);
  spr.pushSprite(0, 0);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("0", 150, 140, 4);
  tft.drawString("off", 195, 95, 4);
}

void setupSinricPro()
{
  //SinricProDimSwitch &myDimSwitch = SinricPro["device ID"];  // put device ID
  SinricProDimSwitch &myDimSwitch = SinricPro["601d34fbaa578b01bba6ab7a"];  // put device ID

  // set callback function to device
  myDimSwitch.onPowerState(onPowerState);
  myDimSwitch.onPowerLevel(onPowerLevel);

  // setup SinricPro
  SinricPro.onConnected([]()
  {
    Serial.println("Connected to SinricPro");
  });
  SinricPro.onDisconnected([]()
  {
    Serial.println("Disconnected from SinricPro");
  });
  SinricPro.begin(APP_KEY, APP_SECRET);    //Put your API key and secret
}

// main setup function
void setup()
{
  //Serial.begin(BAUD_RATE);
  Serial.begin(9600);

//  while (!Serial);

  pinMode(LED_PIN, OUTPUT); // define LED GPIO as output
  digitalWrite(LED_PIN, LOW); // turn off LED on bootup

  tft.begin();
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  spr.fillSprite(TFT_BLACK);
  spr.createSprite(320, 175);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);

  spr.fillRect(0, 0, 320, 45, TFT_BLUE); //Drawing rectangle with blue fill
  spr.setTextColor(TFT_WHITE); //Setting text color
  spr.drawString("LED Dimmer", 80, 10); //Drawing text string
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("WIFI :", 10 , 55);
  spr.setTextColor(TFT_RED, TFT_BLACK);
  spr.drawString("disconneted", 100 , 55);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("Dimmer Power: ", 10, 95);
  spr.drawString("brightness: ", 10, 135);
  spr.drawString("%", 200, 135);
  spr.pushSprite(0, 0);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("0", 150, 140, 4);
  tft.drawString("off", 195, 95, 4);

  Serial.println("\nStarting WIO_Terminal_DimSwitch on " + String(BOARD_NAME));
  //Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupWiFi();
  setupSinricPro();
}

void loop()
{
  SinricPro.handle();
}