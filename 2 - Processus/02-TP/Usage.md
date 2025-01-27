
# TP2 - Appels système & processus

Ce programme permet d'exécuter plusieurs opérations sur les processus et la gestion des flux de données en utilisant les appels système. Les exercices incluent l'utilisation de `fork`, la redirection des flux standards, et la gestion des pipes.

---

## Compilation

Pour compiler le programme, utilisez la commande suivante :

```bash
gcc main.c tools.c -o TP2
```

Ou simplement :

```bash
make
```

---

## Utilisation

Le programme s'exécute avec la syntaxe suivante :

```bash
./TP2 [option]
```

### Commandes disponibles

1. **Fork yourself**  
   Crée un processus fils qui affiche son PID et le PID de son père, puis termine avec un code de retour égal au dernier chiffre de son PID. Le processus père attend la fin du fils et affiche son code de retour.

   **Commande** :  
   ```bash
   ./TP2 1
   ```
   **Ce que cela fait** :  
   Cette commande crée un processus fils et un processus père qui communiquent entre eux en affichant leurs PIDs et en récupérant le code de sortie du fils.

   **Exemple** :  
   ```bash
   ./TP2 1
   ```

2. **Redirection de flux standard**  
   Le programme crée un fils qui ferme le descripteur de sortie standard (`STDOUT`), ouvre un fichier temporaire et exécute une commande passée en argument (via `exec`). Le père attend la fin du fils et affiche un message après la terminaison du fils.

   **Commande** :  
   ```bash
   ./TP2 2 [commande]
   ```
   **Ce que cela fait** :  
   Cette commande crée un processus fils qui redirige la sortie vers un fichier temporaire, et exécute la commande fournie en argument. Le processus père attend la fin du processus fils et affiche un message.

   **Exemple** :  
   ```bash
   ./TP2 2 ls
   ```

3. **Redirection de flux via pipe**  
   Crée deux processus qui communiquent via un pipe. Le premier processus exécute `ps` et passe sa sortie au second qui exécute `grep` pour filtrer les lignes contenant "root". Le résultat est affiché avec la commande `write`.

   **Commande** :  
   ```bash
   ./TP2 3
   ```
   **Ce que cela fait** :  
   Cette commande met en place un pipe entre deux processus pour exécuter la commande `ps` et la filtrer avec `grep`. Si "root" est trouvé, le message "root est connecté" est affiché.

   **Exemple** :  
   ```bash
   ./TP2 3
   ```

---

## Gestion des erreurs

- Si les arguments fournis ne respectent pas le format attendu, le programme affiche un message d'erreur, accompagné de l'usage correct.
- Les erreurs système (comme l'absence de commandes ou de fichiers) affichent un message explicatif basé sur `strerror(errno)`.

---

## Makefile

Un Makefile est fourni pour automatiser les tâches courantes liées à la gestion du projet.
