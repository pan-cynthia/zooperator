#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "animal.h"
#include "exhibit.h"
#include "zoo.h"

class Player {
 public:
  Player(std::string name);

  const std::string& getName() const;

  bool feedAnimal(Zoo& zoo, Animal* animal);
  bool playWithAnimal(Animal* animal);
  bool exerciseAnimal(Animal* animal);
  bool treatAnimal(Zoo& zoo, Animal* animal);

  bool cleanExhibit(Exhibit* exhibit);

 private:
  std::string name_;
};

#endif  // PLAYER_H
