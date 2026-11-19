# Raytracing

Ray caster maison en C++.

## Prérequis

- Docker
- Node.js (uniquement pour utiliser les commandes `npm run docker:*` ci-dessous ; sinon voir la section "Sans npm")

## Build de l'image Docker

```
docker build -t raytracing .
```

Cette étape compile le projet (`cmake` en mode Release) directement pendant la création de l'image. Avec Node installé en local, l'équivalent est `npm run docker:build`.

## Lancer le projet (hello world)

```
docker run --rm raytracing
```

Affiche `Hello world`.

## Commandes à l'intérieur du conteneur

### Avec npm (si tu as Node sur ta machine)

Pas besoin d'entrer manuellement dans le conteneur : chaque commande ci-dessous entre elle-même dans le conteneur (via `docker run`), y exécute l'action, puis en ressort.

| Commande | Effet |
|---|---|
| `npm run docker:build` | Build l'image Docker |
| `npm run build:release` | Entre dans le conteneur, build CMake en mode Release |
| `npm run build:debug` | Entre dans le conteneur, build CMake en mode Debug |
| `npm start` | Entre dans le conteneur, build Release puis exécute le binaire |
| `npm run debug` | Entre dans le conteneur, build Debug puis exécute le binaire |
| `npm test` | Entre dans le conteneur, build Release puis lance les tests (`ctest`) |
| `npm run test:debug` | Entre dans le conteneur, build Debug puis lance les tests (`ctest`) |

### Sans npm (commandes CMake/CTest classiques)

```
# Entrer dans le conteneur
docker run --rm -it raytracing bash

# Release
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release
./build/release/raytracer
ctest --test-dir build/release --output-on-failure

# Debug
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug
./build/debug/raytracer
ctest --test-dir build/debug --output-on-failure
```

## Monter le code source en live (dev loop sans rebuild d'image)

Depuis la racine du projet, sur Windows (PowerShell) :

```
docker run --rm -it -v ${PWD}:/app raytracing bash
```

Puis à l'intérieur du conteneur, rebuilder/tester comme ci-dessus.
