export module player;

import iomanager;

import <string>;
import <memory>;

export class Player {
    public:

    virtual int netWorth() const = 0;
    virtual bool charge(int amount, std::shared_ptr<IOManager> out, bool force, Player* creditor = nullptr) = 0;
    virtual void goTo(int spot) = 0;
    virtual void addCash(int amount) = 0;
    virtual void move(int steps, int numSquares, bool move=false) = 0;
    virtual std::string getName() const = 0;
    virtual bool useRollUp() = 0;
    virtual char getChar() const = 0;
    virtual ~Player() = default;
};
