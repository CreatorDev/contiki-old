CONTIKI_PROJECT = test-motion-click

ifndef TARGET
TARGET=mikro-e
endif

CONTIKI = ../../../..

APPS += dev

APPDIRS += ../..

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

include $(CONTIKI)/Makefile.include
