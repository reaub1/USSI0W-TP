# Documentation - command\_history.c

##  Description

Le fichier `command_history.c` gère l'historique des commandes saisies par l'utilisateur.

##  Fonctions principales

### 1️⃣ `void load_command_history()`

- **Rôle :** Charge l'historique des commandes depuis un fichier.
- **Gestion des erreurs :** Vérifie si `fopen()` échoue et affiche une erreur avec `print_error()`.

### 2️⃣ `void save_command_to_history(const char *command)`

- **Rôle :** Ajoute une commande à l'historique et l'enregistre dans un fichier.
- **Gestion des erreurs :** Vérifie si `fopen()` ou `fprintf()` échoue.

### 3️⃣ `void show_history()`

- **Rôle :** Affiche l'historique des commandes enregistrées.
- **Gestion des erreurs :** Vérifie si `fopen()` échoue.

##  Variables principales

- `FILE *file` : Pointeur de fichier utilisé pour lire/écrire l'historique.
- `char line[1024]` : Stocke temporairement chaque ligne de l'historique.

##  Exemple d'utilisation

```
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


