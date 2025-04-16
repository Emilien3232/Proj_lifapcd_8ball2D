#include "class/Regles.h"
#include "class/Jeu.h"
#include <iostream>

Regles::Regles() : etatActuel(EtatJeu::DEBUT),
                   scoreJaune(0),
                   scoreRouge(0),
                   couleurDeterminee(false),
                   boulesRestantesJaunes(7),
                   boulesRestantesRouges(7)
{
    initialiserReglesBase();
}

void Regles::initialiserReglesBase()
{
    historiqueFautes.clear();
}

void Regles::debutPartie(Jeu &jeu)
{
    etatActuel = EtatJeu::DEBUT;
    std::cout << "Nouvelle partie commencee\n";
}

void Regles::finTour(Jeu &jeu)
{
    // Implémentation de la logique de fin de tour
    changerTour();
}

void Regles::changerTour()
{
    switch (etatActuel)
    {
    case EtatJeu::TOUR_JOUEUR_JAUNE:
        etatActuel = EtatJeu::TOUR_JOUEUR_ROUGE;
        break;
    case EtatJeu::TOUR_JOUEUR_ROUGE:
        etatActuel = EtatJeu::TOUR_JOUEUR_JAUNE;
        break;
    default:
        break;
    }
}

Regles::Faute Regles::verifierCoup(Jeu &jeu, const boule &bouleFrappee)
{
    // Implémentation de la vérification des coups
    return Faute::AUCUNE;
}

void Regles::appliquerSanction(Jeu &jeu, Faute faute)
{
    // Implémentation des sanctions
}

void Regles::assignerCouleur(bool estJaune)
{
    couleurDeterminee = true;
    // Logique d'assignation de couleur
}

void Regles::mettreAJourRegles(Jeu &jeu)
{
    // Mise à jour dynamique des règles
}

void Regles::activerRegleSpecial()
{
    // Activation des règles spéciales
}

Regles::EtatJeu Regles::getEtatActuel() const
{
    return etatActuel;
}

std::string Regles::getDescriptionEtat() const
{
    switch (etatActuel)
    {
    case EtatJeu::DEBUT:
        return "Debut de partie";
    case EtatJeu::CHOIX_COULEUR:
        return "Choix de couleur";
    case EtatJeu::TOUR_JOUEUR_JAUNE:
        return "Tour joueur jaune";
    case EtatJeu::TOUR_JOUEUR_ROUGE:
        return "Tour joueur rouge";
    case EtatJeu::FIN_PARTIE:
        return "Fin de partie";
    default:
        return "Etat inconnu";
    }
}

int Regles::getScore(bool estJaune) const
{
    return estJaune ? scoreJaune : scoreRouge;
}

bool Regles::estCouleurAssignee() const
{
    return couleurDeterminee;
}

bool Regles::verifierVictoire(bool estJaune) const
{
    // Logique de vérification de victoire
    return false;
}

void Regles::gererBouleNoire(Jeu &jeu)
{
    // Logique de gestion de la boule noire
}