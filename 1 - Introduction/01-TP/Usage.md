
# TP1 - Programme de gestion de fichiers

Ce programme permet plusieurs manipulations de fichiers et dossiers : copie, inversion de contenu, affichage des fichiers dans un dossier, et utilisation de fonctions personnalisées pour la gestion de fichiers.

---

## Compilation

Pour compiler le programme, utilisez la commande suivante :

```bash
gcc main.c tools.c -o TP1
```

Ou simplement :

```bash
make
```

---

## Utilisation

Le programme s'exécute avec la syntaxe suivante :

```bash
./TP1 [option] [arguments]
```

### Commandes disponibles

1. **Copie d'un fichier**  
   Copie le contenu d'un fichier source (`srcFile`) dans un fichier destination (`destFile`).

   **Commande** :  
   ```bash
   ./TP1 1 fichier_source.txt fichier_destination.txt
   ```
   **Ce que cela fait** :  
   Cette commande lit le contenu du fichier `fichier_source.txt` et le copie intégralement dans `fichier_destination.txt`.

   **Exemple** :  
   ```bash
   ./TP1 1 sandbox/lorem.txt sandbox/output.txt 
   ```

2. **Inversion du contenu d'un fichier**  
   Affiche le contenu d'un fichier (`srcFile`) en ordre inverse.

   **Commande** :  
   ```bash
    ./TP1 2 fichier_source.txt
   ```
   **Ce que cela fait** :  
   Cette commande lit le contenu de `fichier_source.txt` et affiche les caractères dans l'ordre inverse directement dans le terminal.

   **Exemple** :  
   ```bash
   ./TP1 2 sandbox/lorem.txt 
   ```

3. **Affichage des fichiers d'un dossier**  
   Liste les fichiers présents dans un dossier (`srcFolder`) avec leurs métadonnées (permissions, propriétaire, taille, etc.).

   **Commande** :  
   ```bash
   ./TP1 3 dossier_source
   ```
   **Ce que cela fait** :  
   Cette commande parcourt le dossier spécifié et affiche les informations détaillées sur chaque fichier qu'il contient.

   **Exemple** :  
   ```bash
   ./TP1 3 sandbox
   ```

4. **Copie avec des fonctions personnalisées**  
   Utilise des fonctions personnalisées pour lire un fichier (`srcFile`) caractère par caractère et le copier dans un autre fichier (`destFile`).

   **Commande** :  
   ```bash
   ./TP1 4 fichier_source.txt fichier_destination.txt
   ```
   **Ce que cela fait** :  
   Cette commande utilise les fonctions `my_open`, `my_getc`, `my_putc`, et `my_close` pour copier le contenu de `fichier_source.txt` dans `fichier_destination.txt`.

   **Exemple** :  
   ```bash
   ./TP1 4 sandbox/lorem.txt sandbox/output.txt 
   ```
---

## Gestion des erreurs

- Si les arguments fournis ne respectent pas le format attendu, le programme affiche un message d'erreur, accompagné de l'usage correct.
- Les erreurs système (comme des fichiers ou dossiers inexistants) affichent un message explicatif basé sur `strerror(errno)`.

---

## Makefile

Un Makefile est fourni pour automatiser les tâches courantes liées à la gestion du projet.
