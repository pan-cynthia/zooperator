#include <gtest/gtest.h>

#include "bear.h"
#include "exhibit.h"
#include "penguin.h"
#include "rabbit.h"
#include "zoo.h"

TEST(ZooTest, ConstructorInitialization) {
  Zoo zoo("SF Zoo", 10000);
  EXPECT_EQ(zoo.getName(), "SF Zoo");
  EXPECT_EQ(zoo.getDay(), 0);
  EXPECT_EQ(zoo.getBalance(), 10000.0);
  EXPECT_EQ(zoo.getAnimalCount(), 0);
  EXPECT_EQ(zoo.getExhibitCount(), 0);
}

TEST(ZooTest, ConstructorDefaultBalance) {
  Zoo zoo("SF Zoo");
  EXPECT_EQ(zoo.getBalance(), 10000.0);
}

TEST(ZooTest, PurchaseAnimal) {
  Zoo zoo("Oakland Zoo");
  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  double rabbit_cost = rabbit->getPurchaseCost();

  zoo.purchaseAnimal(std::move(rabbit));
  EXPECT_EQ(zoo.getAnimalCount(), 1);
  EXPECT_EQ(zoo.getBalance(), 10000.0 - rabbit_cost);
}

TEST(ZooTest, PurchaseMultipleAnimals) {
  Zoo zoo("Oakland Zoo");
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

  EXPECT_EQ(zoo.getBalance(), 10000.0 - rabbit_cost - penguin_cost);
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
  EXPECT_EQ(zoo.getBalance(), 10000.0);
}

TEST(ZooTest, SellAnimalRemovesFromExhibit) {
  Zoo zoo("SF Zoo");

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

  EXPECT_EQ(zoo.getAnimal(0), bear_ptr);
}

TEST(ZooTest, GetAnimalOutOfBounds) {
  Zoo zoo("Oakland Zoo");

  zoo.purchaseAnimal(std::make_unique<Bear>("Corduroy", 4));

  EXPECT_NE(zoo.getAnimal(0), nullptr);
  EXPECT_EQ(zoo.getAnimal(1), nullptr);
}

TEST(ZooTest, GetAnimalFromEmptyZoo) {
  Zoo zoo("Oakland Zoo");
  EXPECT_EQ(zoo.getAnimal(0), nullptr);
}

TEST(ZooTest, GetAllAnimals) {
  Zoo zoo("Oakland Zoo");
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
  EXPECT_EQ(zoo.getBalance(), 10000.0 - exhibit_cost);
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
  Zoo zoo("SF Zoo");

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
  Zoo zoo("SF Zoo");

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
  Zoo zoo("SF Zoo");

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
  Zoo zoo("SF Zoo");
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
  Zoo zoo("SF Zoo");

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  double purchase_cost = bear_ptr->getPurchaseCost();
  double feeding_cost = bear_ptr->getFeedingCost();
  bear_ptr->eat(20);
  zoo.spendMoney(feeding_cost);

  EXPECT_EQ(zoo.getBalance(), 10000.0 - purchase_cost - feeding_cost);
}

TEST(ZooTest, UpdateAnimalStats) {
  Zoo zoo("SF Zoo");

  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  zoo.updateAnimalStats();
  EXPECT_EQ(bear_ptr->getHungerLevel(), 5);
  EXPECT_EQ(bear_ptr->getHappinessLevel(), 99);
  EXPECT_EQ(bear_ptr->getEnergyLevel(), 95);
}

TEST(ZooTest, CalculateVisitorCount) {
  Zoo zoo("SF Zoo", 3000.0);
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  int happiness = bear_ptr->getHappinessLevel();
  int health = bear_ptr->getHealthLevel();
  zoo.purchaseAnimal(std::move(bear));

  double avg_happiness = happiness;
  double avg_health = health;
  double happiness_score = (avg_happiness / 100.0) * 2.0;
  double health_score = (avg_health / 100.0) * 1.5;
  double cleanliness_score = 0.5;
  double financial_score = 0.3;

  double rating = happiness_score + health_score + cleanliness_score + financial_score;
  rating = std::min(5.0, std::max(0.0, rating));
  int expected_visitors = 10 * (1.0 + rating / 5.0);

  int bonus = 0;
  if (happiness > 70) {
    bonus = static_cast<int>((happiness / 10.0) * 20);
  }
  EXPECT_EQ(zoo.calculateVisitorCount(), expected_visitors + bonus);
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
  EXPECT_EQ(zoo.calculateDailyExpenses(), 60.0);
}

TEST(ZooTest, AdvanceDay) {
  Zoo zoo("SF Zoo");
  auto bear = std::make_unique<Bear>("Winnie", 8);
  Animal* bear_ptr = bear.get();
  zoo.purchaseAnimal(std::move(bear));

  double old_balance = zoo.getBalance();
  zoo.advanceDay();
  EXPECT_EQ(zoo.getDay(), 1);
}
