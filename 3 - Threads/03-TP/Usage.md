
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
./TP3 1
```

### Commande disponible

1. **find_min_max_thread**  
   Initialise un tableau d'entier de taille 100 000 000 (1e8). On va ensuite rechercher le minimum et le maximum de ce tableau de façon séquentiel et threadé tout en mesurant les temps. On peut influencer la valeur du nombre de thread en modifiant la valeur de la constante NUM_THREADS et en recompilant.

   **Commande** :  
   ```bash
   ./TP3
   ```
   **Ce que cela fait** :  
   Cette commande crée un processus fils et un processus père qui communiquent entre eux en affichant leurs PIDs et en récupérant le code de sortie du fils.

---

### Résultats 


| Nombre de threads | Temps (µs) |
|-------------------|------------|
| Séquentiel        |151 056     |
| 1                 |155 938     |
| 2                 |78 590      |
| 4                 |55 393      |
| 8                 |39 487      |
| 16                |34 792      |
| 32                |33 152      |
| 64                |32 106      |
| 128               |30 738      |
| 256               |30 673      |
| 512               |32 716      |
| 1024              |36 647      |
---

## Gestion des erreurs

- Si les arguments fournis ne respectent pas le format attendu, le programme affiche un message d'erreur, accompagné de l'usage correct.
- Les erreurs système (comme l'absence de commandes ou de fichiers) affichent un message explicatif basé sur `strerror(errno)`.

---

## Makefile

Un Makefile est fourni pour automatiser les tâches courantes liées à la gestion du projet.
