SRC=./src
OBJ=./obj

all: $(OBJ) winsys

# Creating folder
$(OBJ):
	mkdir -p $(OBJ)

# Dynamik linking
winsys: $(OBJ)/main.o $(OBJ)/screen.o $(OBJ)/winsys.o $(OBJ)/snake.o
	g++ -g -Wall -pedantic -std=c++11 $^ -o $@ -lncurses

# With debugging symbols
$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/winsys.h $(SRC)/screen.h $(SRC)/cpoint.h $(SRC)/snake.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/screen.o: $(SRC)/screen.cpp $(SRC)/screen.h $(SRC)/cpoint.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/winsys.o: $(SRC)/winsys.cpp $(SRC)/winsys.h $(SRC)/screen.h $(SRC)/cpoint.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

$(OBJ)/snake.o: $(SRC)/snake.cpp $(SRC)/winsys.h $(SRC)/screen.h $(SRC)/cpoint.h $(SRC)/snake.h
	g++ -g -c -Wall -pedantic -std=c++11 $< -o $@

.PHONY: clean

clean:
	-rm winsys $(OBJ)/*.o
