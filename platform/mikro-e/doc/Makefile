# Doxyfile configuration variables
export docdir	:= .
export picdir	:= ./pics
export docsrc	:= ./mainpage.dox
export docroot	:= ../../../


.PHONY: clean html

# This target requires and graphviz and doxygen
html:
	doxygen Doxyfile

clean:
	@echo "> Cleaning Documentation"
	@$(RM) -r "$(docdir)/html"
	@$(RM) "$(docdir)/tagfile"
	@echo " done."

