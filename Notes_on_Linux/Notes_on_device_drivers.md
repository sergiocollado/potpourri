# Notes on device drivers

References:
 - https://www.kernel.org/doc/html/v5.5/driver-api/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/bus.html
 - Understanding the Structure of a Linux Kernel Device Driver - Sergio Prado, Toradex : https://www.youtube.com/watch?v=pIUTaMKq0Xc
 - Kernel Recipes 2016 - The Linux Driver Model - Greg KH : https://youtu.be/AdPxeGHIZ74
 - https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html
 - examples of linux device drivers: https://github.com/rrmhearts/linux-driver-examples
 - Overview of PCI(e) Subsystem: https://www.youtube.com/watch?v=3ic61kJNEQ0
 - PCI Endpoint Drivers in Linux Kernel and How to Write One: https://www.youtube.com/watch?v=L0HktbuTX5o


There are 3 main components buses (`bus_type`), device_drives (`device_drive`), and devices (`device`). 
 - `bus_type`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/bus.h#L84 - The bus type structure contains a list of all devices that are on that bus type in the system. When device_register is called for a device, it is inserted into the end of this list. The bus object also contains a list of all drivers of that bus type. When driver_register is called for a driver, it is inserted at the end of this list. These are the two events which trigger driver binding.
 - `device_driver`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/driver.h#L51 -  the software that can be associated with a device and performs operations with it
 - `device`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device.h#L458 - a physical device that is attached to a bus, and is handled by the device_driver.

Those components can be reached in `/sys`:

![sys_bus_device_and_drivers](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/sys_bus_device_drivers.png)

In /sys, we can find: 
 - bus: types of bus to which physical devices are connected (pci, ide, usb ...)
 - class: drivers classes that are available in the system (net, sound, usb ...)
 - devices: the hierarchical structure of devices connected to the system


Relevant structs:
 - `device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L619 - belongs to a bus or a 'class'. - normally the `struct device` is embedded in a specialized device. To create a device: 
   - set the bus type
   - set parent pointer
   - set attribute groups
   - `device_initalize()` 
   - do other stuff...
   - `device_add()` 
   - `device_register()` = `device_initalize()` + `device_add()` 
 - `device_type`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L88 - USB is a good example of this, USB has a whole bunch of structure for USB device: interface, endpoints, ports, these all belong to the USB bus, but they are different types. So you can have the same collection of USB devices, you can iterate over them, but they have a type and you can check the type for knowing what is going on. 
 - `device_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/driver.h#L51 - a driver controls a device. So you write a driver of a specific bus type. It defines funtions for prove or resume the device, also power management as shutdown, suspend and resume the device. https://docs.kernel.org/driver-api/driver-model/driver.html
To register a driver:
      - set the bus type
      - set up prove/release
      - set module ownership
      - `drive_register()` 
 - `bus_type`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/bus.h#L24 - busses are somewhat challenging to write :/ - It binds devices and drivers. It handles devices and drivers, and has to define a funtion to define the devices with their drivers. Every bus matches devices and drivers differnetly, there is no a generic way. It also handles the `uevents` for when they are added or removed. And also handles shut down. https://docs.kernel.org/driver-api/driver-model/bus.html, &  https://docs.kernel.org/driver-api/driver-model/binding.html. The responsabilities of a bus:
      - register bus
      - create devices
      - register drivers
      - suspend/resume
      - register bus


### APIs

#### Device

The `struct device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L619 

The structure is usualy embeeded in a higher lever representation of the device: 
 - `i2c_client`:  https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/i2c.h#L329 @ include/linux/i2c.h
 - `struct spi_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/spi/spi.h#L184 @ include/linux/spi/spi.h
 - `struct usb_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/usb.h#L653 @ include/linux/usb.h
 - `struct platform_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L23 @ include/linux/platform_device.h

#### Device driver

The `struct device_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L88 @ include/linux/device/driver.h

- `struct ì2c_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/i2c.h#L235 @ include/linux/i2c
- `struct spi_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/spi/spi.h#L346 @ include/linux/spi/spi.h
- `struct usb_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/usb.h#L1216 @ include/linux/usb.h
- `struct plataform_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L236 @ include/linux/platform_device.h
- `struct pci_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/pci.h#L947 @ include/linux/pci.h


