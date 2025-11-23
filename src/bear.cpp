#include "bear.h"

#include <iostream>
#include <utility>

Bear::Bear(std::string name, int age) : Animal(std::move(name), "Bear", age) {
  purchase_cost_ = 2000.0;
  feeding_cost_ = 30.0;
  maintenance_cost_ = 50.0;
}

void Bear::makeSound() const {
  std::cout << getName() << " the Bear is growling!\n";
}
