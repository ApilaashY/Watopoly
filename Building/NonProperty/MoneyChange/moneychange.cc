export module moneychange;

import building;
import player;
import iomanager;

import <string>;
import <iostream>;
import <memory>;

export class MoneyChange: public Building {
    int amount;
    std::string message;
    int percentage;

    void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);

    public:

    MoneyChange(std::string name, int amount, std::string message, int percentage=0);
};
