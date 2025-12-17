#include "MissionSystem.h"

#include <iomanip>
#include <iostream>
#include <sstream>

MissionSystem::MissionSystem(Zoo& zoo) : zoo_(zoo) {}

std::vector<Mission>& MissionSystem::getMissions() {
  return missions_;
}

void MissionSystem::setupDailyMissions(int day) {
  missions_.clear();

  switch (day) {
    case 1:
      missions_.push_back(
          Mission(true, "Purchase your first animal", MissionType::OWN_X_ANIMALS, 1));
      missions_.push_back(
          Mission(true, "Purchase your first exhibit", MissionType::OWN_X_EXHIBITS, 1));
      missions_.push_back(
          Mission(true, "Add your animal to the exhibit", MissionType::ADD_ANIMAL_TO_EXHIBIT));
      missions_.push_back(Mission(false, "End day with balance of $1200+ (+$100)",
                                  MissionType::BALANCE_AT_LEAST, 0, 1200.0, 100.0, true));
      break;

    case 2:
      missions_.push_back(Mission(true, "Own 2 different species", MissionType::OWN_X_SPECIES, 2));
      missions_.push_back(Mission(true, "Feed an animal", MissionType::FEED_X_ANIMALS, 1));
      missions_.push_back(Mission(true, "End day with no homeless animals",
                                  MissionType::NO_HOMELESS_ANIMALS, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$100)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 100.0, true));

      break;

    case 3:
      missions_.push_back(Mission(true, "Own 3 different species", MissionType::OWN_X_SPECIES, 3));
      missions_.push_back(Mission(true, "Own 2 exhibits", MissionType::OWN_X_EXHIBITS, 2));
      missions_.push_back(Mission(true, "Feed 2 animals", MissionType::FEED_X_ANIMALS, 2));
      missions_.push_back(
          Mission(false, "Clean an exhibit (+$100)", MissionType::CLEAN_X_EXHIBITS, 1, 0.0, 100.0));

      break;

    case 4:
      missions_.push_back(Mission(true, "Play with an animal", MissionType::PLAY_WITH_ANIMAL));
      missions_.push_back(
          Mission(true, "Feed all animals", MissionType::FEED_X_ANIMALS, zoo_.getAnimalCount()));
      missions_.push_back(Mission(true, "All exhibits at 80+ cleanliness",
                                  MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, 80, 0.0, 0.0,
                                  true));
      missions_.push_back(Mission(true, "All animals in preferred habitats",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$100)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 100.0, true));
      break;

    case 5:
      missions_.push_back(Mission(true, "Own 4 different species", MissionType::OWN_X_SPECIES, 4));
      missions_.push_back(Mission(true, "Own a penguin or monkey", MissionType::OWN_MEDIUM_ANIMAL));
      missions_.push_back(Mission(true, "No homeless animals", MissionType::NO_HOMELESS_ANIMALS, 0,
                                  0.0, 0.0, true));
      missions_.push_back(Mission(false, "End day with balance of $800+ (+$100)",
                                  MissionType::BALANCE_AT_LEAST, 0, 800.0, 100.0, true));
      missions_.push_back(Mission(false, "End day with 40+ visitors (+$200)",
                                  MissionType::ATTRACT_X_VISITORS, 40, 0.0, 200.0, true));
      break;

    case 6:
      missions_.push_back(Mission(true, "Exercise an animal", MissionType::EXERCISE_ANIMAL));
      missions_.push_back(
          Mission(true, "Feed all animals", MissionType::FEED_X_ANIMALS, zoo_.getAnimalCount()));
      missions_.push_back(Mission(true, "All exhibits at 80+ cleanliness",
                                  MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, 80, 0.0, 0.0,
                                  true));
      missions_.push_back(Mission(false, "End the day with zoo rating of 4.0+ (+$100)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 100.0, true));
      missions_.push_back(
          Mission(false, "Own 5 animals (+$100)", MissionType::OWN_X_ANIMALS, 5, 0.0, 100.0));
      break;

    case 7:
      missions_.push_back(Mission(true, "Own 3 exhibits", MissionType::OWN_X_EXHIBITS, 3));
      missions_.push_back(Mission(true, "No animals need attention",
                                  MissionType::NO_ANIMALS_NEED_ATTENTION, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$200)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 200.0, true));
      missions_.push_back(Mission(false, "End day with balance of $1500+ (+$100)",
                                  MissionType::BALANCE_AT_LEAST, 0, 1000.0, 100.0, true));
      missions_.push_back(Mission(false, "All animals in preferred habitats (+$200)",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 200.0, true));
      break;

    case 8:
      missions_.push_back(Mission(true, "Own 5 different species", MissionType::OWN_X_SPECIES, 5));
      missions_.push_back(
          Mission(true, "Feed all animals", MissionType::FEED_X_ANIMALS, zoo_.getAnimalCount()));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$200)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 200.0, true));
      missions_.push_back(Mission(false, "End day with balance of $1500+ (+$150)",
                                  MissionType::BALANCE_AT_LEAST, 0, 1500.0, 150.0, true));
      missions_.push_back(Mission(false, "Own a lion, or elephant (+$250)",
                                  MissionType::OWN_SPECIAL_ANIMAL, 0, 0.0, 250.0));
      break;

    case 9:
      missions_.push_back(Mission(true, "Own 6 different species", MissionType::OWN_X_SPECIES, 6));
      missions_.push_back(Mission(true, "No animals need attention",
                                  MissionType::NO_ANIMALS_NEED_ATTENTION, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(true, "All exhibits at 80+ cleanliness",
                                  MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, 80, 0.0, 0.0,
                                  true));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$200)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 200.0, true));
      missions_.push_back(Mission(false, "End day with 60+ visitors (+$250)",
                                  MissionType::ATTRACT_X_VISITORS, 60, 0.0, 250.0, true));
      break;

    case 10:
      missions_.push_back(Mission(true, "No homeless animals", MissionType::NO_HOMELESS_ANIMALS));
      missions_.push_back(Mission(true, "All animals are in preferred habitats",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 0.0, true));
      missions_.push_back(
          Mission(true, "No sick animals", MissionType::NO_SICK_ANIMALS, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(true, "No animals need attention",
                                  MissionType::NO_ANIMALS_NEED_ATTENTION, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(false, "Own 7 different species (+$250)",
                                  MissionType::OWN_X_SPECIES, 7, 0.0, 250.0));
      missions_.push_back(
          Mission(false, "Own an elephant (+$200)", MissionType::OWN_ELEPHANT, 0, 0.0, 200.0));
      missions_.push_back(Mission(false, "End day with zoo rating of 4.0+ (+$200)",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 200.0, true));
      missions_.push_back(Mission(false, "Balance above $2000 (+$200)",
                                  MissionType::BALANCE_AT_LEAST, 0, 2000.0, 200.0, true));
      break;
  }
}

void MissionSystem::checkMissions(bool end_of_day) {
  for (size_t i = 0; i < missions_.size(); ++i) {
    Mission& mission = missions_[i];
    if (mission.completed) {
      continue;
    }

    // don't check end of day missions unless end of day
    if (mission.end_of_day && !end_of_day) {
      continue;
    }

    bool condition_met = false;

    switch (mission.type) {
      case MissionType::ADD_ANIMAL_TO_EXHIBIT:
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (zoo_.findAnimalLocation(animal)) {
            condition_met = true;
            break;
          }
        }
        break;

      case MissionType::OWN_X_ANIMALS:
        condition_met = zoo_.getAnimalCount() >= static_cast<size_t>(mission.int_param);
        break;

      case MissionType::OWN_X_SPECIES: {
        std::set<std::string> species;
        for (const Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        condition_met = species.size() >= static_cast<size_t>(mission.int_param);
        break;
      }

      case MissionType::OWN_X_EXHIBITS:
        condition_met = zoo_.getExhibitCount() >= static_cast<size_t>(mission.int_param);
        break;

      case MissionType::FEED_X_ANIMALS:
        condition_met = (animals_fed_today_.size() == static_cast<size_t>(mission.int_param));
        break;

      case MissionType::PLAY_WITH_ANIMAL:
        condition_met = played_with_animal_today_;
        break;

      case MissionType::EXERCISE_ANIMAL:
        condition_met = exercised_animal_today_;
        break;

      case MissionType::NO_ANIMALS_NEED_ATTENTION:
        condition_met = zoo_.getAnimalsNeedingAttention().empty();
        break;

      case MissionType::NO_SICK_ANIMALS:
        condition_met = true;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getHealthLevel() < 50) {
            condition_met = false;
            break;
          }
        }
        break;

      case MissionType::NO_HOMELESS_ANIMALS:
        condition_met = true;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (zoo_.findAnimalLocation(animal) == nullptr) {
            condition_met = false;
            break;
          }
        }
        break;

      case MissionType::PREFERRED_HABITATS:
        condition_met = true;
        for (Animal* animal : zoo_.getAllAnimals()) {
          Exhibit* exhibit = zoo_.findAnimalLocation(animal);
          if (!exhibit || exhibit->getType() != animal->getPreferredHabitat()) {
            condition_met = false;
            break;
          }
        }
        break;

      case MissionType::CLEAN_X_EXHIBITS:
        condition_met = exhibits_cleaned_today_.size() >= static_cast<size_t>(mission.int_param);
        break;

      case MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X:
        condition_met = true;
        for (Exhibit* exhibit : zoo_.getAllExhibits()) {
          if (exhibit->getCleanliness() < mission.int_param) {
            condition_met = false;
            break;
          }
        }
        break;

      case MissionType::BALANCE_AT_LEAST:
        condition_met = zoo_.getProjectedBalance() >= mission.float_param;
        break;

      case MissionType::ZOO_RATING_ABOVE:
        condition_met = zoo_.calculateZooRating() >= mission.float_param;
        break;

      case MissionType::ATTRACT_X_VISITORS:
        condition_met = zoo_.calculateVisitorCount() >= mission.int_param;
        break;

      case MissionType::OWN_ELEPHANT:
        for (const Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Elephant") {
            condition_met = true;
            break;
          }
        }
        break;

      case MissionType::OWN_MEDIUM_ANIMAL: {
        bool owns_penguin = false;
        bool owns_monkey = false;
        for (const Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Penguin") {
            owns_penguin = true;
          } else if (animal->getSpecies() == "Monkey") {
            owns_monkey = true;
          }
        }
        condition_met = owns_penguin || owns_monkey;
        break;
      }

      case MissionType::OWN_SPECIAL_ANIMAL: {
        bool owns_bear = false;
        bool owns_lion = false;
        bool owns_elephant = false;
        for (const Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Bear") {
            owns_bear = true;
          } else if (animal->getSpecies() == "Lion") {
            owns_lion = true;
          } else if (animal->getSpecies() == "Elephant") {
            owns_elephant = true;
          }
        }
        condition_met = owns_bear || owns_lion || owns_elephant;
        break;
      }
    }
    // don't mark end of day missions complete until end of day
    if (mission.end_of_day) {
      mission.condition_met = condition_met;
    } else if (condition_met) {
      completeMission(i);
    }
  }
}

void MissionSystem::completeMission(size_t mission_index) {
  Mission& mission = missions_[mission_index];
  mission.completed = true;

  std::cout << "\nMission Complete: " << mission.description << "\n";

  if (mission.reward_amount > 0) {
    zoo_.addMoney(mission.reward_amount);
    zoo_.earnBonus(mission.reward_amount);
  }
}

void MissionSystem::displayMissions(bool show_status) {
  std::cout << "\nDAY " << zoo_.getDay() << " MISSIONS\n";
  std::cout << "----------------------------------------------------------------------\n";

  std::cout << "Required:\n";
  for (const Mission& mission : missions_) {
    if (mission.required) {
      std::cout << " - " << mission.description << getMissionProgress(mission);

      if (mission.completed) {
        std::cout << " ✓\n";
      } else if (mission.end_of_day && !show_status) {
        std::cout << " ?\n";
      } else {
        std::cout << " X\n";
      }
    }
  }

  bool has_optional = false;
  for (const Mission& mission : missions_) {
    if (!mission.required) {
      has_optional = true;
      break;
    }
  }

  if (has_optional) {
    std::cout << "\nOptional:\n";
    for (const Mission& mission : missions_) {
      if (!mission.required) {
        std::cout << " - " << mission.description << getMissionProgress(mission);
        if (show_status && mission.completed) {
          std::cout << " ✓";
        } else if (show_status && !mission.completed) {
          std::cout << " X";
        }
        std::cout << "\n";
      }
    }
  }
  std::cout << "----------------------------------------------------------------------\n";
}

bool MissionSystem::canAdvanceDay() {
  for (const Mission& mission : missions_) {
    if (!mission.required) {
      continue;
    }

    if (mission.end_of_day) {
      if (!mission.condition_met) {
        return false;
      }
    } else {
      if (!mission.completed) {
        return false;
      }
    }
  }
  return true;
}

bool MissionSystem::checkMissionsImpossible(int action_points) {
  for (const Mission& mission : missions_) {
    if (!mission.required || mission.completed) {
      continue;
    }

    switch (mission.type) {
      case MissionType::ADD_ANIMAL_TO_EXHIBIT: {
        // need at least one animal and one exhibit
        if (zoo_.getAnimalCount() == 0 || zoo_.getExhibitCount() == 0) {
          double balance_needed = 0.0;
          if (zoo_.getAnimalCount() == 0) {
            balance_needed += 150.0;
          }
          if (zoo_.getExhibitCount() == 0) {
            balance_needed += 300.0;
          }
          if (zoo_.getBalance() < balance_needed) {
            return true;
          }
        }
        break;
      }

      case MissionType::OWN_X_ANIMALS: {
        std::set<std::string> species;
        for (Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        int animals_needed = mission.int_param - zoo_.getAnimalCount();
        if (zoo_.getBalance() < (animals_needed * 150.0)) {
          return true;
        }
        break;
      }

      case MissionType::OWN_X_SPECIES: {
        std::set<std::string> species;
        for (Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        int species_needed = mission.int_param - species.size();
        if (zoo_.getBalance() < (species_needed * 150.0)) {
          return true;
        }
        break;
      }

      case MissionType::OWN_X_EXHIBITS: {
        int exhibits_needed = mission.int_param - zoo_.getExhibitCount();
        if (zoo_.getBalance() < (exhibits_needed * 300.0)) {
          return true;
        }
        break;
      }

      case MissionType::NO_ANIMALS_NEED_ATTENTION: {
        int needy_animals = 0;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->needsAttention()) {
            needy_animals++;
          }
        }
        // estimated treatment cost: treatment ($50) + feeding ($5-50)
        double treatment_cost = needy_animals * 100.0;
        if (zoo_.getBalance() < treatment_cost && action_points == 0) {
          return true;
        }
        break;
      }

      case MissionType::NO_SICK_ANIMALS: {
        int sick_animals = 0;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getHealthLevel() < 50) {
            sick_animals++;
          }
        }
        // estimated treatment cost: treatment ($50) + feeding ($5-50)
        double treatment_cost = sick_animals * 100.0;
        if (zoo_.getBalance() < treatment_cost && action_points == 0) {
          return true;
        }
        break;
      }

      case MissionType::OWN_MEDIUM_ANIMAL: {
        bool owns_penguin = false;
        bool owns_monkey = false;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Penguin") {
            owns_penguin = true;
          } else if (animal->getSpecies() == "Monkey") {
            owns_monkey = true;
          }
        }
        if (!owns_penguin && !owns_monkey) {
          if (zoo_.getBalance() < 400.0) {
            return true;
          }
        }
        break;
      }

      default:
        break;
    }
  }
  return false;
}

std::string MissionSystem::getMissionProgress(const Mission& mission) {
  switch (mission.type) {
    case MissionType::OWN_X_ANIMALS:
      return " [" + std::to_string(zoo_.getAnimalCount()) + "/" +
             std::to_string(mission.int_param) + "]";

    case MissionType::OWN_X_EXHIBITS:
      return " [" + std::to_string(zoo_.getExhibitCount()) + "/" +
             std::to_string(mission.int_param) + "]";

    case MissionType::OWN_X_SPECIES: {
      std::set<std::string> species;
      for (Animal* animal : zoo_.getAllAnimals()) {
        species.insert(animal->getSpecies());
      }
      return " [" + std::to_string(species.size()) + "/" + std::to_string(mission.int_param) + "]";
    }

    case MissionType::FEED_X_ANIMALS:
      if (animals_fed_today_.size() >= static_cast<size_t>(mission.int_param)) {
        return "";
      }
      return " [" + std::to_string(animals_fed_today_.size()) + "/" +
             std::to_string(mission.int_param) + " fed]";

    case MissionType::NO_ANIMALS_NEED_ATTENTION:
      if (zoo_.getAnimalsNeedingAttention().empty()) {
        return "";
      }
      return " [" + std::to_string(zoo_.getAnimalsNeedingAttention().size()) + "]";

    case MissionType::NO_SICK_ANIMALS: {
      int sick_animals = 0;
      for (Animal* animal : zoo_.getAllAnimals()) {
        if (animal->getHealthLevel() < 50) {
          sick_animals++;
        }
      }
      return " [" + std::to_string(sick_animals) + " sick]";
    }

    case MissionType::NO_HOMELESS_ANIMALS: {
      int homeless_animals = 0;
      for (Animal* animal : zoo_.getAllAnimals()) {
        if (zoo_.findAnimalLocation(animal) == nullptr) {
          homeless_animals++;
        }
      }
      return " [" + std::to_string(homeless_animals) + " homeless]";
    }

    case MissionType::PREFERRED_HABITATS: {
      int wrong_habitat = 0;
      for (Animal* animal : zoo_.getAllAnimals()) {
        Exhibit* exhibit = zoo_.findAnimalLocation(animal);
        if (exhibit && exhibit->getType() != animal->getPreferredHabitat()) {
          wrong_habitat++;
        }
      }
      if (wrong_habitat == 0) {
        return "";
      }
      return " [" + std::to_string(wrong_habitat) + " wrong]";
    }

    case MissionType::CLEAN_X_EXHIBITS:
      return " [" + std::to_string(exhibits_cleaned_today_.size()) + "/" +
             std::to_string(mission.int_param) + " cleaned]";

    case MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X: {
      int dirty_exhibits = 0;
      for (Exhibit* exhibits : zoo_.getAllExhibits()) {
        if (exhibits->getCleanliness() < 50) {
          dirty_exhibits++;
        }
      }
      if (dirty_exhibits == 0) {
        return "";
      }
      return " [" + std::to_string(dirty_exhibits) + " dirty]";
    }

    case MissionType::BALANCE_AT_LEAST: {
      std::ostringstream ss;
      ss << "$" << std::fixed << std::setprecision(0) << zoo_.getBalance() << "/$"
         << mission.float_param;
      return " [" + ss.str() + "]";
    }

    case MissionType::ZOO_RATING_ABOVE: {
      std::ostringstream ss;
      ss << std::fixed << std::setprecision(1) << zoo_.calculateZooRating() << "/5.0";
      return " [" + ss.str() + "]";
    }

    case MissionType::ATTRACT_X_VISITORS:
      return " [" + std::to_string(zoo_.calculateVisitorCount()) + "/" +
             std::to_string(mission.int_param) + " visitors]";

    default:
      return "";
  }
  return "";
}

void MissionSystem::trackAnimalFed(Animal* animal) {
  animals_fed_today_.insert(animal);
}

void MissionSystem::trackExhibitCleaned(Exhibit* exhibit) {
  exhibits_cleaned_today_.insert(exhibit);
}

void MissionSystem::trackPlayedWithAnimal() {
  played_with_animal_today_ = true;
}

void MissionSystem::trackExercisedAnimal() {
  exercised_animal_today_ = true;
}

void MissionSystem::resetDailyTracking() {
  animals_fed_today_.clear();
  exhibits_cleaned_today_.clear();
  played_with_animal_today_ = false;
  exercised_animal_today_ = false;
}
