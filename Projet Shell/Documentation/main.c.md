# Documentation : main.c

## Description
Ce fichier contient le point d'entrée principal du shell. Il gère l'initialisation, la boucle d'attente des commandes et leur exécution.

## Fonctions principales

### `int main(int argc, char *argv[])`
- **Rôle** : Fonction principale du shell.
- **Fonctionnement** :
  - Initialise le gestionnaire de signaux.
  - Charge l'historique des commandes.
  - Gère le mode batch (`-c`) et le mode interactif.
  - Lit et exécute les commandes en boucle dans le mode interactif.
- **Gestion des erreurs** : Vérifie les erreurs de lecture des commandes.

## Variables principales
- `char command[MAX_COMMAND_LENGTH]` : Stocke la commande entrée par l'utilisateur.

## Exemple d'utilisation
```
my_sh> ls -l
my_sh> echo "Bonjour"
Bonjour
my_sh> man my_sh
```

## Autres
### Gestion des erreurs
- Vérification des erreurs de lecture (`fgets`).
- Gestion du signal `SIGCHLD` pour éviter les processus zombies.

