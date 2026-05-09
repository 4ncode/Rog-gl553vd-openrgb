#include "ASUSROGGL553VDController.h"
#include <cstring>

ASUSROGGL553VDController::ASUSROGGL553VDController(
    hid_device* device_handle, 
    const char* path,
    uint16_t pid)
    : dev(device_handle), 
      location(path),
      device_pid(pid),
      initialized(false)
{
}

ASUSROGGL553VDController::~ASUSROGGL553VDController()
{
    if (dev) {
        hid_close(dev);
    }
}

void ASUSROGGL553VDController::SendFeatureReport(uint8_t* data, size_t length)
{
    if (!dev) return;
    hid_send_feature_report(dev, data, length);
    
}

void ASUSROGGL553VDController::Initialize()
{
    if (initialized) return;

    uint8_t buffer[8] = {0xCC, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    SendFeatureReport(buffer, 8);

    initialized = true;
}

void ASUSROGGL553VDController::SetBrightness(uint8_t level)
{
    if (level > 3) level = 3;

    uint8_t buffer[8] = {0xCC, 0x0A, level, 0x00, 0x00, 0x00, 0x00, 0x00};
    SendFeatureReport(buffer, 8);
}

void ASUSROGGL553VDController::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    Initialize();

    uint8_t buffer[8] = {0xCC, 0x01, r, g, b, 0x00, 0x00, 0x00};
    SendFeatureReport(buffer, 8);
}

void ASUSROGGL553VDController::SetEffect(Effect mode, uint8_t r, uint8_t g, uint8_t b, uint8_t speed)
{
    Initialize();

    uint8_t buffer[8] = {0xCC, static_cast<uint8_t>(mode), r, g, b, speed, 0x00, 0x00};
    SendFeatureReport(buffer, 8);
}

void ASUSROGGL553VDController::SetMultiColor(
    const std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>& colors)
{
    if (colors.size() < 4) return;

    Initialize();

    uint8_t buffer1[8] = {
        0xCC, 0x0B,
        std::get<0>(colors[0]), std::get<1>(colors[0]),
std::get<2>(colors[0]),
        std::get<0>(colors[1]), std::get<1>(colors[1]),
std::get<2>(colors[1])
    };
    SendFeatureReport(buffer1, 8);

    uint8_t buffer2[8] = {
        0xCC, 0x0C,
        std::get<0>(colors[2]), std::get<1>(colors[2]),
std::get<2>(colors[2]),
        std::get<0>(colors[3]), std::get<1>(colors[3]),
std::get<2>(colors[3])
    };
    SendFeatureReport(buffer2, 8);
}

std::string ASUSROGGL553VDController::GetDeviceLocation()
{
    return location;
}

std::string ASUSROGGL553VDController::GetSerialString()
{
    if (!dev) return "";
    
    wchar_t serial_wchar[256];
    hid_get_serial_number_string(dev, serial_wchar, 256);

    std::wstring ws(serial_wchar);
    return std::string(ws.begin(), ws.end());
}