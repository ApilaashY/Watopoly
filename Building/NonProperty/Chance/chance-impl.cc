module chance;

import iomanager;
import player;
import rollup;

import <string>;
import <iostream>;
import <memory>;

Chance::Chance(std::string name):
    Building{name} {}

void Chance::notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    // Try to convert Player* to User*
    // Under normal conditions this should always work fine
    User* userPointer = dynamic_cast<User*>(person);
    if (userPointer) {
        // Figure out if to issue a Roll up instead
        if (RollUp::addRollUp()) {
            io->getOut() << "CONGRADULATION! You have earned a free Tims Roll Up letting you free the DC Tims line once for free." << std::endl;
            userPointer->addRollUp();
        } else {
            // Do the normal card if a roll up is not issued
            io->getOut() << randomOp(userPointer, io) << std::endl;
        }
    } else {
        io->getOut() << "User is corrupt" << std::endl;
    }
}
