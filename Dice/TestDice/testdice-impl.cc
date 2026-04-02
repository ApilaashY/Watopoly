module testdice;

import <random>;
import <chrono>;

import randomizer;

TestDice::TestDice(std::shared_ptr<IOManager> io): io{io} {}

int TestDice::roll() const {
    return io->getNum("", -12, 12);
}
