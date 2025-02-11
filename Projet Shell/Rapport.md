# Rapport du projet

## 1. Introduction

MiniShell est un projet visant à implémenter un interpréteur de commandes simplifié similaire à Bash. Le projet suit une approche incrémentale en ajoutant progressivement des fonctionnalités essentielles telles que l'exécution de commandes, la gestion des redirections et des opérateurs logiques, ainsi que la prise en charge des alias et de l'historique des commandes.

## 2. Partage des tâches

Nous nous sommes répartis équitablement les tâches, Sébastien s'est plus occupés des contraintes techniques tandis que Robin s'est principalement occupés des fonctions métiers.

Nous avons assurés le suivi des tâches dans le fichier suivant :

[CDC](/Projet%20Shell/CDC.md)

Une page de manuel est utilisable dans le shell pour comprendre comment l'utiliser, il faut compiler le projet avec make dans le répertoire myshell : 

```bash
make
```
puis 
```bash
./my_sh
```
puis
```bash
my_sh> man my_sh
```

## 3. Tests

Pour faciliter le développement et surtout mesurer l'impact des changements, nous avons mis en place un script shell qui lance automatiquement des tests des fonctionnalités, les tests comparent la commande lancé en mode batch avec my_sh, et celle lancé depuis le shell courant.

Pour éxécuter le shell de tests depuis le répertoire myShell:

```bash 
cd TEST
./test_minishell.sh
```

## 4. Doxygen

Le code à été commenté de façon à pouvoir générer une documentation doxygen, pour la lire il faut ouvrir dans un navigateur index.html, vous pouvez utiliser cette commande dans le répertoire myShell :

```bash
open html/index.html 
```

Si le fichier n'est pas généré, vous pouvez le générer avec la commande :

```bash
doxygen -g
```
puis
```bash
doxygen Doxyfile    
```

## 5. GCov

Vous trouverez toutes les informations sur l'utilisation du gcov dans le manuel d'explication :

[Gcov documentation](/Projet%20Shell/Documentation/gcov.md)

## 6. Documentation

Chaque script est documenté avec l'explication des fonctionnalités et méthode dans sa page Markdown. L'ensemble des documents est accessible dans le dossier [Documentation](/Projet%20Shell/Documentation/).

## 7. Conclusion 

Ce projet nous à extrêment plu, il nous a permi de mettre en oeuvre des notions que nous avons vu dans la matière, malheuresement nous n'avons pas réussi à le finir à 100%, une commande avec trop de redirections peut ne pas marcher, certains opérateurs ne sont pas pris en compte.


PICHON Sébastien & BECHLEM Robin