#include <gtest/gtest.h>

#include "bear.h"
#include "elephant.h"
#include "exhibit.h"
#include "lion.h"
#include "monkey.h"
#include "penguin.h"
#include "player.h"
#include "rabbit.h"
#include "tortoise.h"
#include "zoo.h"

TEST(IntegrationTest, CompleteAnimalCareWorkflow) {
  Zoo zoo("SF Zoo", 5000.0);
  Player player("Bob");

  // purchase animals
  auto lion = std::make_unique<Lion>("Simba", 12);
  Animal* lion_ptr = lion.get();
  zoo.purchaseAnimal(std::move(lion));

  auto monkey = std::make_unique<Monkey>("Bananas", 5);
  Animal* monkey_ptr = monkey.get();
  zoo.purchaseAnimal(std::move(monkey));

  // purchase exhibits
  auto savanna = std::make_unique<Exhibit>("Plains", "Savanna", 3, 1000.0, 50.0);
  Exhibit* savanna_ptr = savanna.get();
  zoo.purchaseExhibit(std::move(savanna));

  auto jungle = std::make_unique<Exhibit>("Amazon", "Jungle", 4, 800.0, 45.0);
  Exhibit* jungle_ptr = jungle.get();
  zoo.purchaseExhibit(std::move(jungle));

  // add animals to preferred exhibits
  EXPECT_TRUE(zoo.addAnimalToExhibit(lion_ptr, savanna_ptr));
  EXPECT_TRUE(zoo.addAnimalToExhibit(monkey_ptr, jungle_ptr));

  // verify animals are not homeless
  EXPECT_EQ(zoo.findAnimalLocation(lion_ptr), savanna_ptr);
  EXPECT_EQ(zoo.findAnimalLocation(monkey_ptr), jungle_ptr);

  // take care of animals
  EXPECT_TRUE(player.feedAnimal(zoo, lion_ptr));
  EXPECT_TRUE(player.exerciseAnimal(lion_ptr));
  EXPECT_TRUE(player.playWithAnimal(monkey_ptr));

  // clean exhibits
  jungle_ptr->updateCleanliness(-40);
  EXPECT_TRUE(player.cleanExhibit(jungle_ptr));

  // check zoo stats
  EXPECT_GT(zoo.getBalance(), 0);
  EXPECT_EQ(zoo.getAnimalCount(), 2);
  EXPECT_EQ(zoo.getExhibitCount(), 2);
}

TEST(IntegrationTest, HabitatAffectsHappiness) {
  Zoo zoo("SF Zoo", 5000.0);

  auto bear = std::make_unique<Bear>("Corduroy", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  // wrong habitat
  auto arctic = std::make_unique<Exhibit>("Brrr", "Arctic", 5, 1200.0, 60.0);
  Exhibit* arctic_ptr = arctic.get();
  zoo.purchaseExhibit(std::move(arctic));

  // preferred habitat
  auto forest = std::make_unique<Exhibit>("Trees", "Forest", 3, 600.0, 35.0);
  Exhibit* forest_ptr = forest.get();
  zoo.purchaseExhibit(std::move(forest));

  // place animal in wrong habitat
  zoo.addAnimalToExhibit(bear_ptr, arctic_ptr);
  zoo.updateAnimalStats();
  int wrong_habitat_happiness = bear_ptr->getHappinessLevel();

  // reset animal happiness to initial
  bear_ptr->updateHappiness(100);

  // place animal in preferred habitat
  zoo.moveAnimalToExhibit(bear_ptr, forest_ptr);
  zoo.updateAnimalStats();
  int preferred_habitat_happiness = bear_ptr->getHappinessLevel();
  EXPECT_GT(preferred_habitat_happiness, wrong_habitat_happiness);
}

TEST(IntegrationTest, HomelessAnimalPenalties) {
  Zoo zoo("SF Zoo", 3000.0);

  auto tortoise = std::make_unique<Tortoise>("Crush", 40);
  Animal* tortoise_ptr = tortoise.get();
  zoo.purchaseAnimal(std::move(tortoise));

  int initial_health = tortoise_ptr->getHealthLevel();
  int initial_happiness = tortoise_ptr->getHappinessLevel();

  // simulate day ending
  zoo.updateAnimalStats();

  EXPECT_EQ(zoo.findAnimalLocation(tortoise_ptr), nullptr);

  EXPECT_LT(tortoise_ptr->getHealthLevel(), initial_health);
  // -5 health for homeless, +1 from sleeping
  EXPECT_EQ(tortoise_ptr->getHealthLevel(), 96);

  // -15 happiness for homeless, -6 for daily decay
  EXPECT_LT(tortoise_ptr->getHappinessLevel(), initial_happiness);
  EXPECT_EQ(tortoise_ptr->getHappinessLevel(), 79);
}

TEST(IntegrationTest, BalanceUpdatingCorrectly) {
  Zoo zoo("SF Zoo", 3000.0);
  Player player("Bob");

  // purchase animal and exhibit
  auto animal = std::make_unique<Elephant>("Ellie", 12);
  Animal* animal_ptr = animal.get();
  zoo.purchaseAnimal(std::move(animal));
  double animal_cost = animal_ptr->getPurchaseCost();
  double feeding_cost = animal_ptr->getFeedingCost();

  auto exhibit = std::make_unique<Exhibit>("Savanna", "Plains", 3, 1000.0, 50.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));
  double exhibit_cost = exhibit_ptr->getPurchaseCost();

  zoo.addAnimalToExhibit(animal_ptr, exhibit_ptr);

  // check balance after purchases
  double balance_after_purchases = zoo.getBalance();
  EXPECT_EQ(balance_after_purchases, 3000.0 - animal_cost - exhibit_cost);

  // feed animal
  player.feedAnimal(zoo, animal_ptr);
  double balance_after_feeding = zoo.getBalance();
  EXPECT_LT(balance_after_feeding, balance_after_purchases);
  EXPECT_EQ(balance_after_feeding, balance_after_purchases - feeding_cost);

  // end day, calculate revenue and expenses
  int visitors = zoo.calculateVisitorCount();
  double revenue = zoo.calculateDailyRevenue(visitors);
  double expenses = zoo.calculateDailyExpenses();

  zoo.updateBalance();

  double end_day_balance = zoo.getBalance();
  EXPECT_EQ(end_day_balance, balance_after_feeding + revenue - expenses);
}
