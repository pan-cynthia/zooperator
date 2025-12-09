#ifndef LION_H
#define LION_H

#include <string>

#include "animal.h"

class Lion : public Animal {
 public:
  Lion(std::string name, int age);
  void makeSound() const override;
  void updateStatsEndOfDay() override;
  std::string getPreferredHabitat() const override;
};

#endif  // LION_H
