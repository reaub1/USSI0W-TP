# Documentation - utils.c

##  Description
Le fichier `utils.c` fournit des fonctions utilitaires pour la gestion des erreurs et des processus zombies.

##  Fonctions principales

### `void print_error(const char *msg)`
- **Rôle :** Affiche un message d'erreur standard basé sur `errno`.
- **Utilisation :** Appelée après un échec d'une fonction système (`open()`, `fork()`, etc.).
- **Exemple :**
```c
if (fork() == -1) {
    print_error("Échec du fork");
}
```

### `void print_syntax_error(const char *msg)`

- **Rôle :** Affiche un message d'erreur de syntaxe.

- **Fonctionnement :** Affiche simplement un message sous le format "Erreur de syntaxe : ".

### `void handle_sigchld()`
- **Rôle :** Gère les processus zombies en utilisant `waitpid()` avec `WNOHANG`.
- **Gestion des erreurs :** Vérifie si `errno` est différent de `ECHILD`.

##  Variables principales

- `errno` : Variable globale indiquant le code d'erreur du dernier appel système échoué.

##  Exemple d'utilisation
```
my_sh> ls fichier_inexistant
Erreur : ls - No such file or directory
my_sh> sezzd
ERR : Échec de l'exécution de la commande - No such file or directory
Commande introuvable : sezzd
```



