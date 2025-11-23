#ifndef RABBIT_H
#define RABBIT_H

#include <string>

#include "animal.h"

class Rabbit : public Animal {
 public:
  Rabbit(std::string name, int age);
  void makeSound() const override;
};

#endif  // RABBIT_H