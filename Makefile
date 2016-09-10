all: CA

CA: Main.o GameController.o CellCar.o
	g++ Main.o GameController.o CellCar.o -o CA

Main.o: Main.cpp
	g++ -c Main.cpp

GameController.o: GameController.cpp
	g++ -c GameController.cpp

CellCar.o: CellCar.cpp
	g++ -c CellCar.cpp
