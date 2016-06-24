CONTIKI_PROJECT = test-thermo3
CONTIKI = ../../../..

CFLAGS += -DTHERMO3_CLICK

APPS += thermo3-click
APPDIRS += ../../dev

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
