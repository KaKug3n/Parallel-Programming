#########################################################################
##	Master CHPS
##	Mandelbrot
#########################################################################


#########################################################################
#	Compilateur
#########################################################################

C		= gcc
HOME_DIR	= .

#########################################################################
#	Options
#########################################################################

OPTIONS	=  -fopenmp # ce qu'il faut pour OpenMP

#########################################################################
#	Fichiers
#########################################################################

DEP = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJ	=  $(SRC:.c=.o)
EXEC = princ

#########################################################################
#	Definition des librairies
#########################################################################

LIB	= -lm

#########################################################################
#	Definition du but
#########################################################################

$(EXEC): $(OBJ) 
	@echo "	Edition de liens ..."
	@$(C) $(INCLUDES) $(OPTIONS) $^ -o $@ $(LIB) 
	
#########################################################################
#	Les cibles
#########################################################################

#dependances particulieres
tga.o: tga.h
princ.o: mandelbrot.h 
mandelbrot.o: mandelbrot.h tga.h

# regle generale
%.o: %.c  
	@echo "	Compilation de $<"
	@$(C) $(INCLUDES) $(OPTIONS) $< -c

#########################################################################
#	Nettoyage
#########################################################################

.PHONY: clean mrproper

clean:	
	@rm -rf *.o *.c~

mrproper: clean
	@rm princ
