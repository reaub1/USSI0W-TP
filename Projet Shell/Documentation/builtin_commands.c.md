# Documentation - builtin_commands.c

##  Description
Le fichier `builtin_commands.c` gère les commandes internes du mini-shell comme `cd`, `pwd`, `echo`, et `exit`.

##  Fonctions principales

### 1️⃣ `void execute_builtin_command(char *args[])`
- **Rôle :** Exécute les commandes internes du shell.
- **Commandes prises en charge :** `cd`, `pwd`, `echo`, `history`, `exit`
- **Gestion des erreurs :** `chdir()`, `getcwd()`

### 2️⃣ `int is_builtin_command(char *command)`
- **Rôle :** Vérifie si une commande est interne.
- **Retourne :** `1` si la commande est interne, `0` sinon.

##  Variables principales

- `char cwd[1024]` : Stocke le chemin du répertoire courant.
- `char *builtins[]` : Liste des commandes internes.

##  Exemple d'utilisation
```
my_sh> cd /home/user
my_sh> pwd
/home/user
my_sh> echo Hello World!
Hello World!
my_sh> history
```

##  Gestion des erreurs
- `cd` vérifie si `chdir()` échoue et affiche un message d'erreur via `print_error()`.
- `pwd` affiche une erreur si `getcwd()` échoue.
---


