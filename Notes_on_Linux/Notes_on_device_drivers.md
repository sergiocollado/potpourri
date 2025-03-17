# Notes on device drivers

References:
 - https://www.kernel.org/doc/html/v5.5/driver-api/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/bus.html
 - Understanding the Structure of a Linux Kernel Device Driver - Sergio Prado, Toradex : https://www.youtube.com/watch?v=pIUTaMKq0Xc
 - https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html


There are 3 main components buses (`bus_type`), device_drives (`device_drive`), and devices (`device`). 
 - `bus_type`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/bus.h#L84 - The bus type structure contains a list of all devices that are on that bus type in the system. When device_register is called for a device, it is inserted into the end of this list. The bus object also contains a list of all drivers of that bus type. When driver_register is called for a driver, it is inserted at the end of this list. These are the two events which trigger driver binding.
 - `device_driver`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/driver.h#L51 -  the software that can be associated with a device and performs operations with it
 - `device`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device.h#L458 - a physical device that is attached to a bus, and is handled by the device_driver.

Those components can be reached in `/sys`:

![sys_bus_device_and_drivers](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/sys_bus_device_drivers.png)

In /sys, we can find: 
 - bus: ypes of bus to which physical devices are connected (pci, ide, usb ...)
 - class: drivers classes that are available in the system (net, sound, usb ...)
 - devices: the hierarchical structure of devices connected to the system
