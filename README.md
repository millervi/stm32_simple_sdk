# STM32 simple SDK

#### Project description:

This project demonstrates a minimal and sufficient set of tools for developing embedded software for STM32 microcontrollers.

The build system concept was influenced by the [esp-idf project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html), so if you use esp-idf in your developments, then such a thing as **component_registration** will be familiar to you, a simplified analogue of **idf_component_register** from esp-idf.

Use this demo project as a base for your development and expand its functionality as you please.

> NOTE - this SDK used scripts: **kconfig.py** and **menuconfig.py** from [Zephyr Project](https://github.com/zephyrproject-rtos/zephyr).

#### Concepts:

* **Project** is a directory containing all the files and configuration to create a single **executable application**.
* **Project configuration** is stored in a single **.config** file located in the project's root directory. This configuration file is modified by a project configuration setting. One project contains exactly one project configuration.
* **Application** is an executable file created by the build system. Within one project, one **project application** is created, the main executable file, i.e. your firmware.
* **Components** are modular pieces of **source code**, **embed files**, and **static libraries** that are compile into object files and linked into an application.
* **Target** is the hardware for which the application is being created.

#### Project dependencies:

```
Platform                Windows
Cmake                   version 3.19.0-rc1
GNU Make                version 3.82.90, built for i686-pc-mingw32
Arm GNU Toolchain       version 11.2-2022.02
Open On-Chip Debugger   version 0.10.0-2019-08-28
STM32 ST-LINK CLI       version 3.4.0.0
Doxygen                 version 1.9.4
Python                  version 3.7
VS Code                 version 1.68.1
```

#### Python requirements:

```
kconfiglib
windows-curses
```

#### VS Code extensions:

```
C/C++                   version 1.10.7
Cortex-Debug            version 1.5.1
CMake Language Support  version 0.0.4
Task Buttons            version 1.0.3
Serial Monitor          version 0.1.0
```

#### System variables:

* `OPEN_OCD_PATH` - path to openocd, using in **launch.json** for **STlink debug launch**.
* `GDB_PATH` - path to gdb, using in **launch.json** for **STlink debug launch**.
* `ST-LINK_CLI_PATH` - path to ST-LINK Utility, using in **tasks.json** for **Flash** and **Reset** mcu.

#### Example of create component:

* Create a folder of **your component** in the directory **components**.
* Add source files and **CMakeLists.txt** file to it.
* Register a component using the **component_registration** function.
* Include the component's header file in the listing where you want to use it.
* Build the project.

```
components
|___simple_component
    |___include
    |   |___simple_component.h
    |___sources
    |   |___simple_component.c
    |___CMakeLists.txt
```

Add to CMakeLists.txt:

```cmake
include(${CMAKE_SOURCE_DIR}/component.cmake)

component_registration(
    SOURCE_FILES
        components/simple_component/sources/simple_component.c
    INCLUDE_DIRECTORIES
        components/simple_component/include
)
```

> NOTE - more examples see in project.

#### Tasks:

* **Menu configuration** - Runing kconfig menu configuration.
* **Build** - build project.
* **Build and flash** - build project and flash firmware to mcu.
* **Flash** - flash firmware to mcu.
* **Reset** - reset mcu.
* **Make docs** - make doxygen docs.
* **Clean** - Cleaning the workplace from the build folder and folders with. documentation.

#### Customize for your target:

* Examine and reassign dependencies in **launch.json** to work with the **debugger**.
* Examine and reassign dependencies in **tasks.json** to work with the **STM32 ST-LINK CLI**.
* Examine and reassign dependencies in **project configuration menu** to work with **your target**.

#### Support С++:

The build system allows you to enable C++ support. Check out the **Settings of build** section in **project configuration menu**.