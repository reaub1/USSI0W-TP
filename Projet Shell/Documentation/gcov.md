# Documentation - Utilisation de Gcov dans my_sh

##  Objectif
Ce document explique comment utiliser **Gcov** pour analyser la couverture de code du projet **MiniShell** et générer un rapport visuel.

---

##  1️⃣ Compilation avec les options de couverture
Avant d'exécuter le programme, il faut compiler le projet en activant **la couverture de code**.

###  Commande à exécuter :
```sh
make clean
make coverage
make
```
 Cette commande compile le projet avec les options nécessaires et crée un dossier `coverage/` pour stocker les fichiers de couverture.

---

##  2️⃣ Exécution du programme pour collecter des données
Après la compilation, exécuter plusieurs commandes dans le shell pour enregistrer des statistiques de couverture.

###  Exemple d'utilisation :
```sh
./my_sh
ls
echo "Hello"
history
exit
```
 Ces actions génèrent les fichiers de couverture (`.gcda` et `.gcno`) dans le dossier `coverage/`.

---

##  3️⃣ Génération du rapport de couverture avec Gcov
Une fois le shell testé, récupérer les données de couverture avec :

###  Commande à exécuter :
```sh
lcov --capture --directory coverage --output-file coverage.info --ignore-errors inconsistent
```
 Cette commande génère un fichier `coverage.info` contenant le pourcentage de code exécuté.

---

##  4️⃣ Génération d'un rapport HTML avec Genhtml
Après avoir récupéré les données de couverture, générer un rapport **visuel** en HTML :

###  Commande à exécuter :
```sh
genhtml coverage.info --output-directory coverage_report --ignore-errors inconsistent,corrupt
```
 Cette commande crée un dossier **`coverage_report/`** contenant les fichiers HTML du rapport.

---

##  5️⃣ Visualisation du rapport de couverture
Ouvrir le rapport de couverture dans un navigateur :

###  Commande à exécuter :
```sh
open coverage_report/index.html  # (macOS)
xdg-open coverage_report/index.html  # (Linux)
```
 Cela ouvre une page montrant les parties du code exécutées (vert) et non exécutées (rouge).

---

##  6️⃣ Nettoyage des fichiers de couverture
Pour supprimer les fichiers temporaires et recommencer une nouvelle analyse :

###  Commande à exécuter :
```sh
make clean-coverage
```
 Cette commande supprime tous les fichiers de couverture (`coverage/`, `coverage_report/`, `coverage.info`).

---

## Résumé des actions à effectuer
| **Action** | **Commande** |
|-----------|-------------|
| **Compilation avec Gcov** | `make clean && make coverage && make` |
| **Exécution du shell** | `./my_sh` et quelques commandes (ls, echo, etc.) |
| **Collecte des données** | `lcov --capture --directory coverage --output-file coverage.info --ignore-errors inconsistent` |
| **Génération du rapport HTML** | `genhtml coverage.info --output-directory coverage_report --ignore-errors inconsistent,corrupt` |
| **Visualisation du rapport** | `open coverage_report/index.html` |
| **Nettoyage des fichiers de couverture** | `make clean-coverage` |

---

