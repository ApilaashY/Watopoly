module gototims;

import iomanager;
import player;

import <iostream>;
import <memory>;

GoToTims::GoToTims(std::string name, int position):
    Building{name},
    position{position} {}

void GoToTims::notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2) {
    io->getOut() << "You have been sent to the DC Tims Line" << std::endl;
    person->goTo(position);
}
