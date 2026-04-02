module moneychange;

import iomanager;
import player;

import <iostream>;
import <memory>;

MoneyChange::MoneyChange(std::string name, int amount, std::string message, int percentage):
    Building{name},
    amount{amount},
    message{message},
    percentage{percentage} {}

void MoneyChange::notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    io->getOut() << message << std::endl;

    // Check whether to give a percentage option
    if (percentage != 0) {
        bool paid = false;
        while (!paid) {
            io->getOut() << "    1. Pay $" << amount << std::endl;
            io->getOut() << "    2. Pay " << percentage << "\% of your total net worth ($" << person->netWorth() << ")" << std::endl;

            paid = person->charge(-1*amount, io, false);
        }
    } else {
        if (amount > 0) person->addCash(amount);
        else person->charge(-1 * amount, io, true);
    }
}
