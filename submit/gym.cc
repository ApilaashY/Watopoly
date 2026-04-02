export module gym;

import building;
import player;
import property;
import iomanager;

import <string>;
import <memory>;
import <vector>;


export class Gym: public Property {
    static const int VALUE = 150;
    static const int SINGLEMULTIPLIER = 4;
    static const int DOUBLEMULTIPLIER = 10;

    public:

    Gym(std::string name, Player* owner = nullptr);
    int getValue() const;
    int getSellValue() const;
    int reduceAsset(std::shared_ptr<IOManager> io);
    virtual int getRent(int roll1, int roll2) const;
    virtual std::string canMortgage() const;
    virtual std::string tradable() const;
};
