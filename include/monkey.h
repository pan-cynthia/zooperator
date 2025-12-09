#ifndef MONKEY_H
#define MONKEY_H

#include <string>

#include "animal.h"

class Monkey : public Animal {
 public:
  Monkey(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
};

#endif  // MONKEY_H
