# Variables ====================================================================

## Structure du projet ........................................................:

export PROJECT  = Fractale
EXE_NAME        = fractale

export WD_PATH  = $(shell pwd | sed 's: :\\ :g')/
export SRC_PATH = src/
export INC_PATH = inc/
OBJ_PATH        = obj/
DOC_PATH        = doc/
EXE_PATH        = exe/
REPORT_PATH     = report/

export SRC_EXT  = cpp
export INC_EXT  = hpp

EXEC            = $(EXE_PATH)$(EXE_NAME)
export SRC      = $(shell find $(SRC_PATH)*.$(SRC_EXT))
export INC      = $(shell find $(INC_PATH)*.$(INC_EXT))
OBJ             = $(SRC:$(SRC_PATH)%.$(SRC_EXT)=$(OBJ_PATH)%.o)

## Compilation ................................................................:

QT_INC = /usr/include/qt4
QT_LD = -L/usr/lib/x86_64-linux-gnu -lQtCore -lQtGui

INC_FLAGS       = -I$(INC_PATH) -I$(QT_INC)
DEP_FLAGS       = -MMD -MP
DEBUG_FLAGS     = -g3 -Wall

CC              = g++
CFLAGS          = $(INC_FLAGS) $(DEP_FLAGS) $(DEBUG_FLAGS)
LDFLAGS         = $(QT_LD)

# Cibles =======================================================================

.PHONY : clean mrproper indent tags doc

## Lancement ..................................................................:

run : compil
	@echo "--> Lancement de '$(EXEC)' :"
	$(EXEC) $(ARGS)

## Compilation ................................................................:

compil : $(EXEC)

$(EXEC) : $(OBJ)
	@mkdir -p $(EXE_PATH) 2>/dev/null
	@echo "--> Édition des liens dans '$(EXEC)' :"
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.$(SRC_EXT)
	@mkdir -p $(OBJ_PATH)
	@echo "--> Compilation de '$<' :"
	$(CC) -c $< -o $@ $(CFLAGS)

## Dépendances ................................................................:

-include $(OBJ:%.o=%.d)

## Nettoyage ..................................................................:

clean :
	@echo "--> Suppression des fichier temporaires de $(PROJECT) :"
	rm -rf $(OBJ_PATH) $(SRC_PATH)*~ $(INC_PATH)*~
	@make clean --directory="$(REPORT_PATH)" --no-print-directory

mrproper : clean
	@echo "--> Suppression de l'exécutable de $(PROJECT) :"
	rm -rf $(EXE_PATH)
	@make mrproper --directory="$(DOC_PATH)" --no-print-directory
	@make mrproper --directory="$(REPORT_PATH)" --no-print-directory
	@echo "--> Nettoyage complet du dossier de travail de $(PROJECT)" \
	    "effectué !"

## Debugger ...................................................................:

gdb :
	@echo "--> Debbugage avec $@ :"
	$@ -q --args $(EXEC)

valgrind-lite :
	@echo "--> Debbugage avec $@ (profile 1) :"
	valgrind --tool=memcheck --leak-resolution=high \
	    --show-possibly-lost=yes --show-reachable=yes $(EXEC)

valgrind-full :
	@echo "--> Debbugage avec $@ (profile 2) :"
	valgrind --tool=memcheck --leak-resolution=high --leak-check=full \
	    --show-possibly-lost=yes --show-reachable=yes --track-origins=yes \
	    $(EXEC)

## Présentation ...............................................................:

indent :
	@echo "--> Reformatage de la présentation du code (paramètres dans" \
	    ".indent.pro) :"
	$@ $(SRC_PATH)* $(INC_PATH)*

## Développement ..............................................................:

tags :
	@echo "--> Génération des tags des sources du projet : "
	ctags $(SRC) $(INC)

## Documentation ..............................................................:

doc :
	@make --directory="$(DOC_PATH)" --no-print-directory MASTER=1

report :
	@make --directory="$(REPORT_PATH)" --no-print-directory

