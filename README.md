# Piece Out - Puzzle Game

Un jeu de puzzle développé en C++ avec SFML où vous devez déplacer des pièces sur un plateau en utilisant leurs capacités de déplacement, rotation et symétrie.

## Description

Piece Out est un jeu de réflexion dans lequel chaque pièce possède des opérateurs de transformation (déplacement, rotation, symétrie) qui définissent comment elle peut se déplacer. Le but est de positionner toutes les pièces à leur emplacement cible.

### Fonctionnalités

- 9 niveaux de difficulté progressive
- Système d'annulation des coups (Undo)
- Interface graphique intuitive
- Détection automatique de victoire

## Prérequis

- C++11 ou supérieur
- SFML 2.x (System, Graphics, Window)
- Make

### Installation de SFML

**Ubuntu/Debian :**
```bash
sudo apt-get install libsfml-dev
```

**macOS (Homebrew) :**
```bash
brew install sfml
```

## Compilation et Lancement

### Linux
```bash
make
```

### macOS
```bash
make mac
```

### Nettoyage
```bash
make clean
```

## Comment Jouer

1. Au lancement, sélectionnez un niveau (1-9)
2. Cliquez sur une case d'une pièce pour activer son opérateur
3. Les pièces se déplacent selon leurs opérateurs :
   - **Flèches** : Déplacement directionnel
   - **Rotation** : Rotation horaire/anti-horaire autour d'un point
   - **Symétrie** : Symétrie horizontale/verticale
4. Utilisez le bouton de retour pour annuler un coup
5. Utilisez le bouton home pour revenir au menu

## Architecture

Le projet utilise plusieurs design patterns :

- **MVC** : Séparation Model-View-Controller
- **Singleton** : Pour les contrôleurs et gestionnaires
- **Observer** : Pour la gestion des événements
- **Command** : Pour l'annulation des coups
- **Factory** : Pour la création des opérateurs
- **Decorator** : Pour l'empilement des opérateurs sur les pièces
- **Visitor** : Pour l'application des transformations

### Structure

```
src/
├── Main.cpp
├── controllers/     # Logique de contrôle
├── models/          # Logique métier
├── views/           # Interface graphique
└── utils/           # Utilitaires (Observer, Command, etc.)
```

## Tests Mémoire

Pour vérifier les fuites mémoire :

```bash
make valgrind
```

## Auteurs

- [@guillaume-xue](https://github.com/guillaume-xue)
- [@XiaoGunFr](https://github.com/XiaoGunFr)

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENCE](LICENCE) pour plus de détails.
