#ifndef BEAR_H
#define BEAR_H

#include "animal.h"

class Bear : public Animal {
 public:
  Bear(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
};

#endif  // BEAR_H