#include "penguin.h"

#include <iostream>
#include <utility>

Penguin::Penguin(std::string name, int age) : Animal(std::move(name), "Penguin", age) {
  purchase_cost_ = 400.0;
  feeding_cost_ = 20.0;
  maintenance_cost_ = 30.0;
}

void Penguin::makeSound() const {
  std::cout << getName() << " the Penguin is squawking!\n";
}
