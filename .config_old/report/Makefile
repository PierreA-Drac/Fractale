# Variables ...................................................................:

NAME = Report
PDFVIEWER = evince
COMPILER = pdflatex

# Cibles ......................................................................:

## Visionnage .................................................................:

view : $(NAME).pdf 
	$(info --> Visionnage de $< :)
	$(PDFVIEWER) $< &

## Compilation ................................................................:

$(NAME).pdf : $(NAME).tex
	$(info --> Compilation de $< :)
	$(COMPILER) $<

## Nettoyage ..................................................................:

clean :
	$(info --> Suppression de $(NAME).aux $(NAME).log :)
	rm -f $(NAME).aux $(NAME).log

mrproper : clean 
	$(info --> Suppression de $(NAME).pdf :)
	rm -f $(NAME).pdf 
