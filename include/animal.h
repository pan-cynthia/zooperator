#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal {
 public:
  Animal(std::string name, std::string species, int age);
  virtual ~Animal() = default;

  // prevent copying since animals are unique, allow moving
  Animal(const Animal&) = delete;             // copy constructor
  Animal& operator=(const Animal&) = delete;  // copy assignment operator
  Animal(Animal&&) = default;                 // move constructor
  Animal& operator=(Animal&&) = default;      // move assignment operator

  // core behaviors
  virtual void eat(int amount);
  virtual void sleep(int hours);
  virtual void makeSound() const = 0;

  // getters
  const std::string& getName() const;
  const std::string& getSpecies() const;
  int getAge() const;
  int getHealthLevel() const;
  int getHungerLevel() const;
  int getHappinessLevel() const;
  int getEnergyLevel() const;
  bool isAlive() const;
  bool needsAttention() const;

  double getPurchaseCost() const;
  double getFeedingCost() const;
  double getMaintenanceCost() const;

  // setters
  void updateHealth(int delta);
  void updateHunger(int delta);
  void updateHappiness(int delta);
  void updateEnergy(int delta);
  void updateStatsEndOfDay();

 protected:
  // basic info
  std::string name_;
  std::string species_;
  int age_;

  // stats
  int health_;
  int hunger_;
  int happiness_;
  int energy_;

  // costs
  double purchase_cost_;
  double feeding_cost_;
  double maintenance_cost_;

  // consts
  static constexpr int MIN_STAT = 0;
  static constexpr int MAX_STAT = 100;
  static constexpr int CRITICAL_THRESHOLD = 20;

  static int clamp(int value, int min_val, int max_val);
};

#endif  // ANIMAL_H
