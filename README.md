# Zooperator

Zooperator is a text based zoo management simulation game built in C++. Players act as a zookeeper whose job is to manage a zoo efficiently. The goal is to survive 10 days while completing required missions, keeping animals happy and healthy, and maintaining a high zoo rating.

## Features

- **7 Animal Species**: Each with distinct costs, needs, and behaviors
- **5 Habitat Types**: Animals perform best in their preferred habitats
- **Mission Based Progression**: Complete required and optional daily missions to advance and earn rewards
- **Action Point System**: Limited daily actions (feeding, playing, exercising, treating, cleaning) that scale with zoo size
- **Dynamic Zoo Rating**: Calculated from animal happiness (50%), health (30%), exhibit cleanliness (15%), and finances (5%)
- **Stat Degradation**: Animals and exhibits require constant attention with nightly degradation of health, hunger, happiness, and energy
- **Visitor System**: Attendance influenced by zoo rating, species diversity, and animal welfare
- **Financial Simulation**: Balance visitor revenue against animal/exhibit maintenance and staff wages
- **Object Oriented Design**: Inheritance, polymorphism
- **Unit Testing**: Comprehensive unit tests with GoogleTest

## Future Enhancements

- Save/load game functionality
- More animal species and exhibit types
- Special and random events (births, illness, weather)
- Breeding mechanics
- Difficulty modes
- Compatibility system within exhibits
- Animals age over time
- Customizable action amounts/durations with scaled costs
- Graphical User Interface (GUI)

## Gameplay Preview

Some menus and prompts are omitted for clarity.

### Starting the Game

```plaintext
Welcome to Zooperator Bob!
You'll be working as the zookeeper for: Bob's Zoo.

Goals
 - Keep the zoo running for 10 days.
 - Complete all the required missions each day.
 - Keep all animals happy and healthy.
```

### Main Menu

```plaintext
MAIN MENU | Balance: $2000 | Actions: 3/3
-------------------------------------------------------
1. Help
2. View Missions
3. Manage Animals 
4. Manage Exhibits
5. Manage Zoo
6. End Day
7. Exit Game
-------------------------------------------------------  
```

### Daily Missions

```plaintext
DAY 1 MISSIONS
--------------------------------------------------
Required:
 - Purchase your first animal [0/1] X
 - Purchase your first exhibit [0/1] X
 - Add your animal to the exhibit X

Optional:
 - End day with balance of $1200+ (+$100)
-------------------------------------------------------
```

### Purchasing an Animal Mission

```
PURCHASE ANIMAL | Balance: $2000
-------------------------------------------------------
1. Rabbit - $150 [Grassland]
2. Tortoise - $250 [Grassland]
...

> Name your animal: Miffy
  Purchase Miffy the Rabbit for $150? (1 - Yes, 2 - No)
  - Daily Cost: $13 (Feeding: $5, Maintenance: $8)
  - Preferred Habitat: Grassland
Purchased Miffy the Rabbit for $150.

New Balance: $1850

Mission Complete: Purchase your first animal
```

### End of Day Summary

```plaintext
END OF DAY 1
--------------------------------------------------
Actions performed today:
  1. Fed Miffy the Rabbit

Purchases made today (2)
  1. Animal: Miffy (Rabbit) - $150
  2. Exhibit: Bunny Burrow (Grassland) - $300

Animals:
  Total: 1
  Sick: 0
  Hungry: 0
  Unhappy: 0
  Tired: 0
  Need Attention: 0
  Homeless: 0

Exhibits:
  Total: 1
  Need Cleaning: 0

Stats:
  Visitors: 13
  Revenue : $195
  Expenses: $66
  Net     : $129
  Bonus   : $100
  Balance : $1779

Zoo Rating: 4.7/5.0 (Outstanding)
--------------------------------------------------
```

## Getting Started

Follow the steps below to set up, build, and run Zooperator locally.

### Prerequisites

Make sure you have the following installed:

- C++14 compatible compiler (clang or gcc)
- CMake

### 1. Clone the Repository

```bash
git clone https://github.com/pan-cynthia/zooperator.git
cd zooperator
```

### 2. Configure the Project

Create a build directory and configure CMake

```bash
cmake -S . -B build
```

### 3. Build the Project

```bash
cmake --build build
```

### 4. Run the Project

```bash
./build/zooperator
```

### 5. Run Tests

Unit tests are built and run using GoogleTest which is automatically fetched by CMake.

```bash
ctest
```
