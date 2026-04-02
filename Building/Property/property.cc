export module property;

import building;
import player;
import iomanager;

import <string>;
import <vector>;
import <memory>;

export class Property: public Building {
    int purchaseCost;
    bool mortgaged;
    Player* owner;

    // Using Non-Virtual Interface Idiom
    // Method to transfer User ownership of property.
    // This would be done in the notify function below, but this file can not import user,
    // so it can't do the ownership change. So it has been outsourced to the child class
    // that has access to the User class.

    virtual void notify(Player* person, std::shared_ptr<IOManager> io, int roll1, int roll2);

    protected:
    std::vector<Property*> others;

    public:
    static const int MORTGAGEVALUE = 50;
    static const int UNMORTGAGEVALUE = 60;

    // Constructor
    Property(std::string name, int purchaseCost, Player *owner = nullptr);

    // Basic Getters and Setter
    std::string mortgage();
    bool unMortgage();
    bool isMortgaged() const;

    int getPurchaseCost() const;

    Player* getOwner() const;
    void setOwner(Player* person);

    // Pure virtual methods
    virtual int getValue() const = 0;
    virtual int getSellValue() const = 0;
    virtual int reduceAsset(std::shared_ptr<IOManager> io) = 0;
    virtual int getRent(int roll1, int roll2) const = 0;
    virtual std::string canMortgage() const = 0;
    virtual std::string tradable() const = 0;

    void addOther(Property* other);

    virtual ~Property() = default;
};
