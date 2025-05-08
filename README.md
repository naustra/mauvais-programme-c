## Description

Ce programme simule la gestion d'un petit inventaire de produits pour un commerçant. Il enregistre quelques articles (par exemple, différents types de fruits), avec leur nom, leur poids, leur prix à l'unité et la quantité actuellement en stock. Ensuite, il calcule la valeur totale de cet inventaire, identifie quel article est le plus cher à l'unité, et affiche un résumé de ces informations, utiles pour savoir ce que l'on possède et ce qui a le plus de valeur.

## Problèmes à identifier et corriger

- **Variables Globales Abusives** : `noms_items`, `proprietes_items`, `quantites_items`, `item_actuel_index`, `total_valeur_inventaire_calcul_temporaire`, etc.
  - **Solution** : Créer une structure `Item` (ou `Produit`) et passer des tableaux de ces structures aux fonctions, ou des pointeurs vers elles.
- **"Données Mal Référencées" / Mauvaise Organisation des Données** : Les propriétés d'un même item (nom, poids, prix, quantité) sont réparties dans des tableaux parallèles. L'accès se fait par des indices synchronisés.
  - **Solution** : La structure `Item` résout cela.
- **Nombres Magiques** : `0` et `1` pour accéder au poids et au prix dans `proprietes_items`. `MAX_ITEMS`, `MAX_PROPRIETES` sont des defines, ce qui est mieux, mais pourraient être des `const int` ou gérés dynamiquement.
  - **Solution** : Pour les indices, utiliser des `enum` ou des `defines` plus descriptifs au sein de la structure si on ne peut pas avoir des champs nommés.
- **Fonctions "Fourre-Tout"** : `initialiser_et_calculer_partiellement` fait deux choses distinctes.
  - **Solution** : Séparer en `void initialiser_inventaire(void)` et `float calculer_valeur_totale(void)` (qui prendrait les données en argument).
- **Dépendances Cachées (Effets de Bord)** : Les fonctions modifient des variables globales, et l'ordre d'appel est crucial mais non explicite par les signatures de fonction. `item_actuel_index` est modifié et réutilisé de manière déroutante.
  - **Solution** : Les fonctions ne devraient modifier que les données passées en argument (ou leurs propres variables locales) et retourner des résultats.
- **Redondance / Inefficacité** : Le calcul du poids total dans `afficher_resume_global` pourrait être fait de manière plus propre et plus tôt si nécessaire. La recherche de l'item le plus cher est imbriquée bizarrement.
- **Noms de Variables et Fonctions** : Certains noms sont longs et indiquent le problème (`_calcul_temporaire`, `_en_desordre`), ce qui est un indice pour les étudiants.
- **Manque de modularité** : Tout est dans un seul fichier, mais c'est normal pour un petit exemple. La modularité viendra avec la création de fonctions claires.

## Comment améliorer le code

- Définir une `struct Item { char nom[MAX_NOM_LONGUEUR]; float poids; float prix; int quantite; };`
- Remplacer les tableaux parallèles par un `struct Item inventaire[MAX_ITEMS];`.
- Modifier les fonctions pour qu'elles acceptent des pointeurs/tableaux de `struct Item` et leur taille.
- `initialiser_et_calculer_partiellement` deviendrait `void initialiser_items(struct Item items[], int taille)` et `float calculer_valeur_totale(const struct Item items[], int taille)`.
- `afficher_details_inventaire_en_desordre` deviendrait `void afficher_details_item(const struct Item* item)` et `void afficher_inventaire(const struct Item items[], int taille)`.
- Éliminer `item_actuel_index` global. Les boucles utiliseront des variables locales.
- Et ainsi de suite...
