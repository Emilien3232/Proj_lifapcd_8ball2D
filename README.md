0/0 début de projet, a peu prêt toutes les classes nécessaires sont faites .
    à l'execution la table de jeu s'affiche ainsi que les boules , les boules partent dans tout les sens du à une erreur dans la fonction "checkCollisions" ,
    les collisions ne sont pas actives pour la boule noire j'ai juste oublié. les trous ne sont pas apparant aussi. gestion d'evenement utilisateurs pas encore faites non plus (voir le main) .
    probleme de collisions j'arrive pas à trouver la bonne formule pour les nouvelles vitesses apres collisions entre boules (voir resultCollisions).

14/03 le probleme principal est sur les formules physiques utilisées. 1. les vecteurs de direction ont un impact sur la force des boules et donc leurs vitesses
    se qui ne devrait pas etre le cas , les vecteurs de direction devrait etre des vecteurs comme : Vec(1,0) pour aller à droite , vec2(-1,0) pour aller à gauche
    Vec2(0,1) pour aller en bas , Vec2(0,-1) pour aller en haut.. Vec(x,y) avec (x,y) entre [-1 , 1].
    Donc voir MAJpositionBoules et resultCollisions
    
18/03 creation d'une 
    
