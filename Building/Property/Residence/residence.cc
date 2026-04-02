export module residence;

import building;
import player;
import property;
import iomanager;

import <string>;
import <memory>;
import <vector>;
import <iostream>;

export class Residence: public Property {
    static const int VALUE = 200;
    inline static const std::vector<int> RENTS = {25, 50, 100, 200};

    public:

    Residence(std::string name, Player* owner = nullptr);
    int getValue() const;
    int getSellValue() const;
    int reduceAsset(std::shared_ptr<IOManager> io);
    virtual int getRent(int roll1, int roll2) const;
    virtual std::string canMortgage() const;
    virtual std::string tradable() const;
};
