all : bin/mon_projet

bin/mainTestJeu : src/mainTestJeu.cpp 
	g++  src/mainTestJeu.cpp src/Jeu.cpp -o bin/mainTestJeu

bin/mon_projet : src/main.cpp
	g++ -o bin/mon_projet src/main.cpp src/Jeu.cpp src/Image.cpp -lSDL2 -lSDL2main

projet : 
	./bin/mon_projet

testJeu :
	./bin/mainTestJeu

clean : 
	rm -f bin/mainTestJeu bin/mon_projet