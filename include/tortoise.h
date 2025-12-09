#ifndef TORTOISE_H
#define TORTOISE_H

#include <string>

#include "animal.h"

class Tortoise : public Animal {
 public:
  Tortoise(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
};

#endif  // TORTOISE_H
