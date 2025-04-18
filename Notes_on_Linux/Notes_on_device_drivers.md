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


## Platform devices

References:
 - Platform Devices and Drivers: https://www.kernel.org/doc/html/latest/driver-api/driver-model/platform.html
 - The platform device API : https://lwn.net/Articles/448499/
 - Platform devices and device trees : https://lwn.net/Articles/448502/
 - Device tree usage: https://elinux.org/Device_Tree_Usage
   

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









