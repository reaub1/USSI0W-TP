# Documentation - execution.c

##  Description
Le fichier `execution.c` gère l'exécution des commandes dans le mini-shell. Il prend en charge les commandes simples, les redirections (`<`, `>`, `>>`), et les pipes (`|`).

## Fonctions principales

### `void execute_single_command(char *command)`
- **Rôle** : Exécute une commande simple.
- **Fonctionnement** :
  - Tokenize la commande en arguments.
  - Vérifie si la commande est intégrée et l'exécute directement.
  - Sinon, crée un processus enfant pour exécuter la commande via `execvp()`.
- **Gestion des erreurs** : Vérifie l'existence de la commande et gère les erreurs de fork et `execvp`.

### `void execute_with_redirection(char *command)`
- **Rôle** : Gère la redirection de sortie (`>`).
- **Fonctionnement** :
  - Sépare la commande et le fichier cible.
  - Remplace `STDOUT_FILENO` par le fichier cible.
  - Exécute la commande et restaure la sortie standard.
- **Gestion des erreurs** : Vérifie l'existence du fichier et l'accès en écriture.

### `void execute_with_append_redirection(char *command)`
- **Rôle** : Gère la redirection avec ajout (`>>`).
- **Fonctionnement** : Similaire à `execute_with_redirection`, mais ouvre le fichier en mode append.
- **Gestion des erreurs** : Vérifie l'accès au fichier.

### `void execute_with_input_redirection(char *command)`
- **Rôle** : Gère la redirection d'entrée (`<`).
- **Fonctionnement** :
  - Ouvre le fichier en lecture.
  - Remplace `STDIN_FILENO` par le fichier cible.
  - Exécute la commande en lisant son entrée depuis ce fichier.
- **Gestion des erreurs** : Vérifie l'existence du fichier et gère les erreurs d'ouverture.

### `void execute_with_pipe(char *command)`
- **Rôle** : Exécute deux commandes en les connectant via un pipe (`|`).
- **Fonctionnement** :
  - Sépare les commandes autour du pipe.
  - Crée un pipe et deux processus pour exécuter les commandes.
  - Redirige la sortie de la première commande vers l'entrée de la seconde.
- **Gestion des erreurs** : Vérifie la création du pipe et la gestion des processus.

### `void execute_with_logical_operators(char *command)`
- **Rôle** : Exécute des commandes avec les opérateurs `&&` et `||`.
- **Fonctionnement** :
  - Sépare les commandes selon `&&` ou `||`.
  - Exécute la première commande et, selon le code de retour, exécute la seconde ou non.

### `void execute_command(char *command)`
- **Rôle** : Analyse la commande et appelle l'exécution appropriée.
- **Fonctionnement** :
  - Détecte les redirections (`<`, `>`, `>>`).
  - Détecte les pipes (`|`).
  - Détecte les opérateurs logiques (`&&`, `||`).
  - Exécute la commande correspondante.
- **Gestion des erreurs** : Vérifie la validité de la commande avant exécution.

##  Variables principales

- `char *args[MAX_ARGS]` : Stocke les arguments de la commande.
- `pid_t pid` : Stocke le PID du processus fils.
- `int fd` : Descripteur de fichier pour les redirections.
- `int pipefd[2]` : Tableau de descripteurs de fichier pour les pipes.

##  Exemple d'utilisation
```sh
my_sh> ls -l
my_sh> cat fichier.txt > output.txt
my_sh> grep main < execution.c
my_sh> ls | wc -l
```

### Gestion des erreurs
- Vérification de l'existence des fichiers avant redirection.
- Vérification de l'état des pipes et des processus.
- Gestion des codes de retour pour les opérateurs logiques (`&&`, `||`).
- Toutes les erreurs sont affichées via `print_error()` qui utilise `errno`.