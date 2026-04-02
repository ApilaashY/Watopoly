export module academicbuilding;

import player;
import property;
import iomanager;

import <string>;
import <memory>;
import <vector>;
import <iostream>;


export class AcademicBuilding: public Property {

    const int improvementCost;
    const std::string department;
    std::vector<int> tuition;
    
    int improvements;

    public:
    
    static const int MAXIMPROVEMENTS = 5;
    static const int IMPROVEMENTSELLVALUE = 50;
    static const int SETNOIMPROVEMENTSMULTIPLIER = 2; // How many to multiply the rent by for a property set with no improvements

    // Constructor
    AcademicBuilding(std::string name, int purchaseCost, int improvementCost, std::string department, std::vector<int> tuition, Player *owner = nullptr);
    
    // This should strictly only be used for the decode board function
    void forceImprovement(int amount);

    // Basic Gettors
    int getImprovementCost() const;
    std::string getDepartment() const;
    int getImprovements() const;
    int getSetImprovements() const;

    bool addImprovement();
    bool removeImprovement();
    bool maxedImprovements() const;

    bool isPropertySet(Player* person) const;
    
    int getValue() const;
    int getSellValue() const;
    int reduceAsset(std::shared_ptr<IOManager> io);
    virtual int getRent(int roll1, int roll2) const;
    virtual std::string canMortgage() const;
    virtual std::string tradable() const;
};


