# Doxyfile configuration variables
export docdir	:= .
export picdir	:= ./pics
export docroot	:= ../../../..
export docsrc	:= .

export VERSION	:= 0.2.0

.PHONY: clean html

# This target requires and graphviz and doxygen
html:
	doxygen Doxyfile

clean:
	@echo "> Cleaning Documentation"
	@$(RM) -r "$(docdir)/html"
	@$(RM) "$(docdir)/tagfile"
	@echo " done."

