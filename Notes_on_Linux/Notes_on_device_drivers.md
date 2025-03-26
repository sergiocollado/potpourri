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
 - Linux drivers and devices registration, matching, aliases and modules autoloading : https://blog.dowhile0.org/2022/06/10/linux-drivers-and-devices-registration-matching-aliases-and-modules-autoloading/


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

A device is registered with the function `device_register()` (reference: https://www.kernel.org/doc/html/latest/driver-api/driver-model/binding.html#device-register) -  https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/core.c#L3726 @ drivers/base/core.c

> When a new device is added, the bus’s list of drivers is iterated over to find one that supports it. In order to determine that,
> the device ID of the device must match one of the device IDs that the driver supports. The format and semantics for comparing IDs
> is bus-specific. Instead of trying to derive a complex state machine and matching algorithm, it is up to the bus driver to provide
> a callback to compare a device against the IDs of a driver. The bus returns 1 if a match was found; 0 otherwise.
>
>  `int match(struct device * dev, struct device_driver * drv);`
>
> If a match is found, the device’s driver field is set to the driver and the driver’s probe callback is called. This gives the driver a chance to verify that it really does support the hardware, and that it’s in a working state.

Registering a device implies to add the device to the device's list of the corresponding bus driver.

### Device declaration

The device declaration is not really part of the LDM. Nowadays there are tow methos
 - From the **Device Tree (Open Firmware)**: https://www.kernel.org/doc/html/latest/devicetree/index.html
 - From the **Advanced Confgiration and Power Interface ACPI** : https://www.kernel.org/doc/html/latest/driver-api/acpi/index.html

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
Reference: https://www.kernel.org/doc/html/latest/driver-api/driver-model/driver.html#registration. 

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
device can be declared from the won system. In case of the device tree with the `driver.of_match_table` (the `OF` I think is from "Open Firmware", which is the DeviceTree standard) , 
in case of the ACPI  with `driver.acpi_mat_table` fields. The `id_table`, in these cases are:
 - `struct of_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L282 (the 
 - `struct acpi_device_id`: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L217

### Device-driver binding/matching & hot-plugging

reference: 
 - https://docs.kernel.org/next/driver-api/driver-model/binding.html
 - Linux drivers and devices registration, matching, aliases and modules autoloading: https://blog.dowhile0.org/2022/06/10/linux-drivers-and-devices-registration-matching-aliases-and-modules-autoloading/
 - https://unix.stackexchange.com/questions/550037/how-does-udev-uevent-work
 - https://blog.dowhile0.org/2022/06/21/how-to-troubleshoot-deferred-probe-issues-in-linux/
 - https://blog.dowhile0.org/2024/06/02/some-useful-linux-kernel-cmdline-debug-parameters-to-troubleshoot-driver-issues/

A device driver has a list of devices that it support s in the `id_table` (its type depends on the type of bus). When a device appears on the bus, the bus driver
will check in the list ech ID table for the entry that matches that new device. Every drivers that contains the device ID in its table will have its `probe()` funtion
run, with the device as parameter(https://www.kernel.org/doc/html/latest/driver-api/driver-model/driver.html#callbacks) 

The issue with the previous aproach is that it is only valid to the device drivers that are already loaded (with `insmod` or `modprobe` or built-in). 
A solution to that situation is the module aut-loading. is to expose the device drivers, along their device tables to the user space, and for that 
the macro `MODULE_DEVICE_TABLE()` is used. That macro provides support por hot-plugging. At compilation time, the ubild proces recollects 
this information out of the drivers and buils a human-readable table called `modules.alias`which is located in the
 `/lib/modules/kernel_version/` directory. 

```
MODULE_DEVICE_TABLE(<bus_name>, <array_of_ids>)
```
reference: https://elixir.bootlin.com/linux/v6.13.7/source/include/linux/module.h#L249

The second part of the solution is the kernel reporting to userspace about some events (named **uvents**) 
through _netlink sockets__.

References:
 - https://unix.stackexchange.com/questions/550037/how-does-udev-uevent-work
 - https://en.wikipedia.org/wiki/Udev#Operation
 - https://www.freedesktop.org/software/systemd/man/latest/udev.html
 - https://wiki.debian.org/udev
 - An introduction to Udev: The Linux subsystem for managing device events : https://opensource.com/article/18/11/udev

`udev` stand for "userspace /dev" it is a device manager for the Linux kernel. It is part of systemd (an init system used to bootstrap user space and manage user processes).

Originally `udev` was independent from `systemd`, it was merged with systemd in 2012, this lead to some complication for distribution running without systemd like explained here for the gentoo distribution.

This application (`udev`) is meant to replace devfsd and hotplug, udev primarily manages device nodes in the `/dev` directory. At the same time, `udev` also handles all user space events raised when hardware devices are added into the system or removed from it, including firmware loading as required by certain devices (via kernel modules). Concretely udev is run as systemd service (systemd-udevd.service) to achieve its tasks, it listens to kernel uevents. For every event, systemd-udevd executes matching instructions specified in udev rules (/etc/udev/rules.d/), details about rules writing are available on this article.

At the Linux kernel level the required device information is exported by the sysfs file system. For every device the kernel has detected and initialized, a directory with the device name is created. It contains attribute files with device-specific properties. Every time a device is added or removed, the kernel sends a uevent to notify udev of the change.

The behavior of the udev daemon (service) can be configured using udev.conf(5) (`/etc/udev/udev.conf`), its command line options, environment variables, and on the kernel command line, or changed dynamically with udevadm control.

The udev, as a whole, is divided into three parts:
 - Library libudev that allows access to device information.
 - User space daemon (sytemd) udevd that manages the virtual `/dev`.
 - Administrative command-line utility udevadm for diagnostics.

Udev itself is divided on those three parts but it completely rely on the kernel device management and it's uevents calls, the system gets calls from the kernel via netlink socket. Earlier versions used hotplug, adding a link to themselves in /etc/hotplug.d/default with this purpose.

Note that other application/daemon may listen to `uevents` calls over `libudev`, `gudev` or directly from the kernel with `GUdevClient`.

### Bus structure

The bus trcuture `struct bus_type` (https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/bus.h#L24). The **bus controller** is the root elemento fo any hierarchy. The bus type is
the link between the `devices` and the `drivers`. https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/device/bus.h#L24

> The bus type structure contains a list of all devices that are on that bus type in the system. When device_register is called for a device, it is 
> inserted into the end of this list. The bus object also contains a list of all drivers of that bus type. When driver_register is called for a driver,
> it is inserted at the end of this list. These are the two events which trigger driver binding.

#### match()

Reference: https://www.kernel.org/doc/html/latest/driver-api/driver-model/bus.html#match-attaching-drivers-to-devices

> The purpose of the match callback is to give the bus an opportunity to determine if a particular driver supports a
> particular device by comparing the device IDs the driver supports with the device ID of a particular device, without
>  sacrificing bus-specific functionality or type-safety.
> 
> When a driver is registered with the bus, the bus’s list of devices is iterated over, and the match callback is called
>  for each device that does not have a driver associated with it.
 
Every bus driver has to provide a `match()` function, which will be run by the kernel when a new device or device-driver
is registered in the bus. An example of a `match()`  function is for example in the case of platform devices: https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L1322

```C
/**
 * platform_match - bind platform device to platform driver.
 * @dev: device.
 * @drv: driver.
 *
 * Platform device IDs are assumed to be encoded like this:
 * "<name><instance>", where <name> is a short description of the type of
 * device, like "pci" or "floppy", and <instance> is the enumerated
 * instance of the device, like '0' or '42'.  Driver IDs are simply
 * "<name>".  So, extract the <name> from the platform_device structure,
 * and compare it against the name of the driver. Return whether they match
 * or not.
 */
static int platform_match(struct device *dev, const struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);

	/* When driver_override is set, only bind to the matching driver */
	if (pdev->driver_override)
		return !strcmp(pdev->driver_override, drv->name);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI style match */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	/* Then try to match against the id table */
	if (pdrv->id_table)
		return platform_match_id(pdrv->id_table, pdev) != NULL;

	/* fall-back to driver name match */
	return (strcmp(pdev->name, drv->name) == 0);
}
```



#### probe()

`probe()` this callback is used when a new device or driver is added to the bus and once a match has occurred.










