# Minishell

## Description
Minishell est un projet qui implémente une version simplifiée d'un shell Unix. Ce projet permet de comprendre le fonctionnement d'un shell en créant une version minimaliste mais fonctionnelle. Il reproduit les fonctionnalités essentielles d'un shell Unix tout en restant simple et pédagogique.

Le projet est conçu pour être un excellent exercice d'apprentissage des concepts fondamentaux de la programmation système sous Unix, notamment :
- La gestion des processus et des fils d'exécution
- Les redirections et les pipes
- La gestion des variables d'environnement
- Le parsing de commandes complexes
- La gestion des signaux
- L'implémentation d'une interface en ligne de commande interactive

Minishell utilise une architecture modulaire et bien structurée, avec une séparation claire des responsabilités entre les différents composants. Il implémente un parser qui crée un arbre syntaxique abstrait (AST) pour représenter la structure des commandes, permettant ainsi une exécution efficace et correcte des commandes complexes.

## Auteurs
- [gpichon]
- [mprokosc]

## Fonctionnalités

### Commandes intégrées (Builtins)
- `cd` : changement de répertoire
- `pwd` : affichage du répertoire courant
- `echo` : affichage de texte
- `export` : gestion des variables d'environnement
- `unset` : suppression de variables d'environnement
- `env` : affichage des variables d'environnement
- `exit` : sortie du shell

### Fonctionnalités avancées
- Redirections (`>`, `>>`, `<`)
- Heredocs (`<<`)
- Pipes (`|`)
- Auto-complétion des commandes
- Historique des commandes
- Gestion des signaux (Ctrl+C, etc.)

## Structure du projet

### Architecture
Le projet utilise une architecture modulaire avec les composants suivants :
- **Parsing** : Analyse et création de l'AST (Abstract Syntax Tree)
- **Exécution** : Gestion de l'exécution des commandes
- **Builtins** : Implémentation des commandes intégrées
- **Gestion des variables d'environnement**
- **Gestion des redirections et pipes**

### L'AST (Abstract Syntax Tree)
L'AST est une structure de données arborescente qui représente la syntaxe d'une commande. Les types de nœuds incluent :
- `NODE_CMD` : commande simple
- `NODE_PIPE` : opérateur de pipe
- `NODE_REDIR_IN` : redirection d'entrée
- `NODE_REDIR_OUT` : redirection de sortie
- `NODE_REDIR_APPEND` : redirection de sortie en mode append
- `NODE_HEREDOC` : heredoc

## Compilation
```bash
make
```

## Utilisation
```bash
./minishell
```

## Tests
Le projet inclut un script de test (`test.sh`) qui compare le comportement de minishell avec bash pour diverses commandes.

## Notes techniques
- Le projet est écrit en C
- Utilisation de la libft personnalisée
- Gestion des erreurs et des cas limites
- Support complet des variables d'environnement
- Gestion des signaux pour une expérience utilisateur fluide

## Requirements
- Compilateur C (gcc)
- Make
- readline library

---

# Minishell

## Description
Minishell is a project that implements a simplified version of a Unix shell. This project helps understand how a shell works by creating a minimalist but functional version. It reproduces the essential features of a Unix shell while remaining simple and educational.

The project is designed to be an excellent learning exercise for fundamental Unix system programming concepts, including:
- Process and thread management
- Redirections and pipes
- Environment variables handling
- Complex command parsing
- Signal handling
- Implementation of an interactive command-line interface

Minishell uses a modular and well-structured architecture, with a clear separation of responsibilities between different components. It implements a parser that creates an abstract syntax tree (AST) to represent the structure of commands, enabling efficient and correct execution of complex commands.

## Authors
- [gpichon]
- [mprokosc]

## Features

### Built-in Commands
- `cd` : change directory
- `pwd` : display current directory
- `echo` : display text
- `export` : manage environment variables
- `unset` : remove environment variables
- `env` : display environment variables
- `exit` : exit the shell

### Advanced Features
- Redirections (`>`, `>>`, `<`)
- Heredocs (`<<`)
- Pipes (`|`)
- Command auto-completion
- Command history
- Signal handling (Ctrl+C, etc.)

## Project Structure

### Architecture
The project uses a modular architecture with the following components:
- **Parsing**: Analysis and creation of the AST (Abstract Syntax Tree)
- **Execution**: Command execution management
- **Builtins**: Implementation of built-in commands
- **Environment variables management**
- **Redirections and pipes management**

### The AST (Abstract Syntax Tree)
The AST is a tree data structure that represents the syntax of a command. Node types include:
- `NODE_CMD`: simple command
- `NODE_PIPE`: pipe operator
- `NODE_REDIR_IN`: input redirection
- `NODE_REDIR_OUT`: output redirection
- `NODE_REDIR_APPEND`: output redirection in append mode
- `NODE_HEREDOC`: heredoc

## Compilation
```bash
make
```

## Usage
```bash
./minishell
```

## Tests
The project includes a test script (`test.sh`) that compares minishell's behavior with bash for various commands.

## Technical Notes
- Project written in C
- Uses custom libft library
- Error and edge case handling
- Complete environment variables support
- Signal handling for smooth user experience

## Requirements
- C compiler (gcc)
- Make
- readline library
