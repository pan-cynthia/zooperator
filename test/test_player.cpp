#include <gtest/gtest.h>

#include "bear.h"
#include "exhibit.h"
#include "penguin.h"
#include "player.h"
#include "rabbit.h"
#include "zoo.h"

TEST(PlayerTest, ConstructorInitialization) {
  Player player("Alice");
  EXPECT_EQ(player.getName(), "Alice");
}

TEST(PlayerTest, FeedAnimal) {
  Player player("Alice");
  Zoo zoo("SF Zoo");
  Penguin penguin("Pororo", 8);

  penguin.updateHunger(20);
  EXPECT_TRUE(player.feedAnimal(zoo, &penguin));
  EXPECT_EQ(penguin.getHungerLevel(), 0);
  EXPECT_EQ(zoo.getBalance(), 1500.0 - penguin.getFeedingCost());
}

TEST(PlayerTest, CannotFeedNullAnimal) {
  Player player("Alice");
  Zoo zoo("SF Zoo");
  EXPECT_FALSE(player.feedAnimal(zoo, nullptr));
}

TEST(PlayerTest, CannotFeedDeadAnimal) {
  Player player("Alice");
  Zoo zoo("SF Zoo");
  Penguin penguin("Pororo", 8);

  penguin.updateHealth(-100);
  EXPECT_FALSE(player.feedAnimal(zoo, &penguin));
}

TEST(PlayerTest, LowBalanceCannotFeedAnimal) {
  Player player("Alice");
  Zoo zoo("SF Zoo", 5.0);
  Penguin penguin("Pororo", 8);

  EXPECT_FALSE(player.feedAnimal(zoo, &penguin));
  EXPECT_EQ(zoo.getBalance(), 5.0);
}

TEST(PlayerTest, PlayWithAnimal) {
  Player player("Bob");
  Bear bear("Teddiursa", 5);

  bear.updateHappiness(-35);
  EXPECT_EQ(bear.getEnergyLevel(), 100);
  EXPECT_EQ(bear.getHappinessLevel(), 65);
  EXPECT_EQ(bear.getHungerLevel(), 0);

  EXPECT_TRUE(player.playWithAnimal(&bear));

  EXPECT_EQ(bear.getEnergyLevel(), 90);
  EXPECT_EQ(bear.getHappinessLevel(), 80);
  EXPECT_EQ(bear.getHungerLevel(), 5);
}

TEST(PlayerTest, CannotPlayWithNullAnimal) {
  Player player("Bob");
  EXPECT_FALSE(player.playWithAnimal(nullptr));
}

TEST(PlayerTest, CannotPlayWithDeadAnimal) {
  Player player("Bob");
  Bear bear("Teddiursa", 5);
  bear.updateHealth(-100);
  EXPECT_FALSE(player.playWithAnimal(&bear));
}

TEST(PlayerTest, CannotPlayWithTiredAnimal) {
  Player player("Bob");
  Bear bear("Teddiursa", 5);
  bear.updateEnergy(-85);
  EXPECT_FALSE(player.playWithAnimal(&bear));
}

TEST(PlayerTest, ExerciseAnimal) {
  Player player("Bob");
  Rabbit rabbit("Buster", 8);

  rabbit.updateHealth(-50);
  rabbit.updateHappiness(-60);
  EXPECT_EQ(rabbit.getEnergyLevel(), 100);
  EXPECT_EQ(rabbit.getHealthLevel(), 50);
  EXPECT_EQ(rabbit.getHungerLevel(), 0);
  EXPECT_EQ(rabbit.getHappinessLevel(), 40);

  EXPECT_TRUE(player.exerciseAnimal(&rabbit));

  EXPECT_EQ(rabbit.getEnergyLevel(), 80);
  EXPECT_EQ(rabbit.getHealthLevel(), 60);
  EXPECT_EQ(rabbit.getHungerLevel(), 10);
  EXPECT_EQ(rabbit.getHappinessLevel(), 50);
}

TEST(PlayerTest, CannotExerciseNullAnimal) {
  Player player("Bob");
  EXPECT_FALSE(player.exerciseAnimal(nullptr));
}

TEST(PlayerTest, CannotExerciseDeadAnimal) {
  Player player("Bob");
  Rabbit rabbit("Buster", 8);

  rabbit.updateHealth(-100);
  EXPECT_FALSE(player.exerciseAnimal(&rabbit));
}

TEST(PlayerTest, CannotExerciseTiredAnimal) {
  Player player("Bob");
  Rabbit rabbit("Buster", 8);

  rabbit.updateEnergy(-75);
  EXPECT_FALSE(player.exerciseAnimal(&rabbit));
}

TEST(PlayerTest, TreatAnimal) {
  Player player("Bob");
  Zoo zoo("SF Zoo");
  Penguin penguin("Pororo", 8);

  penguin.updateHealth(-80);
  penguin.updateEnergy(-30);
  EXPECT_TRUE(player.treatAnimal(zoo, &penguin));

  EXPECT_EQ(penguin.getHealthLevel(), 50);
  EXPECT_EQ(penguin.getEnergyLevel(), 80);
  EXPECT_EQ(zoo.getBalance(), 1500.0 - 50.0);
}

TEST(PlayerTest, CannotTreatNullAnimal) {
  Player player("Bob");
  Zoo zoo("SF Zoo");
  EXPECT_FALSE(player.treatAnimal(zoo, nullptr));
}

TEST(PlayerTest, CannotTreatDeadAnimal) {
  Player player("Bob");
  Zoo zoo("SF Zoo");
  Penguin penguin("Pororo", 8);
  penguin.updateHealth(-100);
  EXPECT_FALSE(player.treatAnimal(zoo, &penguin));
}

TEST(PlayerTest, LowBalanceCannotTreatAnimal) {
  Player player("Bob");
  Zoo zoo("SF Zoo", 25.0);
  Penguin penguin("Pororo", 8);
  EXPECT_FALSE(player.treatAnimal(zoo, &penguin));
  EXPECT_EQ(zoo.getBalance(), 25.0);
}

TEST(PlayerTest, CleanExhibit) {
  Player player("Charlie");
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  exhibit.updateCleanliness(-40);
  EXPECT_TRUE(player.cleanExhibit(&exhibit));
  EXPECT_EQ(exhibit.getCleanliness(), 100);
}

TEST(PlayerTest, CannotCleanNullExhibit) {
  Player player("Charlie");
  EXPECT_FALSE(player.cleanExhibit(nullptr));
}

TEST(PlayerTest, CleanAlreadyCleanExhibit) {
  Player player("Charlie");
  Exhibit exhibit("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  EXPECT_TRUE(player.cleanExhibit(&exhibit));
  EXPECT_EQ(exhibit.getCleanliness(), 100);
}
