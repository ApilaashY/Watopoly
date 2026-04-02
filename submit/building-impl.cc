module building;


import <string>;
import <iostream>;


Building::Building(std::string name):
    name{name} {}

std::string Building::getName() const { return name; }

void Building::notifyLand(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    io->getOut() << "You have landed on " << name << std::endl;
    notify(person, io, roll1, roll2);
}

void Building::notifyNoLand(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    notify(person, io, roll1, roll2);
}
