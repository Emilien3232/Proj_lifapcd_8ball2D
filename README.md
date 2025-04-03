0/0 début de projet, a peu prêt toutes les classes nécessaires sont faites . à l'execution la table de jeu s'affiche ainsi que les boules , les boules partent dans tout les sens du à une erreur dans la fonction "checkCollisions" , les collisions ne sont pas actives pour la boule noire j'ai juste oublié. les trous ne sont pas apparant aussi. gestion d'evenement utilisateurs pas encore faites non plus (voir le main) . probleme de collisions j'arrive pas à trouver la bonne formule pour les nouvelles vitesses apres collisions entre boules (voir resultCollisions).

14/03 le probleme principal est sur les formules physiques utilisées. 1. les vecteurs de direction ont un impact sur la force des boules et donc leurs vitesses se qui ne devrait pas etre le cas , les vecteurs de direction devrait etre des vecteurs comme : Vec(1,0) pour aller à droite , vec2(-1,0) pour aller à gauche Vec2(0,1) pour aller en bas , Vec2(0,-1) pour aller en haut.. Vec(x,y) avec (x,y) entre [-1 , 1]. Donc voir MAJpositionBoules et resultCollisions

23/03 création de l'"espace" Jeutest.cpp et MainJeuTest.cpp pour faire des test d'affichage. j'y est fais des tests pour regler les problemes de physique (repasser boule -> vitesseBoule en tant que Vec2 et pas float et retirer boule -> directionBoule). Les modifications on après été apporté à l'espace de base (Jeu.cpp et main.cpp). + mise en commun des deux branches. +suppression de la branch inutile.

pour compiler : make sur un terminal lié pour executer : make testJeu (pour le tests regression de JEUINIT()) make projet (pour afficher le projet (necessaire d'avoir sdl2 d'installer))

ce qui reste à faire : 
	regle de jeu (regles.h fais , regles.cpp à faire)
	une fonction AffichageGraphique() , qui remplace le code sdl2 dans le main
	gestion evenement dans sdl2 (boule tombé, fin de partie, cas particulier de regles (penalité,avantage) , nombre de point par joueur , ... )
	gestion d'evenement utilisateur (alterné joueur 1 / joueur 2 , appliquer une vitesse à la boule blanche , appliquer une direction à la boule blanche , placer la boule blanche en cas d'avantage , ... )
	affichage modifié (avec tableaux de score , affiche à qui est le tour , meilleur esthetique , affiché les direction de la boule blanche / systeme de visée , ... )
	sauvegarder
	niveau de difficulté (multiples sdl)
