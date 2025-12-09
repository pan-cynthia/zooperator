#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "animal.h"

class Elephant : public Animal {
 public:
  Elephant(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
  std::string getPreferredHabitat() const override;
};

#endif  // ELEPHANT_H
