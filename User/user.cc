export module user;

import player;
import rollup;
import property;
import iomanager;
import trader;

import <string>;
import <vector>;
import <memory>;

export class User: public Player {
    std::string name;
    char character;
    Trader* trader;
    std::vector<Property*> properties;
    int cash, rollUps, position;

    void dropOut(std::shared_ptr<IOManager> io, Player* creditor = nullptr);

    public:

    // Constructor
    User(std::string name, char character, Trader* trader, int cash = 0, int position = 0, int rollUps = 0);

    // Getters
    virtual std::string getName() const;
    virtual char getChar() const;
    int getPosition() const;
    int getCash() const;
    int getRollUps() const;

    void addProperty(Property* property);
    void removeProperty(Property* property);
    Property* getProperty(std::string name) const;
    void addCash(int cash);
    void addRollUp();
    virtual bool useRollUp();
    
    bool manageImprove(std::string property, std::shared_ptr<IOManager> out, bool add); // If add is true, then it tries to add an improvement, if add is false it tries to remove an improvement
    bool mortgage(std::string property, std::shared_ptr<IOManager> out);
    bool unMortgage(std::string property, std::shared_ptr<IOManager> out);

    // Extra functions
    int netWorth() const;
    int netSellWorth() const;
    virtual void move(int steps, int numSquares, bool notify=false);
    void goTo(int spot);
    std::string showAssets(bool includeCash = true) const;
    
    virtual bool charge(int amount, std::shared_ptr<IOManager> out, bool force, Player* creditor = nullptr);
    void trade(User* other, std::string give, std::string receive, std::shared_ptr<IOManager> out); // Note that the other person will have to accept/decline the trade
    void auction(Property* prop, std::string exclude);

    ~User();
};

export std::ostream& operator<<(std::ostream& out, const User& player);
