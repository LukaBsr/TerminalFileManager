# 📁 TerminalFileManager

Un explorateur de fichiers en mode terminal écrit en **C++** avec **Ncurses**.  
Il permet de naviguer dans les dossiers, consulter les fichiers, en créer, supprimer, et afficher leurs propriétés, le tout dans une interface textuelle ergonomique.

---

## 🚀 Fonctionnalités

- Navigation dans l’arborescence de fichiers
- Visualisation des fichiers et répertoires
- Création de fichiers et dossiers
- Suppression de fichiers et dossiers
- Affichage des métadonnées d’un fichier (taille, date, type…)
- Interface Ncurses avec couleurs et encadrements

---

## 📸 Aperçu

```bash
+--------------------------------------------------+
| Explorateur de fichiers                          |
| ========================                         |
| > main.cpp                                       |
|   build.sh                                       |
|   include/                                       |
|                                                  |
| [Entrée] Ouvrir  [q] Menu                        |
| [n] Nouveau fichier  [d] Dossier  [x] Supprimer  |
+--------------------------------------------------+
```

---

## 🧰 Installation

### Prérequis

- Linux / WSL
- `g++` avec support C++17 ou plus
- `ncurses` (installable via `libncurses-dev`)

### Cloner et compiler

```bash
git clone https://github.com/LukaBsr/TerminalFileManager.git
cd TerminalFileManager
chmod +x build.sh
./build.sh
```

Ou avec `cmake` :

```bash
mkdir build && cd build
cmake ..
make
```

---

## 🕹️ Raccourcis clavier

| Touche     | Action                                 |
|------------|-----------------------------------------|
| `↑` / `↓`  | Naviguer dans la liste                 |
| `Entrée`   | Ouvrir un dossier ou voir un fichier   |
| `q`        | Revenir au menu principal              |
| `n`        | Créer un nouveau fichier               |
| `d`        | Créer un dossier                       |
| `x`        | Supprimer un fichier ou dossier        |

---

## 📁 Organisation du code

| Dossier / Fichier | Rôle |
|------------------|------|
| `core/`          | Gestion des fichiers et dossiers |
| `ui/`            | Interface Ncurses et vues        |
| `main.cpp`       | Point d’entrée de l’application  |
| `build.sh`       | Script de compilation rapide     |

---

## 📄 Licence

Ce projet est sous licence **MIT**. Voir [LICENSE](./LICENSE) pour plus de détails.

---

## 🙌 Contribuer

Les contributions sont les bienvenues ! Tu peux proposer des issues, pull requests ou idées d’amélioration.

---

## ✨ Auteur

**Luka Boissière**  
GitHub : [@LukaBsr](https://github.com/LukaBsr)
