#include <SDL2/SDL.h>
#include <iostream>
#include "class/Jeu.h"
#include "class/Joueur.h"

const float DIAM_BOULE = 20.5; //diametre des boules
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 746;
const int DIM_TABLE_X = 1000;
const int DIM_TABLE_Y = 546;

// Variables globales
bool isLineFrozen = false;
Vec2 frozenLinePos(0, 0);
float VB = 3.f;
SDL_Color CLR ={0,0,0,255};

void dessinerTable(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_Rect tableRect = {0, 0, DIM_TABLE_X, DIM_TABLE_Y};
    SDL_RenderFillRect(renderer, &tableRect);
}

void dessinerTrajectoire(SDL_Renderer* renderer, boule& b, int X, int Y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    if(X < DIM_TABLE_X && Y < DIM_TABLE_Y) {
        SDL_RenderDrawLine(renderer, b.positionBoule.x, b.positionBoule.y, X, Y);
    }
}

void dessinerBoule(SDL_Renderer* renderer, const boule& b, SDL_Color couleur) {
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    for (int w = 0; w < b.diam; w++) {
        for (int h = 0; h < b.diam; h++) {
            int dx = b.diam / 2 - w;
            int dy = b.diam / 2 - h;
            if ((dx * dx + dy * dy) <= ((b.diam / 2) * (b.diam / 2))) {
                SDL_RenderDrawPoint(renderer, b.positionBoule.x + dx, b.positionBoule.y + dy);
            }
        }
    }
}

void dessinerTrous(SDL_Renderer* renderer, TableDeJeu& table) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    trou* trous = table.gettrous();

    for (int i = 0; i < 6; i++) {
        int x = (int)trous[i].posTrou.x;
        int y = (int)trous[i].posTrou.y;
        int diam = (int)(trous[i].rayonTrou * 2);

        for (int w = 0; w < diam; w++) {
            for (int h = 0; h < diam; h++) {
                int dx = w - diam / 2;
                int dy = h - diam / 2;
                if ((dx * dx + dy * dy) <= (diam / 2) * (diam / 2)) {
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
}

void JaugeVitesse (SDL_Renderer* renderer , float V) {
    SDL_SetRenderDrawColor(renderer, 255, 255 , 0, 255);  
    SDL_Rect jaugeRect = {DIM_TABLE_X +100 , DIM_TABLE_Y , 10 , (int) ((-1) * 5 - V * (DIM_TABLE_Y / 47)) };
    SDL_RenderFillRect(renderer, &jaugeRect);
}

void dessinerRect(SDL_Renderer* renderer ,SDL_Color CLR){
    SDL_SetRenderDrawColor(renderer , CLR.r , CLR.g , CLR.b , CLR.a);
    SDL_Rect Rect = {DIM_TABLE_X / 2 , DIM_TABLE_Y + 70 , 20 , 20};
    SDL_RenderFillRect(renderer , &Rect);
}


bool chgmt_joueur(Jeu jeu , Joueur& JoueurActuel){
    if(jeu.getBouleBlanche().est_tombé){return true;}
    return false;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("8ball_2D",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Erreur fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Initialisation du jeu & des joueurs
    Jeu jeu;
    jeu.INITJEU();

    Joueur Numero1 = Joueur(0,1,jeu.getBR().getBrouges(),0,true);
    Joueur Numero2 = Joueur(1,0,jeu.getBJ().getBjaunes(),0,false);

    //debut boucle principale
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (jeu.getBouleBlanche().diam == 0.0f) { //si la boule blanche est tombée 
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    
                    if (mouseX >= 0 && mouseX <= DIM_TABLE_X && mouseY >= 0 && mouseY <= DIM_TABLE_Y) { //si le curseur est dans la fenetre
                        jeu.getBouleBlanche().positionBoule = Vec2(mouseX, mouseY);
                        jeu.getBouleBlanche().diam = DIAM_BOULE;
                        jeu.getBouleBlanche().vitesseBoule = Vec2(0, 0);
                        std::cout << "la boule blanche est replacée !!" << std::endl;
                        jeu.getBouleBlanche().est_tombé = false; // remettre la boule blanche à l'état initial
                    }
                }
                else { // si la boule blanche n'est pas tombée
                    Vec2 velocity = jeu.getBouleBlanche().vitesseBoule;
                    float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                    if (speed < 0.01f) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        frozenLinePos = Vec2(mouseX, mouseY);
                        isLineFrozen = true;

                        
                        Vec2 ballPos = jeu.getBouleBlanche().positionBoule;
                        Vec2 direction = frozenLinePos - ballPos;
                        direction = direction.normalized();
                        
                        jeu.getBouleBlanche().vitesseBoule = direction * VB;
                    }
                }
            }
            else if(event.type == SDL_KEYDOWN){ 
                if ( event.key.keysym.sym == SDLK_UP) { //gere la vitesse appliquer à la boule blanche (via var glob "VB")
                    VB += 2.f;
                    std::cout<<"vitesse : "<<VB<<std::endl;
                }
                if (event.key.keysym.sym == SDLK_DOWN) { //gere la vitesse appliquer à la boule blanche (via var glob "VB")
                    VB -= 2.f;
                    std::cout<<"vitesse : "<<VB<<std::endl;
                }
                VB = std::max(5.f , std::min(VB , 45.f)); // VB appartient à [5;45]
            }


        

            else if (chgmt_joueur(jeu, (Numero1.getActif() ? Numero1 : Numero2))) {
                // Changement de joueur
                if (Numero1.getActif()) {
                    Numero1.setActif(false);
                    Numero2.setActif(true);
                    CLR = {255, 255, 0, 255};
                }
                else {
                    Numero1.setActif(true);
                    Numero2.setActif(false);
                    CLR = {255, 0, 0, 255};
                }
            }
        } // fin "while (SDL_PollEvent(&event)) { "

        if (!jeu.UPDATEJEU()) { // si update retourne 0 on arrete le jeu
            quit = true;
        }

        Vec2 velocity = jeu.getBouleBlanche().vitesseBoule;
        float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (speed >= 0.01f) {
            isLineFrozen = false;
        }

        SDL_SetRenderDrawColor(renderer, 105, 0, 0, 255);
        SDL_RenderClear(renderer);

        //affichage
        dessinerTable(renderer);
        dessinerTrous(renderer, jeu.getTDJ());
        JaugeVitesse(renderer , VB);
        dessinerRect(renderer, CLR);
        if (jeu.getBouleBlanche().diam > 0.0f) {
            if (isLineFrozen) {
                dessinerTrajectoire(renderer, jeu.getBouleBlanche(), frozenLinePos.x, frozenLinePos.y);
            } else {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                dessinerTrajectoire(renderer, jeu.getBouleBlanche(), mouseX, mouseY);
            }
        }


        //affichage des boules
        SDL_Color couleurJaune = {255, 255, 0, 255};
        SDL_Color couleurRouge = {255, 0, 0, 255};
        SDL_Color couleurBlanche = {255, 255, 255, 255};
        SDL_Color couleurBlancheBIS = {255, 255, 255, 50};
        SDL_Color couleurNoire = {0, 0, 0, 255};

        if (jeu.getBouleBlanche().diam == 0.0f) {
            dessinerBoule(renderer, jeu.getBouleBlanche(), couleurBlancheBIS);
        }
        else {dessinerBoule(renderer, jeu.getBouleBlanche(), couleurBlanche);}

        dessinerBoule(renderer, jeu.getBouleNoire(), couleurNoire);

        boule* bjaunes = jeu.getBJ().getBjaunes();
        for (int i = 0; i < jeu.getBJ().getnbBJ(); i++) {
            dessinerBoule(renderer, bjaunes[i], couleurJaune);
        }

        boule* brouges = jeu.getBR().getBrouges();
        for (int i = 0; i < jeu.getBR().getnbBR(); i++) {
            dessinerBoule(renderer, brouges[i], couleurRouge);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        //fin affichage
    }//fin "while (!quit) {"

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}