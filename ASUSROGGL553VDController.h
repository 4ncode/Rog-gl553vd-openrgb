#ifndef ASUS_ROG_GL553VD_CONTROLLER_H
#define ASUS_ROG_GL553VD_CONTROLLER_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <tuple>

extern "C" {
#include <hidapi/hidapi.h>
}


/**
 * ASUS ROG Strix GL553VD RGB Keyboard Controller
 * 
 * Sterownik dla klawiatury RGB w laptopach ASUS ROG Strix GL553VD
 * Bazuje na reverse engineeringu protokołu USB HID
 * 
 * Autor: [4ncode]
 * Licencja: GPL v2
 */


class ASUSROGGL553VDController
{
public:
    enum class Effect {
        STATIC = 0x01,
        BREATHING = 0x02,
        STROBE = 0x03,
        COLOR_CYCLE = 0x04,
        RANDOM = 0x05,
        RAINBOW = 0x06,
        RAINBOW_BREATHING = 0x07,
        RAINBOW_CYCLE = 0x08,
        RAINBOW_WAVE = 0x09,
        MULTI_STATIC = 0x0B,
        MULTI_BREATHING = 0x0C
    };

    ASUSROGGL553VDController(hid_device* device_handle, 
                              const char* path,
                              uint16_t pid);
    ~ASUSROGGL553VDController();

    void Initialize();
    void SetBrightness(uint8_t level);
    void SetColor(uint8_t r, uint8_t g, uint8_t b);
    void SetEffect(Effect mode, uint8_t r, uint8_t g, 
                   uint8_t b, uint8_t speed);
    void SetMultiColor(const std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>& colors);

    std::string GetDeviceLocation();
    std::string GetSerialString();

    static const uint16_t VENDOR_ID = 0x0B05;
    static const uint16_t PRODUCT_ID = 0x1854;

private:
    hid_device* dev;
    std::string location;
    uint16_t device_pid;
    bool initialized;

    void SendFeatureReport(uint8_t* data, size_t length);
};

#endif