#include <stdio.h>
#include <string.h> // Pour strcpy
#include <stdlib.h> // Pour rand() juste pour varier un peu les données si on voulait

// --- Variables Globales Mal Organisées ---
// On pourrait utiliser des structures, mais non, faisons ça salement.
#define MAX_ITEMS 3
#define MAX_PROPRIETES 2 // Par exemple: poids et prix
#define MAX_NOM_LONGUEUR 50

char noms_items[MAX_ITEMS][MAX_NOM_LONGUEUR];
float proprietes_items[MAX_ITEMS][MAX_PROPRIETES]; // prop[0] = poids, prop[1] = prix
int quantites_items[MAX_ITEMS];
int item_actuel_index = 0; // Pour "traiter" un item à la fois globalement

float total_valeur_inventaire_calcul_temporaire = 0.0;
int item_plus_cher_index_temp = -1;
float prix_max_temporaire = 0.0;

// Une fonction qui fait un peu de tout, et mal.
void initialiser_et_calculer_partiellement() {
    printf("Initialisation confuse des données...\n");

    // Item 1
    strcpy(noms_items[0], "Pommes Super Deluxe");
    proprietes_items[0][0] = 0.15; // poids en kg
    proprietes_items[0][1] = 2.50; // prix unitaire
    quantites_items[0] = 120;

    // Item 2
    strcpy(noms_items[1], "Bananes Bio Équitables");
    proprietes_items[1][0] = 0.18; // poids
    proprietes_items[1][1] = 3.10; // prix
    quantites_items[1] = 75;

    // Item 3
    strcpy(noms_items[2], "Oranges Acides");
    proprietes_items[2][0] = 0.20; // poids
    proprietes_items[2][1] = 1.90; // prix
    quantites_items[2] = 200;

    // Calcul partiel de la valeur totale, qui pourrait être fait ailleurs ou mieux
    for (item_actuel_index = 0; item_actuel_index < MAX_ITEMS; item_actuel_index++) {
        total_valeur_inventaire_calcul_temporaire += proprietes_items[item_actuel_index][1] * quantites_items[item_actuel_index];
        // Recherche mal placée de l'item le plus cher
        if (proprietes_items[item_actuel_index][1] > prix_max_temporaire) {
            prix_max_temporaire = proprietes_items[item_actuel_index][1];
            item_plus_cher_index_temp = item_actuel_index;
        }
    }
    printf("Initialisation et calculs préliminaires terminés (ou pas).\n\n");
}

// Fonction d'affichage qui se base sur l'état global
void afficher_details_inventaire_en_desordre() {
    printf("--- Détails de l'Inventaire (via globales) ---\n");
    // On réutilise item_actuel_index, ce qui est une mauvaise idée si une autre fonction s'attend à ce qu'il ait une autre valeur
    for (item_actuel_index = 0; item_actuel_index < MAX_ITEMS; item_actuel_index++) {
        printf("Item: %s\n", noms_items[item_actuel_index]);
        printf("  Poids unitaire: %.2f kg\n", proprietes_items[item_actuel_index][0]); // Indice magique 0
        printf("  Prix unitaire: %.2f EUR\n", proprietes_items[item_actuel_index][1]);  // Indice magique 1
        printf("  Quantité: %d\n", quantites_items[item_actuel_index]);
        float valeur_stock_item = proprietes_items[item_actuel_index][1] * quantites_items[item_actuel_index];
        printf("  Valeur du stock pour cet item: %.2f EUR\n", valeur_stock_item);
        printf("------------\n");
    }
}

// Encore une fonction qui pourrait être fusionnée ou mieux structurée
void afficher_resume_global() {
    printf("\n--- Résumé de l'Inventaire (basé sur des calculs globaux antérieurs) ---\n");
    printf("Valeur totale de l'inventaire (pré-calculée globalement): %.2f EUR\n", total_valeur_inventaire_calcul_temporaire);

    if (item_plus_cher_index_temp != -1) {
        printf("L'item le plus cher unitairement est: %s (%.2f EUR)\n",
               noms_items[item_plus_cher_index_temp],
               proprietes_items[item_plus_cher_index_temp][1]); // Accès direct via l'index global
    } else {
        printf("Aucun item trouvé pour déterminer le plus cher (ce qui ne devrait pas arriver ici).\n");
    }

    // Un calcul redondant ou mal placé
    float poids_total = 0;
    for(int i=0; i < MAX_ITEMS; ++i) { // Oups, on utilise i alors qu'on avait item_actuel_index... confusion !
        poids_total += proprietes_items[i][0] * quantites_items[i];
    }
    printf("Poids total approximatif de l'inventaire: %.2f kg\n", poids_total);
}


int main() {
    // Tout est fait dans un ordre un peu étrange et dépendant des variables globales
    initialiser_et_calculer_partiellement();

    // On pourrait s'attendre à ce que item_actuel_index soit à MAX_ITEMS ici
    // Mais la fonction suivante va le réinitialiser. Confusion !
    afficher_details_inventaire_en_desordre();

    // On se fie aux calculs faits dans la première fonction et stockés dans des globales
    afficher_resume_global();

    // Manipulation finale d'une variable globale sans trop de contexte
    item_actuel_index = -99; // Valeur sentinelle inutile ici
    printf("\nVariable globale 'item_actuel_index' mise à %d pour aucune raison apparente.\n", item_actuel_index);

    printf("\nProgramme terminé. Les étudiants ont du pain sur la planche !\n");
    return 0;
}

// Compilé avec gcc -Wall -Wextra -o mauvais_programme mauvais_programme.c
// Puis exécuté avec ./mauvais_programme