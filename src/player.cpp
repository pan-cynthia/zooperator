#include "player.h"

#include <iostream>

Player::Player(std::string name) : name_(std::move(name)) {}

const std::string& Player::getName() const {
  return name_;
}

bool Player::feedAnimal(Zoo& zoo, Animal* animal) {
  if (!animal) {
    std::cout << "Animal does not exist!\n";
    return false;
  }

  if (!animal->isAlive()) {
    std::cout << "Animal is not alive.\n";
    return false;
  }

  if (zoo.getBalance() < animal->getFeedingCost()) {
    std::cout << "Not enough money to feed " << animal->getName() << ".\n";
    return false;
  }

  std::cout << name_ << " fed " << animal->getName() << "\n";
  zoo.spendMoney(animal->getFeedingCost());
  animal->eat(20);
  return true;
}

bool Player::playWithAnimal(Animal* animal) {
  if (!animal) {
    std::cout << "Animal does not exist!\n";
    return false;
  }

  if (!animal->isAlive()) {
    std::cout << "Animal is not alive.\n";
    return false;
  }

  if (animal->getEnergyLevel() < 20) {
    std::cout << animal->getName() << " is too tired to play.\n";
    return false;
  }

  std::cout << name_ << " played with " << animal->getName() << "\n";
  animal->updateEnergy(-10);
  animal->updateHappiness(15);
  animal->updateHunger(5);
  return true;
}

bool Player::exerciseAnimal(Animal* animal) {
  if (!animal) {
    std::cout << "Animal does not exist!\n";
    return false;
  }

  if (!animal->isAlive()) {
    std::cout << "Animal is not alive.\n";
    return false;
  }

  // check if animal has enough energy
  if (animal->getEnergyLevel() < 30) {
    std::cout << animal->getName() << " is too tired to exercise.\n";
    return false;
  }

  std::cout << name_ << " exercised " << animal->getName() << ".\n";
  animal->updateEnergy(-20);
  animal->updateHealth(10);
  animal->updateHappiness(10);
  animal->updateHunger(10);
  return true;
}

bool Player::treatAnimal(Zoo& zoo, Animal* animal) {
  if (!animal) {
    std::cout << "Animal does not exist!\n";
    return false;
  }

  if (!animal->isAlive()) {
    std::cout << "Animal is not alive.\n";
    return false;
  }

  if (zoo.getBalance() < 50.0) {
    std::cout << "Not enough money to treat " << animal->getName() << "!\n";
    return false;
  }

  zoo.spendMoney(50.0);
  std::cout << name_ << " gave medical care to " << animal->getName() << ".\n";
  animal->updateHealth(30);
  return true;
}

bool Player::cleanExhibit(Exhibit* exhibit) {
  if (!exhibit) {
    std::cout << "Exhibit does not exist.\n";
    return false;
  }

  std::cout << name_ << " cleaned " << exhibit->getName() << ".\n";
  exhibit->clean();
  return true;
}
