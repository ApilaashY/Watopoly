export module building;

import iomanager;
import player;

import <string>;
import <memory>;
import <iostream>;

export class Building {
    std::string name;

    virtual void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) = 0;
    public:

    Building(std::string name);

    // Getter
    std::string getName() const;

    virtual ~Building() = default;

    void notifyLand(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);
    void notifyNoLand(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);
};
