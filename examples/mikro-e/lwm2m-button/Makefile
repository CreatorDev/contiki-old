CONTIKI=../../..

TARGET = mikro-e
VERSION? = $(shell git describe --abbrev=4 --dirty --always --tags)

# If periodic button presses need to be simulated, uncomment the following line
# CFLAGS += -DBUTTON_PRESS_SIMULATION

CFLAGS += -DVERSION=$(VERSION)
CFLAGS += -Wall -Wno-pointer-sign
CFLAGS += -I $(CONTIKI)/platform/$(TARGET)
CFLAGS += -fno-short-double
LDFLAGS += -Wl,--defsym,_min_heap_size=32000

SMALL=0

APPS += er-coap

all: lwm2m lwm2m-button
	xc32-bin2hex lwm2m-button.$(TARGET)

include $(CONTIKI)/platform/mikro-e/apps/lwm2m/Makefile.lwm2m
include $(CONTIKI)/Makefile.include
