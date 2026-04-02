module residence;

import building;
import player;
import user;
import iomanager;

import <string>;
import <memory>;
import <vector>;
import <iostream>;


Residence::Residence(std::string name, Player* owner):
    Property{name, VALUE, owner} {}

int Residence::getValue() const {
    return getPurchaseCost();
}

int Residence::getSellValue() const {
    return getPurchaseCost()*MORTGAGEVALUE;
}

int Residence::reduceAsset(std::shared_ptr<IOManager> io) {
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

int Residence::getRent(int roll1, int roll2) const {
    if (getOwner() == nullptr) return 0;

    // Figure out how many other residences the owner owns
    int count = 1;
    for (auto res: others) {
        if (res->getOwner() == getOwner()) count++;
    }

    if (count >= static_cast<int>(RENTS.size())) count = static_cast<int>(RENTS.size());

    return RENTS[count];
}

// Residence mortgage has no conditions of whether it can be mortgaged or not
std::string Residence::canMortgage() const { return ""; }

// Residence has no conditions of whether it can be traded or not
std::string Residence::tradable() const { return ""; }
