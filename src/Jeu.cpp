#include "class/Jeu.h"
#include <cassert> // pour les tests
#include <iostream>

//declaration des constantes ou les valeurs réels deviendront des pixels quand on passera à sdl2
//j'ai calculé les différentes mesures en posant que 1000px = 254cm (soit la longueur reglementaire des table de billard américaine) et effectuant des produits en croix
const float DIAM_BOULE = 20.5; //diametre des boules
const float DIM_TABLE_X = 1000.f; //longueur table
const float DIM_TABLE_Y = 546.f; //largeur table
const float ECART = 1.f; //petite distance entre chaque boules à l'initialisation pour eviter les problemes de collision dès l'init
const float DOUBLE_ECART = 2.f;
const float TRIPLE_ECART = 3.f;
const float QUAD_ECART = 4.f;
const float SCAL_F = 0.99f; //constante de frottement
const float SEUIL_VITESSE = 0.0001f; 

void Jeu::INITJEU(){
    //on cherche à definir "TableDeJeu" donc premierement on initialise les trous avec un rayon de 2 * DIAM_BOULE et leurs position
    trou* trousJeu = new trou [6];
    for(int i = 0 ; i < 6 ; i++){
        trousJeu[i].rayonTrou = DIAM_BOULE * 2;
    }
    trousJeu[0].posTrou = Vec2(0,0); //en haut à gauche
    trousJeu[1].posTrou = Vec2(DIM_TABLE_X / 2 , 0); //au milieu en haut
    trousJeu[2].posTrou = Vec2(DIM_TABLE_X , 0); //en haut à droite
    trousJeu[3].posTrou = Vec2(0 , DIM_TABLE_Y); //en bas à gauche
    trousJeu[4].posTrou = Vec2(DIM_TABLE_X / 2 , DIM_TABLE_Y); //au milieu en bas
    trousJeu[5].posTrou = Vec2(DIM_TABLE_X , DIM_TABLE_Y); //en bas à droite
    TDJ = TableDeJeu(DIM_TABLE_X , DIM_TABLE_Y , Vec2(0,0) , trousJeu);

    //on defini la boule blanche et la noir sur des positions precise qui serviront de repere pour les autres
    BouleBlanche = boule(0 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X * 3 / 4 , DIM_TABLE_Y / 2) , Vec2(-1,0) , 8.f); //le vecteur de direction ne doit pas impacté la force de frappe d'un boule mais jjuste sa direction (regler ce probleme)

    BouleNoire = boule(1 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - 2.f , DIM_TABLE_Y / 2), Vec2(0,0) ,0);
    
    //on defini les boules jaunes
    boule* bjaunes = new boule [7];
    bjaunes[0] = boule(1 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 , DIM_TABLE_Y / 2), Vec2(0,0) ,0); //en tete du triangle (les auteres boules sont placés en fonction de celle ci)
    bjaunes[1] = boule(2 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE - ECART , DIM_TABLE_Y / 2 + DIAM_BOULE / 2 + ECART), Vec2(0,0) , 0); 
    bjaunes[2] = boule(3 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE - ECART , DIM_TABLE_Y / 2 - DIAM_BOULE / 2 - ECART), Vec2(0,0) , 0);
    bjaunes[3] = boule(4 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - DOUBLE_ECART , DIM_TABLE_Y / 2 - DIAM_BOULE - ECART), Vec2(0,0) ,0); 
    bjaunes[4] = boule(5 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - DOUBLE_ECART , DIM_TABLE_Y / 2 + DIAM_BOULE + ECART), Vec2(0,0) ,0);
    bjaunes[5] = boule(6 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 - DIAM_BOULE * 2  + DIAM_BOULE / 2 - DOUBLE_ECART), Vec2(0,0) ,0);
    bjaunes[6] = boule(7 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 + DIAM_BOULE * 2 - DIAM_BOULE / 2 + DOUBLE_ECART), Vec2(0,0) ,0);
    BJ = boulesJaunes(bjaunes , 7);

    //et finalement les boules rouges 
    boule* brouges = new boule[7];
    brouges[0] = boule(9, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART, DIM_TABLE_Y / 2), Vec2(0, 0), 0);
    brouges[1] = boule(10, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART, DIM_TABLE_Y / 2 + (ECART + DIAM_BOULE)), Vec2(0, 0), 0);
    brouges[2] = boule(11, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART, DIM_TABLE_Y / 2 + 2 * (ECART + DIAM_BOULE)), Vec2(0, 0), 0);
    brouges[3] = boule(12, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART, DIM_TABLE_Y / 2 - (ECART + DIAM_BOULE)), Vec2(0, 0), 0);
    brouges[4] = boule(13, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART, DIM_TABLE_Y / 2 - 2 * (ECART + DIAM_BOULE)), Vec2(0, 0), 0);
    brouges[5] = boule(14, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART, DIM_TABLE_Y / 2 + DIAM_BOULE / 2 + ECART), Vec2(0, 0), 0);
    brouges[6] = boule(15, DIAM_BOULE, 1.f, Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART, DIM_TABLE_Y / 2 - DIAM_BOULE / 2 - ECART), Vec2(0, 0), 0);
    BR = boulesRouges(brouges, 7);
}

void Jeu::test_INITJEU() {
    // Appel de la fonction INITJEU() pour initialiser le jeu
    INITJEU();

    // Récupération des objets initialisés
    TableDeJeu table = TDJ;
    boulesJaunes boulesJaunes = BJ;
    boulesRouges boulesRouges = BR;
    boule bouleBlanche = BouleBlanche;
    boule bouleNoire = BouleNoire;

    // Test 1 : Vérification des dimensions de la table de jeu
    assert(table.getDimTableX() == 1000);
    assert(table.getDimTableY() == 546);
    std::cout << "Test 1 : Dimensions de la table de jeu OK" << std::endl;

    // Test 2 : Vérification des positions des trous
    trou* trous = table.gettrous();
    assert(trous[0].posTrou == Vec2(0, 0));
    assert(trous[1].posTrou == Vec2(500, 0));
    assert(trous[2].posTrou == Vec2(1000, 0));
    assert(trous[3].posTrou == Vec2(0, 546));
    assert(trous[4].posTrou == Vec2(500, 546));
    assert(trous[5].posTrou == Vec2(1000, 546));
    std::cout << "Test 2 : Positions des trous OK" << std::endl;

    // Test 3 : Vérification des rayons des trous avec une tolérance
    for (int i = 0; i < 6; i++) {
        assert(trous[i].rayonTrou == 20.5 * 2);
    }
    std::cout << "Test 3 : Rayons des trous OK" << std::endl;

    // Test 4 : Vérification de la position de la boule blanche
    assert(bouleBlanche.positionBoule == Vec2(750, 273));
    std::cout << "Test 4 : Position de la boule blanche OK" << std::endl;

    // Test 5 : Vérification de la position de la boule noire
    assert(bouleNoire.positionBoule == Vec2(250 - 20.5 * 2 - 2, 273));
    std::cout << "Test 5 : Position de la boule noire OK" << std::endl;

    // Test 6 : Vérification du nombre de boules jaunes
    assert(boulesJaunes.getnbBJ() == 7);
    std::cout << "Test 6 : Nombre de boules jaunes OK" << std::endl;

    // Test 7 : Vérification du nombre de boules rouges
    assert(boulesRouges.getnbBR() == 7);
    std::cout << "Test 7 : Nombre de boules rouges OK" << std::endl;

    // Test 8 : Vérification des positions des boules jaunes
    boule* bjaunes = boulesJaunes.getBjaunes();
    assert(bjaunes[0].positionBoule == Vec2(250, 273));
    assert(bjaunes[1].positionBoule == Vec2(250 - 20.5 - 1, 273 + 20.5 / 2 + 1));
    assert(bjaunes[2].positionBoule == Vec2(250 - 20.5 - 1, 273 - 20.5 / 2 - 1));
    assert(bjaunes[3].positionBoule == Vec2(250 - 20.5 * 2 - 2, 273 - 20.5 - 1));
    assert(bjaunes[4].positionBoule == Vec2(250 - 20.5 * 2 - 2, 273 + 20.5 + 1));
    assert(bjaunes[5].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 - 20.5 * 2 + 20.5 / 2 - 2));
    assert(bjaunes[6].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 + 20.5 * 2 - 20.5 / 2 + 2));
    std::cout << "Test 8 : Positions des boules jaunes OK" << std::endl;

    // Test 9 : Vérification des positions des boules rouges
    boule* brouges = boulesRouges.getBrouges();
    assert(brouges[0].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273));
    assert(brouges[1].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 + 1 + 20.5));
    assert(brouges[2].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 + 2 * (1 + 20.5)));
    assert(brouges[3].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 - 1 * (1 + 20.5)));
    assert(brouges[4].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 - 2 * (1 + 20.5)));
    assert(brouges[5].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 + 20.5 / 2 + 1));
    assert(brouges[6].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 - 20.5 / 2 - 1));
    std::cout << "Test 9 : Positions des boules rouges OK" << std::endl;

    std::cout << "Tous les tests de régression ont réussi !" << std::endl;
}

bool Jeu::UPDATEJEU() {
    
    //update les positions des boules
    MAJpositionBoules(); 

    //gerer les collisions des boules entre elles et contre les bords
    GestionCollisionsBords(); //possibles de faire que une seule fonction
    GestionCollisionsBoules();
 
    /*
    if(BouleBlanche.vitesseBoule.x < SEUIL_VITESSE && BouleBlanche.vitesseBoule.y < SEUIL_VITESSE) {
        //donner l'option au joueur de tirer (appliquer un vecteur vitesse la ou la souris pointe)
    }
    */

    //verifie les situatons des boules (tombés ou pas), si cette situation implique la fin du jeu => return false
    if(BJ.getnbBJ() != 0 ) {
            bouletombée(BJ); 
    }
    else{return false;}

    if(BR.getnbBR() != 0){
            bouletombée(BR);
    }
    else{return false;}

    bouletombéeBLCH(BouleBlanche);

    //if(bouletombéNR(BouleNoire)) {return false;}   //marche mais je le met en commentaire pour pour pouvoir regarder le programme sans que sa s'arrete trop rapidement

    return true;

}

void Jeu::MAJpositionBoules() { //pour les frottements revenir ici et appliquer un scalaire à la vitesse des boules , indépendament de l'actu de position je pense
    BouleBlanche.positionBoule = BouleBlanche.positionBoule + (BouleBlanche.directionBoule * BouleBlanche.vitesseBoule);
    BouleBlanche.vitesseBoule = BouleBlanche.vitesseBoule * SCAL_F;


    BouleNoire.positionBoule = BouleNoire.positionBoule +(BouleNoire.directionBoule * BouleNoire.vitesseBoule);
    BouleNoire.vitesseBoule = BouleNoire.vitesseBoule * SCAL_F;

    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        bjaunes[i].positionBoule = bjaunes[i].positionBoule + (bjaunes[i].directionBoule * bjaunes[i].vitesseBoule);
        bjaunes[i].vitesseBoule = bjaunes[i].vitesseBoule * SCAL_F;
    }
  
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        brouges[i].positionBoule = brouges[i].positionBoule +(brouges[i].directionBoule * brouges[i].vitesseBoule);
        brouges[i].vitesseBoule = brouges[i].vitesseBoule * SCAL_F;
    }
}

void Jeu::bouletombée(boulesJaunes &B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.getBjaunes()[i].positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            B.setnbBJ(B.getnbBJ() - 1);
            std::cout<<"la boule "<<B.getBjaunes()[i].IDnombre<<" est tombée"<<std::endl;
            B.getBjaunes()[i].positionBoule =Vec2(DIM_TABLE_X /2,DIM_TABLE_Y /2); //faire disparaitre la boule (je la met dans un coin )
            B.getBjaunes()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas (pas sur)
        }
        if(B.getBjaunes()[i].positionBoule.y > DIM_TABLE_Y || B.getBjaunes()[i].positionBoule.x > DIM_TABLE_X) {
            std::cout<<"la boule "<<B.getBjaunes()[i].IDnombre<<" est sortie de la table"<<std::endl;
            B.getBjaunes()[i].positionBoule = Vec2(DIM_TABLE_X /2,DIM_TABLE_Y /2); //faire disparaitre la boule (je la met dans un coin )
            B.getBjaunes()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas (pas sur)
        }
    }
}


void Jeu::bouletombée(boulesRouges &B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.getBrouges()[i].positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou //j'utilise la meme variable pour les trous c'est une erreur 
            B.setnbBR(B.getnbBR() - 1); //pose probleme car n'empeche pas que la boucle reverifie la situation d'une boule deja tombé , elle exclu juste la derniere boule dans la liste
            std::cout<<"la boule "<<B.getBrouges()[i].IDnombre<<" est tombée"<<std::endl;
            B.getBrouges()[i].positionBoule = Vec2(DIM_TABLE_X /2,DIM_TABLE_Y /2);//faire disparaitre la boule (je la met dans un coin )
            B.getBrouges()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas 
        }
        if(B.getBrouges()[i].positionBoule.y > DIM_TABLE_Y + 1|| B.getBrouges()[i].positionBoule.x > DIM_TABLE_X + 1) {
            std::cout<<"la boule "<<B.getBrouges()[i].IDnombre<<" est sortie de la table"<<std::endl;
            B.getBrouges()[i].positionBoule = Vec2(DIM_TABLE_X /2,DIM_TABLE_Y /2); //faire disparaitre la boule (je la met dans un coin )
            B.getBrouges()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas (pas sur)
        }
    }
}

void Jeu::bouletombée(boule &B) {
    if(B.positionBoule.Dist(TDJ.gettrous()[1].posTrou) < DIAM_BOULE || B.positionBoule.Dist(TDJ.gettrous()[0].posTrou) < DIAM_BOULE || B.positionBoule.Dist(TDJ.gettrous()[2].posTrou) < DIAM_BOULE || B.positionBoule.Dist(TDJ.gettrous()[3].posTrou) < DIAM_BOULE || B.positionBoule.Dist(TDJ.gettrous()[5].posTrou) < DIAM_BOULE ) { //si la boule B est dans un trou 
        std::cout<<"la boule "<<B.IDnombre<<" est tombée"<<std::endl;
        B.positionBoule = Vec2(DIM_TABLE_X / 2 , DIM_TABLE_Y / 2);
        B.diam = 0.f;
    }
    if(B.positionBoule.y > DIM_TABLE_Y || B.positionBoule.x > DIM_TABLE_X) {
        std::cout<<"la boule "<<B.IDnombre<<" est sortie de la table"<<std::endl;
        B.positionBoule = Vec2(DIM_TABLE_X / 2 , DIM_TABLE_Y / 2);
        B.diam = 0.f;
    }
}

void Jeu::bouletombéeBLCH(boule &B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            std::cout<<"la boule blanche est tombée !!"<<std::endl;
            B.positionBoule = Vec2(DIM_TABLE_X * 3 / 4 , DIM_TABLE_Y / 2) ; //si la boule blanche je la remet à sa position de départ
            B.vitesseBoule = 0;
            B.directionBoule = Vec2(0,0);
        }
    }
}

bool Jeu::bouletombéeNR(boule &B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            std::cout<<"la boule noire est tombée !!"<<std::endl;
            return true; //si la boule noire tombe je retourne true
        }
    }
    return false;
}


bool Jeu::checkCollision(const boule b1 , const boule b2) { //retourne true si il y a collision
    float distance = b1.positionBoule.Dist(b2.positionBoule);
    float sommeRad = b1.diam + b2.diam ;
    return distance < sommeRad / 2;
}
void Jeu::resultCollision(boule& b1, boule& b2) {
    // Vecteur normalisé de la collision (de b1 vers b2)
    Vec2 Norm = (b2.positionBoule - b1.positionBoule).normalized();

    // Vitesses vectorielles initiales
    Vec2 v1 = b1.directionBoule * b1.vitesseBoule;
    Vec2 v2 = b2.directionBoule * b2.vitesseBoule;

    // Vecteur relatif et produit scalaire
    Vec2 relativeVel = v1 - v2;
    float dotProd = relativeVel.ProduitScalaire(Norm);

    // Collision seulement si les boules se rapprochent
    if (dotProd >= 0) return;

    // Calcul de l'impulsion (avec masses)
    float j = -(1.0f + 0.8f) * dotProd / (1.0f / b1.masse + 1.0f / b2.masse); // 0.8 = coefficient de restitution

    // Mise à jour des vitesses
    Vec2 new_v1 = v1 - Norm * (j / b1.masse); // Direction correcte
    Vec2 new_v2 = v2 + Norm * (j / b2.masse); 

    // Normalisation et mise à jour des directions/vitesses
    float speed1 = new_v1.Normal(); // ||v||²
    float speed2 = new_v2.Normal();

    b1.directionBoule = (speed1 > 0) ? new_v1.normalized() : Vec2(0, 0);
    b1.vitesseBoule = sqrt(speed1); // Racine carrée pour la norme réelle

    b2.directionBoule = (speed2 > 0) ? new_v2.normalized() : Vec2(0, 0);
    b2.vitesseBoule = sqrt(speed2);
}


void Jeu::GestionCollisionsBoules() {
    // Collisions entre la boule blanche et les boules jaunes
    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        if (checkCollision(BouleBlanche, BJ.getBjaunes()[i])) {
            resultCollision(BouleBlanche, BJ.getBjaunes()[i]);
        }
    }

    // Collisions entre la boule noire et les boules jauness
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        if (checkCollision(BouleNoire, BJ.getBjaunes()[i])) {
            resultCollision(BouleNoire, BJ.getBjaunes()[i]);
        }
    }

    // Collisions entre la boule blanche et les boules rouges
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        if (checkCollision(BouleBlanche, brouges[i])) {
            resultCollision(BouleBlanche, brouges[i]);
        }
    }
    
    // Collisions entre la boule noire et les boules rouges
    for (int i = 0; i < BR.getnbBR(); i++) {
        if (checkCollision(BouleNoire, brouges[i])) {
            resultCollision(BouleNoire, brouges[i]);
        }
    }


    // Collisions entre la boule blanche et la boule noire
    if (checkCollision(BouleBlanche, BouleNoire)) {
        resultCollision(BouleBlanche, BouleNoire);
    }

    // Collisions entre les boules jaunes et les boules rouges
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        for (int j = 0; j < BR.getnbBR(); j++) {
            if (checkCollision(bjaunes[i], brouges[j])) {
                resultCollision(bjaunes[i], brouges[j]);
            }
        }
    }

    // Collisions entre les boules jaunes elles-mêmes
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        for (int j = i + 1; j < BJ.getnbBJ(); j++) {
            if (checkCollision(bjaunes[i], bjaunes[j])) {
                resultCollision(bjaunes[i], bjaunes[j]);
            }
        }
    }

    // Collisions entre les boules rouges elles-mêmes
    for (int i = 0; i < BR.getnbBR(); i++) {
        for (int j = i + 1; j < BR.getnbBR(); j++) {
            if (checkCollision(brouges[i], brouges[j])) {
                resultCollision(brouges[i], brouges[j]);
            }
        }
    }
}

void Jeu::GestionCollisionsBords() {
    // Gestion des collisions pour la boule blanche
    if (BouleBlanche.positionBoule.x - BouleBlanche.diam / 2 < 0 || BouleBlanche.positionBoule.x + BouleBlanche.diam / 2 > DIM_TABLE_X) {
        BouleBlanche.directionBoule.x *= -1;
    }
    if (BouleBlanche.positionBoule.y - BouleBlanche.diam / 2 < 0 || BouleBlanche.positionBoule.y + BouleBlanche.diam / 2 > DIM_TABLE_Y) {
        BouleBlanche.directionBoule.y *= -1; 
    }

    // Gestion des collisions pour la boule noire
    if (BouleNoire.positionBoule.x - BouleNoire.diam / 2 < 0 || BouleNoire.positionBoule.x + BouleNoire.diam / 2 > DIM_TABLE_X) {
        BouleNoire.directionBoule.x *= -1;
    }
    if (BouleNoire.positionBoule.y - BouleNoire.diam / 2 < 0 || BouleNoire.positionBoule.y + BouleNoire.diam / 2 > DIM_TABLE_Y) {
        BouleNoire.directionBoule.y *= -1; 
    }

    // Gestion des collisions pour les boules jaunes
    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        if (bjaunes[i].positionBoule.x - bjaunes[i].diam / 2 < 0 || bjaunes[i].positionBoule.x + bjaunes[i].diam / 2 > DIM_TABLE_X) {
            bjaunes[i].directionBoule.x *= -1;
        }
        if (bjaunes[i].positionBoule.y - bjaunes[i].diam / 2 < 0 || bjaunes[i].positionBoule.y + bjaunes[i].diam / 2 > DIM_TABLE_Y) {
            bjaunes[i].directionBoule.y *= -1; 
        }
    }

    // Gestion des collisions pour les boules rouges
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        if (brouges[i].positionBoule.x - brouges[i].diam / 2 < 0 || brouges[i].positionBoule.x + brouges[i].diam / 2 > DIM_TABLE_X) {
            brouges[i].directionBoule.x *= -1; 
        }
        if (brouges[i].positionBoule.y - brouges[i].diam / 2 < 0 || brouges[i].positionBoule.y + brouges[i].diam / 2 > DIM_TABLE_Y) {
            brouges[i].directionBoule.y *= -1; 
        }
    }
}