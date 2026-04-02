export module chance;

import building;
import player;
import user;
import iomanager;

import <string>;
import <iostream>;
import <memory>;

export class Chance: public Building {
    virtual std::string randomOp(User* person, std::shared_ptr<IOManager> io) = 0;
    virtual void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);

    public:

    Chance(std::string name);
};
