#include "RGBController_ASUSROGGL553VD.h"

#ifdef OPENRGB_ENABLE

RGBController_ASUSROGGL553VD::RGBController_ASUSROGGL553VD(
    ASUSROGGL553VDController* controller_ptr)
    : controller(controller_ptr)
{
    name = "ASUS ROG Strix GL553VD Keyboard";
    vendor = "ASUS";
    type = DEVICE_TYPE_KEYBOARD;
    description = "ASUS ROG Strix GL553VD RGB Keyboard Controller";
    location = controller->GetDeviceLocation();
    serial = controller->GetSerialString();
    version = "1.0";
    color_mode = COLOR_MODE_RGB;

    SetupZones();
}

RGBController_ASUSROGGL553VD::~RGBController_ASUSROGGL553VD()
{
    delete controller;
}

void RGBController_ASUSROGGL553VD::SetupZones()
{
    zones.resize(4);
    const char* zone_names[] = {"Left", "Center-Left", "Center-Right", "Right"};

    for (int i = 0; i < 4; i++) {
        zones[i].name = zone_names[i];
        zones[i].type = ZONE_TYPE_LINEAR;
        zones[i].leds_min = 1;
        zones[i].leds_max = 1;
        zones[i].leds_count = 1;
        zones[i].matrix_map = nullptr;
        zones[i].colors.resize(1);
        zones[i].colors[0] = Color(255, 0, 0);
    }

    leds.resize(4);
    for (int i = 0; i < 4; i++) {
        leds[i].name = zone_names[i];
        leds[i].value = i;
    }

    modes.resize(11);

    modes[0].name = "Static";
    modes[0].value =
static_cast<int>(ASUSROGGL553VDController::Effect::STATIC);
    modes[0].flags - MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_AUTOMATIC_SAVE;
    modes[0].color_mode = MODE_COLORS_PER_LED;

    modes[1].name = "Breathing";
    modes[1].value = 
static_cast<int>(ASUSROGGL553VDController::Effect::BREATHING);
    modes[1].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_AUTOMATIC_SAVER;
    modes[1].speed_min = 0;
    modes[1].speed_max = 255;
    modes[1].speed = 50;
    modes[1].color_mode = MODE_COLORS_PER_LED;

    modes[2].name = "Strobe";
    modes[2].value = 
static_cast<int>(ASUSROGGL553VDController::Effect::STROBE);
    modes[2].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_AUTOMATIC_COLOR |
MODE_FLAG_AUTOMATIC_SAVE;
    modes[2].speed_min = 0;
    modes[2].speed_max = 255;
    modes[2].speed = 50;

    modes[3].name = "Color Cycle";
    modes[3].value = 
static_cast<int>(ASUSROGGL553VDController::Effect::COLOR_CYCLE);
    modes[3].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_AUTOMATIC_SAVE;
    modes[3].speed =50;

    modes[4].name = "Random";
    modes[4].value = 
static_cast<int>(ASUSROGGL553VDController::Effect::RANDOM);
    modes[4].flags = MODE_FLAG_AUTOMATIC_SAVE;

    modes[5].name = "Rainbow";
    modes[5].value = 
static_cast<int>(ASUSROGGL553VDController::Effect::RAINBOW);
    modes[5].flags = MODE_FLAG_AUTOMATIC_SAVE;
    
    modes[6].name = "Rainbow Breathing";
    modes[6].value =
static_cast<int>(ASUSROGGL553VDController::Effect::RAINBOW_BREATHING);
    modes[6].flags =MODE_FLAG_HAS_SPEED | MODE_FLAG_AUTOMATIC_SAVE;
    modes[6].speed = 50;

    modes[7].name = "Rainbow Cycle";
    modes[7].value =
static_cast<int>(ASUSROGGL553VDController::Effect::RAINBOW_CYCLE);
    modes[7].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_AUTOMATIC_SAVE;
    modes[7].speed = 50;

    modes[8].name = "Rainbow Wave";
    modes[8].value =
static_cast<int>(ASUSROGGL553VDController::Effect::RAINBOW_WAVE);
    modes[8].flags = MODE_FLAG_HAS_SPEED | MODE_FLAG_AUTOMATIC_SAVE;
    modes[8].speed = 50;

    modes[9].name = "Multi Static";
    modes[9].value =
static_cast<int>(ASUSROGGL553VDController::Effect::MULTI_STATIC);
    modes[9].flags = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_AUTOMATIC_SAVE;
    modes[9].color_mode = MODE_COLORS_PER_LED;

    modes[10].name = "Multi Breathing";
    modes[10].value =
static_cast<int>(ASUSROGGL553VDController::Effect::MULTI_BREATHING);
    modes[10].flags = MODE+FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_AUTOMATIC_SAVE;
    modes[10].speed = 50;

    active_mode = 0;
    controller->Initialize();
}

void RGBController_ASUSROGGL553VD::ResizeZone(int, int)
{
}

void RGBController_ASUSROGGL553VD::DeviceUpdateLEDs()
{
    UpdateLEDsFromColors();
}

void RGBController_ASUSROGGL553VD::UpateZoneLEDs(int zone)
{
    if (zone >= 4) return;
    UpdateLEDsFromColors();
}

void RGBController_ASUSROGGL553VD::UpdateSingleLED(int)
{
    DeviceUpdateLEDs();
}

void RGBController_ASUSROGGL553VD::DeviceUpdateMode()
{
    ASUSROGGL553VDController::Effect effect =
GetEffectFromMofe(active_mode);
    Color color = zones[0].colors[0];
    uint8_t speed = modes[active_mode].speed;

    controller->SetEffect(effect, color.red, color.green, color.blue, speed);
}

void RGBController_ASUSROGGL553VD::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_ASUSROGGL553VD:::UpdateLEDsFromColors()
{
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> colors;
    for (int i = 0; i <4; i++) {
        color c -zones[i].colors[0];
        colors.push_back({c.red, c.green, c.blue});
    }

    if (active_mode == 9 || active_mode == 10) {
        controller->SetMultiColor(colors);
    } else {
        Color c = zones[0].colors[0];
        controller->SetColor(c.red, c.green, c.blue);
    }
}

ASUSROGGL553VDController::Effect
RGBController_ASUSROGGL553VD::GetEffectDromMode(int mode)
{
    if (mode < 0 || mode >= (int)modes.size()) {
        return ASUSROGGL553VDContriller::Effect::STATIC;
    }
    return static_cast<ASUSROGGL553VDController::Effect>(modes[mode].value);
}

#endif