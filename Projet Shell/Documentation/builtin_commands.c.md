# Documentation : builtin_commands.c

## Description
Ce fichier implémente les commandes intégrées du shell, telles que `cd`, `alias`, `unalias`, `history`, `exit` ou `man`. Il permet de gérer des alias et d'exécuter certaines commandes spécifiques sans passer par des processus externes.

## Fonctions principales

### `void show_aliases()`
- **Rôle** : Affiche la liste des alias enregistrés.
- **Fonctionnement** : Parcourt la liste des alias et affiche chaque alias sous la forme `nom='valeur'`.

### `void remove_alias(char *name)`
- **Rôle** : Supprime un alias existant.
- **Fonctionnement** : Recherche l'alias dans la liste et le supprime si trouvé.
- **Gestion des erreurs** : Affiche un message si l'alias n'est pas trouvé.

### `char *get_alias_value(char *name)`
- **Rôle** : Récupère la valeur d'un alias.
- **Retour** : La valeur de l'alias si trouvé, `NULL` sinon.

### `void add_alias(char *name, char *value)`
- **Rôle** : Crée un nouvel alias ou met à jour un alias existant.
- **Gestion des erreurs** : Vérifie si la limite des alias est atteinte.

### `void execute_builtin_command(char *args[])`
- **Rôle** : Exécute une commande intégrée.
- **Fonctionnement** : Vérifie si la commande correspond à un alias ou une commande interne, puis l'exécute en conséquence.
- **Gestion des erreurs** : Affiche des messages en cas d'erreur de syntaxe ou d'utilisation incorrecte.

### `int is_builtin_command(char *command)`
- **Rôle** : Vérifie si une commande est intégrée.
- **Retour** : `1` si la commande est intégrée, `0` sinon.


## Variables principales

- `char cwd[1024]` : Stocke le chemin du répertoire courant.
- `char *builtins[]` : Liste des commandes internes.

## Exemple d'utilisation
```sh
my_sh> cd /home/user
my_sh> pwd
/home/user
my_sh> echo "Hello World!"
Hello World!
my_sh> history
my_sh> man my_sh
my_sh> alias ls='ls --color=auto'
my_sh> alias
ls='ls --color=auto'

my_sh> unalias ls
my_sh> alias

```

### Gestion des erreurs
- Vérification de l'existence des alias avant leur suppression.
- Messages d'erreur pour les commandes mal formées (`alias name='command'`).
- Gestion de l'échec des commandes intégrées (`cd`, `exit`, etc.).
---


