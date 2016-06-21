CONTIKI_PROJECT = test-i2c

CONTIKI = ../../../..

ifndef TARGET
TARGET=mikro-e
endif

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

include $(CONTIKI)/Makefile.include
