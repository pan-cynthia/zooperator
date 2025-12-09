#ifndef PENGUIN_H
#define PENGUIN_H

#include <string>

#include "animal.h"

class Penguin : public Animal {
 public:
  Penguin(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
  std::string getPreferredHabitat() const override;
};

#endif  // PENGUIN_H
