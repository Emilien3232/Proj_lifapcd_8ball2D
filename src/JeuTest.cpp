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
const float PB = 0.001f;

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

    Vec2 direction = (BouleNoire.positionBoule - BouleBlanche.positionBoule).normalized();

    //on defini la boule blanche et la noir sur des positions precise qui serviront de repere pour les autres
    BouleBlanche = boule(0 , DIAM_BOULE , PB , Vec2(DIM_TABLE_X * 3 / 4 , DIM_TABLE_Y / 2) , Vec2(-1 , 0) , 10.f); //le vecteur de direction ne doit pas impacté la force de frappe d'un boule mais jjuste sa direction (regler ce probleme)

    BouleNoire = boule(1 , DIAM_BOULE , PB , Vec2(DIM_TABLE_X /4 , DIM_TABLE_Y / 2), Vec2(0,0) , 0);
    

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
 

    bouletombéeBLCH(BouleBlanche);

    //if(bouletombéNR(BouleNoire)) {return false;}   //marche mais je le met en commentaire pour pour pouvoir regarder le programme sans que sa s'arrete trop rapidement

    return true;

}

void Jeu::MAJpositionBoules() { 
    BouleBlanche.positionBoule = BouleBlanche.positionBoule + (BouleBlanche.directionBoule * BouleBlanche.vitesseBoule);
    BouleBlanche.vitesseBoule = BouleBlanche.vitesseBoule * SCAL_F;

    BouleNoire.positionBoule = BouleNoire.positionBoule +(BouleNoire.directionBoule * BouleNoire.vitesseBoule);
    BouleNoire.vitesseBoule = BouleNoire.vitesseBoule * SCAL_F;
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

Vec2 Jeu::TrouverVitessePara(const Vec2 VecDirection , const float vitesse ,  const Vec2 Norm) {
    return (Norm * VecDirection.ProduitScalaire(Norm)).normalized() * vitesse; 
}

Vec2 Jeu::TrouverVitessePerp(const Vec2 VecDirection , const float vitesse , const Vec2 Norm) {
    return (VecDirection - TrouverVitessePara(VecDirection , vitesse , Norm)).normalized() * vitesse; 
}

bool Jeu::checkCollision(const boule b1 , const boule b2) { //retourne true si il y a collision
    float distance = b1.positionBoule.Dist(b2.positionBoule);
    float sommeRad = b1.diam + b2.diam ;
    return distance < sommeRad / 2;
}

void Jeu::resultCollision(boule& b1, boule& b2) {
    Vec2 VecDeCollision = b2.positionBoule - b1.positionBoule; 
    Vec2 VDCnormalise = VecDeCollision.normalized();

    // Décomposer les vitesses en composantes parallèles et perpendiculaires
    Vec2 vitesse1Para = TrouverVitessePara(b1.directionBoule, b1.vitesseBoule , VDCnormalise);
    Vec2 vitesse1Perp = TrouverVitessePerp(b1.directionBoule, b1.vitesseBoule , VDCnormalise);
    Vec2 vitesse2Para = TrouverVitessePara(b2.directionBoule, b2.vitesseBoule , VDCnormalise);
    Vec2 vitesse2Perp = TrouverVitessePerp(b2.directionBoule, b2.vitesseBoule , VDCnormalise);

    // Calculer les nouvelles magnitudes des vitesses 
    float m1 = b1.masse;
    float m2 = b2.masse;
    float v1 = vitesse1Para.Normal(); // Magnitude de la composante parallèle de b1
    float v2 = vitesse2Para.Normal(); // Magnitude de la composante parallèle de b235
   
    float v1_prime = (2 * m2 * v2) / (m1 + m2);
    float v2_prime = (2 * m1 * v1) / (m1 + m2);
    
    // echanger les composantes parallèles et appliquer les nouvelles vitesses
    b1.directionBoule = (vitesse2Para + vitesse1Perp).normalized();
    b1.vitesseBoule = v1_prime;
    b2.directionBoule = (vitesse1Para + vitesse2Perp).normalized();
    b2.vitesseBoule = v2_prime;

    //eviter les superpositions
    float distance = b1.positionBoule.Dist(b2.positionBoule);
    float sommeRad = b1.diam + b2.diam;
    if (distance < sommeRad / 2) {
        float overlap = (sommeRad / 2) - distance;
        b1.positionBoule = b1.positionBoule - VDCnormalise * (overlap / 2);
        b2.positionBoule = b2.positionBoule + VDCnormalise * (overlap / 2);
    }

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