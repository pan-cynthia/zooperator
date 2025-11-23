#include "penguin.h"

#include <iostream>
#include <utility>

Penguin::Penguin(std::string name, int age) : Animal(std::move(name), "Penguin", age) {
  purchase_cost_ = 500.0;
  feeding_cost_ = 15.0;
  maintenance_cost_ = 25.0;
}

void Penguin::makeSound() const {
  std::cout << getName() << " the Penguin is squawking!\n";
}
