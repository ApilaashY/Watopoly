module timsline;

import iomanager;
import player;
import board;

import <string>;
import <memory>;
import <iostream>;
import <algorithm>;

TimsLine::TimsLine(std::string name):
    Building{name} {}

void TimsLine::notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    // If the roll is not -1, then we consider that the user is just passing by,
    // if not, then we must put them in jail or if they are already in jail, increment their count or force them to pay
    if (roll1 != -1 && !inLine(person)) {
        io->getOut() << "You are passing by the DC Tims Line, it seems very long." << std::endl;
        return;
    }

    // Check if user is already in the line
    auto prisonIter = prisoners.begin();
    int index = 0;
    while (prisonIter != prisoners.end() && (*prisonIter)->getName() != person->getName()) {
        prisonIter++;
        index++;
    }

    if (prisonIter != prisoners.end()) {
        bool repeat = true;
        bool getOut = false;

        // Figure out if the user rolled doubles and is now free
        if (roll1 == roll2) {
            io->getOut() << "You rolled doubles, you are now free" << std::endl;
            getOut = true;
        } else {
            turns[index]++;
            io->getOut() << "You have been in the DC Tims Line for " << turns[index] << " turn" << ((turns[index]!=1)?"s":"") << std::endl;

            // See if the must pay their way out
            if (turns[index] >= MAXTURNS) {
                // Force user to pay out
                io->getOut() << "You have stayed here for too long, now you must pay out or use a Tims Roll Up" << std::endl;
            }
        }

        while (repeat && !getOut) {
            io->getOut() << "    1. Pay Fine" << std::endl;
            io->getOut() << "    2. Use Roll Up" << std::endl;
            if (turns[index] < MAXTURNS) {
                // Give user option to skip if allowed to
                io->getOut() << "    3. Skip for now" << std::endl;
            }
            int option = io->getNum("What would you like to do: ", 1, ((turns[index] < MAXTURNS)?3:2));

            if (option == 1) {
                if (person->charge(FINE, io, turns[index] >= MAXTURNS)) {
                    io->getOut() << "Paid to get out of DC Tim Line" << std::endl << std::endl;
                    getOut = true;
                } else {
                    // Check if the user dropped out
                    if (turns[index] >= MAXTURNS) {
                        person = nullptr;
                        getOut = true;
                    } else {
                        io->getOut() << "You didn't pay out, so you will stay in the line" << std::endl << std::endl;
                    }
                }
            } else if (option == 2) {
                // Try to use roll ups
                if (person->useRollUp()) {
                    io->getOut() << "Used Roll Up to get out of DC Tim Line, you are now free" << std::endl << std::endl;
                    getOut = true;
                } else {
                    io->getOut() << "You have no Roll Ups to use" << std::endl << std::endl;
                }
            } else if (option == 3) {
                repeat = false;
            }
        }

        // Free the user if they are supposed to be freed
        if (getOut) {
            prisoners.erase(prisonIter, prisonIter+1);
            turns.erase(turns.begin()+index, turns.begin()+index+1);
            if (person != nullptr) {

                person->move(roll1+roll2, Board::SQUARES, true);
            }
        }
    } else {
        io->getOut() << "You have been put in the DC Tims Line. You will be stuck here till you roll doubles, use a Tims Roll Up, or pay a $50 fine. You must get out within " << MAXTURNS << " rounds." << std::endl;
        // Add the person to the prisoner list
        addPerson(person);
    }
}

bool TimsLine::inLine(Player* person) const {
    for (auto& user: prisoners) {
        if (user == person) return true;
    }
    return false;
}

int TimsLine::linePosition(Player* person) const {
    int index = 0;
    for (auto& user: prisoners) {
        if (user == person) return turns[index];
        index++;
    }
    return 0;
}

void TimsLine::addPerson(Player* person, int times) {
    prisoners.push_back(person);
    turns.push_back(times);
}
