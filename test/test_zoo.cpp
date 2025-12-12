#include <gtest/gtest.h>

#include "bear.h"
#include "exhibit.h"
#include "penguin.h"
#include "rabbit.h"
#include "zoo.h"

TEST(ZooTest, ConstructorInitialization) {
  Zoo zoo("SF Zoo", 2000.0);
  EXPECT_EQ(zoo.getName(), "SF Zoo");
  EXPECT_EQ(zoo.getDay(), 1);
  EXPECT_EQ(zoo.getBalance(), 2000.0);
  EXPECT_EQ(zoo.getAnimalCount(), 0);
  EXPECT_EQ(zoo.getExhibitCount(), 0);
}

TEST(ZooTest, ConstructorDefaultBalance) {
  Zoo zoo("SF Zoo");
  EXPECT_EQ(zoo.getBalance(), 2000.0);
}

TEST(ZooTest, PurchaseAnimal) {
  Zoo zoo("Oakland Zoo");
  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  double rabbit_cost = rabbit->getPurchaseCost();

  zoo.purchaseAnimal(std::move(rabbit));
  EXPECT_EQ(zoo.getAnimalCount(), 1);
  EXPECT_EQ(zoo.getBalance(), 2000.0 - rabbit_cost);
}

TEST(ZooTest, PurchaseMultipleAnimals) {
  Zoo zoo("Oakland Zoo", 2500.0);
  zoo.purchaseAnimal(std::make_unique<Rabbit>("Miffy", 7));
  zoo.purchaseAnimal(std::make_unique<Penguin>("Pororo", 8));
  zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 4));
  EXPECT_EQ(zoo.getAnimalCount(), 3);
}

TEST(ZooTest, CannotPurchaseAnimalWithInsufficientFunds) {
  Zoo zoo("Oakland Zoo", 100.0);
  EXPECT_FALSE(zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 4)));
  EXPECT_EQ(zoo.getAnimalCount(), 0);
  EXPECT_EQ(zoo.getBalance(), 100.0);
}

TEST(ZooTest, CorrectBalance) {
  Zoo zoo("Oakland Zoo");

  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  double rabbit_cost = rabbit->getPurchaseCost();
  zoo.purchaseAnimal(std::move(rabbit));

  auto penguin = std::make_unique<Penguin>("Pororo", 8);
  double penguin_cost = penguin->getPurchaseCost();
  zoo.purchaseAnimal(std::move(penguin));

  EXPECT_EQ(zoo.getBalance(), 2000.0 - rabbit_cost - penguin_cost);
}

TEST(ZooTest, SellAnimal) {
  Zoo zoo("Oakland Zoo");
  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  double rabbit_cost = rabbit->getPurchaseCost();
  Animal* rabbit_ptr = rabbit.get();

  zoo.purchaseAnimal(std::move(rabbit));
  double balance_after_purchase = zoo.getBalance();

  zoo.sellAnimal(rabbit_ptr);
  EXPECT_EQ(zoo.getAnimalCount(), 0);
  EXPECT_EQ(zoo.getBalance(), balance_after_purchase + (rabbit_cost / 2.0));
}

TEST(ZooTest, CannotSellNullAnimal) {
  Zoo zoo("Oakland Zoo");
  EXPECT_FALSE(zoo.sellAnimal(nullptr));
}

TEST(ZooTest, CannotSellNonexistentAnimal) {
  Zoo zoo("Oakland Zoo");
  Bear bear("Corduroy", 4);
  EXPECT_FALSE(zoo.sellAnimal(&bear));
  EXPECT_EQ(zoo.getBalance(), 2000.0);
}

TEST(ZooTest, SellAnimalRemovesFromExhibit) {
  Zoo zoo("SF Zoo", 2500.0);

  auto bear = std::make_unique<Bear>("Corduroy", 4);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  auto exhibit = std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(bear_ptr, exhibit_ptr);
  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 1);

  zoo.sellAnimal(bear_ptr);
  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 0);
}

TEST(ZooTest, GetAnimal) {
  Zoo zoo("Oakland Zoo");

  auto bear = std::make_unique<Bear>("Corduroy", 4);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));
  auto animals = zoo.getAllAnimals();

  EXPECT_EQ(animals[0], bear_ptr);
}

TEST(ZooTest, GetAnimalOutOfBounds) {
  Zoo zoo("Oakland Zoo");

  zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 4));
  auto animals = zoo.getAllAnimals();

  EXPECT_NE(animals[0], nullptr);
  EXPECT_EQ(animals[1], nullptr);
}

TEST(ZooTest, GetAnimalFromEmptyZoo) {
  Zoo zoo("Oakland Zoo");
  auto animals = zoo.getAllAnimals();
  EXPECT_EQ(animals.size(), 0);
}

TEST(ZooTest, GetAllAnimals) {
  Zoo zoo("Oakland Zoo", 2500.0);
  zoo.purchaseAnimal(std::make_unique<Rabbit>("Miffy", 7));
  zoo.purchaseAnimal(std::make_unique<Penguin>("Pororo", 8));
  zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 4));
  EXPECT_EQ(zoo.getAllAnimals().size(), 3);
}

TEST(ZooTest, GetAllAnimalsFromEmptyZoo) {
  Zoo zoo("Oakland Zoo");
  EXPECT_EQ(zoo.getAllAnimals().size(), 0);
}

TEST(ZooTest, GetAnimalsNeedingAttention) {
  Zoo zoo("Oakland Zoo");

  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  rabbit_ptr->updateHunger(85);
  auto needy = zoo.getAnimalsNeedingAttention();
  EXPECT_EQ(needy.size(), 1);
  EXPECT_EQ(needy[0], rabbit_ptr);
}

TEST(ZooTest, NoAnimalsNeedAttention) {
  Zoo zoo("Oakland Zoo");
  zoo.purchaseAnimal(std::make_unique<Rabbit>("Miffy", 7));
  EXPECT_EQ(zoo.getAnimalsNeedingAttention().size(), 0);
}

TEST(ZooTest, RemoveDeadAnimals) {
  Zoo zoo("Oakland Zoo");

  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));
  EXPECT_EQ(zoo.getAnimalCount(), 1);

  rabbit_ptr->updateHealth(-100);
  EXPECT_FALSE(rabbit_ptr->isAlive());

  zoo.removeDeadAnimals();
  EXPECT_EQ(zoo.getAnimalCount(), 0);
}

TEST(ZooTest, PurchaseExhibit) {
  Zoo zoo("San Diego Zoo");

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  double exhibit_cost = exhibit->getPurchaseCost();
  zoo.purchaseExhibit(std::move(exhibit));

  EXPECT_EQ(zoo.getExhibitCount(), 1);
  EXPECT_EQ(zoo.getBalance(), 2000.0 - exhibit_cost);
}

TEST(ZooTest, PurchaseMultipleExhibits) {
  Zoo zoo("San Diego Zoo");
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0));
  EXPECT_EQ(zoo.getExhibitCount(), 2);
}

TEST(ZooTest, CannotPurchaseExhibitWithInsufficientFunds) {
  Zoo zoo("San Diego Zoo", 100.0);
  EXPECT_FALSE(
      zoo.purchaseExhibit(std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0)));
  EXPECT_EQ(zoo.getExhibitCount(), 0);
  EXPECT_EQ(zoo.getBalance(), 100.0);
}

TEST(ZooTest, SellExhibit) {
  Zoo zoo("San Diego Zoo");

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  double exhibit_cost = exhibit->getPurchaseCost();
  zoo.purchaseExhibit(std::move(exhibit));

  double balance_after_purchase = zoo.getBalance();

  zoo.sellExhibit(exhibit_ptr);
  EXPECT_EQ(zoo.getExhibitCount(), 0);
  EXPECT_EQ(zoo.getBalance(), balance_after_purchase + (exhibit_cost / 2.0));
}

TEST(ZooTest, GetExhibit) {
  Zoo zoo("San Diego Zoo");
  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));
  EXPECT_EQ(zoo.getExhibit(0), exhibit_ptr);
}

TEST(ZooTest, GetExhibitOutOfBounds) {
  Zoo zoo("San Diego Zoo");
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0));
  EXPECT_NE(zoo.getExhibit(0), nullptr);
  EXPECT_EQ(zoo.getExhibit(1), nullptr);
}

TEST(ZooTest, GetAllExhibits) {
  Zoo zoo("San Diego Zoo");
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0));
  EXPECT_EQ(zoo.getAllExhibits().size(), 2);
}

TEST(ZooTest, GetExhibitsNeedingCleaning) {
  Zoo zoo("San Diego Zoo");

  auto clean_exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  zoo.purchaseExhibit(std::move(clean_exhibit));

  auto dirty_exhibit = std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Exhibit* dirty_exhibit_ptr = dirty_exhibit.get();
  zoo.purchaseExhibit(std::move(dirty_exhibit));

  dirty_exhibit_ptr->updateCleanliness(-60);
  std::vector<Exhibit*> dirty = zoo.getExhibitsNeedingCleaning();
  EXPECT_EQ(dirty.size(), 1);
  EXPECT_EQ(dirty[0], dirty_exhibit_ptr);
}

TEST(ZooTest, NoExhibitsNeedCleaning) {
  Zoo zoo("San Diego Zoo");
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0));
  EXPECT_EQ(zoo.getExhibitsNeedingCleaning().size(), 0);
}

TEST(ZooTest, AddAnimalToExhibit) {
  Zoo zoo("SF Zoo");
  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  EXPECT_TRUE(zoo.addAnimalToExhibit(rabbit_ptr, exhibit_ptr));
  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 1);
  EXPECT_EQ(zoo.findAnimalLocation(rabbit_ptr), exhibit_ptr);
}

TEST(ZooTest, CannotAddAnimalToFullExhibit) {
  Zoo zoo("SF Zoo");
  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 1, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto rabbit1 = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit1_ptr = rabbit1.get();
  zoo.purchaseAnimal(std::move(rabbit1));

  auto rabbit2 = std::make_unique<Rabbit>("My Melody", 5);
  Animal* rabbit2_ptr = rabbit2.get();
  zoo.purchaseAnimal(std::move(rabbit2));

  EXPECT_TRUE(zoo.addAnimalToExhibit(rabbit1_ptr, exhibit_ptr));
  EXPECT_FALSE(zoo.addAnimalToExhibit(rabbit2_ptr, exhibit_ptr));
  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 1);
}

TEST(ZooTest, RemoveAnimalFromExhibit) {
  Zoo zoo("SF Zoo", 2500.0);

  auto exhibit = std::make_unique<Exhibit>("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto penguin = std::make_unique<Penguin>("Pororo", 8);
  Animal* penguin_ptr = penguin.get();
  zoo.purchaseAnimal(std::move(penguin));

  zoo.addAnimalToExhibit(penguin_ptr, exhibit_ptr);

  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 1);
  EXPECT_TRUE(zoo.removeAnimalFromExhibit(penguin_ptr, exhibit_ptr));
  EXPECT_EQ(exhibit_ptr->getCapacityUsed(), 0);
  EXPECT_EQ(zoo.findAnimalLocation(penguin_ptr), nullptr);
}

TEST(ZooTest, CannotRemoveAnimalNotInExhibit) {
  Zoo zoo("SF Zoo");

  auto exhibit = std::make_unique<Exhibit>("Penguin Point", "Arctic", 5, 1500.0, 60.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto penguin = std::make_unique<Penguin>("Pororo", 8);
  Animal* penguin_ptr = penguin.get();
  zoo.purchaseAnimal(std::move(penguin));

  EXPECT_FALSE(zoo.removeAnimalFromExhibit(penguin_ptr, exhibit_ptr));
}

TEST(ZooTest, MoveAnimalToExhibit) {
  Zoo zoo("SF Zoo", 3500.0);

  auto exhibit1 = std::make_unique<Exhibit>("Bear Habitat 1", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit1_ptr = exhibit1.get();
  zoo.purchaseExhibit(std::move(exhibit1));

  auto exhibit2 = std::make_unique<Exhibit>("Bear Habitat 2", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit2_ptr = exhibit2.get();
  zoo.purchaseExhibit(std::move(exhibit2));

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  // add animal to first exhibit
  EXPECT_TRUE(zoo.addAnimalToExhibit(bear_ptr, exhibit1_ptr));
  EXPECT_EQ(exhibit1_ptr->getCapacityUsed(), 1);
  EXPECT_EQ(exhibit2_ptr->getCapacityUsed(), 0);
  EXPECT_EQ(zoo.findAnimalLocation(bear_ptr), exhibit1_ptr);

  // move animal to second exhibit
  EXPECT_TRUE(zoo.moveAnimalToExhibit(bear_ptr, exhibit2_ptr));
  EXPECT_EQ(exhibit1_ptr->getCapacityUsed(), 0);
  EXPECT_EQ(exhibit2_ptr->getCapacityUsed(), 1);
  EXPECT_EQ(zoo.findAnimalLocation(bear_ptr), exhibit2_ptr);
}

TEST(ZooTest, CannotMoveAnimalToExistingExhibit) {
  Zoo zoo("SF Zoo", 2500.0);

  auto exhibit = std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));
  EXPECT_TRUE(zoo.addAnimalToExhibit(bear_ptr, exhibit_ptr));

  EXPECT_FALSE(zoo.moveAnimalToExhibit(bear_ptr, exhibit_ptr));
}

TEST(ZooTest, CannotMoveAnimalNotInExhibit) {
  Zoo zoo("SF Zoo");

  auto exhibit = std::make_unique<Exhibit>("Bear Habitat 1", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  // animal is not part of any exhibits yet, cannot move it
  EXPECT_FALSE(zoo.moveAnimalToExhibit(bear_ptr, exhibit_ptr));
}

TEST(ZooTest, CannotMoveAnimalToFullExhibit) {
  Zoo zoo("SF Zoo", 5000.0);
  auto exhibit1 = std::make_unique<Exhibit>("Bear Habitat 1", "Forest", 1, 800.0, 35.0);
  Exhibit* exhibit1_ptr = exhibit1.get();
  zoo.purchaseExhibit(std::move(exhibit1));

  auto exhibit2 = std::make_unique<Exhibit>("Bear Habitat 2", "Forest", 3, 800.0, 35.0);
  Exhibit* exhibit2_ptr = exhibit2.get();
  zoo.purchaseExhibit(std::move(exhibit2));

  auto bear1 = std::make_unique<Bear>("Winnie", 8);
  Animal* bear1_ptr = bear1.get();
  zoo.purchaseAnimal(std::move(bear1));

  auto bear2 = std::make_unique<Bear>("Boris", 3);
  Animal* bear2_ptr = bear2.get();
  zoo.purchaseAnimal(std::move(bear2));

  zoo.addAnimalToExhibit(bear1_ptr, exhibit1_ptr);
  zoo.addAnimalToExhibit(bear2_ptr, exhibit2_ptr);

  EXPECT_FALSE(zoo.moveAnimalToExhibit(bear2_ptr, exhibit1_ptr));
  EXPECT_EQ(exhibit1_ptr->getCapacityUsed(), 1);
  EXPECT_EQ(zoo.findAnimalLocation(bear2_ptr), exhibit2_ptr);
}

TEST(ZooTest, CannotMoveNullAnimal) {
  Zoo zoo("SF Zoo");
  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));
  EXPECT_FALSE(zoo.moveAnimalToExhibit(nullptr, exhibit_ptr));
}

TEST(ZooTest, CannotMoveAnimalToNullExhibit) {
  Zoo zoo("SF Zoo");
  auto rabbit = std::make_unique<Rabbit>("My Melody", 5);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(rabbit_ptr, exhibit_ptr);
  EXPECT_FALSE(zoo.moveAnimalToExhibit(rabbit_ptr, nullptr));
}

TEST(ZooTest, FindAnimalLocation) {
  Zoo zoo("SF Zoo");

  auto rabbit = std::make_unique<Rabbit>("My Melody", 5);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  zoo.addAnimalToExhibit(rabbit_ptr, exhibit_ptr);
  EXPECT_EQ(zoo.findAnimalLocation(rabbit_ptr), exhibit_ptr);
}

TEST(ZooTest, FindAnimalLocationNotInAnyExhibit) {
  Zoo zoo("SF Zoo");

  auto rabbit = std::make_unique<Rabbit>("My Melody", 5);
  Animal* rabbit_ptr = rabbit.get();
  zoo.purchaseAnimal(std::move(rabbit));

  auto exhibit = std::make_unique<Exhibit>("Rabbit Meadow", "Grassland", 2, 300.0, 15.0);
  zoo.purchaseExhibit(std::move(exhibit));

  EXPECT_EQ(zoo.findAnimalLocation(rabbit_ptr), nullptr);
}

TEST(ZooTest, SpendMoney) {
  Zoo zoo("SF Zoo", 3000.0);

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  double purchase_cost = bear_ptr->getPurchaseCost();
  double feeding_cost = bear_ptr->getFeedingCost();
  bear_ptr->eat(20);
  zoo.spendMoney(feeding_cost);

  EXPECT_EQ(zoo.getBalance(), 3000.0 - purchase_cost - feeding_cost);
}

TEST(ZooTest, UpdateAnimalStats) {
  Zoo zoo("SF Zoo");

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  zoo.updateAnimalStats();
  EXPECT_EQ(bear_ptr->getHungerLevel(), 20);
  EXPECT_EQ(bear_ptr->getHappinessLevel(), 82);
  EXPECT_EQ(bear_ptr->getEnergyLevel(), 92);
}

TEST(ZooTest, CalculateVisitorCountHighRating) {
  Zoo zoo("SF Zoo", 3000.0);
  zoo.purchaseAnimal(std::make_unique<Bear>("Winnie", 8));
  EXPECT_EQ(zoo.calculateVisitorCount(), 13);
}

TEST(ZooTest, CalculateVisitorCountMediumRating) {
  Zoo zoo("SF Zoo", 3000.0);
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  bear_ptr->updateHappiness(-30);
  bear_ptr->updateHealth(-30);

  // 1.75 (happiness), 1.05 (health), 0.5 (cleanliness), 0.05 (financial) = 3.35 zoo rating
  // rating multpier = 1.0, animal count = 1, base visitors = 5 (no happiness bonus or penalties)
  EXPECT_EQ(zoo.calculateVisitorCount(), 6);
}

TEST(ZooTest, CalculateVisitorCountNeglectPenalty) {
  Zoo zoo("SF Zoo", 3000.0);
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  bear_ptr->updateHunger(85);

  EXPECT_GE(zoo.calculateVisitorCount(), 0);
  EXPECT_LE(zoo.calculateVisitorCount(), 11);
  // visitors = 10, happiness +2, neglect -3
  EXPECT_EQ(zoo.calculateVisitorCount(), 10);
}

TEST(ZooTest, CalculateVisitorCountDirtyExhibit) {
  Zoo zoo("SF Zoo", 5000.0);
  zoo.purchaseAnimal(std::make_unique<Bear>("Winnie", 8));
  auto exhibit = std::make_unique<Exhibit>("Bear Habitat", "Forest", 800.0, 3, 35.0);
  Exhibit* exhibit_ptr = exhibit.get();
  zoo.purchaseExhibit(std::move(exhibit));

  exhibit_ptr->updateCleanliness(-60);
  EXPECT_LT(zoo.calculateVisitorCount(), 12);
  EXPECT_EQ(zoo.calculateVisitorCount(), 11);
}

TEST(ZooTest, CalculateVisitorCountNeverNegative) {
  Zoo zoo("SF Zoo", 3000.0);
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  bear_ptr->updateHappiness(-80);
  bear_ptr->updateHealth(-90);
  bear_ptr->updateHunger(100);

  EXPECT_GE(zoo.calculateVisitorCount(), 0);
}

TEST(ZooTest, CalculateVisitorCountNoAnimals) {
  Zoo zoo("SF Zoo", 3000.0);
  EXPECT_EQ(zoo.calculateVisitorCount(), 0);
}

TEST(ZooTest, CalculateDailyRevenue) {
  Zoo zoo("SF Zoo");
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();

  int visitor_count = zoo.calculateVisitorCount();
  double expected_revenue = visitor_count * 15.0;
  EXPECT_EQ(zoo.calculateDailyRevenue(visitor_count), expected_revenue);
}

TEST(ZooTest, CalculateDailyExpenses) {
  Zoo zoo("SF Zoo");
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));
  double maintenance_cost = bear_ptr->getMaintenanceCost();
  EXPECT_EQ(zoo.calculateDailyExpenses(), 98.0);
}

TEST(ZooTest, CalculateZooRatingPerfectConditions) {
  Zoo zoo("SF Zoo", 5000.0);
  zoo.purchaseAnimal(std::make_unique<Bear>("Winnie", 8));

  // health 100, happiness 100, no exhibits, balance 3500 after purchasing bear
  // expected: 2.5 (happiness) + 1.5 (health) + 0.5 (no exhibits) + 0.25 (financial) = 4.75
  EXPECT_NEAR(zoo.calculateZooRating(), 4.75, 0.01);
}

TEST(ZooTest, CalculateZooRatingWithExhibit) {
  Zoo zoo("SF Zoo", 5000.0);
  zoo.purchaseAnimal(std::make_unique<Bear>("Winnie", 8));
  zoo.purchaseExhibit(std::make_unique<Exhibit>("Bear Habitat", "Forest", 3, 800.0, 35.0));

  // health 100, happiness 100, 1 exhibit, balance 2700 after purchasing bear
  // expected: 2.5 (happiness) + 1.5 (health) + 0.75 (1 exhibit) + 0.15 (financial) = 4.9
  EXPECT_NEAR(zoo.calculateZooRating(), 5.0, 0.01);
}

TEST(ZooTest, CalculateZooRatingNeglectedAnimal) {
  Zoo zoo("SF Zoo", 5000.0);
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  bear_ptr->updateHappiness(-50);
  bear_ptr->updateHealth(-80);

  // expected: 1.25 (happiness) + 0.3 (health) + 0.5 (no exhibits) + 0.25 (financial) = 2.3
  EXPECT_NEAR(zoo.calculateZooRating(), 2.3, 0.01);
}

TEST(ZooTest, CalculateZooRatingNoAnimals) {
  Zoo zoo("SF Zoo");
  EXPECT_EQ(zoo.calculateZooRating(), 0.65);
}

TEST(ZooTest, AdvanceDay) {
  Zoo zoo("SF Zoo");
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  double old_balance = zoo.getBalance();
  zoo.calculateEndOfDayStats();
  EXPECT_EQ(zoo.getDay(), 1);
  zoo.displayEndOfDaySummary();
  zoo.advanceDay();
  EXPECT_EQ(zoo.getDay(), 2);
}
