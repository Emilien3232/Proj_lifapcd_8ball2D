all : projet

test : src/mainTestJeu.cpp 
	g++  src/mainTestJeu.cpp src/Jeu.cpp -o bin/mainTestJeu
	./bin/mainTestJeu

projet : src/main.cpp
	g++ src/main.cpp src/Jeu.cpp -o bin/mon_projet -lSDL2 -lSDL2main
	./bin/mon_projet
	

clean : 
	rm -f bin/mainTestJeu bin/mon_projet