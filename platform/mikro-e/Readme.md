# Using Contiki on Mikro-E Clicker

## Overview

This section explains how to build Contiki code for Mikro-E Clicker and to flash the compiled application image on Mikro-E Clicker.

## Revision History

| revision  | changes from previous revision |
|---------- |------------------------------- |
| 1.0.0     | Initial release                |

## Package Content

Some key paths where IMG have added source code to support Contiki on Mikro-E Clicker:

| Folder              				| Content                                              							                      |
| :----               				| :----                                                							                      |
| platform/mikro-e			      | Porting of drivers for peripherals like Button, LED, CC2520 etc. on Mikro-E Clicker			|
| examples/mikro-e            | Applications for Mikro-E Clicker board                                                  |         

## Getting Started

The xc32 compiler version 1.34 from Microchip can be used for compilation of the source code. Download the xc32 compiler from
<a href="http://www.microchip.com/pagehandler/en_us/devtools/mplabxc/">Microchip's website</a> and add tool chain path in the
environment variables and compile an example, say "Hello World" which is included in Contiki as per below:

    $ export PATH=$PATH:/opt/microchip/xc32/v1.34/bin/

The application e.g. Hello World can be built for Mikro-E Clicker and HEX file can be generated to flash on the board as per below:

    $ cd examples/hello-world
    $ make TARGET=mikro-e
    $ /opt/microchip/xc32/v1.34/bin/xc32-bin2hex hello-world.mikro-e

