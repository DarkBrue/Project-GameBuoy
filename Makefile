run: project_gamebuoy.cpp Project-Libraries/resize_window.cpp
	g++ -o main project_gamebuoy.cpp Project-Libraries/resize_window.cpp -lsfml-graphics -lsfml-window -lsfml-system
	/.main
