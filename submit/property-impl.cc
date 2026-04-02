module property;

import iomanager;
import board;
import trader;
import user;
import player;

import <iostream>;
import <memory>;

Property::Property(std::string name, int purchaseCost, Player* owner):
    Building{name},
    purchaseCost{purchaseCost},
    mortgaged{false},
    owner{owner} {}

void Property::addOther(Property* other) {
    others.push_back(other);
}

std::string Property::mortgage() {
    if (mortgaged) return "Cannot mortgage already mortgaged property";

    if (canMortgage() != "") return canMortgage();

    mortgaged = true;
    return ""; // Return whether mortgage was successful
}

bool Property::unMortgage() {
    if (!mortgaged) return false;

    mortgaged = false;
    return true; // Return whether unmortgage was successful
}

bool Property::isMortgaged() const {
    return mortgaged;
}

int Property::getPurchaseCost() const {
    return purchaseCost;
}

Player* Property::getOwner() const {
    return owner;
}

void Property::setOwner(Player* person) {
    owner = person;
}

void Property::notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    // If no one owns the property, allow the user to buy it, if not, charge the person who landed for rent
    if (owner == nullptr) {
        io->getOut() << "Would you like to purchase the property, " << getName() << " for $" << purchaseCost << "?(Yes/No): ";
        std::string choice = io->getString("", {"Yes", "No"});
        io->getOut() << std::endl;

        if (User* uPerson = dynamic_cast<User*>(person); choice == "Yes" && uPerson != nullptr && person->charge(getPurchaseCost(), io, false)) {
            uPerson->addProperty(this);
            
            io->getOut() << "You have purchased property, " << getName() << std::endl;
        } else {
            io->getOut() << "The property will now be going to auction" << std::endl;
            User* pointer = dynamic_cast<User*>(person);

            if (pointer) {
                pointer->auction(this, pointer->getName());
            } else {
                io->getOut() << "Cannot auction property" << std::endl;
            }
        }
    } else {
        // Check if the user who landed and the person who landed are the same
        if (person == owner) {
            io->getOut() << "You have landed on your own property" << std::endl;
            return;
        }

        // Check if the property has been mortgaged
        if (isMortgaged()) {
            io->getOut() << "You have landed on a mortgaged property, you don't have to pay anything!" << std::endl;
            return;
        }

        int rent = getRent(roll1, roll2);
        io->getOut() << "Charging $" << rent << " to " << person->getName() << " going to " << owner->getName() << " for landing on " << getName() << std::endl;

        // Charge the person who landed, if they can't pay, don't give the cash to the owner since the owner will get the person's assets
        if (person->charge(rent, io, true, owner)) owner->addCash(rent);
    }
}

