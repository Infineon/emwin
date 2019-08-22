# SEGGER emWin Graphics Library 5.48.1
 
### What's Included?

For a complete description of the emWin Middleware, refer to [README.md](./README.md) and
[API Reference Guide](https://cypresssemiconductorco.github.io/emwin/emwin_overview/html/index.html).
The revision history of the emWin Middleware is available
at [API Reference Guide Changelog](https://cypresssemiconductorco.github.io/emwin/emwin_overview/html/index.html#group_emwin_changelog).
New in this release:
* Implemented the ModusToolbox flow support.
* Added emWin PC Tools to support the emWin GUI development.
* Updated the documentation.

### Known Issues
<table>
    <tr>
        <th>Problem</th>
        <th>Workaround</th>
    </tr>
    <tr>
        <td>
            emWin operates incorrectly with a floating point when a project
            is compiled with IAR or ARM Compiler 6 within MbedOS. <br>
            This is caused by the inconsistent floating-point ABI selection
            between toolchains in MbedOS: <br>
            https://github.com/ARMmbed/mbed-os/issues/9153
        </td>
        <td>
            To avoid the incorrect operation, use one of the following workarounds: <br>
            1. Use the GCC toolchain for MbedOS emWin projects. <br>
            2. Manually replace the emWin softfp library with its hardfp version.
               For example, for NOSNTS emWin core variant and IAR toolchain, replace the library in 
               <br> GUI/COMPONENT_SOFTFP/COMPONENT_EMWIN_NOSNTS/TOOLCHAIN_IAR <br>
               with the library from
               <br> GUI/COMPONENT_HARDFP/COMPONENT_EMWIN_NOSNTS/TOOLCHAIN_IAR.
        </td>
    </tr>
</table>

### Defect Fixes
* Fixed linker error for ARM Compiler 6 hardfp libraries.

### Supported Software and Tools
This version of the emWin Middleware was validated for compatibility with the following Software and Tools:

| Software and Tools                                      | Version |
| :---                                                    | :----:  |
| ModusToolbox Software Environment                       | 2.0     |
| PSoC6 Peripheral Driver Library (PDL)                   | 1.2.0   |
| GCC Compiler                                            | 7.2.1   |
| IAR Compiler                                            | 8.32    |
| ARM Compiler 6                                          | 6.11    |
| MBED OS                                                 | 5.13.3  |
| FreeRTOS                                                | 10.0.1  |

### More information
The following resources contain more information:
* [emWin Middleware README.md](./README.md)
* [emWin Middleware API Reference Guide](https://cypresssemiconductorco.github.io/emwin/emwin_overview/html/index.html)
* [ModusToolbox Software Environment, Quick Start Guide, Documentation, and Videos](https://www.cypress.com/products/modustoolbox-software-environment)
* [emWin Middleware Code Example for MBED OS](https://github.com/cypresssemiconductorco)
* [emWin Middleware Code Examples at GITHUB](https://github.com/cypresssemiconductorco)
* [PSoC 6 Technical Reference Manuals](https://www.cypress.com/search/all?f%5B0%5D=meta_type%3Atechnical_documents&f%5B1%5D=resource_meta_type%3A583&f%5B2%5D=field_related_products%3A114026)
* [PSoC 6 Programmable System-on-Chip datasheets](https://www.cypress.com/search/all?f%5B0%5D=meta_type%3Atechnical_documents&f%5B1%5D=field_related_products%3A114026&f%5B2%5D=resource_meta_type%3A575)
* [Cypress Semiconductor](http://www.cypress.com)

---
© Cypress Semiconductor Corporation, 2019.
