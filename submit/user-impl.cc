module user;

import academicbuilding;
import rollup;
import board;
import player;
import trader;

import <string>;
import <vector>;
import <iostream>;
import <sstream>;
import <memory>;

User::User(std::string name, char character, Trader* trader, int cash, int position, int rollUps):
    name{name},
    character{character},
    trader{trader},
    cash{cash},
    rollUps{RollUp::addRollUp(rollUps)},
    position{position} {}

void User::dropOut(std::shared_ptr<IOManager> io, Player* creditor) {
    // Check if there is a creditor to give all the assets, if not, put them up for auction
    // First try to convert the creditor to a User*
    User* creditorPointer = dynamic_cast<User*>(creditor);
    if (creditorPointer != nullptr) {
        for (auto prop: properties) {
            // Transfer ownership to current player
            creditorPointer->addProperty(prop);
        }

        // Add cash from other person
        creditorPointer->addCash(cash);
    } else {
        Board* boardTrader = dynamic_cast<Board*>(trader);

        if (boardTrader) {
            io->getOut() << getName() << " has dropped out and will have assets on auction" << std::endl << std::endl;
            for (auto property: properties) {
                io->getOut() << "Auctioning Property " << property->getName() << std::endl;
                boardTrader->auction(property, getName());
            }

            boardTrader->removeUser(this);
        }
    }
}

std::string User::getName() const {
    return name;
}

char User::getChar() const {
    return character;
}

int User::getPosition() const {
    return position;
}

int User::getCash() const {
    return cash;
}

int User::getRollUps() const {
    return rollUps;
}

void User::addProperty(Property* prop) {
    prop->setOwner(this);
    properties.push_back(prop);
}

void User::removeProperty(Property* prop) {
    // Find iterator index of property
    auto iterator = properties.begin();

    while (prop != *iterator && iterator != properties.end()) {
        iterator++;
    }
    
    // Erase if the iterator didn't reach the end
    if (iterator != properties.end()) properties.erase(iterator, iterator+1);
}

Property* User::getProperty(std::string name) const {
    // Find iterator index of property
    auto iterator = properties.begin();

    while (iterator != properties.end() && name != (*iterator)->getName()) {
        iterator++;
    }
    
    // Return the pointer to the property if the iterator didn't reach the end
    if (iterator != properties.end()) {
        return *iterator;
    }
    return nullptr;
}

void User::addCash(int cash) {
    this->cash += cash;
}

void User::addRollUp() {
    rollUps++;
}

bool User::useRollUp() {
    if (rollUps > 0) {
        rollUps--;
        RollUp::usedRollUp();
        return true;
    } else {
        return false;
    }
}

bool User::manageImprove(std::string property, std::shared_ptr<IOManager> io, bool add) {
    // Find the pointer to the property
    auto curProperty = properties.begin();
    while (curProperty != properties.end() && (*curProperty)->getName() != property) {
        curProperty++;
    }

    // Check if a property was found, end if not
    if (curProperty == properties.end()) {
        io->getOut() << "You don't own a property called " << property << std::endl;
        return false;
    }

    // Try type casting the property to see if it's an AcademicBuilding pointer
    AcademicBuilding* propPointer = dynamic_cast<AcademicBuilding*>(*curProperty);
    if (!propPointer) {
        io->getOut() << property << " isn't an improvable building" << std::endl;
        return false;
    }

    // Check whether to add or remove property
    if (add) {
        // Check if user can afford improvement, return if not
        if (cash < propPointer->getImprovementCost()) {
            io->getOut() << "Not enough money to purchase improvement (Cost: $" << propPointer->getImprovementCost() << ", Remaining Needed: $" << propPointer->getImprovementCost()-cash << ")" << std::endl;
            return false;
        }

        // Try to add an improvement, if one was not added, then we have some kind of error
        if (!propPointer->addImprovement()) {
            // Check if the property is an entire property set, if it isn't thats the issue, if not we already have the max number of allowed improvements
            if (!propPointer->isPropertySet(this)) {
                io->getOut() << "Can't build improvements if you do not own the entire property set" << std::endl;
            } else {
                io->getOut() << "Already have " << AcademicBuilding::MAXIMPROVEMENTS << " improvements, which is the max, cannot add any more" << std::endl;
            }
            return false;
        }

        // If we got here that means everything was successful and we can remove the cost of the improvement from cash
        cash -= propPointer->getImprovementCost();
        io->getOut() << "Added 1 improvement and paid $" << propPointer->getImprovementCost() << std::endl;
        io->getOut() << "Now, " << propPointer->getName() << " has " << propPointer->getImprovementCost() << " improvement" << ((propPointer->getImprovementCost() != 1)?"s":"") << std::endl;
        return true;
    } else {
        // Try to remove an improvement, if one was not remove, then we have 0
        if (!propPointer->removeImprovement()) {
            io->getOut() << "Don't have any improvements, cannot remove any more" << std::endl;
            return false;
        }

        // If we got here that means everything was successful and we can remove the cost of the improvement from cash
        cash += propPointer->getImprovementCost()*AcademicBuilding::IMPROVEMENTSELLVALUE/100;
        io->getOut() << "Removed 1 improvement and received $" << propPointer->getImprovementCost()*AcademicBuilding::IMPROVEMENTSELLVALUE/100 << std::endl;
        io->getOut() << "Now, " << propPointer->getName() << " has " << propPointer->getImprovementCost() << " improvement" << ((propPointer->getImprovementCost() != 1)?"s":"") << std::endl;
        return true;
    }
}

bool User::mortgage(std::string property, std::shared_ptr<IOManager> io) {
    // Find the pointer to the property
    auto curProperty = properties.begin();
    while (curProperty != properties.end() && (*curProperty)->getName() != property) {
        curProperty++;
    }

    // Check if a property was found, end if not
    if (curProperty == properties.end()) {
        io->getOut() << "You don't own a property called " << property << std::endl;
        return false;
    }

    // Try to mortgage the property, if it is already mortgaged don't do anything
    if (std::string response = (*curProperty)->mortgage(); response != "") {
        io->getOut() << response << std::endl;
        return false;
    }

    // If we have gotten to this point that means that the property has been mortgaged, so we need to add the cash
    cash += (*curProperty)->getValue() * Property::MORTGAGEVALUE / 100;
    io->getOut() << "Mortgaged property and received $" << (*curProperty)->getValue() * Property::MORTGAGEVALUE / 100 << std::endl;
    return true;
}

bool User::unMortgage(std::string property, std::shared_ptr<IOManager> io) {
    // Find the pointer to the property
    auto curProperty = properties.begin();
    while (curProperty != properties.end() && (*curProperty)->getName() != property) {
        curProperty++;
    }

    // Check if a property was found, end if not
    if (curProperty == properties.end()) {
        io->getOut() << "You don't own a property called " << property << std::endl;
        return false;
    }

    // Check if the user has enough cash to unmortgage
    if (cash < (*curProperty)->getValue() * Property::UNMORTGAGEVALUE / 100) {
        io->getOut() << "Not enough money to unmortgage property, $" << ((*curProperty)->getValue() * Property::UNMORTGAGEVALUE / 100)-cash << " more needed" << std::endl;
        return false;
    }

    // Try to unmortgage the property, if it is already unmortgaged don't do anything
    if (!(*curProperty)->unMortgage()) {
        io->getOut() << "Can't unmortgage an already unmortgaged property" << std::endl;
        return false;
    }

    // If we have gotten to this point that means that the property has been mortgaged, so we need to add the cash
    cash -= (*curProperty)->getValue() * Property::UNMORTGAGEVALUE / 100;
    io->getOut() << "Unmortgaged property and paid $" << (*curProperty)->getValue() * Property::UNMORTGAGEVALUE / 100 << std::endl;
    return true;
}

int User::netWorth() const {
    int propWorth = 0;

    for (auto prop: properties) {
        propWorth += prop->getValue();
    }

    return propWorth + cash;
}

int User::netSellWorth() const {
    int propWorth = 0;

    for (auto prop: properties) {
        propWorth += prop->getSellValue();
    }

    return propWorth + cash;
}

void User::move(int steps, int numSquares, bool notify) {
    position += steps;

    // Correct negative movement
    while (position < 0) position += numSquares;

    if (position >= numSquares) {
        position %= numSquares;
        cash += Board::PASSGOREWARD;
    }

    if (notify) {
         // Try to notify the board square that the user has gone there
        Board* boardPointer = dynamic_cast<Board*>(trader);

        if (boardPointer) {
            boardPointer->notify(position, this);
        }
    }
}

bool User::charge(int amount, std::shared_ptr<IOManager> io, bool force, Player* creditor) {
    // Check if the user has enough cash to pay off amount
    if (amount <= cash) {
        // Subtract amount from cash
        cash -= amount;
        io->getOut() << "Successfully removed $" << amount << " from cash balance" << std::endl;
        io->getOut() << "New Balance: $" << cash << std::endl;
        return true;
    } else {
        // Get the user to sell assets to make money
        std::string command;

        io->getOut() << "$" << cash << " was paid from cash balance, the remaining $" << amount-cash << " needs to be from assets. Which property would you like to try to get money out of?" << std::endl;
        while (cash < amount) {
            io->getOut() << showAssets(false);

            // Add a last option of whether to just stop if not forced, Drop Out if forced
            io->getOut() << "    " << (properties.size()+1) << ". ";
            if (force) {
                io->getOut() << "Drop Out (Defeat)";
            } else {
                io->getOut() << "Cancel";
            }
            io->getOut() << std::endl;
            io->getOut() << "    Or you can call a trade by typing \"trade [other player] [item to give] [item to receive]\"" << std::endl;

            // Generate a vector of valid options
            std::vector<std::string> choices = {"trade"};
            for (long unsigned int i = 1; i<=properties.size()+1; ++i) {
                choices.push_back(std::to_string(i));
            }

            std::string prop = io->getString("Select an option: ", choices);

            // Check if user is initiating trade or selecting a property
            if (prop == std::to_string(properties.size()+1)) {
                // If this is a force, ask if they are sure they want to call ;
                if (force) {
                    std::string option = io->getString("Are you sure you would like to Drop Out (You will lose this game)?(Yes/No): ", {"Yes", "No"});
                    if (option == "Yes") {
                        dropOut(io, creditor);
                        return false;
                    }
                }

            } else if (prop != "trade") {
                // Call virtual reduceAsset on selected property
                properties[std::stoi(prop)-1]->reduceAsset(io);
            } else {
                // Issue a trade
                trader->trade(this);
            }
        }

        cash -= amount;
        return true;
    }
}

void User::goTo(int position) {
    // Give the user their OSAP money if they have to go around the board;
    if (position < this->position) {
        addCash(Board::PASSGOREWARD);
    }

    this->position = position;

    // Try to notify the board square that the user has gone there
    Board* boardPointer = dynamic_cast<Board*>(trader);

    if (boardPointer) {
        boardPointer->notify(position, this);
    }
}

std::string User::showAssets(bool includeCash) const {
    std::string total = "";
    std::ostringstream cashOut;

    // Include Cash Asset if wanted
    if (includeCash) {
        cashOut << "Cash: $" << cash << std::endl;
    }

    // Go through and list all properties
    for (long unsigned int i = 0; i<properties.size(); ++i) {
        std::ostringstream out;
        out << "    " << (i + 1) << ": " << properties[i]->getName() << ((properties[i]->isMortgaged())?" (Mortgaged)":"");

        // Try converting the property to an Academic property and add improvements
        // If it fails, then it is not an Academic property and do nothing else
        AcademicBuilding* prop = dynamic_cast<AcademicBuilding*>(properties[i]);
        if (prop) {
            if (!prop->isMortgaged()) {
                out << " with " << prop->getImprovements() << " improvements";
                if (prop->maxedImprovements()) {
                    out << " (MAX)";
                }
            }
        }

        out << std::endl;

        total += out.str();
    }

    // Add message if the user has no assets
    if (total == "") {
        std::ostringstream out;
        out << "No assets other than cash" << std::endl;
        total += out.str();
    }

    return cashOut.str() + total;
}

void User::trade(User* other, std::string give, std::string receive, std::shared_ptr<IOManager> io) {
    // Check if the other user exists
    if (!other) {
        io->getOut() << "That person does not exist" << std::endl;
        return;
    }

    // Make sure the trade isn't with itself
    if (this == other) {
        io->getOut() << "Can't trade yourself" << std::endl;
        return;
    }

    int cashGive, cashRec;
    std::istringstream g{give}, r{receive};
    // If reading neither of the above values are failed, then they are trying to trade money for money
    if (g >> cashGive && r >> cashRec) {
        io->getOut() << "Can't trade money for money" << std::endl;
        return;
    }

    // Check for negative cash
    if ((g && cashGive <= 0) || (r && cashRec <= 0)) {
        io->getOut() << "Can't trade negative cash value" << std::endl;
        return;
    }

    // Check if one or both of the properties are actually owned and have no improvements
    Property* giveP = getProperty(give);
    Property* receiveP = other->getProperty(receive);
    
    if (!g && !giveP) {
        io->getOut() << getName() << " does not have property, " << give << std::endl;
        return;
    } else if (!g) {
        // This means they have a property and we have to make sure it's tradable

        if (std::string message = giveP->tradable(); message != "") {
            io->getOut() << message << std::endl;
            return;
        }
    }

    if (!r && !receiveP) {
        io->getOut() << other->getName() << " does not have property, " << receive << std::endl;
        return;
    } else if (!r) {
        // This means they have a property and we have to make sure it's tradable

        if (std::string message = receiveP->tradable(); message != "") {
            io->getOut() << message << std::endl;
            return;
        }
    }

    // Ask other person if they accept
    std::string input;
    io->getOut() << other->getName() << ", do you accept to give, " << receive << ", in return " << getName() << " will give you " << give << std::endl;
    input = io->getString("Enter \"Yes\" if you accept the trade deal, anything else if not: ");
    if (input != "Yes") {
        io->getOut() << "Trade Declined" << std::endl;
        return;
    }

    // Perform trade

    io->getOut() << std::endl;

    // Pre charge both of the users
    // This is done here to make sure that if one of them can't pay the trade price,
    // there is no headache of swapping back the properties
    if (g) {
        if (!charge(cashGive, io, false)) {
            // If we are here, then person 1 can't pay trade value, so we cancel the trade
            io->getOut() << "Trade cancelled since " << getName() << " cannot pay balance" << std::endl;
            return;
        }
    }

    // Now charge person 2
    if (r) {
        if (other->charge(cashRec, io, false)) {
            // If we are here, then person 2 can't pay trade value, so we cancel the trade
            io->getOut() << "Trade cancelled since " << other->getName() << " cannot pay balance" << std::endl;
            return;
        }
    }


    // Remove property/cash from player 1 and give to player 2
    if (g) {
        other->addCash(cashGive);
    } else {
        removeProperty(giveP);
        other->addProperty(giveP);
    }

    // Remove property/cash from player 2
    if (r) {
        addCash(cashRec);
    } else {
        other->removeProperty(receiveP);
        addProperty(receiveP);
    }

    io->getOut() << "Property has been transfered" << std::endl;
    io->getOut() << "Trade Successful" << std::endl;

    return;
}

void User::auction(Property* prop, std::string exclude) {
    Board* pointer = dynamic_cast<Board*>(trader);

    if (pointer) pointer->auction(prop, exclude);
}

std::ostream& operator<<(std::ostream& out, const User& player) {
    out << player.getName() << " (" << player.getChar() << ")";
    return out;
}

User::~User() {
    while (rollUps > 0) {
        RollUp::usedRollUp();
        rollUps--;
    }
}
