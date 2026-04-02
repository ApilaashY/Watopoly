export module gototims;

import building;
import player;
import iomanager;

import <string>;
import <iostream>;
import <memory>;

export class GoToTims: public Building {
    int position;

    virtual void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);

    public:

    GoToTims(std::string name, int position);
};
