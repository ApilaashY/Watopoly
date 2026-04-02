export module testdice;

import dice;
import iomanager;

import <iostream>;
import <memory>;

export class TestDice: public Dice {
    std::shared_ptr<IOManager> io;

    public:

    TestDice(std::shared_ptr<IOManager> io);
    virtual int roll() const;
};
