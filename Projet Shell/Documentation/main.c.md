# Documentation - main.c

##  Description
Le fichier `main.c` est le point d'entrée du mini-shell. Il gère la boucle principale du programme et l'exécution des commandes.

##  Fonctions principales

### 1️⃣ `int main()`
- **Rôle :** Initialise le shell, gère l'affichage du prompt, et traite les commandes saisies.
- **Étapes :**
  1. Affiche `my_sh>`
  2. Lit l'entrée avec `fgets()`
  3. Exécute la commande avec `execute_command()`
  4. Répète jusqu'à la fin du programme

##  Variables principales

- `char command[MAX_COMMAND_LENGTH]` : Stocke la commande entrée par l'utilisateur.

##  Exemple d'utilisation
```
my_sh> ls -l
my_sh> echo "Bonjour"
Bonjour
```

##  Gestion des erreurs
- `fgets()` est vérifié avec `ferror()` pour détecter les erreurs de lecture.
- Si `fgets()` échoue, `print_error()` est utilisé.
---


