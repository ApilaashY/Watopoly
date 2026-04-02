module needles;

import chance;
import user;
import randomizer;
import iomanager;

import <string>;
import <sstream>;
import <memory>;

Needles::Needles():
    Chance{"Needles Hall"} {}

std::string Needles::randomOp(User* person, std::shared_ptr<IOManager> io) {
    int num = Randomizer::randomNum(1, TOTALPROBABILITY);

    for (long unsigned int i = 0; i<CHANCES.size(); ++i) {
        if (num <= CHANCES[i]) {
            std::ostringstream out;
            if (CHARGES[i] >= 0) {
                person->addCash(CHARGES[i]);
                out << "You have received $" << CHARGES[i] << std::endl;
            } else {
                person->charge(-1*CHARGES[i], io, true);
                out << "You have been charged $" << -1 * CHARGES[i] << std::endl;
            }
            return out.str();
        }
    }
    return "";
}
