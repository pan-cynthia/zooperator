#include <gtest/gtest.h>

#include "bear.h"
#include "exhibit.h"
#include "penguin.h"
#include "rabbit.h"

TEST(ExhibitTest, ConstructorInitialization) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  EXPECT_EQ(exhibit.getName(), "Penguin Point");
  EXPECT_EQ(exhibit.getType(), "Arctic");
  EXPECT_EQ(exhibit.getMaxCapacity(), 5);
  EXPECT_EQ(exhibit.getCapacityUsed(), 0);
  EXPECT_EQ(exhibit.getCleanliness(), 100);
  EXPECT_EQ(exhibit.getPurchaseCost(), 1500.0);
  EXPECT_EQ(exhibit.getMaintenanceCost(), 60.0);
}

TEST(ExhibitTest, CanAddAnimal) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  EXPECT_TRUE(exhibit.canAddAnimal());

  Penguin penguin1("Ramon", 15);
  Penguin penguin2("Nestor", 16);
  Penguin penguin3("Raul", 14);
  Penguin penguin4("Lombardo", 15);
  Penguin penguin5("Rinaldo", 16);

  EXPECT_TRUE(exhibit.addAnimal(&penguin1));
  EXPECT_TRUE(exhibit.canAddAnimal());

  EXPECT_TRUE(exhibit.addAnimal(&penguin2));
  EXPECT_TRUE(exhibit.canAddAnimal());

  EXPECT_TRUE(exhibit.addAnimal(&penguin3));
  EXPECT_TRUE(exhibit.canAddAnimal());

  EXPECT_TRUE(exhibit.addAnimal(&penguin4));
  EXPECT_TRUE(exhibit.canAddAnimal());

  EXPECT_TRUE(exhibit.addAnimal(&penguin5));
  EXPECT_FALSE(exhibit.canAddAnimal());  // exhibit is full now
}

TEST(ExhibitTest, CannotAddSameAnimalTwice) {
  Exhibit exhibit("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Bear bear("Grizz", 25);

  EXPECT_TRUE(exhibit.addAnimal(&bear));
  EXPECT_FALSE(exhibit.addAnimal(&bear));
}

TEST(ExhibitTest, CannotAddAnimalWhenFull) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  EXPECT_TRUE(exhibit.canAddAnimal());

  Penguin penguin1("Ramon", 15);
  Penguin penguin2("Nestor", 16);
  Penguin penguin3("Raul", 14);
  Penguin penguin4("Lombardo", 15);
  Penguin penguin5("Rinaldo", 16);
  Penguin penguin6("Mumble", 8);

  EXPECT_TRUE(exhibit.addAnimal(&penguin1));
  EXPECT_TRUE(exhibit.addAnimal(&penguin2));
  EXPECT_TRUE(exhibit.addAnimal(&penguin3));
  EXPECT_TRUE(exhibit.addAnimal(&penguin4));
  EXPECT_TRUE(exhibit.addAnimal(&penguin5));

  EXPECT_FALSE(exhibit.canAddAnimal());
  EXPECT_FALSE(exhibit.addAnimal(&penguin6));

  EXPECT_EQ(exhibit.getCapacityUsed(), 5);
  EXPECT_EQ(exhibit.getMaxCapacity(), 5);
}

TEST(ExhibitTest, CannotAddNullAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  EXPECT_FALSE(exhibit.addAnimal(nullptr));
  EXPECT_EQ(exhibit.getCapacityUsed(), 0);
}

TEST(ExhibitTest, AddAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  EXPECT_EQ(exhibit.getCapacityUsed(), 0);

  Rabbit rabbit("Judy Hopps", 8);
  EXPECT_TRUE(exhibit.addAnimal(&rabbit));
  EXPECT_EQ(exhibit.getCapacityUsed(), 1);
}

TEST(ExhibitTest, AddMultipleAnimals) {
  Exhibit exhibit("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Bear bear1("Grizz", 25);
  Bear bear2("Ice Bear", 23);
  Bear bear3("Panda", 24);

  EXPECT_TRUE(exhibit.addAnimal(&bear1));
  EXPECT_TRUE(exhibit.addAnimal(&bear2));
  EXPECT_TRUE(exhibit.addAnimal(&bear3));

  EXPECT_EQ(exhibit.getCapacityUsed(), 3);
}

TEST(ExhibitTest, RemoveAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);

  Rabbit rabbit("Judy Hopps", 8);
  EXPECT_TRUE(exhibit.addAnimal(&rabbit));
  EXPECT_EQ(exhibit.getCapacityUsed(), 1);

  EXPECT_TRUE(exhibit.removeAnimal(&rabbit));
  EXPECT_EQ(exhibit.getCapacityUsed(), 0);
}

TEST(ExhibitTest, RemoveNullAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  EXPECT_FALSE(exhibit.removeAnimal(nullptr));
}

TEST(ExhibitTest, RemoveNonexistentAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Rabbit rabbit("Judy Hopps", 8);
  EXPECT_FALSE(exhibit.removeAnimal(&rabbit));
}

TEST(ExhibitTest, ContainsAnimal) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  Penguin penguin("Mumble", 8);

  EXPECT_FALSE(exhibit.containsAnimal(&penguin));
  exhibit.addAnimal(&penguin);
  EXPECT_TRUE(exhibit.containsAnimal(&penguin));

  exhibit.removeAnimal(&penguin);
  EXPECT_FALSE(exhibit.containsAnimal(&penguin));
}

TEST(ExhibitTest, ContainsNullAnimal) {
  Exhibit exhibit("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  EXPECT_FALSE(exhibit.containsAnimal(nullptr));
}

TEST(ExhibitTest, GetAnimal) {
  Exhibit exhibit("Bear Habitat", "Forest", 3, 800.0, 35.0);

  Bear bear("Grizz", 25);
  exhibit.addAnimal(&bear);
  auto animals = exhibit.getAllAnimals();
  EXPECT_EQ(animals[0]->getName(), "Grizz");
}

TEST(ExhibitTest, GetAnimalOutOfBounds) {
  Exhibit exhibit("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Bear bear("Grizz", 25);
  exhibit.addAnimal(&bear);
  auto animals = exhibit.getAllAnimals();
  EXPECT_NE(animals[0], nullptr);
  EXPECT_EQ(animals[1], nullptr);
}

TEST(ExhibitTest, GetAnimalFromEmptyExhibit) {
  Exhibit exhibit("Bear Habitat", "Forest", 3, 800.0, 35.0);
  auto animals = exhibit.getAllAnimals();
  EXPECT_EQ(animals.size(), 0);
}

TEST(ExhibitTest, InitialCleanliness) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  EXPECT_EQ(exhibit.getCleanliness(), 100);
}

TEST(ExhibitTest, UpdateCleanliness) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  exhibit.updateCleanliness(-20);
  EXPECT_EQ(exhibit.getCleanliness(), 80);
  exhibit.updateCleanliness(15);
  EXPECT_EQ(exhibit.getCleanliness(), 95);
  exhibit.updateCleanliness(-30);
  EXPECT_EQ(exhibit.getCleanliness(), 65);
}

TEST(ExhibitTest, CleanlinessClampAt100) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  exhibit.updateCleanliness(10);
  EXPECT_EQ(exhibit.getCleanliness(), 100);
}

TEST(ExhibitTest, CleanlinessClampAt0) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  exhibit.updateCleanliness(-150);
  EXPECT_EQ(exhibit.getCleanliness(), 0);
}

TEST(ExhibitTest, CleanExhibit) {
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  exhibit.updateCleanliness(-60);
  exhibit.clean();
  EXPECT_EQ(exhibit.getCleanliness(), 100);
}
