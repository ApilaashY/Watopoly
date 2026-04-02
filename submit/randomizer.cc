export module randomizer;

import <random>;
import <chrono>;
import <memory>;

export class Randomizer {
    inline static auto gen = std::make_unique<std::default_random_engine>(std::chrono::system_clock::now().time_since_epoch().count());

    public:

    // Min and max are inclusive
    static int randomNum(int min, int max);
    static int randomNum(int max);
    static void updateSeed(unsigned seed);
};
