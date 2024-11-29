run: project_gamebuoy.cpp Project-Libraries/resize_window.cpp Project-Libraries/mapLoader.cpp
	g++ -o main project_gamebuoy.cpp Project-Libraries/resize_window.cpp Project-Libraries/mapLoader.cpp -lsfml-graphics -lsfml-window -lsfml-system
	./main
