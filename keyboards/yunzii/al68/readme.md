Keyboard Maintainer: [Jacky](https://github.com/jackyjia73), [Enes](https://github.com/MEnesCakar), [Ryan](https://github.com/ElCyborg)

## Special Functions

1. For the knob turning functions you can use the following macros:
   layer 0 left turn= Macro 10
   layer 0 right turn= Macro 10
   layer 1 left clockwise turn= Macro 12
   layer 1 right clockwise turn= Macro 13

## Instructions

1. To compile qmk compile --clean -kb yunzii/al68 -km via (Use QMK MSYS))
2. To flash you need to go into bootloader mode (hold left ctrl + escape while plugging in) in wired mode. (Easier in QMK Toolbox))
3. You need to use the design json named VIA.json which can be found in this folder for VIA functions. (Use Wired Mode)

## For OpenRGB setup via Color Hoster

1. Drag the ColorHoster.json into the ColorHoster.exe
2. Create a ColorHoster.exe service for future auto startuop (optional `./ColorHoster.exe -b --port 6743 --service create`)
3. Listen to the port in OpenRGB using SDK Client
