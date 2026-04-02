export module trader;

import building;
import player;
import player;
import property;

import <string>;

export class Trader {
    public:

    virtual void trade(Player* person) = 0;
    virtual void auction(Property* prop, std::string exclude) = 0;
    virtual void notify(int position, Player* person) = 0;
};
