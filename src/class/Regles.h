#ifndef _REGLES_H
#define _REGLES_H

#include "boule.h"
#include <string>
#include <vector>

// Déclaration anticipée pour éviter l'inclusion circulaire
class Jeu;

class Regles {
public:
enum class EtatJeu {
DEBUT,
CHOIX_COULEUR,
TOUR_JOUEUR_JAUNE,
TOUR_JOUEUR_ROUGE,
FIN_PARTIE
};

enum class Faute {
AUCUNE,
BLANCHE_TOMBEE,
NOIRE_TOMBEE,
MAUVAISE_COULEUR,
PAS_DE_COLLISION
};

Regles();

// Gestion du jeu
void debutPartie(Jeu& jeu);
void finTour(Jeu& jeu);
void changerTour();
void verifierFinPartie(Jeu& jeu);

// Vérification des règles
Faute verifierCoup(Jeu& jeu, const boule& bouleFrappee);
void appliquerSanction(Jeu& jeu, Faute faute);
void assignerCouleur(bool estJaune);

// Gestion dynamique des règles
void mettreAJourRegles(Jeu& jeu);
void activerRegleSpecial();

// Accesseurs
EtatJeu getEtatActuel() const;
std::string getDescriptionEtat() const;
int getScore(bool estJaune) const;
bool estCouleurAssignee() const;

private:
EtatJeu etatActuel;
int scoreJaune;
int scoreRouge;
bool couleurDeterminee;
int boulesRestantesJaunes;
int boulesRestantesRouges;
std::vector<std::string> historiqueFautes;

void initialiserReglesBase();
bool verifierVictoire(bool estJaune) const;
void gererBouleNoire(Jeu& jeu);
};

#endif