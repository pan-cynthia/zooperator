#ifndef ZOO_H
#define ZOO_H

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "animal.h"
#include "exhibit.h"

class Zoo {
 public:
  Zoo(std::string name, double starting_balance = 10000.0);

  // getters
  const std::string& getName() const;
  int getDay() const;
  double getBalance() const;

  // animal management
  bool purchaseAnimal(std::unique_ptr<Animal> animal);
  bool sellAnimal(Animal* animal);
  Animal* getAnimal(size_t index);
  std::vector<Animal*> getAllAnimals();
  std::vector<Animal*> getAnimalsNeedingAttention();
  size_t getAnimalCount() const;

  // exhibit management
  bool purchaseExhibit(std::unique_ptr<Exhibit> exhibit);
  Exhibit* getExhibit(size_t index);
  std::vector<Exhibit*> getExhibitsNeedingCleaning();
  size_t getExhibitCount() const;

  // animal-exhibit management
  Exhibit* findAnimalLocation(Animal* animal);
  bool addAnimalToExhibit(Animal* animal, Exhibit* exhibit);
  bool removeAnimalFromExhibit(Animal* animal, Exhibit* exhibit);
  bool moveAnimalToExhibit(Animal* animal, Exhibit* exhibit);

 private:
  std::string name_;
  int day_;
  double balance_;
  std::vector<std::unique_ptr<Animal>> animals_;
  std::vector<std::unique_ptr<Exhibit>> exhibits_;
  std::map<Animal*, Exhibit*> animal_locations_;
};

#endif  // ZOO_H