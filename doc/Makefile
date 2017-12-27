# Variables ====================================================================

## Dépendances ................................................................:

DEPS = Doxyfile
# Si on appelle ce Makefile depuis le Makefile maître :
ifdef MASTER
    DEPS += $(INC:%.$(INC_EXT)=$(WD_PATH)%.$(INC_EXT)) $(SRC:%.$(SRC_EXT)=$(WD_PATH)%.$(SRC_EXT)) $(WD_PATH)README.md
endif

## Logiciels ..................................................................:

PDF_VIEWER = evince
INTERNET_BROWSER = firefox

# Commandes ...................................................................:

LESS = less -RmN

# Cibles =======================================================================

.PHONY : mrproper

## Visionnage .................................................................:

view : compil
	@echo "--> Visionnement de la documentation de $(PROJECT) :"
	$(INTERNET_BROWSER) html/index.html >/dev/null 2>&1 &
	$(PDF_VIEWER) latex/refman.pdf >/dev/null 2>&1 &

## Compilation ................................................................:

compil : html/index.html latex/refman.pdf

html/index.html : $(DEPS)
	@echo "--> Création de la documentation de $(PROJECT) :"
	doxygen Doxyfile | grep "warning" | $(LESS)
	
latex/refman.pdf : $(DEPS)
	@echo "--> Compilation de la documentation en PDF de $(PROJECT)" \
	    "dans 'latex/' :"
	make --directory="latex/" --no-print-directory

## Nettoyage ..................................................................:

mrproper:
	@echo "--> Suppression de la documentation de $(PROJECT) :"
	rm -f -r html/ latex/ doxygen_*.tmp
