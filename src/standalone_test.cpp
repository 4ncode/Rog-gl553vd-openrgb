#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unistd.h>

#include "ASUSROGGL553VDController.h"

int main()
{
    std::cout << "=== ASUS ROG GL553VD RGB Test ===" << std::endl;
    
    if (hid_init() != 0) {
        std::cerr << "Hidapi initialization error" << std::endl;
        return 1;
    }
    
    struct hid_device_info* devs = hid_enumerate(
        ASUSROGGL553VDController::VENDOR_ID,
        ASUSROGGL553VDController::PRODUCT_ID
    );
    
    if (!devs) {
        std::cerr << "No device found!"No device found! << std::endl;
        hid_exit();
        return 1;
    }
    
    hid_device* handle = hid_open_path(devs->path);
    if (!handle) {
        std::cerr << "The device cannot be opened" << std::endl;
        hid_free_enumeration(devs);
        hid_exit();
        return 1;
    }
    
    std::cout << "Found: " << devs->manufacturer_string 
              << " " << devs->product_string << std::endl;
    
    ASUSROGGL553VDController* controller = 
        new ASUSROGGL553VDController(handle, devs->path, devs->product_id);
    
    std::cout << "Initializing the keyboard..." << std::endl;
    controller->Initialize();
    sleep(1);
    
    std::cout << "Red (3 seconds)..." << std::endl;
    controller->SetColor(255, 0, 0);
    sleep(3);
    
    std::cout << "Green (3 seconds)..." << std::endl;
    controller->SetColor(0, 255, 0);
    sleep(3);
    
    std::cout << "Blue (3 seconds)..." << std::endl;
    controller->SetColor(0, 0, 255);
    sleep(3);
    
    std::cout << "Power off (black)..." << std::endl;
    controller->SetColor(0, 0, 0);
    
    std::cout << "The test is over!" << std::endl;
    
    // Close
    delete controller;
    hid_close(handle);
    hid_free_enumeration(devs);
    hid_exit();
    
    return 0;
}
