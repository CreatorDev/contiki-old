The Contiki Operating System
============================

[![Build Status](https://travis-ci.org/contiki-os/contiki.svg?branch=release-3-0)](https://travis-ci.org/contiki-os/contiki/branches)

Contiki is an open source operating system that runs on tiny low-power
microcontrollers and makes it possible to develop applications that
make efficient use of the hardware while providing standardized
low-power wireless communication for a range of hardware platforms.

Contiki is used in numerous commercial and non-commercial systems,
such as city sound monitoring, street lights, networked electrical
power meters, industrial monitoring, radiation monitoring,
construction site monitoring, alarm systems, remote house monitoring,
and so on.

For more information, see the Contiki website:

[http://contiki-os.org](http://contiki-os.org)

=====

## 6LoWPAN Clicker Build Instructions

**If you would like to build the IoT Creator Kit projects, go to https://github.com/CreatorKit/build and follow the instructions there.**

===
Install the XC32 compiler from microchip: http://microchip.wikidot.com/xc32:installation
<pre>
$ git clone https://github.com/CreatorDev/contiki.git
$ cd contiki
$ git submodule init && git submodule sync && git submodule update
</pre>
You can now go to 'platform/mikro-e/apps/sample-app' and run:
<pre>$ make</pre>
to build the sample application.
