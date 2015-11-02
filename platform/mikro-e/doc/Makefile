# Doxyfile configuration variables
export docdir	:= .
export picdir	:= ./pics
export docroot	:= ../../../
export docsrc	:= ./ \
		    $(docroot)/examples/mikro-e

export VERSION	:= 0.1.0
export BUTTON_APP_VERSION := 0.1.0
export LED_APP_VERSION	:= 0.1.0

.PHONY: clean html

# This target requires and graphviz and doxygen
html:
	doxygen Doxyfile

clean:
	@echo "> Cleaning Documentation"
	@$(RM) -r "$(docdir)/html"
	@$(RM) "$(docdir)/tagfile"
	@echo " done."

