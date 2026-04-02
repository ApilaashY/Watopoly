module slc;

import chance;
import user;
import randomizer;
import board;

import <string>;
import <iostream>;
import <sstream>;

SLC::SLC(int tims, int osap):
    Chance{"SLC"},
    timsLine{tims},
    osap{osap} {}

std::string SLC::randomOp(User* person, std::shared_ptr<IOManager> io) {
    int num = Randomizer::randomNum(1, TOTALPROBABILITY);

    io->getOut() << num << std::endl;

    for (long unsigned int i = 0; i<CHANCES.size(); ++i) {
        if (num <= CHANCES[i]) {
            return (*FUNCS[i])(person, timsLine, osap);
        }
    }
    return "";
}

std::string SLC::backOne(User* person, int timsLine, int osap) {
    person->move(-1, Board::SQUARES);
    return "Moved back 1 Square";
}

std::string SLC::backTwo(User* person, int timsLine, int osap) {
    person->move(-2, Board::SQUARES);
    return "Moved back 2 Squares";
}

std::string SLC::backThree(User* person, int timsLine, int osap) {
    person->move(-3, Board::SQUARES);
    return "Moved back 3 Squares";
}

std::string SLC::forwardOne(User* person, int timsLine, int osap) {
    person->move(1, Board::SQUARES);
    return "Moved forward 1 Square";
}

std::string SLC::forwardTwo(User* person, int timsLine, int osap) {
    person->move(2, Board::SQUARES);
    return "Moved forward 2 Squares";
}

std::string SLC::forwardThree(User* person, int timsLine, int osap) {
    person->move(3, Board::SQUARES);
    return "Moved forward 3 Squares";
}

std::string SLC::toTims(User* person, int timsLine, int osap) {
    person->goTo(timsLine);
    return "";
}

std::string SLC::toOsap(User* person, int timsLine, int osap) {
    person->goTo(osap);
    std::ostringstream out;
    out << "Moved to Collect OSAP and received $" << Board::PASSGOREWARD;
    return out.str();
}
