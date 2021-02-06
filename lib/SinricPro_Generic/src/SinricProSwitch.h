/****************************************************************************************************************************
  SinricProSwitch.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.8.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
  2.6.1   K Hoang      15/08/2020 Sync with SinricPro v2.6.1: add AirQualitySensor, Camera Class.
  2.7.0   K Hoang      06/10/2020 Sync with SinricPro v2.7.0: Added AppKey, AppSecret and DeviceId classes and RTT function.
  2.7.4   K Hoang      12/11/2020 Sync with SinricPro v2.7.4. Add WIO Terminal support and examples
  2.8.0   K Hoang      10/12/2020 Sync with SinricPro v2.8.0. Add examples. Use std::queue instead of QueueList. SSL Option.
 *****************************************************************************************************************************/

#ifndef _SINRIC_PRO_SWITCH_H_
#define _SINRIC_PRO_SWITCH_H_

#include "SinricProDevice.h"

/**
   @class SinricProSwitch
   @brief Device suporting basic on / off command
 **/
class SinricProSwitch :  public SinricProDevice 
{
  public:
    SinricProSwitch(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("SWITCH"); 
    }
    //////
};

SinricProSwitch::SinricProSwitch(const DeviceId &deviceId) : SinricProDevice(deviceId) {}


#endif    //_SINRIC_PRO_SWITCH_H_
