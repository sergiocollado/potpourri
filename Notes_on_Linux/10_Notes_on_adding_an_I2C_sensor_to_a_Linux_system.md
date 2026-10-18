# Example of usage RPi with MPU6050  


![mpu6050 image](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/mpu6050.jpg)

references:
 - how mpu6050 works: https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/
 - Help with reading mpu6050 configured with device tree and overlays: https://forums.raspberrypi.com/viewtopic.php?p=2314647&hilit=mpu6050#p2314647
     - https://docs.kernel.org/iio/iio_devbuf.html
     - https://docs.kernel.org/admin-guide/abi-testing-files.html#abi-file-testing-sysfs-bus-iio
     - https://stackoverflow.com/questions/36791837/reading-iio-device-data-from-user-space
     - https://stackoverflow.com/questions/43134050/no-output-from-iio-character-device-output-iio-buffer/43369725#43369725
 - https://bootlin.com/blog/the-backbone-of-a-linux-industrial-i-o-driver/
 - datasheet: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 - binding: https://www.kernel.org/doc/Documentation/devicetree/bindings/iio/imu/invensense%2Cmpu6050.yaml
 - how to instanciate i2c devices: https://www.kernel.org/doc/html/latest/i2c/instantiating-devices.html#how-to-instantiate-i2c-devices
 - linux kernel device: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/iio/imu/inv_mpu6050?h=v6.15-rc6
 - https://github.com/OpenChannelSSD/linux/blob/master/Documentation/devicetree/bindings/iio/imu/inv_mpu6050.txt
 - rpi pinouot cheatsheet: https://pinout.xyz/
 - https://embarcados.com.br/utilizando-o-mpu-6050-com-device-driver-e-device-tree-na-raspberry-pi-zero-w/#Os-Melhores-Treinamentos-sobre-Sistemas-embarcados-e-IoT
 - https://hubtronics.in/learn/mastering-device-tree-overlays-rpi
 - https://tutorials-raspberrypi.com/measuring-rotation-and-acceleration-raspberry-pi/
 - mpu6050 overlay: https://github.com/raspberrypi/linux/blob/rpi-5.10.y/arch/arm/boot/dts/overlays/mpu6050-overlay.dts # check the rpi version that you need
 - https://www.raspberrypi.com/documentation/computers/configuration.html#part2
 - https://www.linuxquestions.org/questions/linux-kernel-70/invensense-mpu6050-and-device-trees-4175728278/#google_vignette
 - https://www.electronicwings.com/raspberry-pi/mpu6050-accelerometergyroscope-interfacing-with-raspberry-pi
 - Understanding I2C Communication in Linux: A Beginner's Guide with Sample Code for Raspberry Pi : https://www.linkedin.com/pulse/understanding-i2c-communication-linux-beginners-guide-soheil-nazari/
 - linux kernel mpu6050 device driver: https://github.com/torvalds/linux/tree/master/drivers/iio/imu/inv_mpu6050
 - MPU-6050 Linux Device Driver: https://github.com/fdcavalcanti/driver-mpu6050/tree/main
 - MPU6050 driver code: https://github.com/anasvag575/MPU6050_driver/tree/master/Driver_code
 - Use the MPU6050 accelerometer on Raspberry-Pi with i2c commands: https://openest.io/non-classe-en/mpu6050-accelerometer-on-raspberry-pi/
 - https://wiki.stmicroelectronics.cn/stm32mpu/index.php?title=How_to_use_the_IIO_user_space_interface&oldid=77686
 - https://www.kernel.org/doc/Documentation/i2c/dev-interface
 - https://emlogic.no/2025/06/accessing-i2c-devices-from-userspace-in-linux/
 - Guide to interfacing a Gyro and Accelerometer with a Raspberry Pi: https://ozzmaker.com/berryimu/
 - i2c userspace development: https://github.com/rrmhearts/linux-driver-examples/tree/master/i2c#userspace-developmentf

linux drivers code: 
 - MPU-6050 Linux Device Driver: https://github.com/fdcavalcanti/driver-mpu6050/tree/main
 - MPU6050 driver code: https://github.com/anasvag575/MPU6050_driver/tree/master/Driver_code (for a Nucleo board!) 
 - linux kernel mpu6050 device driver: https://github.com/torvalds/linux/tree/master/drivers/iio/imu/inv_mpu6050
 - i2c drivers examples: https://github.com/rrmhearts/linux-driver-examples/tree/master/i2c
 - https://github.com/jrowberg/i2cdevlib/tree/master/LinuxI2CDev/MPU6050
 - [https://github.com/chetansunaskar/MPU6050_LINUX_DEVICE_DRIVER/tree/main](https://github.com/chetansunaskar/MPU6050_LINUX_DEVICE_DRIVER/blob/main/Drivers/Linux/Mpu6050I2cDriver.c)

MPU6059 documentation: 
 - https://mjwhite8119.github.io/Robots/mpu6050
 - https://www.invensense.tdk.com/en-us/search-result?query=PS-MPU-6000A-00%20%E2%80%93%20MPU-6000%20and%20MPU-6050%20Datasheet
 - https://github.com/anasvag575/MPU6050_driver/blob/master/Doc/MPU60x0%20Register%20Map.pdf
 - https://github.com/anasvag575/MPU6050_driver/blob/master/Doc/User%20Manual%20MPU60x0.pdf
 - https://github.com/Destinysj/Self_Balancing_Bot/blob/master/MPU-6050-Register-Map.pdf
 - https://github.com/Destinysj/Self_Balancing_Bot/blob/master/MPU-6050_DataSheet.pdf
   
The system used is:
```
- $ uname -r: 6.12.25+rpt-rpi-v8
- $ cat /sys/firmware/devicetree/base/model: Raspberry Pi 4 Model B Rev 1.4
```

also check with: 

```
cat /etc/os-release
```

The connection of the device shoud be (reference: https://pinout.xyz/pinout/ground):

```
rpi            | mpu6050
pin2 5V        | Vcc
pin3 i2c1 sda  | SDA
pin5 i2c1 scl  | SCL
pin39 ground   | GND
pin34 ground   | AD0 (so the address is 0x68)
```

The MPU6050 depends on I2C so enable it in the rpi by the GUI or editing the configuration files. You can also enable the i2c interface with `sudo raspi-config`.

Check the version of linux kernel used by the system with the command `uname -r`.

Got to the device drivers folder located in `/lib/modules/<kernel_version>/kernel/drivers` (the kernel version is the one retrieved in the previous step).

Search for the the mpu6050 driver, for example using `find . -name '*mpu*' `. 

If you cannot find the driver there are two options: 
 - the driver has not been implemented yet
 - the driver exists but has not been compiled for the kernel being used

Check if the overlay file exists, it should be in `/boot/overlays`, you can search for it with the command `find . -name "*mpu*"`. 

If the overaly doesn't exist you can create it: create a new `.dts` file with the description of the hardware you want to apply to the base device tree. 

The mpu6050 overlay is defined here: https://github.com/raspberrypi/linux/blob/rpi-5.18.y/arch/arm/boot/dts/overlays/mpu6050-overlay.dts .. check the branch/version you need.

If the overlay file exist you can dinamically create the dts. If you don't have it already installed, install the dtc compiler with  `sudo apt-get install device-tree-compiler` 

Use the `dtc` compiler to compile the overlay source file into a device tree overlay (`.dtbo`) file: 

```
dtc -@ -I dts -O dtb -o my_overaly.dtbo my_overalay.dts
```

load the overlay, move the overlay to the overlay's folder

```
sudo cp my_overaly.dtbo /boot/overalays
```

add the overlay into the configuration. (the actual line can be slightly different with regard the os version, check here: https://github.com/raspberrypi/linux/tree/rpi-6.12.y/arch/arm/boot/dts/overlays
```
sudo sh -c "echo my_overlay.dtbo >> /boot/config.txt" # or just open the config.txt file and add the overlay
```
or the raspbery 4 used, only is needed to add the line: "dtoverlay=i2c-sensor,mpu6050". Please, remember that for using it, you have to activate also the i2c, so in the `/boot/firmware/confit.txt` file (or the correct file in your system), update the i2c configuration to: `dtparam=i2c_arm=on`. 

If you are not generating the dtc, you can apply the mpu6050 overaly in the `/boot/firmware/config.txt` file, adding: `dtoverlay=i2c-sensor,mpu6050,addr=0x69` the `address` is only if you want to definen the addres, if it is not defined by default is `0x68` 

so for example: 

```
# @ File /boot/firmware/config.txt

# For more options and information see
# http://rptl.io/confitxt
# Some settings may impact device functionality . See link below for details

# Unconmment some or all of these to enable the optional hardware interfaces
dtparam=i2c-arm=on    # <-- UNCOMMENT THIS!!! 
#dtparam=i2s=on
#dtparam=spi=on

# Enable mpu6050
dtoverlay=i2c-sensor,mpu6050,addr=0x68   # <-- DEFINE THIS!!!

#Aditional overlays and parameters are documented
# /boot/firmware/overlays/README
   ...
```

reboot the rpi `sudo reboot`. 

Verify the overlay: After rebooting, you can verify that the overlay was applied by checking the device tree: `dtc -I fs /sys/firmware/devicetree/base`

Check if the mpu6050 is detected and running correctly using `i2cdetect -y 1` to scan for I2C devices

```
$ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- UU -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --

// note that the addes is colum 8, row 60, that is address: 0x68 - that is the address where the sensor is.

// In the output, UU denotes a device which is used by a kernel driver, and you are not recommended to interfere with it.               
```

If you list the i2c devices you will get: 

```
sergio@rpihole:/dev $ i2cdetect -l
i2c-1   i2c             bcm2835 (i2c@7e804000)                  I2C adapter
i2c-2   i2c             bcm2835 (i2c@7e805000)                  I2C adapter
i2c-11  i2c             i2c-1-mux (chan_id 0)                   I2C adapter
```

<hr> 

--- 

**NOTE**: Notice the difference if the sensor is not defined in the device tree (by means of the definition in `/boot/firmware/config.txt`)

In case the driver-device is not defined in the `/boot/firmware/config.txt` file, then the i2c device will appear as: 

```
$ i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- 68 -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
```

If you list the i2c devices you will get: 

```
$ i2cdetect -l
i2c-1   i2c             bcm2835 (i2c@7e804000)                  I2C adapter
i2c-2   i2c             bcm2835 (i2c@7e805000)                  I2C adapter
```

If we check into the `/dev` directory, no dev is associated to `iio`: 

```
 $ ls
autofs         dma_heap   hidraw1  loop1         media0     null   ram12  ram7    stdout  tty7       vchiq   vcs6   vcsa7     vcsu7    video18    zram0
block          dri        hwrng    loop2         media1     port   ram13  ram8    tty     tty8       vcio    vcs7   vcsm-cma  vhci     video20
btrfs-control  fd         i2c-1    loop3         media2     ppp    ram14  ram9    tty0    tty9       vc-mem  vcsa   vcsu      video10  video21
bus            full       i2c-2    loop4         mem        ptmx   ram15  random  tty1    ttyprintk  vcs     vcsa1  vcsu1     video11  video22
cec0           fuse       initctl  loop5         mmcblk0    pts    ram2   rfkill  tty10   uhid       vcs1    vcsa2  vcsu2     video12  video23
char           gpiochip0  input    loop6         mmcblk0p1  ram0   ram3   shm     tty11   uinput     vcs2    vcsa3  vcsu3     video13  video31
console        gpiochip4  kmsg     loop7         mmcblk0p2  ram1   ram4   snd     tty12   urandom    vcs3    vcsa4  vcsu4     video14  watchdog
cuse           gpiomem    log      loop-control  mqueue     ram10  ram5   stderr  tty13   usb        vcs4    vcsa5  vcsu5     video15  watchdog0
disk           hidraw0    loop0    mapper        net        ram11  ram6   stdin   tty14   v4l        vcs5    vcsa6  vcsu6     video16  zero
```

also, there is not `iio` folder in the `/sys` directory: 

```
/sys/bus $ ls
amba  clockevents  container  event_source  genpd  hid  iscsi_flashnode  media     mmc       nvmem         platform  sdio    serial-base  spi  vchiq-bus
cec   clocksource  cpu        gadget        gpio   i2c  mdio_bus         mipi-dsi  mmc_rpmb  nvmem-layout  scsi      serial  snd_seq      usb  workqueue
```
--- 
<hr>


Access IIO data: You can now access the IIO data from your device using the IIO driver, which is typically done through the `/sys/bus/iio/devices` directory or through a library like `libiio`

Watch out: The mpu6050 device tree overlay is not a standard inclusion in the Raspberry Pi 3 (Pi 3) kernel, unlike later models. This means you'll need to manually configure and load the overlay if you wish to use an MPU6050 sensor with your Pi 3. The Pi 3 lacks a dedicated MPU6050 overlay for ease of use, but it can still be used with additional setup. Reference: https://forums.raspberrypi.com/viewtopic.php?t=230766

To read data from an MPU6050 device file within the Linux kernel, you'll generally interact with the device using the iio (Industrial Input/Output) framework and the files found in /sys/bus/iio/devices/. Specifically, you'll need to configure the scan elements and triggers associated with the MPU6050 to enable data capture. 

```
$ ls /sys/bus/iio/devices/iio:device0
buffer                   in_accel_scale            in_accel_z_calibbias        in_anglvel_x_raw        in_temp_offset  sampling_frequency            waiting_for_supplier
buffer0                  in_accel_scale_available  in_accel_z_raw              in_anglvel_y_calibbias  in_temp_raw     sampling_frequency_available
current_timestamp_clock  in_accel_x_calibbias      in_anglvel_mount_matrix     in_anglvel_y_raw        in_temp_scale   scan_elements
dev                      in_accel_x_raw            in_anglvel_scale            in_anglvel_z_calibbias  name            subsystem
in_accel_matrix          in_accel_y_calibbias      in_anglvel_scale_available  in_anglvel_z_raw        of_node         trigger
in_accel_mount_matrix    in_accel_y_raw            in_anglvel_x_calibbias      in_gyro_matrix          power           uevent
```

The different files are explained here: https://docs.kernel.org/iio/iio_devbuf.html

To read the values of the mpu6050 a step-by-step guide:

references: 
 - https://stackoverflow.com/questions/36791837/reading-iio-device-data-from-user-space#:~:text=I%20believe%20your%20issue%20relates,%5Bx%5D/trigger/current_trigger.&text=hope%20thats%20help.
 - https://patchwork.kernel.org/project/linux-iio/patch/20210322132408.1003443-1-linus.walleij@linaro.org/#24069765


1. Identify the MPU6050's iio device directory:<br>
Look for the MPU6050's entry under /sys/bus/iio/devices/. It will be something like iio:device[x], where x is a number.

3. Configure scan elements:<br>
Within the device directory, you'll find the scan_elements directory.<br>
Inside, you'll find files like _en, _index, and _type for each sensor (accelerometer, gyroscope, etc.).<br>
To enable a sensor, write 1 to its corresponding _en file.<br>
The _type file indicates the type of data (e.g., "accel", "gyro").<br> 
The _index file specifies the channel for the data.

5. Set up triggers (if needed):<br>
Some MPU6050 drivers may require you to enable a trigger to start data acquisition.<br>
If so, there will be a trigger directory within the device directory.<br>
You might need to write the trigger name to the current_trigger file within the trigger directory.

The correct command is: `cat /sys/bus/iio/devices/trigger[x]/name > /sys/bus/iio/devices/iio:device[x]/trigger/current_trigger`.

7. Configure the buffer:<br>
You'll also find a buffer directory.<br>
Here, you can set the buffer length using the length file.<br>
Enable the buffer by writing 1 to the enable file.

9. Read data: <br>
Once configured, you can read the data from the device file.<br>
The specific file and format will depend on the MPU6050 driver and how it's configured.<br>
You can use the read system call to read the data.

Example: <br>
Let's say the MPU6050 is recognized as iio:device0. <br>
Navigate to /sys/bus/iio/devices/iio:device0/.<br>
Enable the gyroscope: echo 1 > scan_elements/gyro_en.<br>
Enable a trigger (if required): echo "mpu6050-dev1" > trigger/current_trigger.<br>
Set the buffer length: echo 100 > buffer/length.<br>
Enable the buffer: echo 1 > buffer/enable.<br>
Read data: cat /sys/bus/iio/devices/iio:device0/in_accelx_raw (or similar, depending on the specific sensor).<br>

Important notes:
You'll need appropriate permissions (usually root) to access and modify these files. 
Refer to the specific MPU6050 driver documentation for details on the exact configuration and data formats. <br>
You may need to load the relevant kernel module (e.g., inv_mpu6050.ko). <br>
By following these steps, you can interact with the MPU6050 device file and read its sensor data within the Linux kernel environment. 


To grant non-root user access to `/sys/bus/iio/devices`, you have to create a custom udev rule: `sudo vim /etc/udev/rules.d/99-iio.rules`

Add the following lines to assign IIO devices to an iio group and make them group-writable:
```
SUBSYSTEM=="iio", KERNEL=="iio:device[0-9]*", GROUP="iio", MODE="0664"
SUBSYSTEM=="iio", ACTION=="add", PROGRAM="/bin/sh -c 'chgrp -R iio /sys%p; chmod -R g+w /sys%p'"
```

Create the iio group if it does not already exist: `sudo groupadd -f iio`

Add your user (replace pi with your actual username) to the iio group: `sudo usermod -aG iio pi`

Reload the udev rules and trigger them:

```
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Log out and log back in (or reboot your Raspberry Pi) for the group membership change to take full effect.

... Or you can just `chmod` the files and then you can read/write them.

Go to the device `ls /sys/bus/iio/devices/`

Move into the device directory `cd /sys/bus/iio/devices/iio:device0/`

Read accelerometer values (X, Y, Z) : `cat cat in_accel_[x,y,z]_raw`:

```
cat in_accel_x_raw
cat in_accel_y_raw
cat in_accel_z_raw
```
Read gyroscope values (X, Y, Z)
```
cat in_anglvel_x_raw
cat in_anglvel_y_raw
cat in_anglvel_z_raw
```

Read the temperature sensor
```
cat in_temp_raw
```

You can check with the command: ` watch cat in_accel_[x,y,z]_raw` ... it should be printing different values as you move the sensor around.


... then you may want to calibrate the sensor...

To convert these raw integers into physical values (like m/s² or degrees per second), multiply the raw value by its corresponding scale file: `cat in_accel_scale`.

To see what scale configurations your kernel driver supports, check the corresponding `_scale_available` attribute files (if exposed by your specific driver version)

 - Read accelerometer options: `cat /sys/bus/iio/devices/iio:device0/in_accel_scale_available`
 - Read gyroscope options: `cat /sys/bus/iio/devices/iio:device0/in_anglvel_scale_available`

You can define the scale like: `echo 0.000598 > /sys/bus/iio/devices/iio:device0/in_accel_scale`

references:
 - https://www.youtube.com/watch?v=5xLHZEl0h10
 - https://forum.arduino.cc/t/mpu-6050-calculating-yaw-pitch-and-roll/1360842
 - https://github.com/anasvag575/MPU6050_driver/blob/master/Driver_code/mpu6050.c <- Self Test Routine (calibration method) -- check the self test routine (calibration method)

### Error: Device or resource busy (errno = 16)

In Linux Industrial I/O (IIO), a "Device or resource busy" (EBUSY) error typically occurs when you attempt to read a sysfs attribute (like `in_voltageX_raw`) while the device is actively running in continuous buffer/streaming mode, or when another process/daemon already has an open handle to the character device node (`/dev/iio:deviceX`)

#### Common Causes and Solutions

**The cause**: Trying to use a standard cat command on a raw sysfs file (e.g., `cat /sys/bus/iio/devices/iio:device0/in_voltage0_raw`) while the ADC or sensor is already configured and running inside a capture buffer.

**The fix**: If the device's buffer is enabled, you must read data via the character device interface (`/dev/iio:deviceX`) rather than individual `_raw+  sysfs files, or stop the buffer first

#### Active Buffer Capture LockoutThe Cause:

An application (such as `iio-capture` or a custom user-space daemon using `libiio`) opened a buffer stream and did not cleanly close or disable it. The kernel keeps the resource locked.

**The fix**: Explicitly disable the buffer via sysfs to release the lock: `echo 0 > /sys/bus/iio/devices/iio:deviceX/buffer/enable`

So:
 - one-shot reads (buffer enable = 0) -> read from: `/sys/bus/iio/devices/iio:device0`
 - automatic reads (buffer enable = 1) -> read from `/dev/iio:device0`

The iio subsystem provides two ways to program the ADC and read the values:
 - One-shot conversions performed by reading the files in /sys/bus/iio/devices/iio\:device0/
 - Continuous conversions of a single channel at a time using the /dev/iio:device0 character device file
 - reference: https://community.nxp.com/t5/i-MX-Processors/Re-how-to-read-info-from-iio-device-iio-device0/td-p/269079?profile.language=en
 - libiio: https://analogdevicesinc.github.io/libiio/main/theory.html

### Id est: 

To read a sensor from `/dev/iio:device0`, use one-shot `sysfs` files for single values or configure the character device buffer for continuous data streams.

#### Reading **Single Values (One-Shot)**

 - For basic reads without data streams, look in the matching `sysfs` folder instead of the device file:Find the folder: `/sys/bus/iio/devices/iio:device0/` 
 - Read a channel file (for example, `cat /sys/bus/iio/devices/iio:device0/in_temp_input`).
 - Multiply the raw number by the matching scale file value to get real units. 

#### Reading Continuous Data Streams (Buffers)
 - To stream raw data from `/dev/iio:device0`, set up the buffer and triggers first: Enable scan elements: `echo 1 > /sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en`
 - Set buffer length: `echo 128 > /sys/bus/iio/devices/iio:device0/buffer/length`
 - Turn on the buffer: `echo 1 > /sys/bus/iio/devices/iio:device0/buffer/enable`
 - Read the binary stream using a tool like hexdump or a custom program: `hexdump -e '"%04x\n"' /dev/iio:device0`.

references:
  - https://stackoverflow.com/questions/36791837/reading-iio-device-data-from-user-space
  - https://forums.raspberrypi.com/viewtopic.php?t=113988
  - https://community.nxp.com/t5/i-MX-Processors/Re-how-to-read-info-from-iio-device-iio-device0/td-p/269079

### Programing the sensor

 Now you can program the sensor, reading the regitster or by means of i2c communication or with libiio. 

 For example:
  - https://openest.io/non-classe-en/activate-raspberry-pi-4-i2c-bus/
  - https://openest.io/non-classe-en/mpu6050-accelerometer-on-raspberry-pi/



### Reading the sensor from user-space

To be able to use this, the system needs to DON'T have the sensor defined in its device tree.

You will need to install the tools `sudo apt-get install i2c-tools libi2c-dev`, so you can use the i2c bus from the user-space.

In case the driver-device is not defined in the  `/boot/firmware/config.txt` file, then the i2c device will appear as: 

```
$ i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- 68 -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
```

If you list the i2c devices you will get: 

```
$ i2cdetect -l
i2c-1   i2c             bcm2835 (i2c@7e804000)                  I2C adapter
i2c-2   i2c             bcm2835 (i2c@7e805000)                  I2C adapter
```

Reference to read the i2c sensor from user-space in the documentation: 
 - https://www.kernel.org/doc/html/latest/i2c/dev-interface.html
 - https://www.kernel.org/doc/Documentation/i2c/dev-interface

The example program (remember you will have to defiene the correct values in the configuration registries) : 

```c 
// reference: https://openest.io/non-classe-en/mpu6050-accelerometer-on-raspberry-pi/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/i2c-dev.h> // I2C_SLAVE
#include <sys/ioctl.h> // ioctl()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open(), O_RDONLY
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // read(), write(), usleep()
#include <stdint.h>  // uint8_t, uint16_t, uint32_t, uint64_t
#include <errno.h>

#define MPU6050_I2C_ADDR 0x68

#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40
#define REG_PWR_MGMT_1 0x6B
#define REG_ACCEL_CONFIG 0x1C
#define REG_SMPRT_DIV 0x19
#define REG_CONFIG 0x1A
#define REG_FIFO_EN 0x23
#define REG_USER_CTRL 0x6A
#define REG_FIFO_COUNT_L 0x72
#define REG_FIFO_COUNT_H 0x73
#define REG_FIFO 0x74
#define REG_WHO_AM_I 0x75

int file = -1;

// Please note, this is not the recommanded way to write data
// to i2c devices from user space.
void i2c_write(__u8 reg_address, __u8 val) {
        char buf[2];
        if(file < 0) {
                printf("Error, i2c bus is not available\n");
                exit(1);
        }

        buf[0] = reg_address;
        buf[1] = val;

        if (write(file, buf, 2) != 2) {
                printf("Error, unable to write to i2c device\n");
                exit(1);
        }

}

// Please note, this is not thre recommanded way to read data
// from i2c devices from user space.
char i2c_read(uint8_t reg_address) {
        char buf[1];
        if(file < 0) {
                printf("Error, i2c bus is not available\n");
                exit(1);
        }

        buf[0] = reg_address;

        if (write(file, buf, 1) != 1) {
                printf("Error, unable to write to i2c device\n");
                exit(1);
        }


        if (read(file, buf, 1) != 1) {
                printf("Error, unable to read from i2c device\n");
                exit(1);
        }

        return buf[0];

}

uint16_t merge_bytes_int( uint8_t LSB, uint8_t MSB) {
        return  (uint16_t) ((( LSB & 0xFF) << 8) | MSB);
}

// 16 bits data on the MPU6050 are in two registers,
// encoded in two complement. So we convert those to int16_t
int16_t two_complement_to_int( uint8_t LSB, uint8_t MSB) {
        int16_t signed_int = 0;
        uint16_t word;

        word = merge_bytes_int(LSB, MSB);

        if((word & 0x8000) == 0x8000) { // negative number
                signed_int = (int16_t) -(~word);
        } else {
                signed_int = (int16_t) (word & 0x7fff);
        }

        return signed_int;
}

int main(int argc, char *argv[]) {
        printf("Starting the program to read the MPU6050\n");
        int adapter_nr = 1; /* probably dynamically determined */
        char bus_filename[250];
        char accel_x_h,accel_x_l,accel_y_h,accel_y_l,accel_z_h,accel_z_l,temp_h,temp_l;
        uint16_t fifo_len = 0;
        int16_t x_accel = 0;
        int16_t y_accel = 0;
        int16_t z_accel = 0;
        int16_t temp = 0;
        float x_accel_g, y_accel_g, z_accel_g, temp_f;

        snprintf(bus_filename, 250, "/dev/i2c-1", adapter_nr);
        file = open(bus_filename, O_RDWR);
        if (file < 0) {
                /* ERROR HANDLING; you can check errno to see what went wrong */
                printf("Error opening the file of the MPU6050\n");
                exit(1);
        }

    errno = 0;
        if (ioctl(file, I2C_SLAVE, MPU6050_I2C_ADDR) < 0) {
                /* ERROR HANDLING; you can check errno to see what went wrong */
                printf("Error configuring the MPU6050; errono: %d\n", errno);
                close(file);
                exit(1);
        }

        i2c_write(REG_PWR_MGMT_1, 0x01);
        i2c_write(REG_ACCEL_CONFIG, 0x00);
        i2c_write(REG_SMPRT_DIV, 0x07);
        i2c_write(REG_CONFIG, 0x00);
        i2c_write(REG_FIFO_EN, 0x88);
        i2c_write(REG_USER_CTRL, 0x44);

        //while(fifo_len != 1024) {
        while(fifo_len < 1024+1) {
                accel_x_h = i2c_read(REG_FIFO_COUNT_L);
                accel_x_l = i2c_read(REG_FIFO_COUNT_H);
                fifo_len = merge_bytes_int(accel_x_h,accel_x_l);
                //printf("fifo length: %d\n", fifo_len);

                //if(fifo_len == 1024) {
                if(fifo_len == 1024) {
                        printf("fifo overflow !\n");
                        i2c_write(REG_USER_CTRL, 0x44); // reset fifo
                        continue;
                }

                if(fifo_len >= 8) {
                        accel_x_h = i2c_read(REG_FIFO);
                        accel_x_l = i2c_read(REG_FIFO);
                        accel_y_h = i2c_read(REG_FIFO);
                        accel_y_l = i2c_read(REG_FIFO);
                        accel_z_h = i2c_read(REG_FIFO);
                        accel_z_l = i2c_read(REG_FIFO);
                        temp_h = i2c_read(REG_FIFO);
                        temp_l= i2c_read(REG_FIFO);

                        x_accel= two_complement_to_int(accel_x_h,accel_x_l);
                        x_accel_g = ((float) x_accel)/16384;

                        y_accel= two_complement_to_int(accel_y_h,accel_y_l);
                        y_accel_g = ((float) y_accel)/16384;

                        z_accel= two_complement_to_int(accel_z_h,accel_z_l);
                        z_accel_g = ((float) z_accel)/16384;

                        temp = two_complement_to_int(temp_h, temp_l);
                        temp_f = (float)temp/340 + 36.53; // calculated as described in the MPU60%) register map document

                        printf("fifo_len: %5d\t x_accel %.3fg   y_accel %.3fg   z_accel %.3fg   temp=%.1fc \r", fifo_len, x_accel_g, y_accel_g, z_accel_g, temp_f);
                } else {
                        usleep(10000);
                }

                usleep(700000);
                fflush(stdout);
                i2c_write(REG_USER_CTRL, 0x44); // reset fifo
        }

        return 0;
}
```

Other way: 


```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h> // Requires libi2c-dev package

int main() {
    int file;
    char filename[20];
    int adapter_nr = 1; // Corresponds to /dev/i2c-1
    int addr = 0x48;    // Target I2C slave device address

    // 1. Open the i2c-dev bus file descriptor
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        perror("Failed to open the I2C bus");
        return 1;
    }

    // 2. Configure the file descriptor with the target slave address
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        close(file);
        return 1;
    }

    // 3. Recommended way: Use SMBus functions to read data safely
    __s32 res = i2c_smbus_read_byte_data(file, 0x00); // Read from register 0x00
    if (res < 0) {
        perror("Read failed");
    } else {
        printf("Data read: 0x%02X\n", res);
    }

    close(file);
    return 0;
}

```

reference:
 - accessing i2c devices from user-space: https://www.kernel.org/doc/Documentation/i2c/dev-interface
 - accessing i2c from user-space: https://emlogic.no/2025/06/accessing-i2c-devices-from-userspace-in-linux/

Other example: 

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_DEVICE      "/dev/i2c-0"
#define I2C_ADDR        0x53    // Device address
#define REG_POWER_CTL   0x2D    // Power control register
#define REG_DATA_START  0x32    // Data register start

int main(void) {
    int file;
    uint8_t buf[2];
    uint8_t data[6];
    int16_t x, y, z;

    // Open I2C device
    if ((file = open(I2C_DEVICE, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        exit(EXIT_FAILURE);
    }

    // Specify the address of the I2C Device to communicate with
    if (ioctl(file, I2C_SLAVE, I2C_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to device");
        close(file);
        exit(EXIT_FAILURE);
    }

    // Wake up the device: write 0x08 to POWER_CTL register
    buf[0] = REG_POWER_CTL;
    buf[1] = 0x08;
    if (write(file, buf, 2) != 2) {
        perror("Failed to write to the power control register");
        close(file);
        exit(EXIT_FAILURE);
    }

    printf("Reading 6 bytes from register 0x%02X...\n", REG_DATA_START);
    // Set register pointer to data start
    buf[0] = REG_DATA_START;
    if (write(file, buf, 1) != 1) {
        perror("Failed to set data register pointer");
        break;
    }

    // Read 6 bytes of data (X, Y, Z)
    if (read(file, data, 6) != 6) {
        perror("Failed to read data from device");
        break;
    }

    // Convert little-endian bytes to signed 16-bit values
    x = (int16_t)((data[1] << 8) | data[0]);
    y = (int16_t)((data[3] << 8) | data[2]);
    z = (int16_t)((data[5] << 8) | data[4]);
    // Print the raw values
    printf("X: %6d, Y: %6d, Z: %6d\n", x, y, z);
    close(file);
    return 0;
}
```

??? The recommended way to read I2C devices from user space in Linux is by interacting with the standard i2c-dev character device interface (located at `/dev/i2c-X`). While writing a dedicated kernel driver is ideal for production systems, i2c-dev is the official, universal standard for user-space development. Read/write directly to `/dev/i2c-1` using `open()` + `write()` libc functions, so you write directly to `/dev/i2c-1` as if it were a normal file.

### Using libiio

The Industrial I/O (IIO) subsystem in Linux provides two completely different ways to read sensor data depending on your performance needs.

#### 1. The Attribute Method (No Buffer Needed)
The code uses standard Linux sysfs attributes (iio_channel_attr_read_longlong).
 - How it works: Every time your code calls this function, the operating system directly queries the sensor driver, reads a single data point, and hands it back to your program as a string conversion.
 - Best for: Low-speed applications (under ~100 Hz) such as reading environmental sensors (temperature, pressure, gas levels, or battery voltages).
 - Pros: Extremely simple code; no buffer setup or cleanup required.

#### 2. The Buffer Method (Required for High-Speed Streams)
You must create a reading buffer if you are capturing high-speed continuous data stream packets (like audio, RF, or fast 3-axis accelerometer profiles).
 - How it works: The hardware or driver pushes data continuously into a kernel-level Ring Buffer. Your C program then pulls chunks of data out of this buffer using an iio_buffer struct.
 - Best for: High-speed data (over 100 Hz up to MHz) like accelerometers, gyroscopes, IMUs, and ADCs.

### Example with libiio Attribute method

```C

// Install libiio: https://analogdevicesinc.github.io/libiio/main/install/#linux
// $ sudo apt-get update
// $ sudo apt-get install libiio0 libiio-utils
// to use it in c/cc++ applications also install the developer package
// $ sudo apt-get install libiio-dev

/*
When you install libiio on a Raspberry Pi Zero 2 W (running Raspberry Pi OS), the files go to standard Linux system directories depending on how you install them.
APT Package Installation (sudo apt install libiio-dev / libiio0)
If you install via the package manager, the files are placed in standard system paths:
• C Shared Libraries (.so files): /usr/lib/arm-linux-gnueabihf/ (or /lib/arm-linux-gnueabihf/)
• Header Files (.h files): /usr/include/
• Binaries/Utilities (iio_info, etc.): /usr/bin/
• Config/Pkg-config files: /usr/lib/arm-linux-gnueabihf/pkgconfig/
*/

// compile with: gcc my_libiio.c -o progiio -liio

// reference libiio: https://analogdevicesinc.github.io/libiio/main/
// reference iio kernel subsystem: https://www.kernel.org/doc/html/latest/driver-api/iio/index.html
// libiio examples: https://docs.kernel.org/iio/iio_tools.html
// local backend: https://wiki.analog.com/resources/tools-software/linux-software/libiio_internals#the_local_backend

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <iio.h>

static bool keep_running = true;

void signal_handler(int sig) {
    keep_running = false;
}

int main(void) {
    struct iio_context *ctx = NULL;
    struct iio_device *dev = NULL;
    struct iio_channel *ax = NULL, *ay = NULL, *az = NULL;
    
    double ax_scale = 1.0, ay_scale = 1.0, az_scale = 1.0;
    char scale_str[64];

    signal(SIGINT, signal_handler);

    // 1. Create context and find your explicit mpu6050 device
    ctx = iio_create_default_context();
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create IIO context.\n");
        return -1;
    }

    dev = iio_context_find_device(ctx, "mpu6050");
    if (!dev) {
        fprintf(stderr, "Error: MPU6050 hardware instance not found.\n");
        iio_context_destroy(ctx);
        return -1;
    }

    // 2. Identify the Axis Channels
    ax = iio_device_find_channel(dev, "accel_x", false);
    ay = iio_device_find_channel(dev, "accel_y", false);
    az = iio_device_find_channel(dev, "accel_z", false);

    if (!ax || !ay || !az) {
        fprintf(stderr, "Error: Could not locate accelerometer channels.\n");
        iio_context_destroy(ctx);
        return -1;
    }

    // 3. Read Scale Factors directly from your hardware
    if (iio_channel_attr_read(ax, "scale", scale_str, sizeof(scale_str)) > 0) ax_scale = strtod(scale_str, NULL);
    if (iio_channel_attr_read(ay, "scale", scale_str, sizeof(scale_str)) > 0) ay_scale = strtod(scale_str, NULL);
    if (iio_channel_attr_read(az, "scale", scale_str, sizeof(scale_str)) > 0) az_scale = strtod(scale_str, NULL);

    printf("Single-Shot Polling Active (No Interrupt Wire Required). Press Ctrl+C to exit.\n");

    // 4. Polling Loop
    while (keep_running) {
        long long raw_x = 0, raw_y = 0, raw_z = 0;

        // Directly read raw attributes
        int r_x = iio_channel_attr_read_longlong(ax, "raw", &raw_x);
        int r_y = iio_channel_attr_read_longlong(ay, "raw", &raw_y);
        int r_z = iio_channel_attr_read_longlong(az, "raw", &raw_z);

        if (r_x >= 0 && r_y >= 0 && r_z >= 0) {
            // Apply scale rules to find physical values (m/s²)
            double phys_x = (double)raw_x * ax_scale;
            double phys_y = (double)raw_y * ay_scale;
            double phys_z = (double)raw_z * az_scale;

            printf("Accel (m/s²) -> X: %8.4f | Y: %8.4f | Z: %8.4f\n", phys_x, phys_y, phys_z);
            fflush(stdout);
        } else {
            fprintf(stderr, "Failed to read sensor attributes.\n");
        }

        // Sleep for 20000 microseconds (20ms) to loop at roughly 50 Hz
        // usleep(20000);
        // use 10 Hz for easiest visualization
        usleep(100000);
    }

    printf("\nExiting cleanly...\n");
    iio_context_destroy(ctx);
    return 0;
}

```


## Program without libiio

Next is a sample program without libiio. 

Take into account, you need the interruptions of the mpu6050 enabled. to check its interrupts: 

```shell
watch -n 1 "cat /proc/interrupts | grep -i mpu"
```

for example: 

```shell
cat /proc/interrupts | grep -i mpu                                                                                                                                   rpihole: Sun Oct 18 01:37:09 2026

199:      47405      47346      46968      47312  pinctrl-bcm2835   4 Edge      inv_mpu
200:          0          0          0     189031  mpu6050-dev0     Edge      mpu6050_consumer0
```

• Line 199 (inv_mpu): This is the low-level hardware interrupt linked to physical GPIO 4 (pinctrl-bcm2835 4 Edge). The counts across all four CPU cores (47405, 47346, etc.) show that the physical INT pin on your MPU6050 is firing rapidly, and the Pi's GPIO controller is successfully catching every single pulse.

• Line 200 (mpu6050_consumer0): This is a threaded software interrupt managed by the Linux Industrial I/O (IIO) subsystem. It has registered a staggering 189,031 events on the 4th CPU core. This proves that the Linux driver is waking up a specific software worker thread every time the hardware interrupt fires to pull data from the MPU6050.



Also the commands, for the comfiguration of the mpu6050: 

```shell
cd /sys/bus/iio/devices/iio:device0

# Set the trigger to use the MPU6050's hardware interrupt pin
echo "mpu6050-dev0" > trigger/current_trigger

# Enable all acceleration channels
echo 1 > scan_elements/in_accel_x_en
echo 1 > scan_elements/in_accel_y_en
echo 1 > scan_elements/in_accel_z_en

# Enable all gyroscope channels
echo 1 > scan_elements/in_anglvel_x_en
echo 1 > scan_elements/in_anglvel_y_en
echo 1 > scan_elements/in_anglvel_z_en

# Enable the buffer
echo 100 > buffer/length
echo 1 > buffer/enable
```

Although this configuration can be done also in the program. 

At this point after the previous configuration you should be able to read the sensor data, for example with: `cat /dev/iio:device0 | hexdump -v`. 

<details>
  <summary>ANTIPATTERN!!! -> The program with timers </summary>
  
```c
// compiles with: gcc readmpu.c -o readmpu -O -Wall -lm
// -lm is for #include <math.h>
// THIS EXAMPLE IS NOT THE BEST OPTION, SEE AFTER THE SNIPPET

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>   
#include <sys/stat.h>
#include <string.h>
#include <math.h>

#define IIO_DEVICE_DIR     "/sys/bus/iio/devices/iio:device0/"
#define IIO_DEV_PATH       "/dev/iio:device0"
#define SCALE_ACCEL_PATH   IIO_DEVICE_DIR "in_accel_scale"
#define SCALE_GYRO_PATH    IIO_DEVICE_DIR "in_anglvel_scale"
#define DEVICE_NAME_PATH   IIO_DEVICE_DIR "name"

#define MAX_BUFFER_SIZE 32

// Math constant multipliers
#define RAD_TO_DEG (180.0 / 3.14159265358979323846)

// Global runtime variables
volatile bool keep_running = true;        
volatile bool timer_triggered = false;    
int fd = -1;
ssize_t expected_packet_size = 0;
double accel_scale = 1.0, gyro_scale = 1.0;
uint64_t loop_counter = 0;
struct timespec start_time, current_time;

void sigint_handler(int sig) {
    keep_running = false;
}

void timer_handler(int sig, siginfo_t *si, void *uc) {
    timer_triggered = true;
}

int write_sysfs(const char *relative_path, const char *value) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", IIO_DEVICE_DIR, relative_path);
    
    FILE *fp = fopen(full_path, "w");
    if (!fp) {
        fprintf(stderr, "Error: Failed to write to sysfs file: %s (Are you running with 'sudo'?)\n", full_path);
        return -1;
    }
    fprintf(fp, "%s", value);
    fclose(fp);
    return 0;
}

int verify_iio_dir_exists() {
    struct stat s;
    if (stat(IIO_DEVICE_DIR, &s) != 0) {
        if (errno == ENOENT) {
            fprintf(stderr, "Error: IIO directory '%s' does not exist.\n", IIO_DEVICE_DIR);
        } else {
            perror("Error calling stat() on IIO directory");
        }
        return 0;
    }
    return S_ISDIR(s.st_mode);
}

int verify_device_name() {
    char name_buffer[64];
    FILE *fp = fopen(DEVICE_NAME_PATH, "r");
    
    if (!fp) {
        perror("Error opening device name verification node");
        return 0;
    }

    if (fgets(name_buffer, sizeof(name_buffer), fp) == NULL) {
        fprintf(stderr, "Error: Could not read contents from %s\n", DEVICE_NAME_PATH);
        fclose(fp);
        return 0;
    }
    fclose(fp);

    name_buffer[strcspn(name_buffer, "\r\n")] = '\0';

    if (strncmp(name_buffer, "mpu6050", 7) != 0) {
        fprintf(stderr, "Error: Device mismatch! Expected 'mpu6050' but found '%s'\n", name_buffer);
        return 0;
    }

    fprintf(stderr, "Device identity verified: %s\n", name_buffer);
    return 1;
}

int initialize_iio_sensors() {
    if (!verify_iio_dir_exists()) return -1;
    if (!verify_device_name()) return -1;

    fprintf(stderr, "Initializing MPU6050 subsystem parameters...\n");
    if (write_sysfs("buffer/enable", "0") < 0) return -1;
    if (write_sysfs("trigger/current_trigger", "mpu6050-dev0") < 0) return -1;

    write_sysfs("scan_elements/in_accel_x_en", "1");
    write_sysfs("scan_elements/in_accel_y_en", "1");
    write_sysfs("scan_elements/in_accel_z_en", "1");
    write_sysfs("scan_elements/in_anglvel_x_en", "1");
    write_sysfs("scan_elements/in_anglvel_y_en", "1");
    write_sysfs("scan_elements/in_anglvel_z_en", "1");
    write_sysfs("scan_elements/in_timestamp_en", "1");
    write_sysfs("buffer/length", "2048");

    if (write_sysfs("buffer/enable", "1") < 0) return -1;

    fprintf(stderr, "Subsystem configuration applied successfully.\n\n");
    return 0;
}

/*=========================================================================
 * DYNAMIC PACKET SIZE DETECTION
 * =========================================================================
 * The Linux IIO subsystem does not guarantee a fixed struct size. The total
 * bytes per frame changes depending on enabled channels and how the specific 
 * kernel architecture applies padding alignment (e.g., matching CPU cache lines). 
 * 
 * Instead of hardcoding a size (like 12 or 20 bytes), we perform a non-blocking 
 * read of a single data sample block at startup to see its exact length. This:
 *   1. Prevents byte-shifting (keeps Axis data from bleeding into wrong variables).
 *   2. Ensures driver portability across different kernel versions (e.g. 32-byte alignment).
 *   3. Automatically adjusts if you change enabled channels in initialize_iio_sensors().
 * =========================================================================
 */
ssize_t detect_packet_size(int device_fd) {
    uint8_t rx_raw[MAX_BUFFER_SIZE];
    ssize_t size = 0;
    int attempts = 0;

    fprintf(stderr, "Detecting packet size... ");
    while (size <= 0 && attempts < 100) {
        size = read(device_fd, rx_raw, MAX_BUFFER_SIZE);
        if (size < 0 && errno != EAGAIN) {
            perror("Fatal error during channel detection");
            return -1;
        }
        usleep(5000);
        attempts++;
    }
    
    if (size <= 0) {
        size = 32;
        fprintf(stderr, "Size: default to %zd bytes\n", size);
    } else {
        fprintf(stderr, "Size: %zd bytes\n", size);
    }
    return size;
}

double get_sysfs_scale(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) return 1.0;
    double scale = 1.0;
    if (fscanf(fp, "%lf", &scale) != 1) scale = 1.0;
    fclose(fp);
    return scale;
}

int main() {
    uint8_t rx_raw[MAX_BUFFER_SIZE];
    uint8_t latest_raw[MAX_BUFFER_SIZE];
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;

    setvbuf(stdout, NULL, _IOLBF, 0);

    signal(SIGINT, sigint_handler);

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Fatal: Failed to register timer action context");
        return EXIT_FAILURE;
    }

    if (initialize_iio_sensors() < 0) return EXIT_FAILURE;

    accel_scale = get_sysfs_scale(SCALE_ACCEL_PATH);
    gyro_scale = get_sysfs_scale(SCALE_GYRO_PATH);
    fprintf(stderr, "Loaded Scales -> Accel: %f, Gyro: %f\n", accel_scale, gyro_scale);

    fd = open(IIO_DEV_PATH, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Error opening IIO stream");
        return EXIT_FAILURE;
    }

    expected_packet_size = detect_packet_size(fd);
    if (expected_packet_size < 0) {
        close(fd);
        return EXIT_FAILURE;
    }

    // Clear display and hide blinking layout cursor
	printf("Press Ctrl+C to end the program\r\n\n");
    printf("\033[2J\033[H\033[?25l");
    printf("=============================================================================================================\n");
    printf("                                  MPU6050 ORIENTATION TILT INSTRUMENT DASHBOARD                              \n");
    printf("=============================================================================================================\n");
    
    printf("\033[s"); // Save static layout coordinate position

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) == -1) {
        perror("Fatal: Failed to build hardware interval timer object");
        close(fd);
        return EXIT_FAILURE;
    }

    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 20000000;    
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 20000000; 
    
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("Fatal: Failed to arm periodic timer queue parameters");
        close(fd);
        return EXIT_FAILURE;
    }

    while (keep_running) {
        pause();

        if (timer_triggered && keep_running) {
            timer_triggered = false; 
            ssize_t bytes_read;
            bool fresh_data_found = false;

            while ((bytes_read = read(fd, rx_raw, expected_packet_size)) == expected_packet_size) {
                for (int i = 0; i < expected_packet_size; i++) {
                    latest_raw[i] = rx_raw[i];
                }
                fresh_data_found = true;
            }

            if (bytes_read < 0 && errno != EAGAIN) {
                if (errno == EINTR) continue; 
                perror("Fatal error reading hardware stream");
                break;
            }

            if (fresh_data_found) {
                loop_counter++;

                clock_gettime(CLOCK_MONOTONIC, &current_time);
                double elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000.0 + 
                                    (current_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

                int16_t raw_ax = (int16_t)((latest_raw[0] << 8) | latest_raw[1]);
                int16_t raw_ay = (int16_t)((latest_raw[2] << 8) | latest_raw[3]);
                int16_t raw_az = (int16_t)((latest_raw[4] << 8) | latest_raw[5]);
                int16_t raw_gx = (int16_t)((latest_raw[6] << 8) | latest_raw[7]);
                int16_t raw_gy = (int16_t)((latest_raw[8] << 8) | latest_raw[9]);
                int16_t raw_gz = (int16_t)((latest_raw[10] << 8) | latest_raw[11]);

                // Apply scales to acquire real physical values
                double ax = raw_ax * accel_scale;
                double ay = raw_ay * accel_scale;
                double az = raw_az * accel_scale;

                // MATHEMATICAL ORIENTATION CONVERSION: Compute Pitch and Roll in Degrees
                double roll  = atan2(ay, az) * RAD_TO_DEG;
                double pitch = atan2(-ax, sqrt(ay * ay + az * az)) * RAD_TO_DEG;

                // ANSI Code: Return cursor to template base row
                printf("\033[u");
                printf("  Sequence Frame: #%06llu   |   Telemetry Run Time: %.2f ms\n", (unsigned long long)loop_counter, elapsed_ms);
                printf("-------------------------------------------------------------------------------------------------------------\n");
                printf("  ACCELEROMETER (m/s²)  =>  X: %6.2f   Y: %6.2f   Z: %6.2f\n", ax, ay, az);
                printf("  GYROSCOPE (rad/s)     =>  X: %6.2f   Y: %6.2f   Z: %6.2f\n", 
                       raw_gx * gyro_scale, raw_gy * gyro_scale, raw_gz * gyro_scale);
                printf("-------------------------------------------------------------------------------------------------------------\n");
                // New orientation block section
                printf("  ORIENTATION CALCULATED ROTATIONS (Degrees):\n");
                printf("    ► ROLL  (Rotation around X-axis): %7.2f°\n", roll);
                printf("    ► PITCH (Rotation around Y-axis): %7.2f°\n", pitch);
                printf("-------------------------------------------------------------------------------------------------------------\n");
            }
        }
    }

    // Cleanup routines
    timer_delete(timerid);
    if(fd > 0) close(fd);
    write_sysfs("buffer/enable", "0");
	// ANSI Code: Show the terminal cursor back upon exit
    printf("\033[?25h\n");
    fprintf(stderr, "\nClosing data stream cleanly. Goodbye!\n");
    return EXIT_SUCCESS;
}
```
</details>

If instead of timers we favor a program running with epoll, then: 

```C
// compiles with: gcc readmpu.c -o readmpu -O -Wall -lm
// -lm is for #include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>   
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <poll.h>       // Polling system structure
#include <inttypes.h>   // For correct uint64_t formatting macros

#define IIO_DEVICE_DIR     "/sys/bus/iio/devices/iio:device0/"
#define IIO_DEV_PATH       "/dev/iio:device0"
#define SCALE_ACCEL_PATH   IIO_DEVICE_DIR "in_accel_scale"
#define SCALE_GYRO_PATH    IIO_DEVICE_DIR "in_anglvel_scale"
#define DEVICE_NAME_PATH   IIO_DEVICE_DIR "name"

#define MAX_BUFFER_SIZE 32

// Math constant multipliers
#define RAD_TO_DEG (180.0 / 3.14159265358979323846)

// Global runtime variables
volatile bool keep_running = true;        
int fd = -1;
ssize_t expected_packet_size = 0;
double accel_scale = 1.0, gyro_scale = 1.0;
uint64_t loop_counter = 0;

void sigint_handler(int sig) {
    keep_running = false;
}

int write_sysfs(const char *relative_path, const char *value) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", IIO_DEVICE_DIR, relative_path);
    
    FILE *fp = fopen(full_path, "w");
    if (!fp) {
        fprintf(stderr, "Error: Failed to write to sysfs file: %s (Are you running with 'sudo'?)\n", full_path);
        return -1;
    }
    fprintf(fp, "%s", value);
    fclose(fp);
    return 0;
}

int verify_iio_dir_exists() {
    struct stat s;
    if (stat(IIO_DEVICE_DIR, &s) != 0) {
        if (errno == ENOENT) {
            fprintf(stderr, "Error: IIO directory '%s' does not exist.\n", IIO_DEVICE_DIR);
        } else {
            perror("Error calling stat() on IIO directory");
        }
        return 0;
    }
    return S_ISDIR(s.st_mode);
}

int verify_device_name() {
    char name_buffer[64];
    FILE *fp = fopen(DEVICE_NAME_PATH, "r");
    
    if (!fp) {
        perror("Error opening device name verification node");
        return 0;
    }

    if (fgets(name_buffer, sizeof(name_buffer), fp) == NULL) {
        fprintf(stderr, "Error: Could not read contents from %s\n", DEVICE_NAME_PATH);
        fclose(fp);
        return 0;
    }
    fclose(fp);

    name_buffer[strcspn(name_buffer, "\r\n")] = '\0';

    if (strncmp(name_buffer, "mpu6050", 7) != 0) {
        fprintf(stderr, "Error: Device mismatch! Expected 'mpu6050' but found '%s'\n", name_buffer);
        return 0;
    }

    fprintf(stderr, "Device identity verified: %s\n", name_buffer);
    return 1;
}

int initialize_iio_sensors() {
    if (!verify_iio_dir_exists()) return -1;
    if (!verify_device_name()) return -1;

    fprintf(stderr, "Initializing MPU6050 subsystem parameters...\n");
    write_sysfs("buffer/enable", "0");
    
    // Watermark 1 gives immediate wakeups for real-time sample processing
    write_sysfs("buffer/watermark", "1");

	// sampling frequency 50 Hz
    write_sysfs("sampling_frequency", "50")

    write_sysfs("scan_elements/in_accel_x_en", "1");
    write_sysfs("scan_elements/in_accel_y_en", "1");
    write_sysfs("scan_elements/in_accel_z_en", "1");
    write_sysfs("scan_elements/in_anglvel_x_en", "1");
    write_sysfs("scan_elements/in_anglvel_y_en", "1");
    write_sysfs("scan_elements/in_anglvel_z_en", "1");
    write_sysfs("scan_elements/in_timestamp_en", "1");
    write_sysfs("buffer/length", "2048");

    if (write_sysfs("buffer/enable", "1") < 0) return -1;

    fprintf(stderr, "Subsystem configuration applied successfully.\n\n");
    return 0;
}

double get_sysfs_scale(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) return 1.0;
    double scale = 1.0;
    if (fscanf(fp, "%lf", &scale) != 1) scale = 1.0;
    fclose(fp);
    return scale;
}

int main() {
    uint8_t rx_raw[MAX_BUFFER_SIZE];
    uint8_t latest_raw[MAX_BUFFER_SIZE];
    struct pollfd pfd;

    // Time Tracking Context Variables
    uint64_t initial_timestamp = 0;
    bool is_first_timestamp = true;
    uint64_t last_sensor_ts = 0;
    
    // Frequency variables
    double sensor_freq = 0.0;
    double ui_freq = 0.0;
    
    struct timespec last_ui_time, current_ui_time;
    clock_gettime(CLOCK_MONOTONIC, &last_ui_time);

    setvbuf(stdout, NULL, _IOLBF, 0);
    signal(SIGINT, sigint_handler);

    if (initialize_iio_sensors() < 0) return EXIT_FAILURE;

    accel_scale = get_sysfs_scale(SCALE_ACCEL_PATH);
    gyro_scale = get_sysfs_scale(SCALE_GYRO_PATH);
    fprintf(stderr, "Loaded Scales -> Accel: %f, Gyro: %f\n", accel_scale, gyro_scale);

    fd = open(IIO_DEV_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Error opening IIO stream");
        return EXIT_FAILURE;
    }

    pfd.fd = fd;
    pfd.events = POLLIN;

    printf("Press Ctrl+C to end the program\r\n\n");
    printf("\033[2J\033[H\033[?25l");
    printf("=============================================================================================================\n");
    printf("                                  MPU6050 ORIENTATION TILT INSTRUMENT DASHBOARD                              \n");
    printf("=============================================================================================================\n");
    
    printf("\033[s"); 

    while (keep_running) {
        int ret = poll(&pfd, 1, 1000);
        
        if (ret < 0) {
            if (errno == EINTR) continue; 
            perror("Poll system error");
            break;
        }
        
        if (ret == 0) {
            printf("\033[u  [SYSTEM STATUS]  Waiting for sensor hardware interrupts...\n");
            continue;
        }

        if (pfd.revents & POLLIN) {
            ssize_t bytes_read = read(fd, rx_raw, MAX_BUFFER_SIZE);
            
            if (bytes_read >= 16) {
                for (int i = 0; i < bytes_read; i++) {
                    latest_raw[i] = rx_raw[i];
                }
                expected_packet_size = bytes_read;
                loop_counter++;

                // 1. Extract 16-bit Big-Endian sensor channels
                int16_t raw_ax = (int16_t)((latest_raw[0] << 8) | latest_raw[1]);
                int16_t raw_ay = (int16_t)((latest_raw[2] << 8) | latest_raw[3]);
                int16_t raw_az = (int16_t)((latest_raw[4] << 8) | latest_raw[5]);
                int16_t raw_gx = (int16_t)((latest_raw[6] << 8) | latest_raw[7]);
                int16_t raw_gy = (int16_t)((latest_raw[8] << 8) | latest_raw[9]);
                int16_t raw_gz = (int16_t)((latest_raw[10] << 8) | latest_raw[11]);

                // 2. Extract 64-bit kernel timestamp based on architectural alignment
                uint64_t ts_raw = 0;
                if (expected_packet_size == 20) {
                    memcpy(&ts_raw, &latest_raw[12], sizeof(uint64_t));
                } else if (expected_packet_size >= 24) {
                    memcpy(&ts_raw, &latest_raw[16], sizeof(uint64_t));
                } else {
                    memcpy(&ts_raw, &latest_raw[expected_packet_size - 8], sizeof(uint64_t));
                }

                // Initialize reference baseline clock at program start
                if (is_first_timestamp) {
                    initial_timestamp = ts_raw;
                    last_sensor_ts = ts_raw;
                    is_first_timestamp = false;
                }

                // Compute relative time elapsed from start (in seconds)
                double relative_secs = (double)(ts_raw - initial_timestamp) / 1000000000.0;

                // A. Compute Sensor Sampling Frequency (from hardware timestamp delta)
                if (ts_raw > last_sensor_ts) {
                    uint64_t ts_delta = ts_raw - last_sensor_ts;
                    sensor_freq = 1000000000.0 / (double)ts_delta;
                }
                last_sensor_ts = ts_raw;

                // B. Compute Console UI Loop Refresh Frequency
                clock_gettime(CLOCK_MONOTONIC, &current_ui_time);
                double ui_delta_sec = (current_ui_time.tv_sec - last_ui_time.tv_sec) + 
                                      (current_ui_time.tv_nsec - last_ui_time.tv_nsec) / 1e9;
                if (ui_delta_sec > 0.0) {
                    ui_freq = 1.0 / ui_delta_sec;
                }
                last_ui_time = current_ui_time;

                // Process engineering unit variants
                double ax = raw_ax * accel_scale;
                double ay = raw_ay * accel_scale;
                double az = raw_az * accel_scale;
                double gx = raw_gx * gyro_scale;
                double gy = raw_gy * gyro_scale;
                double gz = raw_gz * gyro_scale;

                double pitch = atan2(-ax, sqrt(ay*ay + az*az)) * RAD_TO_DEG;
                double roll  = atan2(ay, az) * RAD_TO_DEG;

                // Render expanded layout metrics
                printf("\033[u"); 
                printf("  [SYSTEM STATUS]  Loops Sampled: %-10" PRIu64 " | Frame Bytes: %-2zd\n", loop_counter, expected_packet_size);
                printf("  [KERNEL TIME]    Timestamp (ns): %-20" PRIu64 " | Elapsed Secs: %10.4f s\n", ts_raw, relative_secs);
                printf("  [DIAGNOSTICS]    Sensor Freq: %7.2f Hz         | Console UI Freq: %7.2f Hz\n", sensor_freq, ui_freq);
                printf("-------------------------------------------------------------------------------------------------------------\n");
                printf("  ACCELEROMETER (m/s²)                 GYROSCOPE (rad/s)                    CALCULATED TILT ANGLE            \n");
                printf("  X-Axis: %7.3f                        X-Axis: %7.4f                        Pitch Angle: %7.2f°             \n", ax, gx, pitch);
                printf("  Y-Axis: %7.3f                        Y-Axis: %7.4f                        Roll Angle:  %7.2f°             \n", ay, gy, roll);
                printf("  Z-Axis: %7.3f                        Z-Axis: %7.4f                                                         \n", az, gz);
                printf("=============================================================================================================\n");
			}
		}
	}

printf("\033[?25h\n\nStopping instrumentation framework...\n");
close(fd);
write_sysfs("buffer/enable", "0");
return EXIT_SUCCESS;
}
```

The epoll (or standard poll) option is by far the better and more professional choice for reading sensor data.
In embedded Linux and systems programming, using a timer to read a streaming device buffer like an IIO sensor is considered an anti-pattern.
Here is a direct comparison of why hardware-driven polling beats software timers:

Feature	epoll / poll (Hardware-Driven)	POSIX Timer / Loop Sleep (Software-Driven)
Accuracy	Perfect. Wakes up precisely when the sensor hardware finishes a measurement.	Poor. Software clocks always drift, causing missed samples or duplicates.
CPU Usage	Very Low. Your thread sleeps completely until the hardware wakes it up.	Higher. Constant timer interrupts and thread switching even if data isn't ready.
Data Integrity	No Duplicates. You read data exactly once per hardware sample.	High Risk. If your timer ticks faster than the sensor, you read duplicate data.
Latency	Minimal. The moment data enters the kernel, your program is unblocked.	Variable. You can wait up to the length of your timer period to get the data.


## The Deep Technical Reason: System Clock vs. Sensor Crystal

Every physical chip (like the MPU6050) has its own internal clock oscillator. Your Linux computer (like a Raspberry Pi) also has its own CPU clock. These two clocks are never perfectly synced.
• If you use a 50Hz Timer: Your software wakes up exactly every 20ms. However, if the MPU6050 is running slightly fast (e.g., 50.1Hz), it creates data every 19.96ms. Over time, the sensor buffer will slowly overflow because you aren't reading fast enough. If the sensor runs slightly slow (49.9Hz), your timer will eventually wake up before a new sample is ready, causing your code to read a duplicate stale value or crash into an empty buffer state.
• If you use epoll: Your code matches the heartbeat of the sensor itself. When the MPU6050 finishes a calculation, it fires a physical interrupt line to the Linux CPU. The Linux kernel reads it immediately and unblocks your epoll() loop. Your software adapts perfectly, even if the sensor frequency slightly drifts due to room temperature changes.

When would you use a timer?

The only time a timer option is acceptable is if you are dealing with a primitive sensor that lacks an internal data buffer (FIFO) or a data-ready interrupt pin, and you are forced to manual-poll it by sending I2C read requests at regular intervals. For a modern device like the MPU6050, epoll is the standard.
.


