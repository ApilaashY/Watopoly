export module rollup;

export class RollUp {
    inline static int issued = 0;
    static const int MAXISSUED = 4;
    static const int CHANCE = 100;

    public:

    static bool addRollUp();
    static int addRollUp(int amount);
    static void usedRollUp();
    static bool reachedMax();
};
