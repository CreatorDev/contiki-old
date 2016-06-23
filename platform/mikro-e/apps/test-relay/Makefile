CONTIKI_PROJECT = test-relay
CONTIKI = ../../../..

RELAY_CLICK = relay-click

CFLAGS += -DRELAY_CLICK

APPS += relay-click
APPDIRS += ../../dev

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
