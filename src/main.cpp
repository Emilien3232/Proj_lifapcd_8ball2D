#include <SDL2/SDL.h>
#include <iostream>
#include "class/Jeu.h"

const int SCREEN_WIDTH = 1000;  // Largeur de la fenêtre
const int SCREEN_HEIGHT = 546;  // Hauteur de la fenêtre

void dessinerTable(SDL_Renderer* renderer) {
    // Dessiner la table (un rectangle vert)
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);  // Couleur verte
    SDL_Rect tableRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &tableRect);
}

void dessinerBoule(SDL_Renderer* renderer, const boule& b, SDL_Color couleur) {
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    for (int w = 0; w < b.diam ; w++) {
        for (int h = 0; h < b.diam ; h++) {
            int dx = b.diam / 2 - w;  // Distance horizontale par rapport au centre
            int dy = b.diam / 2 - h;  // Distance verticale par rapport au centre
            if ((dx * dx + dy * dy) <= ((b.diam / 2) * (b.diam / 2))) {
                SDL_RenderDrawPoint(renderer, b.positionBoule.x + dx, b.positionBoule.y + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow(
        "Simulation de Billard",            // Titre de la fenêtre
        SDL_WINDOWPOS_CENTERED,             // Position X
        SDL_WINDOWPOS_CENTERED,             // Position Y
        SCREEN_WIDTH,                       // Largeur
        SCREEN_HEIGHT,                      // Hauteur
        SDL_WINDOW_SHOWN                    // Flags
    );

    if (window == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialisation du jeu
    Jeu jeu;
    jeu.INITJEU();

    // Boucle principale du jeu
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Mise à jour du jeu
        if (!jeu.UPDATEJEU()) {
            quit = true;  // Fin du jeu
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fond noir
        SDL_RenderClear(renderer);

        // Dessiner les éléments du jeu (à implémenter)
        dessinerTable(renderer);

        // Dessiner les boules
        SDL_Color couleurJaune = {255, 255, 0, 255};  // Jaune
        SDL_Color couleurRouge = {255, 0, 0, 255};    // Rouge
        SDL_Color couleurBlanche = {255, 255, 255, 255};  // Blanc
        SDL_Color couleurNoire = {0, 0, 0, 255};      // Noir

        dessinerBoule(renderer, jeu.getBouleBlanche(), couleurBlanche);
        dessinerBoule(renderer, jeu.getBouleNoire(), couleurNoire);

        boule* bjaunes = jeu.getBJ().getBjaunes();
        for (int i = 0; i < jeu.getBJ().getnbBJ(); i++) {
            dessinerBoule(renderer, bjaunes[i], couleurJaune);
        }

        boule* brouges = jeu.getBR().getBrouges();
        for (int i = 0; i < jeu.getBR().getnbBR(); i++) {
            dessinerBoule(renderer, brouges[i], couleurRouge);
        }

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);

        // Limiter le taux de rafraîchissement
        SDL_Delay(16);  // Environ 60 FPS
    }

    // Nettoyage et fermeture
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}