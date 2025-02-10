# MiniShell - `my_sh`


## 🛠️ Fonctionnalités attendues et avancement

| Fonctionnalité | Description | Statut |
|--------------|------------|--------|
| **FM01** | Exécuter une commande simple (`ls`, `ps`, `who`...) | ✅ Fait |
| **FM02** | Exécuter un sous-ensemble de commandes (max 3) | 🚧 En cours |
| **FM02.1** | Gérer les opérateurs `&&` et `\|\|` | ✅ Fait |
| **FM02.2** | Gérer les redirections `\|`, `>`, `<`, `>>`, `<<` | ✅ Fait |
| **FM02.3** | Gérer l’exécution en arrière-plan `&` | ✅ Fait |
| **FM03** | Implémenter des commandes internes (`cd`, `pwd`, `echo`, `exit`) | ✅ Fait |
| **FM04** | Sauvegarder l’historique des commandes dans un fichier | ✅ Fait |
| **FM05** | Ajouter un mode batch (`./my_sh -c "ls -al \| grep toto"`) | ✅ Fait |
| **FM06** | Gérer des variables d’environnement (`VAR=value`) | ❌ À faire |
| **FM07** | Ajouter des alias (`alias ll="ls -al"`) | ❌ À faire |

---

## ⚙️ Contraintes techniques

| Exigence | Description | Statut |
|----------|------------|--------|
| **CT01** | Compilation via un `Makefile` | ✅ Fait |
| **CT02** | Définition des structures dans `typedef.h` | ❌ À faire |
| **CT03** | Séparer les prototypes `.h` et implémentations `.c` | ✅ En place, à affiner |
| **CT04** | Code documenté avec commentaires | 🚧 En cours |
| **CT05** | Gestion des erreurs avec `errno` | ✅ Fait |
| **CTO01** | Documentation avec `doxygen` | ❌ À faire |
| **CTO02** | Vérification de couverture avec `gcov` | ✅ Fait
| **CTO03** | Rédaction d’une page de manuel Linux | ✅ Fait |

## 📝 Notes de développement
- **Approche incrémentale** : on implémente d’abord la base, puis on ajoute progressivement les fonctionnalités.
- **Prochaines étapes** :
  1. Gérer des variables d’environnement.
  2. Ajouter des alias.
  3. Définir des structures dans typedef.h.
