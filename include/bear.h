#ifndef BEAR_H
#define BEAR_H

#include "animal.h"

class Bear : public Animal {
 public:
  Bear(std::string name, int age);
  void makeSound() const;
};

#endif  // BEAR_H