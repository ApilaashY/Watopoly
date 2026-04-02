export module dice;

export class Dice {
    static const int MINROLL = 1;
    static const int MAXROLL = 6;

    public:

    virtual int roll() const;
};
