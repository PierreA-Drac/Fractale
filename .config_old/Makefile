# Variables ====================================================================

## Structure du projet ........................................................:

export PROJECT  = Fractale
EXE_NAME        = fractale

export WD_PATH  = $(shell pwd | sed 's: :\\ :g')/
export SRC_PATH = src/
export INC_PATH = inc/
OBJ_PATH        = obj/
DOC_PATH        = doc/
EXE_PATH        = bin/
REPORT_PATH     = report/

export SRC_EXT  = cpp
export INC_EXT  = hpp

EXEC            = $(EXE_PATH)$(EXE_NAME)
export SRC      = $(shell find $(SRC_PATH)*.$(SRC_EXT))
export INC      = $(shell find $(INC_PATH)*.$(INC_EXT))
OBJ             = $(SRC:$(SRC_PATH)%.$(SRC_EXT)=$(OBJ_PATH)%.o)

# Qt Meta Object Compiler
MOC_CMD 	= moc-qt4
# MOC_CMD 	= moc
MOC_EXT         = moc_
MOC_SRC         = $(SRC:$(SRC_PATH)%=$(SRC_PATH)$(MOC_EXT)%)
MOC_OBJ         = $(OBJ:$(OBJ_PATH)%=$(OBJ_PATH)$(MOC_EXT)%)

# Valgrind parameters
VAL_SUPP 	= .valgrind.supp
VAL_OUT 	= .valgrind.out

## Compilation ................................................................:

QT_INC        = /usr/include/qt4
# QT_INC      = /usr/include/x86_64-linux-gnu/qt5
QT_LD         = -L/usr/lib/x86_64-linux-gnu -lQtCore -lQtGui -lQtOpenGL
# QT_LD       = -L/usr/lib/x86_64-linux-gnu -lQt5Core -lQt5Gui -lQt5OpenGL \
		# -lQt5Widgets
GL_INC        = /usr/include/GL
GL_LD         = -lGL

INC_FLAGS     = -I$(INC_PATH) -I$(QT_INC) -I$(GL_INC)
DEP_FLAGS     = -MMD -MP
DEBUG_FLAGS   = -g3 -Wall
POS_IND_FLAGS = -fPIC
STD_FLAGS     = -std=c++0x

CC            = g++
CFLAGS        = $(STD_FLAGS) $(POS_IND_FLAGS) $(INC_FLAGS) $(DEP_FLAGS) $(DEBUG_FLAGS)
LDFLAGS       = $(QT_LD) $(GL_LD)

# Commandes ...................................................................:

LESS = less -RmN

# Cibles =======================================================================

.PHONY : clean mrproper indent doc report

## Lancement ..................................................................:

run : compil
	@echo "--> Lancement de '$(EXEC)' :"
	$(EXEC) $(ARGS)

## Compilation ................................................................:

compil : $(EXEC) tags

$(EXEC) : $(OBJ) $(MOC_OBJ)
	@mkdir -p $(EXE_PATH)
	@echo "--> Édition des liens dans '$(EXEC)' :"
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.$(SRC_EXT)
	@mkdir -p $(OBJ_PATH)
	@echo "--> Compilation de '$<' :"
	$(CC) -c $< -o $@ $(CFLAGS)

## Dépendances ................................................................:

-include $(OBJ:%.o=%.d)

$(SRC_PATH)$(MOC_EXT)%.$(SRC_EXT) : $(INC_PATH)%.$(INC_EXT)
	@echo "--> Génération du code Qt de '$<' :"
	$(MOC_CMD) $< -o $@

## Nettoyage ..................................................................:

clean :
	@echo "--> Suppression des fichier temporaires de $(PROJECT) :"
	rm -rf $(OBJ_PATH) $(SRC_PATH)*~ $(SRC_PATH)moc_* $(INC_PATH)*~ $(VAL_OUT) .gdb_history
	@make clean --directory="$(REPORT_PATH)" --no-print-directory

mrproper : clean
	@echo "--> Suppression de l'exécutable de $(PROJECT) :"
	rm -rf $(EXE_PATH)
	@make mrproper --directory="$(DOC_PATH)" --no-print-directory
	@make mrproper --directory="$(REPORT_PATH)" --no-print-directory
	@echo "--> Nettoyage complet du dossier de travail de $(PROJECT)" \
	    "effectué !"

## Debugger ...................................................................:

gdb : compil
	@echo "--> Debbugage avec $@ :"
	$@ -q --args $(EXEC)

valgrind-lite : compil
	@echo "--> Debbugage avec $@ (profile 1) :"
	valgrind --tool=memcheck --leak-resolution=high \
	    --show-possibly-lost=yes --show-reachable=yes \
	    --suppressions=$(VAL_SUPP) --log-file=$(VAL_OUT) $(EXEC) && \
	    cat $(VAL_OUT) | $(LESS)

valgrind-full : compil
	@echo "--> Debbugage avec $@ (profile 2) :"
	valgrind --tool=memcheck --leak-resolution=high --leak-check=full \
	    --show-possibly-lost=yes --show-reachable=yes --track-origins=yes \
	    --suppressions=$(VAL_SUPP) --log-file=$(VAL_OUT) $(EXEC) && \
	    cat $(VAL_OUT) | $(LESS)

## Présentation ...............................................................:

indent :
	@echo "--> Reformatage de la présentation du code (paramètres dans" \
	    ".indent.pro) :"
	$@ $(SRC_PATH)* $(INC_PATH)*

## Développement ..............................................................:

tags : $(SRC) $(INC) Makefile
	@echo "--> Génération des tags des sources du projet : "
	ctags $^ 2>/dev/null

## Documentation ..............................................................:

doc :
	@make --directory="$(DOC_PATH)" --no-print-directory MASTER=1

report :
	@make --directory="$(REPORT_PATH)" --no-print-directory
