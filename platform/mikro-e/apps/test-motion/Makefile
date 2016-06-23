CONTIKI_PROJECT = test-motion
CONTIKI = ../../../..

CFLAGS += -DMOTION_CLICK

APPS += motion-click
APPDIRS += ../../dev

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
