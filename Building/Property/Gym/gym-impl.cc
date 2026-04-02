module gym;

import user;
import player;
import iomanager;

import <string>;
import <memory>;
import <vector>;
import <iostream>;


Gym::Gym(std::string name, Player* owner):
    Property{name, VALUE, owner} {}

int Gym::getValue() const {
    return getPurchaseCost();
}

int Gym::getSellValue() const {
    return getPurchaseCost()*MORTGAGEVALUE;
}

int Gym::reduceAsset(std::shared_ptr<IOManager> io) {
    int choice;
    io->getOut() << "    1. Mortgage Property" << std::endl;
    choice = io->getNum("What would you like to do?(1): ", 1, 2);

    if (choice == 1) {
        // Check if property is already mortgaged
        if (std::string response = mortgage(); response == "") {
            io->getOut() << "Mortgaged property for $" << getPurchaseCost()*MORTGAGEVALUE/100 << " back" << std::endl;
            return getPurchaseCost()*MORTGAGEVALUE/100;
        } else {
            io->getOut() << response << std::endl;
            return 0;
        }
    }
    return 0;
}

int Gym::getRent(int roll1, int roll2) const {
    int multiplier = 0;

    if (getOwner() != nullptr) {
        multiplier = SINGLEMULTIPLIER;
        bool allSame = true;
        for (auto prop: others) {
            if (prop->getOwner() != getOwner()) {
                allSame = false;
                break;
            }
        }

        if (allSame) multiplier = DOUBLEMULTIPLIER;
    }

    return (roll1 + roll2) * multiplier;
}

// Gym mortgage has no conditions of whether it can be mortgaged or not
std::string Gym::canMortgage() const { return ""; }

// Gym has no conditions of whether it can be traded or not
std::string Gym::tradable() const { return ""; }
