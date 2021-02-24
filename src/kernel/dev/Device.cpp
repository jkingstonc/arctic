#include "Device.h"

#include <kernel/memory/KMalloc.h>
#include <kernel/dev/Bus.h>
#include <kernel/dev/Keyboard.h>
#include <kernel/io/Debug.h>

namespace Device{
    DeviceTree* kernel_dev_tree;

    Device::Device(){}
    Device::~Device(){}

    void Device::setup(){}

    String Device::name(){
        return "unknown device";
    } 

    u32 Device::id(){
        return 0;
    }

    void DeviceTree::setup_dev_tree(){
        // the first job is to create the main bus device which can then locate other devices
        Bus* bus = (Bus*)Memory::kmalloc(sizeof(Bus));
        Keyboard* keyboard = (Keyboard*)Memory::kmalloc(sizeof(Keyboard));
        m_devices.push_back(bus);
        m_devices.push_back(keyboard);
    }  

    
    Device* DeviceTree::get(u32 id){
        for(int i=0;i<m_devices.size();i++){
            if(m_devices[i]->id()==id){
                return m_devices[i];
            }
        }
        return 0;
    }

    void setup_devices(){
        kernel_dev_tree = (DeviceTree*)Memory::kmalloc(sizeof(DeviceTree));
        kernel_dev_tree->setup_dev_tree();
        IO::dbg() << "setup devices\n";
    }
}
