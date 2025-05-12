# Notes on device drivers

References:
 - https://www.kernel.org/doc/html/v5.5/driver-api/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/bus.html
 - Understanding the Structure of a Linux Kernel Device Driver - Sergio Prado, Toradex : https://www.youtube.com/watch?v=pIUTaMKq0Xc
 - Kernel Recipes 2016 - The Linux Driver Model - Greg KH : https://youtu.be/AdPxeGHIZ74
 - https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html
 - examples of linux device drivers: https://github.com/rrmhearts/linux-driver-examples
 - The Linux Device Model: https://www.linkedin.com/pulse/embedded-linux-device-driver-development-part-2-model-kumar-phd?trk=public_post_feed-article-content
 - Overview of PCI(e) Subsystem: https://www.youtube.com/watch?v=3ic61kJNEQ0
 - PCI Endpoint Drivers in Linux Kernel and How to Write One: https://www.youtube.com/watch?v=L0HktbuTX5o
 - How to Avoid Writing Device Drivers for Embedded Linux - Chris Simmonds, 2net: https://youtu.be/QIO2pJqMxjE
 - Linux Driver Workshop 2025: https://youtu.be/krBP637d_8k
 - Linux drivers and devices registration, matching, aliases and modules autoloading : https://blog.dowhile0.org/2022/06/10/linux-drivers-and-devices-registration-matching-aliases-and-modules-autoloading/
 - Industrial I/O: https://www.kernel.org/doc/html/v4.15/driver-api/iio/index.html
 - The backbone of a Linux Industrial I/O driver: https://bootlin.com/blog/the-backbone-of-a-linux-industrial-i-o-driver/
 - IIO overview: https://wiki.st.com/stm32mpu/wiki/IIO_overview#:~:text=The%20Industrial%20I%2FO%20Linux,sensors%20through%20sysfs%20and%20devfs.
 - Industrial I/O and triggers: https://www.marcusfolkesson.se/blog/industrial-io-triggers/
 - IIO a new kernel subsystem: https://bootlin.com/pub/conferences/2012/fosdem/iio-a-new-subsystem/iio-a-new-subsystem.pdf
 - Interfacing Sensors via the Industrial I/O (IIO) Subsystem: https://www.linkedin.com/pulse/embedded-linux-weekend-hacking-part-5-interfacing-via-kumar-phd-s0obc
 - Simplify and Reuse Your Driver's Code with Regmaps - Ioan Adrian Ratiu, Collabora Ltd: https://youtu.be/ZSl7S58z8e0
 - How to Create a sysfs File Correctly: http://kroah.com/log/blog/2013/06/26/how-to-create-a-sysfs-file-correctly/
 - udev: https://en.wikipedia.org/wiki/Udev#Operation
 - kernel-programming-device-model-i2c.pdf : https://bootlin.com/pub/conferences/2018/elc/opdenacker-kernel-programming-device-model-i2c/kernel-programming-device-model-i2c.pdf
 - Basics of I2C on Linux - Luca Ceresoli, Bootlin : https://youtu.be/g9-wgdesvwA
 - Tutorial: Introduction to I2C and SPI: Both In-kernel and In-userspace - Michael Welling : https://youtu.be/c10wAKWpjts
 - https://embarcados.com.br/utilizando-o-mpu-6050-com-device-driver-e-device-tree-na-raspberry-pi-zero-w/
 - https://embarcados.com.br/device-driver-i2c-para-linux-embarcado/


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

The structure is usualy embedded in a higher lever representation of the device: 
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


## Platform devices

In the very early days, Linux users often had to tell the kernel where specific devices were to be found before their systems would work. In the absence of this information, the driver could not know which I/O ports and interrupt line(s) the device was configured to use. Happily, we now live in the days of busses like PCI which have discoverability built into them; any device sitting on a PCI bus can tell the system what sort of device it is and where its resources are. So the kernel can, at boot time, enumerate the devices available and everything Just Works.

Alas, life is not so simple; there are plenty of devices which are still not discoverable by the CPU. In the embedded and system-on-chip world, non-discoverable devices are, if anything, increasing in number. So the kernel still needs to provide ways to be told about the hardware that is actually present. "Platform devices" have long been used in this role in the kernel

References:
 - Platform Devices and Drivers: https://www.kernel.org/doc/html/latest/driver-api/driver-model/platform.html
 - The platform device API : https://lwn.net/Articles/448499/
 - Platform devices and device trees : https://lwn.net/Articles/448502/
 - Device tree usage: https://elinux.org/Device_Tree_Usage

### What is a platform device?

Platform devices are inherently *not discoverable* They cannot inform software of their presence. i2c devices fall into this category. The software must know at compile time of their existence (via `board_info` or device tree (dts)..) 
They are bound to drivers by *name matching* which you can learn in the i2c/ directory. Should be registered asap so that they can used.

USB and PCI would then **not** count as platform devices.

There are 2 requirements to work with platform devices
1. **registering the driver by name**
2. **registering the device using the same name as the driver**

Notice these things about platform drivers
1. register and interrupt addresses are hardcoded in the device tree, which represents the SoC
2. there is no way to remove the device hardware (since it is part of the SoC)
3. the correct driver is selected by the `compatible` device tree property which matches platform_driver.name in the driver
    platform_driver_register is the main register interface

e.g. an example from the device tree source (dts) of a compatible device
```
		lkmc_platform_device@101e9000 {
			compatible = "lkmc_platform_device";
			reg = <0x101e9000 0x1000>;
			interrupts = <18>;
			interrupt-controller;
			#interrupt-cells = <2>;
			clocks = <&pclk>;
			clock-names = "apb_pclk";
			lkmc-asdf = <0x12345678>;
};
```

### What is a non-platform device (USB, PCI)?

Non-platform devices such as PCI are inherently *discoverable*. This means that software can **find** new devices added to the system during runtime.

Notice these things about non-platform drivers
1. register and interrupt addresses are dynamically allocated by the PCI system, no device tree is used
2. the correct driver is selected by the PCI vendor:device ID. Each device must have the ID included in the software. Vendors must ensure uniqueness through a registration process. (Microsoft uses these ids for Plug and Play Technologies.)
3. we can insert and remove the PCI device with `device_add` and `device_del` as we can in real life. Probing is not automatic, but can be done after boot with echo 1 > /sys/bus/pci/rescan.


### Platform device

platform device: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L23

```C
#define PLATFORM_DEVID_NONE	(-1)
#define PLATFORM_DEVID_AUTO	(-2)

struct platform_device {
	const char	*name;
	int		id;
	bool		id_auto;
	struct device	dev;
	u64		platform_dma_mask;
	struct device_dma_parameters dma_parms;
	u32		num_resources;
	struct resource	*resource;

	const struct platform_device_id	*id_entry;
	/*
	 * Driver name to force a match.  Do not set directly, because core
	 * frees it.  Use driver_set_override() to set or clear it.
	 */
	const char *driver_override;

	/* MFD cell pointer */
	struct mfd_cell *mfd_cell;

	/* arch specific additions */
	struct pdev_archdata	archdata;
};
```

the member `id` works as follows:
 - If `id == -1 (PLATFORM_DEVID_NONE)`, then the underlying `dev` will have the dame name as the platform device. The platform device will do `dev_set_name(&pdev->dev, "%s", pdev->name);`
 - If `id == -2 (PLATFORM_DEVID_AUTO)`, then `dev` will be asssigned a valid ID, `dev_set_name(&pdev->dev, "%s.%d.auto", pdev->name, <auto_id>);`.
 - in other cases, id will be assigned: `dev_set_name(&pdev->dev, "%s.%d", pdev->name, pdev->id);`

`resource` is an array of resources assigned to the platform device, and `num_resources` is the number of elements in that array.


### Platform drivers

Platform drivers: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L236

```C
struct platform_driver {
	int (*probe)(struct platform_device *);

	/*
	 * .remove_new() is a relic from a prototype conversion of .remove().
	 * New drivers are supposed to implement .remove(). Once all drivers are
	 * converted to not use .remove_new any more, it will be dropped.
	 */
	union {
		void (*remove)(struct platform_device *);
		void (*remove_new)(struct platform_device *);
	};

	void (*shutdown)(struct platform_device *);
	int (*suspend)(struct platform_device *, pm_message_t state);
	int (*resume)(struct platform_device *);
	struct device_driver driver;
	const struct platform_device_id *id_table;
	bool prevent_deferred_probe;
	/*
	 * For most device drivers, no need to care about this flag as long as
	 * all DMAs are handled through the kernel DMA API. For some special
	 * ones, for example VFIO drivers, they know how to manage the DMA
	 * themselves and set this flag so that the IOMMU layer will allow them
	 * to setup and manage their own I/O address space.
	 */
	bool driver_managed_dma;
};
```

`probe()` is the funtion that is called when the device reclaims its driver after a `match()` happens between the driver and the device. 

The other thing the driver must provide is a way for the bus code to bind actual devices to the driver; there are two mechanisms which can be used for that purpose. The first is the id_table argument; the relevant structure is:

```C
    struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data;
    };
```

If an ID table is present, the platform bus code will scan through it every time it has to find a driver for a new platform device. If the device's name matches the name in an ID table entry, the device will be given to the driver for management; a pointer to the matching ID table entry will be made available to the driver as well. As it happens, though, most platform drivers do not provide an ID table at all; they simply provide a name for the driver itself in the driver field. 


### Platform device registration

To register the platform devices, use: 
 - To statically register one`platform_device_register(struct platrfomr_device *pdev)` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L767
 - for arrays of platform devices, use `platform_add_devices()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L497
 - To dynbamically register one, use: `platform_device_alloc()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L569, in the case that it succeed , then register it with `platform_device_add()` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L650, it case this functions returns an error (negative value), then the device has to be released with `platform_device_put()`.
 - To unregister the device use `platform_device_unregister` : https://elixir.bootlin.com/linux/v6.12.6/source/drivers/base/platform.c#L783

### Platform device resources

The `resource` field in `struct platform_device` defines the resouces that will need the platform device. It his defined at https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/ioport.h#L21

```C
/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	unsigned long desc;
	struct resource *parent, *sibling, *child;
};
```

In the structure the `start`/`end`  pints ot he beginning/end of the resource of the I/O or memory regions needed.  for IRQ lines or buses, or DMA channes, as they don't have ranges, the usual is to define the 
same value in the `start`/`end`. 

`flags` is a mask that defines the type of resource accoring to the definitions at: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/ioport.h#L31

```
/*
 * IO resources have these defined flags.
 *
 * PCI devices expose these flags to userspace in the "resource" sysfs file,
 * so don't move them.
 */
#define IORESOURCE_BITS		0x000000ff	/* Bus-specific bits */

#define IORESOURCE_TYPE_BITS	0x00001f00	/* Resource type */
#define IORESOURCE_IO		0x00000100	/* PCI/ISA I/O ports */
#define IORESOURCE_MEM		0x00000200
#define IORESOURCE_REG		0x00000300	/* Register offsets */
#define IORESOURCE_IRQ		0x00000400
#define IORESOURCE_DMA		0x00000800
#define IORESOURCE_BUS		0x00001000
...
/* I/O resource extended types */
#define IORESOURCE_SYSTEM_RAM		(IORESOURCE_MEM|IORESOURCE_SYSRAM)

/* PnP IRQ specific bits (IORESOURCE_BITS) */
#define IORESOURCE_IRQ_HIGHEDGE		(1<<0)
#define IORESOURCE_IRQ_LOWEDGE		(1<<1)
#define IORESOURCE_IRQ_HIGHLEVEL	(1<<2)
#define IORESOURCE_IRQ_LOWLEVEL		(1<<3)
#define IORESOURCE_IRQ_SHAREABLE	(1<<4)
#define IORESOURCE_IRQ_OPTIONAL		(1<<5)
#define IORESOURCE_IRQ_WAKECAPABLE	(1<<6)

/* PnP DMA specific bits (IORESOURCE_BITS) */
#define IORESOURCE_DMA_TYPE_MASK	(3<<0)
#define IORESOURCE_DMA_8BIT		(0<<0)
...

/* PCI ROM control bits (IORESOURCE_BITS) */
#define IORESOURCE_ROM_ENABLE		(1<<0)	/* ROM is enabled, same as PCI_ROM_ADDRESS_ENABLE */
#define IORESOURCE_ROM_SHADOW		(1<<1)	/* Use RAM image, not ROM BAR */

/* PCI control bits.  Shares IORESOURCE_BITS with above PCI ROM.  */
#define IORESOURCE_PCI_FIXED		(1<<4)	/* Do not move resource */
#define IORESOURCE_PCI_EA_BEI		(1<<5)	/* BAR Equivalent Indicator */
```

The resource's assignation can be done in tow ways, frist int the same compilation unit
where the platform device has been declared an registere, second, from the device tree.


### Platform device data

The `struct resource`, may be lacking in case of complex drivers, so as an extension to that `platform_device.device.platform_data` is used in case extra information is needed.

For using it dynamically use the function `platform_device_add_data()`. Also to retrieve that field use the function `dev_get_data()`. 

Remark: there is no way to check the type of data, the driver must assume it is given the correct type. 

### Platform device resouce provisioning

The device tree is interpreted as an instance of `struct resources` by the platform core, so the function `platform_get_resource()`,
`platform_get_resource_by_name()`, or `platform_get_irq()`, return the appropiated resource. 

Nevertheless, the device tree doesn't know of the structure of the platform data, so it cannot present the information
in that form. To pass suche data, driver use the `.data` field in the `of_device_id` entry that it is used
by the platform device and the driver to match.

When a device is instantiated from the device tree, the `platform_data` pointer is `NULL`, indicating that the data
is expected to be retrieved from the device tree. In this case the driver will find a `device_node` pointer in 
the platform `dev.of_node`field. The device tree access routines (e.g: `of_get_property()`) can be used to retrieve
the required data from the device tree.

### Probing a platform device

The entry point for the driver is the `probe(strcut platform_device *pdev)`. If the platform device is correct, this 
function must return 0, otherwise must return a negative value with the correspinding error code. 

The device then can report its resources with the functions: `platform_get_resource()`,
`platform_get_resource_by_name()`, or `platform_get_irq()`. 

the prove method must request any resorce required, and if mapping needs to be done the `probe()`  method is the place to do it.

Whe the device has to be release, everything that was done in the `probe()` method must be undone, using the `remove()` method, 
and return 0 if everyting has been properly undone, or an error code otherwise. 

### Provisioning supporting devices in the driver

The driver must inform the kernel of its supported devices by means of the `id_table` field (https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/platform_device.h#L253) . If the module complies with 
autoloading (plug and play (PnP)), then use the macro `MODULE_DEVICE_TABLE`. 

```C
struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data;
};
```
platform_device_id: https://elixir.bootlin.com/linux/v6.12.6/source/include/linux/mod_devicetable.h#L607

 - `name` is just a descriptive name for the device
 - `driver_data` it can be set a pointer to a per-device-dirver structure:

To allow matching platform devices declared in the device tree using their compatible string, 
the platform driver must set `platform_driver.driver.of_match_table` wit a list of elements of 
`struct of_device_id`, then, to allow module autolaoding from the device tree matcing as well, this device tree match table, 
 must be given to `MODULE_DEVICE_TABLE` MACRO. 

For example: https://elixir.bootlin.com/linux/v6.12.6/source/drivers/mmc/host/mxs-mmc.c
 
```C
static const struct of_device_id mxs_mmc_dt_ids[] = {
	{ .compatible = "fsl,imx23-mmc", .data = (void *) IMX23_SSP, },
	{ .compatible = "fsl,imx28-mmc", .data = (void *) IMX28_SSP, },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, mxs_mmc_dt_ids);
```

### Device driver initialization and registration

In the module init function call: 
 - `platform_driver_register()` - puts the drivers  into a list of drivers mantained by the kernel, and the `probe()` function will be called on demand. 
 - `platform_driver_probe()` - this method don't register the driver on the system. the kernel unst immediately the matching loop, to see fi there is any devices that matches agains tit, and the driver will call the `probe()` methods in the devices that matched. If at that moment no devices matches, the drives will be ignored after that. In this case, the `probe()` function muste be placed in an `__init` section, which is freeded later when the kernel boot is completed... this methods is used when it is a certainty that the devices is present in the system.

Upon module exit, use: `platform_driver_unregister()`.

## I2C Device drivers

References: 
 - https://www.kernel.org/doc/html/v4.14/driver-api/i2c.html
 - https://hackerbikepacker.com/i2c-on-linux
 - https://github.com/rrmhearts/linux-driver-examples/tree/master/i2c
 - kernel-programming-device-model-i2c.pdf : https://bootlin.com/pub/conferences/2018/elc/opdenacker-kernel-programming-device-model-i2c/kernel-programming-device-model-i2c.pdf
 - Basics of I2C on Linux - Luca Ceresoli, Bootlin : https://youtu.be/g9-wgdesvwA
 - Tutorial: Introduction to I2C and SPI: Both In-kernel and In-userspace - Michael Welling : https://youtu.be/c10wAKWpjts
 - https://www.eevblog.com/forum/microcontrollers/i2c-sensor-integration-in-linux/
 - https://github.com/torvalds/linux/blob/master/drivers/hwmon/lm75.c
 - https://github.com/torvalds/linux/blob/master/drivers/gpio/gpio-pca9570.c
 - https://archive.kernel.org/oldwiki/i2c.wiki.kernel.org/ (deprecated, but interesting for historical reasons)
 - https://archive.kernel.org/oldwiki/i2c.wiki.kernel.org/index.php/File:I2c-layers.png.html (i2c linux subsystem diagram - is it deprecated?)
 - https://www.kernel.org/doc/Documentation/i2c/dev-interface
 - https://github.com/Sensirion/i2c-tools/blob/master/README
 - https://www.linkedin.com/pulse/understanding-i2c-communication-linux-beginners-guide-soheil-nazari/
 - Let's code a Linux Driver - 22: Device Tree driver for an I2C Device: https://youtu.be/GQ1XwFWA2Nw
 - Let's code a Linux Driver - 36: I2C Device Driver without Device Tree: https://youtu.be/pESMpoQnfDU?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
 - Guide to interfacing a Gyro and Accelerometer with a Raspberry Pi: https://ozzmaker.com/berryimu/
 - https://embarcados.com.br/utilizando-o-mpu-6050-com-device-driver-e-device-tree-na-raspberry-pi-zero-w/
 - https://embarcados.com.br/device-driver-i2c-para-linux-embarcado/
 - Embedded Linux (PART-10)-I2C Device Driver on BeaglBone Black| I2C Client Driver: https://youtu.be/lYoFy9p8UAw

### Fundamentals of I2C

 References:
  - Understanding I2C: https://youtu.be/CAvawEcxoPU
  - https://www.ti.com/lit/an/sbaa565/sbaa565.pdf?ts=1745316874300
  - https://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/
  - understanding i2c: https://youtu.be/CAvawEcxoPU
  - https://learn.sparkfun.com/tutorials/i2c/all
  - https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/i2c/i2c-protocol.rst
  - https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/i2c/smbus-protocol.rst (SMbus = System Management bus a subsed of I2C definded by Intel).

###  I2C on Linux
The i2c subsystem allows Linux to be master and all connected devices to be slaves. They interact on the i2c bus.

When we talk about I2C, we use the following terms:

```
  **Bus**    -> *Algorithm*, 
                *Adapter*
```
An Algorithm driver cointains general code that can be used for a whole class of I2C adapters. Each specific adapter driver either depends on one algorithm or includes its own implementation.
  
```
  **Device** -> *Driver*, 
                *Client*

```
A Driver contains the general code to access some type of device. Each detected device gets its own data in the Client structure. Usually, Driver and -Client are more closely integrated
than Algorithm and Adapter. 
  
### How does a I2C device differ from a platform device?

An i2c device is an example of a platform device, however the complexities of i2c protocol are abstracted in a piece of hardware called the *i2c controller* which provides a way to connect and communicate to i2c devices. 

The driver used for configuring and using the i2c controller is a *platform driver*. The controller is an example of a platform device..

If an i2c device does not fit into the i2c controller model... may have to create it as a platform driver and customize for device.?

### I2C Algorithm

An Algorithm driver contains general code that can be used for a whole class of I2C adapters. It's function is to read and write the I2C messages to the hardware. 
Each specific adapter driver either depends on one algorithm driver, or includes its own implementation. 
There are three algorithms defined for the bus: 
 - pca
 - pcf
 - bitbanging.
   
Bigbanging involves GPIO lines where the others write to an I2C controller chip. (Is the *I2c controller* required?)

**I2C algorithms** are used to communicate with devices when the driver requests to write or read data from the device. 
They are represented by the structure `i2c_algorithm` which allows you to define function pointers that can write I2C messages (`master_xfer`) or SMBus messages (`smbus_xfer`). 

the `i2c_algorithm` abstracts the I2C bus transaction interface, where trnasaction means a tranfer, such a read or write operations. 

### I2C Adapter
There are multiple buses on the board and each bus is represented to Linux by a `struct i2c_adapter` (include/linux/i2c.h) 
Each bus in the system is represented by a *bus number* connecting a bus to a i2c adapter structure. 
The bus is subject to a protocol called the *i2c algorithm* for communicating with the device. 
This bus may be used with I2C messages or SMBus (System Management Bus) messsages. Modern pcs rely on SMBus to connect devices such as RAM modules, i2c devices, and others. The SMBus is considered a subset of the I2C protocol. 

If there is a system with 3 I2C buses, two controllowed by a *controller chip* and one *big-banged*, there would be 3 instances of `i2c_adapter` and 2 instances of an `i2c_algorithm`.

An `i2c_adapter`is used to identify a physical I2C bus.

### I2C Client
Each *device* connected to the bus is represented by the `struct i2c_client` (include/linux/i2c.h). This **maybe** defined beforehand in board-related code (arch/arm/mach.../board-omap...c). 
The device has an *address* that is used by driver to determine where the device is on the bus. This address is hardcoded by the device? It's something like 0x14. The device also has a *name* and an *interrupt number* used to trigger and interrupt. 

You must tell the *client* about the *adapter* which represents its bus line. When you want to read or write to device, it must know which bus line to use for communication. The *client* represents the device to linux. Since the device is hardware, this is usually defined under [Board Information](###I2C-Board-Information)

`i2c_client` is used to abstact a slave device sitting in the I2C bus. 

###  I2C Board Information
Again, this may be where the `i2c_client` is defined in `struct i2c_board_info` (include/linux/i2c.h). 
The board information structure contains information related to the board as well as devices on the board? The *type* field indicates the type of (i2c) device and is copied to the `i2c_client` object. The *addr* field is similar to above in the client (copied to address field in *i2c_client*. There is also parallels *irq* .. The board information structS are written as an array of devices like the following:
```C
static struct i2c_board_info z23_devices[] = {
	{
		.type = eeprom_abc,
		.addr = 0x28,
		.irq = 5,
	},
	{
		.type = adc_efg,
		.addr = 0x29,
	},
};
```
This board info is received into the kernel during bootup. The *i2c_client* is created when the *i2c_adapter* is registered. It is possible to manually add *i2c_clients* that the board does not know about.?

### I2C Driver

For each device, there exists a driver that corresponds to it. The driver is represented by `struct i2c_driver` (https://elixir.bootlin.com/linux/v6.14.4/source/include/linux/i2c.h#L235). 
The driver has a *name* which is used to link the client device with one driver. The driver also has a *probe* function which is called when the device and driver are both found on the system by a *Linux device driver subsystem*. For example: 

```C
static struct i2c_driver foo_driver = {
	.driver = {
		.name = "foobar",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(foo_dt_ids) // for the device tree 
	},
	.id_table = foo_idtable,
	.probe    = foo_probe,
	.remove   = foo_remove,
};

static struct i2c_device_id foo_idtable[] = {
	{ "foo", 0},
	{}
}

MODULE_DEVICE_TABLE(i2c, foo_idtable);

static const struct of_device_id foo_dt_ids[] = {
	{.compatible = "foo,bar", .data = (void*) 0xDEADBEEF},
	{}
};

MODULE_DEVICE_TABLE(of, foo_dt_ids);
```

The `i2c_driver` is the driver of a slave device. 

Below is an image of the I2C subsystem for reference. This image is most helpful for reference and understanding the system as a whole.
![](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/linux_i2c_subsystem.jpg)

### Define an i2c_driver

1- Define an allocate a private data struct ( that contains `struct i2c_adapter`)

2- Fill algorithm struct: 
 - `.master_xfer()` - function to transform transfer
 - `.functionality` - function to retrieve bus functionality
   
3- Fill adaptor struct:
 - `i2c_set_adapdata()
 - `.algo` pointer to algorithm struct.
 - `.algo_data` pointer the private data struct.
   
4- Add adapter
   - `i2c_add_adapter()`

### I2c Device driver general data

Each client structure has a special data field that can point to any structure at all. Use this to keep device 
specific data. This can be used for example to keep an internal state. 

```
// store the value
void i2c_set_clientdata(struct i2c_client *client, void *data);
```

```
// retrieve value
void i2c_get_clientdata(const struct i2c_client *client);
```

### I2c driver initialization

```
static int __int foo_init(void)
{
	return i2c_add_driver(&foo_driver);
}
module_init(foo_init);

static void __exit foo_cleanup(void)
{
	i2c_del_driver(&foo_driver);
}
module_exit(foo_cleanup);
```

The `module_i2c_driver()`  macro can be used to reduce the above code

```
module_i2c_driver(foo_driver);
```

### I2C Device Driver plain I2C API


These routines read and write some bytes from/to a client. The client contains the i2c address, so you do not 
have to include it. The second parameter contains the bytes to read/write, the third the number of bytes to 
read/write (must be less than the length of the buffer, also should be less that 64k since msg.len is u16). 
Returns the actual number of bytes read/written. 


 - https://elixir.bootlin.com/linux/v6.14.4/source/include/linux/i2c.h#L98

```
/**
 * i2c_master_send - issue a single I2C message in master transmit mode
 * @client: Handle to slave device
 * @buf: Data that will be written to the slave
 * @count: How many bytes to write, must be less than 64k since msg.len is u16
 *
 * Returns negative errno, or else the number of bytes written.
 */
static inline int i2c_master_send(const struct i2c_client *client,
				  const char *buf, int count)
```

 - https://elixir.bootlin.com/linux/v6.14.4/source/include/linux/i2c.h#L68

```
/**
 * i2c_master_recv - issue a single I2C message in master receive mode
 * @client: Handle to slave device
 * @buf: Where to store data read from slave
 * @count: How many bytes to read, must be less than 64k since msg.len is u16
 *
 * Returns negative errno, or else the number of bytes read.
 */
static inline int i2c_master_recv(const struct i2c_client *client,
				  char *buf, int count)
```


This sends a series of messages. Each message can be read or write, and they can 
be mixed in any way. No stop condition is issued between transactions. The i2c_msg structure contains for each message the client address, 
the number of bytes of the message and the message data itself. 

https://elixir.bootlin.com/linux/v6.14.4/source/drivers/i2c/i2c-core-base.c#L2279
```
/**
 * i2c_transfer - execute a single or combined I2C message
 * @adap: Handle to I2C bus
 * @msgs: One or more messages to execute before STOP is issued to
 *	terminate the operation; each message begins with a START.
 * @num: Number of messages to be executed.
 *
 * Returns negative errno, else the number of messages executed.
 *
 * Note that there is no requirement that each message be sent to
 * the same slave address, although that is the most common model.
 */
int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
```

### I2C Device Registration

If the bus number on which the device is connected is known use,

```C
int i2c_register_board_info(int busnum, struct i2c_board_info &ast;info, unsigned len);
```

where *busnum* is the number of the bus which the device is connected (identify the *i2c_adapter*); info is an array of *i2c_board_info* structures and *len* is the array length..

Else if the bus number is not known but the *i2c_adapter* is known, use,

```C
struct i2c_client &ast;
i2c_new_device(struct i2c_adapter &ast;adap, struct i2c_board_info const *info);
```

where info is an object, indexed of the previous array (adap, &z23_devices[1]).

Also, the `struct i2c_driver` has to be registered with the I2C subsytem in the `module_init`
```C
i2c_add_driver(struct i2c_driver *drv);
```
This line will match the name of the driver through the i2c subsytem to all the i2c_client names; on a match, the probe routine of the driver will be called and the *client* will verified as a device (in probe). 	

### Communicating on the I2C Bus

#### Reading bytes from bus
```C
i2c_smbus_read_byte_data(struct i2c_client *client, u8 command);
```
Client is received in probe function...
And reading words is similar:
```C
i2c_smbus_read_word_data(struct i2c_client *client, u8 command);
```

#### Writing bytes
```C
i2c_smbus_write_byte_data(struct i2c_client *client, u8 command, u8 data);

i2c_smbus_write_word_data(struct i2c_client *client, u8 command, u16 data);
```

### Instantiating I2C devices

There are several means of declaring/instantiating a I2C device

1. Declare device by bus number in `i2c_board_info` found in arch/ board code
```C
static struct i2c_board_info h4_i2c_board_info[] __initdata = {
   {
           I2C_BOARD_INFO("isp1301_omap", 0x2d),
           .irq            = OMAP_GPIO_IRQ(125),
   },
   {       /* EEPROM on mainboard */
           I2C_BOARD_INFO("24c01", 0x52),
           .platform_data  = &m24c01,
   },
   {       /* EEPROM on cpu card */
           I2C_BOARD_INFO("24c01", 0x57),
           .platform_data  = &m24c01,
   },
};

static void __init omap_h4_init(void)
{
       (...)
        i2c_register_board_info(1, h4_i2c_board_info,
                       ARRAY_SIZE(h4_i2c_board_info));
       (...)
}
```

2. Declare device via device tree (dts) and will be imported into kernel

```C
i2c1: i2c@400a0000 {
	clock-frequency = <100000>;
	...
```
3. Declare device explicitly in module. Usually when you don't know the i2c bus number ahead of time or for internal communication. 
You include the `i2c_board_info` within the module and then call `i2c_new_device()` to register device with system.
```C
static struct i2c_board_info sfe4001_hwmon_info = {
        I2C_BOARD_INFO("max6647", 0x4e),
};

int sfe4001_init(struct efx_nic *efx)
{
        (...)
        efx->board_info.hwmon_client =
                i2c_new_device(&efx->i2c_adap, &sfe4001_hwmon_info);

        (...)
}
```

4. Probe I2C bus for devices
This method allows i2c-core to probe for devices after their drivers are loaded. If one is found, an I2C device will be initiated.
The driver must implement the "detect()" method which identifies a supported device by reading arbitrary registers. 
This method will only probe buses that are likely to have supported devices and *agree* to be probed.

5. Lastly, you can instantiate a device from user space through sysfs
This is only if you cannot modify the kernel. You need to know the name of the I2C device and the address.
**Example**

```C
$ echo eeprom 0x50 > /sys/bus/i2c/devices/i2c-3/new_device
```

This method can be used to correct mistaken addresses and such in dts or kernel. 
Unexpected address. Unsupported devices. Development issues.


### Userspace development

reference: [https://github.com/rrmhearts/linux-driver-examples/tree/master/i2c](https://www.kernel.org/doc/Documentation/i2c/dev-interface)

You can read and write to I2C devices from the userspace. 
First, one must use `i2c-detect -l` to find out adapter number information. 
After you have this and the address of the device, see the following code from [dev-interface](https://www.kernel.org/doc/Documentation/i2c/dev-interface).

```C
#include <linux/i2c-dev.h>

...
// Open device
  int file;
  int adapter_nr = 2; /* probably dynamically determined */
  char filename[20];
  
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
  }
...
// Specify address
  int addr = 0x40; /* The I2C address */

  if (ioctl(file, I2C_SLAVE, addr) < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
  }
...
// Use SMBus commands or I2C to communicate. (SMBus is preferred)
  __u8 reg = 0x10; /* Device register to access */
  __s32 res;
  char buf[10];

  /* Using SMBus commands */
  res = i2c_smbus_read_word_data(file, reg);
  if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
  } else {
    /* res contains the read word */
  }

  /* Using I2C Write, equivalent of 
     i2c_smbus_write_word_data(file, reg, 0x6543) */
  buf[0] = reg;
  buf[1] = 0x43;
  buf[2] = 0x65;
  if (write(file, buf, 3) != 3) {
    /* ERROR HANDLING: i2c transaction failed */
  }

  /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
  if (read(file, buf, 1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
  } else {
    /* buf[0] contains the read byte */
  }

```


## Industrial I/O devices

References:
 - https://www.kernel.org/doc/html/v4.14/driver-api/iio/index.html
 - sample: https://elixir.bootlin.com/linux/latest/source/drivers/iio/dummy/iio_simple_dummy.c
 - https://abhashpl.hashnode.dev/my-linux-kernel-bug-fixing-mentorship-experience (iio drives)
 - https://www.kernel.org/doc/html/latest/driver-api/iio/index.html
 - https://linux.ime.usp.br/~marcelosc/2019/09/Simple-IIO-driver
 - https://linux.ime.usp.br/~marcelosc/2019/09/Introduction-to-IIO-driver-development
 - 10 Years of the Industrial I/O Kernel Subsystem - Jonathan Cameron: https://youtu.be/644oH1FXdtE?si=1A9JVMcIvjoRdIi1
 - https://www.kernel.org/doc/html/v4.12/driver-api/uio-howto.html
 - https://bootlin.com/blog/the-backbone-of-a-linux-industrial-i-o-driver/
 - https://www.kernel.org/doc/html/v4.12/driver-api/iio/index.html
 - rpi compilation tutorial: https://linux.ime.usp.br/~marcelosc/2019/09/RaspberryPi-kernel-compilation
 - video iio example: https://youtu.be/l8mQtpZhgYI
 - https://linux.ime.usp.br/~marcelosc/2019/09/Introduction-to-IIO-driver-development
 - https://linux.ime.usp.br/~marcelosc/2019/09/Simple-IIO-driver
 - LibIIO - A Library for Interfacing with Linux IIO Devices - Dan Nechita: https://youtu.be/p_VntEwUe24
 - example PR: https://github.com/analogdevicesinc/linux/pull/436/commits/3d2c7522c01b19c19c77adfac0ab1546b56426bc
 - how to connect to a rpi thru the USB port: https://linux.ime.usp.br/~marcelosc/2019/01/SSH-em-Raspberrypi-conectada-por-USB
 - LibIIo: https://www.youtube.com/watch?v=p_VntEwUe24
 - https://wiki.analog.com/software/linux/docs/iio/iio
 - Embedded Linux Weekend Hacking, Part 5: Interfacing Sensors via the Industrial I/O (IIO) Subsystem: https://www.linkedin.com/pulse/embedded-linux-weekend-hacking-part-5-interfacing-via-kumar-phd-s0obc/


The IIO framework interaces sensors (ADCs or DACs) with the kernel.

Usually these sensors are connected via SPI or I2C. A common use case of the sensors devices is to have combined functionality (e.g. light plus proximity sensor).

The IIO model is based on device an channel architecture: 
 - the device represents the chip itself, at the top hierachical level.
 - the channels represents the acquisitons modes of the device, a device can have one or more channels ... for example an accelerometer or gyroscope.

The IIO element will be exposed to the user space as a character device (when triggered buffer is supported ) and in the sysfs directory 
whit the channels defined in it: 
 - `/dev/ioo:deviceX` exports events and buffered data
 - `/sys/bus/iio/iio:deviceX/`, a direcotry with represents the device and its channels


Example IIO:
- [AD7292 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/AD7292.PDF)
- [iio: adc: ad7292: add driver support for
AD7292](https://github.com/analogdevicesinc/linux/pull/436/commits/3d2c7522c01b19c19c77adfac0ab1546b56426bc)
- [dt-bindings: iio: adc: add DT docs for
AD7292](https://github.com/analogdevicesinc/linux/pull/436/commits/9bcafa90d1b01c36619b20f788fb769e1d43a727)
- [iio: adc: ad7292: add dtoverlay for
AD7292](https://github.com/analogdevicesinc/linux/pull/436/commits/774e39b7ac4bbcfb4104778e5e08e73b863923be)
- [iio: adc: ad7292: add IIO ADC
channels](https://github.com/analogdevicesinc/linux/pull/456/commits/be0aa43f1bcbf934402002693e496cd61bb15541)
- [iio: adc: ad7292: add voltage regulator
support](https://github.com/analogdevicesinc/linux/pull/456/commits/09434bb92f8828802ef7ec4e055e22d20518537b)
- [iio: adc: ad7292: add SPI reg read
functions](https://github.com/analogdevicesinc/linux/pull/456/commits/49db8a5d1421636f7e893a0836c4e6f4391c84b1)
- [iio: adc: ad7292: read single conversion
results](https://github.com/analogdevicesinc/linux/pull/529/commits/9f3cc26a3fb5d8331396debfd6f55803e92e887f)
- [iio: adc: ad7292: add support to read ADC
scale](https://github.com/analogdevicesinc/linux/pull/529/commits/f7b5cbeba36ad42143994a7c7862adad70c45006)

drivers/iio/adc/ad7292.c
```C
// SPDX-License-Identifier: GPL-2.0
/*
 * Analog Devices AD7292 SPI ADC driver
 *
 * Copyright 2019 Analog Devices Inc.
 */

#include <linux/device.h>
#include <linux/module.h>
#include <linux/spi/spi.h>

#include <linux/iio/iio.h>

struct ad7292_state {
	struct spi_device *spi;
};

static int ad7292_setup(struct ad7292_state *st)
{
	return 0;
}

static int ad7292_read_raw(struct iio_dev *indio_dev,
			   const struct iio_chan_spec *chan,
			   int *val, int *val2, long info)
{
	return 0;
}

static int ad7768_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long info)
{
	return 0;
}

static const struct iio_info ad7292_info = {
	.read_raw = ad7292_read_raw,
	.write_raw = &ad7768_write_raw,
};

static const struct iio_chan_spec ad7292_channels[] = {
};

static int ad7292_probe(struct spi_device *spi)
{
	struct ad7292_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad7292_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7292_channels);
	indio_dev->info = &ad7292_info;

	ret = ad7292_setup(st);
	if (ret)
		return ret;

	return devm_iio_device_register(&spi->dev, indio_dev);
}

static const struct spi_device_id ad7292_id_table[] = {
	{ "ad7292", 0 },
	{}
};
MODULE_DEVICE_TABLE(spi, ad7292_id_table);

static const struct of_device_id ad7292_of_match[] = {
	{ .compatible = "adi,ad7292" },
	{ },
};
MODULE_DEVICE_TABLE(of, ad7292_of_match);

static struct spi_driver ad7292_driver = {
	.driver = {
		.name = "ad7292",
		.of_match_table = ad7292_of_match,
	},
	.probe = ad7292_probe,
	.id_table = ad7292_id_table,
};
module_spi_driver(ad7292_driver);

MODULE_AUTHOR("Marcelo Schmitt <marcelo.schmitt1@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD7292 ADC driver");
MODULE_LICENSE("GPL");
```


### Core elements: 

Reference: https://www.kernel.org/doc/html/latest/driver-api/iio/core.html









