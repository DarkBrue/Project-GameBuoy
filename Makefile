run: project_gamebuoy.cpp Project-Libraries/resize_window.cpp Project-Libraries/map_loader.cpp Project-Libraries/visible_grid.cpp
	g++ -o main project_gamebuoy.cpp Project-Libraries/resize_window.cpp Project-Libraries/map_loader.cpp Project-Libraries/visible_grid.cpp -lsfml-graphics -lsfml-window -lsfml-system
	./main
