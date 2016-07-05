CONTIKI_PROJECT = test-proximity
CONTIKI = ../../../..

CFLAGS += -DPROXIMITY_CLICK -DMOTION_CLICK

APPS += proximity-click
APPS += motion-click
APPDIRS += ../../dev

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
