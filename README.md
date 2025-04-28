# Heroes of the Abyss

A turn-based RPG battle game written in C++ featuring strategic combat, elemental affinities, and unique character abilities.

## Features

- Turn-based combat system with initiative order based on speed and luck
- 20 unique playable characters with distinct roles and abilities
- Elemental affinity system (Fire, Ice, Water, Earth, Light) with strengths and weaknesses
- Special skills system with cooldowns
- 3 waves of combat with increasing difficulty
- Boss battles at the end of each wave
- Team composition strategy with front/back line positioning

## Getting Started

### Prerequisites

- C++ compiler with C++23 support (g++)
- Make build system

### Building the Project

1. Clone the repository
2. Navigate to the project directory
3. Run make to build:

```sh
make
```

### Running the Game

After building, run the executable:

```sh
./main
```

## Gameplay

1. **Team Selection**: Choose 4 characters (2 front line, 2 back line)
2. **Combat**: 
   - Each wave has 5 rounds
   - First 4 rounds: Regular enemies
   - 5th round: Boss battle
   - Characters take turns based on Speed (SPD) and Luck (LCK)
   - Choose between basic attacks or special skills

## Character Stats

- **HP**: Health Points
- **ATK**: Attack Power
- **DEF**: Defense
- **SPD**: Speed (affects turn order)
- **LCK**: Luck (affects critical hits)

## Affinities

- **FIR** (Fire)
- **ICE** (Ice)
- **WTR** (Water)
- **ERT** (Earth)
- **LGT** (Light)

Each affinity is strong against one element and weak against another.

## Project Structure

- `src/`: Source files
- `include/`: Header files
- `data/`: JSON data files for characters, enemies, and bosses
- `Makefile`: Build configuration

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.