#include <gtest/gtest.h>

#include "animal.h"
#include "penguin.h"

TEST(AnimalTest, ConstructorInitialization) {
  Penguin penguin("Pororo", 8);
  EXPECT_EQ(penguin.getName(), "Pororo");
  EXPECT_EQ(penguin.getSpecies(), "Penguin");
  EXPECT_EQ(penguin.getAge(), 8);
  EXPECT_EQ(penguin.getHealthLevel(), 100);
  EXPECT_EQ(penguin.getHungerLevel(), 0);
  EXPECT_EQ(penguin.getHappinessLevel(), 100);
  EXPECT_EQ(penguin.getEnergyLevel(), 100);
}

TEST(AnimalTest, StatsClampAt100) {
  Penguin penguin("Pororo", 8);
  penguin.updateHealth(50);
  EXPECT_EQ(penguin.getHealthLevel(), 100);

  penguin.updateHunger(110);
  EXPECT_EQ(penguin.getHungerLevel(), 100);

  penguin.updateHappiness(10);
  EXPECT_EQ(penguin.getHappinessLevel(), 100);

  penguin.updateEnergy(25);
  EXPECT_EQ(penguin.getEnergyLevel(), 100);
}

TEST(AnimalTest, StatsClampAt0) {
  Penguin penguin("Pororo", 8);
  penguin.updateHealth(-150);
  EXPECT_EQ(penguin.getHealthLevel(), 0);

  penguin.updateHunger(-15);
  EXPECT_EQ(penguin.getHungerLevel(), 0);

  penguin.updateHappiness(-125);
  EXPECT_EQ(penguin.getHappinessLevel(), 0);

  penguin.updateEnergy(-101);
  EXPECT_EQ(penguin.getEnergyLevel(), 0);
}

TEST(AnimalTest, IsAlive) {
  Penguin penguin("Pororo", 8);
  EXPECT_TRUE(penguin.isAlive());

  penguin.updateHealth(-100);
  EXPECT_FALSE(penguin.isAlive());
}

TEST(AnimalTest, NeedsAttentionWhenHealthLow) {
  Penguin penguin("Pororo", 8);
  EXPECT_FALSE(penguin.needsAttention());

  penguin.updateHealth(-90);  // health = 10
  EXPECT_TRUE(penguin.needsAttention());
}

TEST(AnimalTest, NeedsAttentionWhenHungerHigh) {
  Penguin penguin("Pororo", 8);
  EXPECT_FALSE(penguin.needsAttention());

  penguin.updateHunger(85);  // hunger = 85
  EXPECT_TRUE(penguin.needsAttention());
}

TEST(AnimalTest, NeedsAttentionWhenHappinessLow) {
  Penguin penguin("Pororo", 8);
  EXPECT_FALSE(penguin.needsAttention());

  penguin.updateHappiness(-82);  // happiness = 18
  EXPECT_TRUE(penguin.needsAttention());
}

TEST(AnimalTest, NeedsAttentionWhenEnergyLow) {
  Penguin penguin("Pororo", 8);
  EXPECT_FALSE(penguin.needsAttention());

  penguin.updateEnergy(-99);
  EXPECT_TRUE(penguin.needsAttention());
}

TEST(AnimalTest, DoesNotNeedAttention) {
  Penguin penguin("Pororo", 8);
  penguin.updateHealth(-50);     // health = 50
  penguin.updateHunger(40);      // hunger = 40
  penguin.updateHappiness(-30);  // happiness = 70
  penguin.updateEnergy(-15);     // energy = 85
  EXPECT_FALSE(penguin.needsAttention());
}

TEST(AnimalTest, EatingReducesHunger) {
  Penguin penguin("Pororo", 8);
  penguin.updateHunger(50);  // make hungry
  penguin.eat(20);
  EXPECT_EQ(penguin.getHungerLevel(), 30);
}

TEST(AnimalTest, EatingIncreasesHappiness) {
  Penguin penguin("Pororo", 8);
  penguin.updateHappiness(-30);  // happiness = 70
  penguin.eat(20);
  EXPECT_EQ(penguin.getHappinessLevel(), 75);  // 70 + 5
}

TEST(AnimalTest, EatingIncreasesEnergy) {
  Penguin penguin("Pororo", 8);
  penguin.updateEnergy(-10);
  penguin.eat(20);
  EXPECT_EQ(penguin.getEnergyLevel(), 95);
}

TEST(AnimalTest, EatingZeroAmount) {
  Penguin penguin("Pororo", 8);
  penguin.updateHunger(50);

  int initial_hunger = penguin.getHungerLevel();
  penguin.eat(0);
  EXPECT_EQ(penguin.getHungerLevel(), initial_hunger);
}

TEST(AnimalTest, EatingNegativeAmount) {
  Penguin penguin("Pororo", 8);
  penguin.updateHunger(40);

  int initial_hunger = penguin.getHungerLevel();  // hunger = 40
  penguin.eat(-10);
  EXPECT_EQ(penguin.getHungerLevel(), initial_hunger);
}

TEST(AnimalTest, SleepingRestoresEnergy) {
  Penguin penguin("Pororo", 8);
  penguin.updateEnergy(-70);  // energy = 30

  penguin.sleep();
  EXPECT_EQ(penguin.getEnergyLevel(), 38);
}

TEST(AnimalTest, SleepingRestoresHealth) {
  Penguin penguin("Pororo", 8);
  penguin.updateHealth(-15);  // health = 85

  penguin.sleep();
  EXPECT_EQ(penguin.getHealthLevel(), 86);
}

TEST(AnimalTest, SleepingIncreasesHunger) {
  Penguin penguin("Pororo", 8);
  penguin.updateHunger(25);  // hunger = 25

  penguin.sleep();
  EXPECT_EQ(penguin.getHungerLevel(), 33);
}
