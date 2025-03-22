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
 - How to Avoid Writing Device Drivers for Embedded Linux - Chris Simmonds, 2net: https://youtu.be/QIO2pJqMxjE
 - Linux Driver Workshop 2025: https://youtu.be/krBP637d_8k


## Overview

There are 3 main components buses (`struct bus_type`), device_drives (`struct device_drive`), and devices (`struct device`). 
 - `struct bus_type`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/bus.h#L84 - The bus type structure contains a list of all devices that are on that bus type in the system. When device_register is called for a device, it is inserted into the end of this list. The bus object also contains a list of all drivers of that bus type. When driver_register is called for a driver, it is inserted at the end of this list. These are the two events which trigger driver binding.
 - `struct device_driver`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/driver.h#L51 -  the software that can be associated with a device and performs operations with it
 - `struct device`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device.h#L458 - a physical device that is attached to a bus, and is handled by the device_driver.

Those components can be reached in `/sys`:

![sys_bus_device_and_drivers](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/sys_bus_device_drivers.png)

In `/sys`, we can find: 
 - bus: types of bus to which physical devices are connected (pci, ide, usb ...)
 - class: drivers classes that are available in the system (net, sound, usb ...)
 - devices: the hierarchical structure of devices connected to the system


Relevant structs:
 - `struct device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L619 - belongs to a bus or a 'class'. - normally the `struct device` is embedded in a specialized device. To create a device: 
   - set the bus type
   - set parent pointer
   - set attribute groups
   - `device_initalize()` 
   - do other stuff...
   - `device_add()` 
   - `device_register()` = `device_initalize()` + `device_add()` 
 - `struct device_type`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L88 - USB is a good example of this, USB has a whole bunch of structure for USB device: interface, endpoints, ports, these all belong to the USB bus, but they are different types. So you can have the same collection of USB devices, you can iterate over them, but they have a type and you can check the type for knowing what is going on. 
 - `struct device_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/driver.h#L51 - a driver controls a device. So you write a driver of a specific bus type. It defines funtions for prove or resume the device, also power management as shutdown, suspend and resume the device. https://docs.kernel.org/driver-api/driver-model/driver.html
To register a driver:
      - set the bus type
      - set up prove/release
      - set module ownership
      - `drive_register()` 
 - `struct bus_type`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/bus.h#L24 - busses are somewhat challenging to write :/ - It binds devices and drivers. It handles devices and drivers, and has to define a funtion to define the devices with their drivers. Every bus matches devices and drivers differnetly, there is no a generic way. It also handles the `uevents` for when they are added or removed. And also handles shut down. https://docs.kernel.org/driver-api/driver-model/bus.html, &  https://docs.kernel.org/driver-api/driver-model/binding.html. The responsabilities of a bus:
      - register bus
      - create devices
      - register drivers
      - suspend/resume
      - register bus


## APIs

### Device

Reference: https://docs.kernel.org/next/driver-api/driver-model/device.html

The `struct device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L619 

The structure is usualy embeeded in a higher lever representation of the device: 
 - `i2c_client`:  https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/i2c.h#L329 @ include/linux/i2c.h
 - `struct spi_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/spi/spi.h#L184 @ include/linux/spi/spi.h
 - `struct usb_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/usb.h#L653 @ include/linux/usb.h
 - `struct platform_device`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L23 @ include/linux/platform_device.h

A device is registered with the function `device_register`: https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/core.c#L3726 @ drivers/base/core.c

Registering a device implies to add the device to the device's list of the corresponding bus driver.

### Device driver

References:
 - https://docs.kernel.org/next/driver-api/driver-model/driver.html
 - https://docs.kernel.org/next/driver-api/driver-model/binding.html

The `struct device_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device.h#L88 @ include/linux/device/driver.h

- `struct ì2c_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/i2c.h#L235 @ include/linux/i2c
- `struct spi_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/spi/spi.h#L346 @ include/linux/spi/spi.h
- `struct usb_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/usb.h#L1216 @ include/linux/usb.h
- `struct plataform_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L236 @ include/linux/platform_device.h
- `struct pci_driver`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/pci.h#L947 @ include/linux/pci.h

A driver registration consists on adding the driver into the list of drivers that is mantained by the driver's bus. 

The base function to register a driver in its bus is: `driver_register()` https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/driver.c#L222 @ drivers/base/driver.c.

But altmost every bus has its specialized resgistration function:
 - `i2c_register_driver()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/i2c/i2c-core-base.c#L1993 @ drivers/i2c/i2c-core-base.c
 - `spi_register_driver()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/spi/spi.c#L481 @ include/linux/spi/spi.c
 - `usb_register_driver()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/usb/core/driver.c#L1063 @ drivers/usb/core/driver.c
 - `pci_register_driver()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/pci/pci-driver.c#L1424 @ drivers/pci/pci-driver.c

Of course those funtions have an equivalent funtion for un-registering.

Usually the driver's registration funtions are used in the init/exit of the module. In those cases, it is posible to use a helper macro that handles the registering in init
and unregistering in the exit function. 

 - `module_i2c_driver(__i2c_driver)`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/i2c.h#L956 @ include/linux/i2c.h
 - `module_api_driver(__spi_driver)`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/spi/spi.h#L376 @ include/linux/spi/spi.h
 - `module_usb_driver(__usb_driver)`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/usb.h#L1332 @ include/linux/usb.h
 - `module_pci_driver(__pci_driver)`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/pci.h#L1591 @ include/linux/pci.h

### Driver device table: the device driver id_table field (what devices are supported?)

Reference: https://docs.kernel.org/next/driver-api/basics.html#driver-device-table

Every driver has a field named `id_table`, the type of that field depends of the type of bus. For example: 
 - `struct i2c_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L478 @ include/linux/mod_devicetable.h
 - `struct spi_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L515
 - `struct platform_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L607
 - `struct pci_device_id`: https://elixir.bootlin.com/linux/v6.12.6/A/ident/pci_device_id
 - `struct usb_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L81

The field `id_table`has an array of device IDs that identifies those devices that are supported by the driver. 

There are two exceptions, the device tree and ACPI, which can expose the devices. In those cases, the
device can be declared from the won system. In case of the device tree with the `driver.of_match_table`, 
in case of the ACPI  with `driver.acpi_mat_table` fields. The `id_table`, in these cases are:
 - `struct of_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L282
 - `struct acpi_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L217

### Device-driver binding/matching 


