CONTIKI_PROJECT = test-proximity
CONTIKI = ../../../..

PROXIMITY_CLICK = proximity-click

CFLAGS += -DPROXIMITY_CLICK

APPS += proximity-click
APPDIRS += ../../dev

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
