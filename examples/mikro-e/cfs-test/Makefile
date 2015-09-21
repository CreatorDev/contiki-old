CONTIKI=../../..

TARGET = mikro-e
VERSION? = $(shell git describe --abbrev=4 --dirty --always --tags)

CFLAGS += -DVERSION=$(VERSION)
CFLAGS += -Wall -Wno-pointer-sign
CFLAGS += -I $(CONTIKI)/platform/$(TARGET)
CFLAGS += -fno-short-double
LDFLAGS += -Wl,--defsym,_min_heap_size=32000

SMALL=0

all: cfs-test
	xc32-bin2hex cfs-test.$(TARGET)

include $(CONTIKI)/Makefile.include
