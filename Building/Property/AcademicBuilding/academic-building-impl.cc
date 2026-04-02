module academicbuilding;

import building;
import player;
import user;
import iomanager;

import <string>;
import <memory>;
import <vector>;


AcademicBuilding::AcademicBuilding(std::string name, int p, int i, std::string d, std::vector<int> t, Player *owner):
    Property{name, p, owner},
    improvementCost{i},
    department{d},
    tuition{t},
    improvements{0} {
        // Force the tuition to be 5 elements long

        // Set the first tuition element
        if (tuition.size() == 0) {
            tuition.push_back(0);
        }

        // Keep adding the biggest improvement to fill the list up to MAXIMPROVEMENTS elements
        while (tuition.size() < MAXIMPROVEMENTS+1) {
            tuition.push_back(tuition.back());
        }
}

void AcademicBuilding::forceImprovement(int amount) {
    improvements += amount;

    if (improvements < 0) improvements = 0;
    else if (improvements > MAXIMPROVEMENTS) improvements = MAXIMPROVEMENTS;
}

int AcademicBuilding::getImprovementCost() const {return improvementCost;}

std::string AcademicBuilding::getDepartment() const {return department;}

int AcademicBuilding::getImprovements() const {return improvements;}

int AcademicBuilding::getSetImprovements() const {
    int total = getImprovements();
    
    for (auto building: others) {
        AcademicBuilding* pointer = dynamic_cast<AcademicBuilding*>(building);
        if (pointer) {
            total += pointer->getImprovements();
        }
    }
    return total;
}

bool AcademicBuilding::addImprovement() {
    // Make sure that the owner of all the property sets is the same
    if (!isPropertySet(getOwner())) {
        return false;
    } else if (improvements >= MAXIMPROVEMENTS) {
        improvements = MAXIMPROVEMENTS;
        return false;
    } else {
        ++improvements;
        return true;
    }
}

bool AcademicBuilding::removeImprovement() {
    if (improvements > 0) {
        improvements--;
        return true;
    } else {
        improvements = 0;
        return false;
    }
}

bool AcademicBuilding::maxedImprovements() const {
    return improvements == MAXIMPROVEMENTS;
}

bool AcademicBuilding::isPropertySet(Player* person) const {
    for (auto prop: others) {
        if (prop->getOwner() != getOwner()) {
            return false;
        }
    }
    return getOwner() == person;
}

int AcademicBuilding::getValue() const {
    return getPurchaseCost() + improvementCost * improvements;
}

int AcademicBuilding::getSellValue() const {
    return getPurchaseCost()*MORTGAGEVALUE / 100 + improvements*improvementCost*IMPROVEMENTSELLVALUE / 100;
}

int AcademicBuilding::reduceAsset(std::shared_ptr<IOManager> io) {
    int choice;
    io->getOut() << "    1. Remove Improvement" << std::endl;
    io->getOut() << "    2. Mortgage Property" << std::endl;
    choice = io->getNum("What would you like to do?(1/2): ", 1, 2);

    if (choice == 1) {
        if (!removeImprovement()) {
            io->getOut() << "No improvements to remove" << std::endl;
            return 0;
        } else {
            io->getOut() << "Removed improvement and got $" << improvementCost*IMPROVEMENTSELLVALUE/100 << " back." << std::endl;
            return improvementCost*IMPROVEMENTSELLVALUE/100;
        }
    } else if (choice == 2) {
        if (improvements > 0) {
            io->getOut() << "Can't mortgage a property with improvements on it" << std::endl;
            return 0;
        } else {
            // Check if property is already mortgaged
            if (std::string response = mortgage(); response == "") {
                io->getOut() << "Mortgaged property for $" << getPurchaseCost()*MORTGAGEVALUE/100 << " back" << std::endl;
                return getPurchaseCost()*MORTGAGEVALUE/100;
            } else {
                io->getOut() << response << std::endl;
                return 0;
            }
        }
    }

    return 0;
}

int AcademicBuilding::getRent(int roll1, int roll2) const {
    if (getOwner() == nullptr) return 0;

    int rent = tuition[improvements];

    // Multiply the rent by SETNOIMPROVEMENTSMULTIPLIER if the property is a set, with no improvements
    if (isPropertySet(getOwner()) && improvements==0) {
        rent *= SETNOIMPROVEMENTSMULTIPLIER;
    }

    return rent;
}

std::string AcademicBuilding::canMortgage() const {
    return (improvements == 0) ? "" : "Improved properties cannot be mortgaged until all of the improvements are sold";
}

std::string AcademicBuilding::tradable() const {
    if (getSetImprovements() > 0) {
        return "Can't trade a property with a set with improvements";
    }
    return "";
}
