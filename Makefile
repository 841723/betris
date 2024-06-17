
#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -std=c++11     		#opciones de compilación
LDFLAGS =                       #opciones de linkado
RM = rm -f                      #comando para borrar ficheros

#-----------------------------------------------------------
betris: betris.o mainB.o
	${CC} betris.o mainB.o -I ../trabajo -o betris ${LDFLAGS}

betris.o: betris.cpp 
	${CC} -c betris.cpp -I ../trabajo ${CPPFLAGS}

mainB.o: mainB.cpp 
	${CC} -c mainB.cpp -I ../trabajo ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} betris.o mainB.o
