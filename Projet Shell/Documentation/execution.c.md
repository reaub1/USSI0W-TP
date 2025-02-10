# Documentation - execution.c

##  Description
Le fichier `execution.c` gère l'exécution des commandes dans le mini-shell. Il prend en charge les commandes simples, les redirections (`<`, `>`, `>>`), et les pipes (`|`).

##  Fonctions principales

### 1️⃣ `void execute_command(char *command)`
- **Rôle :** Analyse la commande et appelle la fonction appropriée selon le type de commande (simple, redirection, pipe, etc.).

### 2️⃣ `void execute_single_command(char *command)`
- **Rôle :** Exécute une commande simple en créant un processus fils.
- **Erreurs gérées :** `fork()`, `execvp()`, `waitpid()`

### 3️⃣ `void execute_with_redirection(char *command)`
- **Rôle :** Gère la redirection de sortie (`>`).
- **Erreurs gérées :** `open()`, `fork()`, `dup2()`

### 4️⃣ `void execute_with_append_redirection(char *command)`
- **Rôle :** Gère la redirection en mode ajout (`>>`).
- **Erreurs gérées :** `open()`, `fork()`, `dup2()`

### 5️⃣ `void execute_with_input_redirection(char *command)`
- **Rôle :** Gère la redirection d'entrée (`<`).
- **Erreurs gérées :** `open()`, `fork()`, `dup2()`

### 6️⃣ `void execute_with_pipe(char *command)`
- **Rôle :** Exécute deux commandes en les connectant via un pipe (`|`).
- **Erreurs gérées :** `pipe()`, `fork()`, `dup2()`, `waitpid()`

##  Variables principales

- `char *args[MAX_ARGS]` : Stocke les arguments de la commande.
- `pid_t pid` : Stocke le PID du processus fils.
- `int fd` : Descripteur de fichier pour les redirections.
- `int pipefd[2]` : Tableau de descripteurs de fichier pour les pipes.

##  Exemple d'utilisation
```
my_sh> ls -l
my_sh> cat fichier.txt > output.txt
my_sh> grep main < execution.c
my_sh> ls | wc -l
```

##  Gestion des erreurs
Toutes les erreurs sont affichées via `print_error()` qui utilise `errno`.

---


