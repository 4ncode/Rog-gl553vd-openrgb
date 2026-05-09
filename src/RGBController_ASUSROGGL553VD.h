#ifndef RGB_CONTROLLER_ASUS_ROG_GL553VD_H
#define RGB_CONTROLLER_ASUS_ROG_GL553VD_H

#ifdef OPENRGB_ENABLE

#include "RGBController.h"
#include "ASUSROGGL553VDController.h"

class RGBController_ASUSROGGL553VD : public RGBController
{
public:
    RGBController_ASUSROGGL553VD(ASUSROGGL553VDController* controller_ptr);
    ~RGBController_ASUSROGGL553VD();

    void SetupZones();
    void ResizeZone(int zone, int new_size);
    void DeviceUpdateLEDs();
    void UpdateZoneLEDs(int zone);
    void UpdateSingleLED(int led);
    void DeviceUpdateMode();
    void SetCustomMode();

private:
    ASUSROGGL553VDController* controller;

    void UpdateLEDsFromColors();
    ASUSROGGL553VDController::Effect GetEffectFromMode(int mode);
};

#endif

#endif