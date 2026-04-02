module dice;

import <random>;
import <chrono>;

import randomizer;


int Dice::roll() const {
    return Randomizer::randomNum(MINROLL, MAXROLL);
}

