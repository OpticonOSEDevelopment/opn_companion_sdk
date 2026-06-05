# OPN Companion Application SDK (for OPN-2xxx/PX-20/RS-3000 and OPN-6000)
This is the official SDK from Opticon Sensors Europe BV for the Companion Scanners to create and customize Linux, Windows and web applications and more 

The prerequisites for using this SDK are:
- `Latest SDK files` from this repository
- `Visual Studio 2017 or newer` (for building the Windows applications)
- `Xcode` (for building the OS X applications)
- `Appload` firmware upload application for Windows [Appload](https://www.opticon.com/support/Appload/Appload%20Setup.exe)
- `Opticon USB Drivers` can download from here: [USB Drivers Installer](https://www.opticon.com/support/Drivers/USB%20Drivers%20Installer.exe)

# Getting started

- Download and extract this complete repository into a working folder
- Download and install the latest Opticon USB drivers
- Download and install the latest Appload version 

# SDK Files

This SDK contains the following components:

## /Firmware
Latest OPN-2001 compatible firmware files for the OPN Companion

See `/Documents/How to load Firmware.pdf` for more information on how to load the firmware files on Opticon Companion scanners

- `OPN2001` -> OPN2001_RBBV021x.hex
- `OPN2002` -> RBFV02xx_RFF3510x.hex
- `OPN2003` -> RBGV02xx_RFG3510x.hex
- `OPN2004` -> PN2004_RBIV00xx_RFI3727x.hex
- `OPN2005` -> OPN2005_RBLV00xx_RFI3727Qx.hex
- `OPN2006` -> OPN2006_RBNV00xx_RFI3727x.hex
- `OPN2500` -> OPN2500_FANV00xx_FBNV0xxx_FFN4076x.bin
- `OPN6000` -> OPN6000_FAMV00xx_FBMV0xxx_FFM4076x.bin
- `PX20` -> PX20_RBMV00xx_RFM3727x.hex
- `RS3000` -> RS3000_RBZV00xx_RFM3727x.hex

## /API

### /WebSerial
- `index.html` -> Communicate with OPN Companion scanners using Google Chrome web serial api

### /dotNET
#### /x64		
- `Csp2Ex.dll`	-> CSP2-dll for 64-bit applications
- `Opticon.csp2Ex.net.dll`-> .NET wrapper for 64-bit applications
- `Opticon.csp2Ex.net.XML`
#### /x86 
- `Csp2.dll`-> CSP2-dll for 32-bit applications
- `Opticon.csp2.net.dll` -> .NET wrapper for 32-bit applications
- `Opticon.csp2.net.xml`

### /OS X
- `Instructions.pdf`
- `license.txt`
- `OPN.framework/`	-> framework for Xcode projects

### /Windows
- `CSp2.h`

#### /DLL
- `debug/Csp2.dll`
- `release/Csp2.dll`
- `x64/debug/Csp2Ex.dll`
- `x64/release/Csp2Ex.dll`

#### /LIB
- `coff\csp2.lib`
- `coff\Csp2Ex.lib`

## /Applications
- `OPN2001 .NET Demo`
- `OPN2001 ActiveX Demo`
- `OPN2001 MauiDemo`
- `OPN2001 OS X Demo`
- `OPN2001 Standard Demo`

## /Documents
- `OPN-2001 Datasheet.pdf`
- `OPN-2001 Device Parameters.pdf`
- `OPN-2001 Specification Manual v33301.pdf`
- `OPN-2001 User Manual.pdf`
- `How to load Firmware.pdf`
- `Windows API/` -> Manual for the Windows API
- `OS X API/` -> HTML Help for the OS X API

### /USB Driver
- `USB Drivers Installer.exe` USB Installer for all Opticon Companion scanners
