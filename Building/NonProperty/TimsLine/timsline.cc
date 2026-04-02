export module timsline;

import building;
import player;
import iomanager;

import <iostream>;
import <vector>;
import <string>;
import <memory>;

export class TimsLine: public Building {
    static const int MAXTURNS = 3;
    static const int FINE = 50;
    std::vector<Player*> prisoners;
    std::vector<int> turns;

    virtual void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);

    public:

    bool inLine(Player* person) const;
    int linePosition(Player* person) const;
    void addPerson(Player* person, int times=0);

    TimsLine(std::string name);
};
