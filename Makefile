CXX=g++
XXFLAGS=-Wall -MMD
EXEC=run
OBJECTS=interact.o stock.o trade.o 
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}
