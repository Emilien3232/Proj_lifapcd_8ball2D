all : projet test

test : src/mainTestJeu.cpp 
	g++  src/mainTestJeu.cpp src/Jeu.cpp -o bin/mainTestJeu
	./bin/mainTestJeu

test_p : src/mainTestp.cpp 
	g++ src/mainTestp.cpp src/JeuTest.cpp -o bin/mon_testp -lSDL2 -lSDL2main
	./bin/mon_testp

projet : src/main.cpp
	g++ src/main.cpp src/Jeu.cpp -o bin/mon_projet -lSDL2 -lSDL2main
	./bin/mon_projet
	
	
clean : 
	rm -f bin/mainTestJeu bin/mon_projet bin/mon_testp