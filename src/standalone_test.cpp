#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unistd.h>

#include "ASUSROGGL553VDController.h"

int main()
{
    std::cout << "=== ASUS ROG GL553VD RGB Test ===" << std::endl;
    
    if (hid_init() != 0) {
        std::cerr << "Blad inicjalizacji hidapi" << std::endl;
        return 1;
    }
    
    struct hid_device_info* devs = hid_enumerate(
        ASUSROGGL553VDController::VENDOR_ID,
        ASUSROGGL553VDController::PRODUCT_ID
    );
    
    if (!devs) {
        std::cerr << "Nie znaleziono urzadzenia!" << std::endl;
        hid_exit();
        return 1;
    }
    
    hid_device* handle = hid_open_path(devs->path);
    if (!handle) {
        std::cerr << "Nie mozna otworzyc urzadzenia" << std::endl;
        hid_free_enumeration(devs);
        hid_exit();
        return 1;
    }
    
    std::cout << "Znaleziono: " << devs->manufacturer_string 
              << " " << devs->product_string << std::endl;
    
    ASUSROGGL553VDController* controller = 
        new ASUSROGGL553VDController(handle, devs->path, devs->product_id);
    
    std::cout << "Inicjalizacja klawiatury..." << std::endl;
    controller->Initialize();
    sleep(1);
    
    std::cout << "Czerwony (3 sekundy)..." << std::endl;
    controller->SetColor(255, 0, 0);
    sleep(3);
    
    std::cout << "Zielony (3 sekundy)..." << std::endl;
    controller->SetColor(0, 255, 0);
    sleep(3);
    
    std::cout << "Niebieski (3 sekundy)..." << std::endl;
    controller->SetColor(0, 0, 255);
    sleep(3);
    
    std::cout << "Wylaczanie (czarny)..." << std::endl;
    controller->SetColor(0, 0, 0);
    
    std::cout << "Test zakonczony!" << std::endl;
    
    // Zamykamy
    delete controller;
    hid_close(handle);
    hid_free_enumeration(devs);
    hid_exit();
    
    return 0;
}