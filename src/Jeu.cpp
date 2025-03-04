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
    BouleBlanche = boule(0 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X * 3 / 4 , DIM_TABLE_Y / 2) , Vec2(0,0) , Vec2(0,0));
    BouleNoire = boule(1 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - 2.f , DIM_TABLE_Y / 2), Vec2(0,0) ,Vec2(0,0));
    
    //on defini les boules jaunes
    boule* bjaunes = new boule [7];
    bjaunes[0] = boule(1 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 , DIM_TABLE_Y / 2), Vec2(0,0) ,Vec2(0,0)); //en tete du triangle (les auteres boules sont placés en fonction de celle ci)
    bjaunes[1] = boule(2 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE - ECART , DIM_TABLE_Y / 2 + DIAM_BOULE + ECART), Vec2(0,0) , Vec2(0,0)); 
    bjaunes[2] = boule(3 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE - ECART , DIM_TABLE_Y / 2 - DIAM_BOULE - ECART), Vec2(0,0) , Vec2(0,0));
    bjaunes[3] = boule(4 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - DOUBLE_ECART , DIM_TABLE_Y / 2 - DIAM_BOULE - ECART), Vec2(0,0) ,Vec2(0,0)); 
    bjaunes[4] = boule(5 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 2 - DOUBLE_ECART , DIM_TABLE_Y / 2 + DIAM_BOULE + ECART), Vec2(0,0) ,Vec2(0,0));
    bjaunes[5] = boule(6 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 + DIAM_BOULE + ECART), Vec2(0,0) ,Vec2(0,0)); 
    bjaunes[6] = boule(7 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 + DIAM_BOULE * 2 + DOUBLE_ECART), Vec2(0,0) ,Vec2(0,0));
    BJ = boulesJaunes(bjaunes , 7);

    //et finalement les boules rouges 
    boule* brouges = new boule [7];
    brouges[0] = boule(13 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART , DIM_TABLE_Y / 2) , Vec2(0,0) , Vec2(0,0));
    for(unsigned int i = 1 ; i <= 2 ; i++){
        brouges[i] = boule(13+i , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART , DIM_TABLE_Y / 2 + i * (ECART + DIAM_BOULE)) , Vec2(0,0) , Vec2(0,0));
    }
    for(unsigned int i = 1 ; i <= 2 ; i++){
        brouges[2+i] = boule(13-i , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - 4 * DIAM_BOULE - QUAD_ECART , DIM_TABLE_Y / 2 - i * (ECART + DIAM_BOULE)) , Vec2(0,0) , Vec2(0,0));
    }
    brouges[5] = boule(10 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 - DIAM_BOULE * 2 - DOUBLE_ECART), Vec2(0,0) ,Vec2(0,0));
    brouges[6] = boule(9 , DIAM_BOULE , 1.f , Vec2(DIM_TABLE_X / 4 - DIAM_BOULE * 3 - TRIPLE_ECART , DIM_TABLE_Y / 2 - DIAM_BOULE - ECART), Vec2(0,0) ,Vec2(0,0));
    BR = boulesRouges(brouges , 7);
}


void Jeu::test_INITJEU() { //je l'ai fait avec deepseek lui
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
    assert(bjaunes[1].positionBoule == Vec2(250 - 20.5 - 1, 273 + 20.5 + 1));
    assert(bjaunes[2].positionBoule == Vec2(250 - 20.5 - 1, 273 - 20.5 - 1));
    assert(bjaunes[3].positionBoule == Vec2(250 - 20.5 * 2 - 2, 273 - 20.5 - 1));
    assert(bjaunes[4].positionBoule == Vec2(250 - 20.5 * 2 - 2, 273 + 20.5 + 1));
    assert(bjaunes[5].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 + 20.5 + 1));
    assert(bjaunes[6].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 + 20.5 * 2 + 2));
    std::cout << "Test 8 : Positions des boules jaunes OK" << std::endl;

    // Test 9 : Vérification des positions des boules rouges
    boule* brouges = boulesRouges.getBrouges();
    assert(brouges[0].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273));
    assert(brouges[1].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 + 1 + 20.5));
    assert(brouges[2].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 + 2 * (1 + 20.5)));
    assert(brouges[3].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 - 1 * (1 + 20.5)));
    assert(brouges[4].positionBoule == Vec2(250 - 4 * 20.5 - 4, 273 - 2 * (1 + 20.5)));
    assert(brouges[5].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 - 20.5 * 2 - 2));
    assert(brouges[6].positionBoule == Vec2(250 - 20.5 * 3 - 3, 273 - 20.5 - 1));
    std::cout << "Test 9 : Positions des boules rouges OK" << std::endl;

    std::cout << "Tous les tests de régression ont réussi !" << std::endl;
}

bool Jeu::UPDATEJEU() {
    
    //update les positions des boules
    MAJpositionBoules(); 

    //gerer les collisions des boules entre elles et contre les bords
    GestionCollisionsBords();
    GestionCollisionsBoules();
 
    /*
    if(BouleBlanche.vitesseBoule.x < SEUIL_VITESSE && BouleBlanche.vitesseBoule.y < SEUIL_VITESSE) {
        //donner l'option au joueur de tirer (appliquer un vecteur vitesse la ou la souris pointe)
    }
    */

    //verifie les situatons des boules (tombés ou pas), si cette situation implique la fin du jeu => return false
    if (BJ.getnbBJ() == 0 ) { return false ;}
    else {
        for(int i=0;i<BJ.getnbBJ();i++){
            bouletombé(BJ);
        }
    }
    if (BR.getnbBR() == 0) {return false ;}
    else {
        for(int i=0;i<BR.getnbBR();i++){
            bouletombé(BR);
        }
    }
    bouletombéBLCH(BouleBlanche);
    if(bouletombéNR(BouleNoire)) {return false;}

    return true;

}

void Jeu::MAJpositionBoules() { //pour les frottements revenir ici et appliquer un scalaire à la vitesse des boules , indépendament de l'actu de position je pense
    BouleBlanche.positionBoule = BouleBlanche.positionBoule + BouleBlanche.vitesseBoule;
    BouleBlanche.vitesseBoule = BouleBlanche.vitesseBoule * SCAL_F;


    BouleNoire.positionBoule = BouleNoire.positionBoule + BouleNoire.vitesseBoule;
    BouleNoire.vitesseBoule = BouleNoire.vitesseBoule * SCAL_F;

    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        bjaunes[i].positionBoule = bjaunes[i].positionBoule + bjaunes[i].vitesseBoule;
        bjaunes[i].vitesseBoule = bjaunes[i].vitesseBoule * SCAL_F;
    }
  
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        brouges[i].positionBoule = brouges[i].positionBoule + brouges[i].vitesseBoule;
        brouges[i].vitesseBoule = brouges[i].vitesseBoule * SCAL_F;
    }
}

void Jeu::bouletombé(boulesJaunes B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.getBjaunes()[i].positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            B.setnbBJ(B.getnbBJ() - 1);
            std::cout<<"la boule "<<B.getBjaunes()[i].IDnombre<<" est tombée"<<std::endl;
            B.getBjaunes()[i].positionBoule = Vec2(0,0); //faire disparaitre la boule (je la met dans un coin )
            B.getBjaunes()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas (pas sur)
        }
    }
}


void Jeu::bouletombé(boulesRouges B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.getBrouges()[i].positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            B.setnbBR(B.getnbBR() - 1);
            std::cout<<"la boule "<<B.getBrouges()[i].IDnombre<<" est tombée"<<std::endl;
            B.getBrouges()[i].positionBoule = Vec2(0,0); //faire disparaitre la boule (je la met dans un coin )
            B.getBrouges()[i].diam = 0.f;  //et mets son rayon si petit qu'elle ne s'affcihcera pas (pas sur)
        }
    }
}

void Jeu::bouletombéBLCH(boule B) {
    for (int i = 0 ; i < 6 ; i++){
        if(B.positionBoule.Dist(TDJ.gettrous()[i].posTrou) < DIAM_BOULE) { //si la boule B est dans un trou 
            std::cout<<"la boule blanche est tombée !!"<<std::endl;
            B.positionBoule = Vec2(DIM_TABLE_X * 3 / 4 , DIM_TABLE_Y / 4); //si la boule blanche je la remet à sa position de départ
            B.vitesseBoule = Vec2(0,0);
        }
    }
}

bool Jeu::bouletombéNR(boule B) {
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
    float sommeRad = b1.diam + b2.diam -1000;
    return distance < sommeRad;
}

void Jeu::resultCollision(boule& b1, boule& b2) { //applique les nouvelles vitesses après une collision entre deux boules 
    
    b1.vitesseBoule =  b1.vitesseBoule + Vec2(1,1);
    b2.vitesseBoule = b2.vitesseBoule + Vec2(1,1);
}

void Jeu::GestionCollisionsBoules() {
    // Collisions entre la boule blanche et les boules jaunes
    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        if (checkCollision(BouleBlanche, BJ.getBjaunes()[i])) {
            resultCollision(BouleBlanche, BJ.getBjaunes()[i]);
        }
    }

    // Collisions entre la boule blanche et les boules rouges
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        if (checkCollision(BouleBlanche, brouges[i])) {
            resultCollision(BouleBlanche, brouges[i]);
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
        BouleBlanche.vitesseBoule.x *= -1;
    }
    if (BouleBlanche.positionBoule.y - BouleBlanche.diam / 2 < 0 || BouleBlanche.positionBoule.y + BouleBlanche.diam / 2 > DIM_TABLE_Y) {
        BouleBlanche.vitesseBoule.y *= -1; 
    }

    // Gestion des collisions pour la boule noire
    if (BouleNoire.positionBoule.x - BouleNoire.diam / 2 < 0 || BouleNoire.positionBoule.x + BouleNoire.diam / 2 > DIM_TABLE_X) {
        BouleNoire.vitesseBoule.x *= -1;
    }
    if (BouleNoire.positionBoule.y - BouleNoire.diam / 2 < 0 || BouleNoire.positionBoule.y + BouleNoire.diam / 2 > DIM_TABLE_Y) {
        BouleNoire.vitesseBoule.y *= -1; 
    }

    // Gestion des collisions pour les boules jaunes
    boule* bjaunes = BJ.getBjaunes();
    for (int i = 0; i < BJ.getnbBJ(); i++) {
        if (bjaunes[i].positionBoule.x - bjaunes[i].diam / 2 < 0 || bjaunes[i].positionBoule.x + bjaunes[i].diam / 2 > DIM_TABLE_X) {
            bjaunes[i].vitesseBoule.x *= -1;
        }
        if (bjaunes[i].positionBoule.y - bjaunes[i].diam / 2 < 0 || bjaunes[i].positionBoule.y + bjaunes[i].diam / 2 > DIM_TABLE_Y) {
            bjaunes[i].vitesseBoule.y *= -1; 
        }
    }

    // Gestion des collisions pour les boules rouges
    boule* brouges = BR.getBrouges();
    for (int i = 0; i < BR.getnbBR(); i++) {
        if (brouges[i].positionBoule.x - brouges[i].diam / 2 < 0 || brouges[i].positionBoule.x + brouges[i].diam / 2 > DIM_TABLE_X) {
            brouges[i].vitesseBoule.x *= -1; 
        }
        if (brouges[i].positionBoule.y - brouges[i].diam / 2 < 0 || brouges[i].positionBoule.y + brouges[i].diam / 2 > DIM_TABLE_Y) {
            brouges[i].vitesseBoule.y *= -1; 
        }
    }
}