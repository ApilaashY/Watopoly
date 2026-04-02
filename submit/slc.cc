export module slc;

import chance;
import user;
import iomanager;

import <string>;
import <vector>;
import <memory>;

export class SLC: public Chance {
    int timsLine;
    int osap;

    static std::string backOne(User*, int, int);
    static std::string backTwo(User*, int, int);
    static std::string backThree(User*, int, int);
    static std::string forwardOne(User*, int, int);
    static std::string forwardTwo(User*, int, int);
    static std::string forwardThree(User*, int, int);
    static std::string toTims(User*, int, int);
    static std::string toOsap(User*, int, int);

    static const int TOTALPROBABILITY = 24;
    inline static const std::vector<int> CHANCES = {3, 7, 11, 14, 18, 22, 23, TOTALPROBABILITY};
    inline static const std::vector<std::string(*)(User*, int, int)> FUNCS = {
        &SLC::backThree, 
        &SLC::backTwo, 
        &SLC::backOne,
        &SLC::forwardOne,
        &SLC::forwardTwo,
        &SLC::forwardThree,
        &SLC::toTims,
        &SLC::toOsap
    };

    std::string randomOp(User* person, std::shared_ptr<IOManager> io);

    public:

    SLC(int tims, int osap);
};
