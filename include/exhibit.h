#ifndef EXHIBIT_H
#define EXHIBIT_H

#include <string>
#include <vector>

#include "animal.h"

class Exhibit {
 public:
  Exhibit(std::string name, std::string type, int capacity, double purchase_cost,
          double maintenance_cost);

  // animal management
  bool canAddAnimal() const;
  bool addAnimal(Animal* animal);
  bool removeAnimal(Animal* animal);
  void removeAllAnimalsFromExhibit();
  bool containsAnimal(Animal* animal) const;
  Animal* getAnimal(size_t index);

  // getters
  const std::string& getName() const;
  const std::string& getType() const;
  int getMaxCapacity() const;
  size_t getCapacityUsed() const;
  int getCleanliness() const;
  double getPurchaseCost() const;
  double getMaintenanceCost() const;
  bool needsCleaning();

  // setters
  void updateCleanliness(int delta);
  void clean();

 private:
  std::string name_;
  std::string type_;
  int capacity_;
  int cleanliness_;
  double purchase_cost_;
  double maintenance_cost_;
  std::vector<Animal*> animals_;
};

#endif  // EXHIBIT_H
