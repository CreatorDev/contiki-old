CONTIKI_PROJECT=test-relay
CONTIKI=../../../..

APPS += dev
APPDIRS += ../..

all: $(CONTIKI_PROJECT)
	xc32-bin2hex $(CONTIKI_PROJECT).$(TARGET)

distclean: cleanall

cleanall:
	rm -f $(CONTIKI_PROJECT).hex
	rm -f symbols.*

include $(CONTIKI)/Makefile.include
