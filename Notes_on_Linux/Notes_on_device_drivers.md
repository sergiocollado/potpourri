# Notes on device drivers

References:
 - https://www.kernel.org/doc/html/v5.5/driver-api/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/index.html
 - https://www.kernel.org/doc/html/v5.5/driver-api/driver-model/bus.html
 - Understanding the Structure of a Linux Kernel Device Driver - Sergio Prado, Toradex : https://www.youtube.com/watch?v=pIUTaMKq0Xc
 - https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html


There are 3 main components buses (`bus_type`), device_drives (`device_drive`), and devices (`device`). 
 - `bus_type`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/bus.h#L84
 - `device_driver`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device/driver.h#L51
 - `device`: https://elixir.bootlin.com/linux/v6.0/source/include/linux/device.h#L458

Those components can be reached in `/sys`:

![sys_bus_device_and_drivers](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/sys_bus_device_drivers.png)
