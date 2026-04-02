export module needles;

import chance;
import user;
import iomanager;

import <string>;
import <vector>;
import <memory>;

export class Needles: public Chance {
    static const int TOTALPROBABILITY = 18;
    inline static const std::vector<int> CHANCES = {1, 3, 6, 12, 15, 17, 18};
    inline static const std::vector<int> CHARGES = {-200, -100, -50, 25, 50, 100, 200};

    std::string randomOp(User* person, std::shared_ptr<IOManager> io);

    public:

    Needles();
};
