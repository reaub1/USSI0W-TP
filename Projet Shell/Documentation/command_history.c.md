# Documentation : command_history.c

## Description
Ce fichier implémente la gestion de l'historique des commandes pour le shell. Il permet de sauvegarder, charger et afficher l'historique des commandes exécutées par l'utilisateur.

## Fonctions principales

### `char *get_history_path()`
- **Rôle** : Retourne le chemin du fichier d'historique.
- **Fonctionnement** : Récupère la variable d'environnement `HOME` et concatène avec le nom du fichier d'historique.
- **Gestion des erreurs** : Retourne `NULL` si `HOME` n'est pas défini ou en cas d'échec d'allocation mémoire.

### `void load_command_history()`
- **Rôle** : Charge l'historique des commandes depuis un fichier.
- **Fonctionnement** : Lit le fichier d'historique ligne par ligne et stocke les commandes.
- **Gestion des erreurs** : Vérifie l'existence du fichier et gère les erreurs d'ouverture et de lecture.

### `void save_command_to_history(const char *command)`
- **Rôle** : Sauvegarde une commande dans le fichier d'historique.
- **Fonctionnement** : Ajoute la commande au fichier d'historique en mode `append`.
- **Gestion des erreurs** : Vérifie si le fichier peut être ouvert et écrit correctement.

### `void show_history()`
- **Rôle** : Affiche l'historique des commandes exécutées.
- **Fonctionnement** : Lit le fichier et affiche chaque commande avec son index.
- **Gestion des erreurs** : Affiche un message si aucun historique n'est disponible.

## Variables principales
- `HISTORY_FILE` : Définit le chemin relatif du fichier d'historique.

##  Exemple d'utilisation

```sh
my_sh> ls
my_sh> history
1 ls
my_sh> echo "Bonjour"
my_sh> history
1 ls
2 echo "Bonjour"
```

##  Gestion des erreurs

- `fopen()` vérifié pour éviter les erreurs d'accès au fichier.
- `fclose()` est également vérifié pour éviter les fichiers corrompus.
---
