export module board;

import user;
import building;
import player;
import iomanager;
import trader;
import property;
import dice;

import <memory>;
import <vector>;
import <iostream>;
import <string>;

export class Board: public Trader {
    static const int STARTINGCASH = 1500;
    static const int CELLSIZE = 7;
    static const int JAILPOSITION = 10;
    static const int DOUBLESTILLJAIL = 3;

    User* lastDoublePerson;
    int lastDoubleTimes;
    int lastDoubleNumber;

    std::vector<std::unique_ptr<Building>> buildings;
    std::vector<std::unique_ptr<User>> users;

    const std::shared_ptr<IOManager> IO;
    bool fairBidding;

    public:
    static const int PASSGOREWARD = 200;
    static const int SQUARES = 40;
    inline static const std::vector<std::string> NAMES = {"Goose", "GRT Bus", "Tim Hortons Doughnut", "Professor", "Student", "Money", "Laptop", "Pink tie"};
    inline static const std::vector<char> PIECES = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};

    // Constructor
    Board(std::shared_ptr<IOManager> io, bool fairBidding);

    // Basic Setters and Getters
    bool addUser(std::string name);
    bool addUser(std::string name, char piece, int money, int position, int tims);
    bool addUser(std::string name, char piece);
    void removeUser(User* name);
    User* getUser(long unsigned int index) const;
    User* getUser(std::string name) const; // Override of previous method to find player from name
    Building* getBuilding(std::string name) const;
    int playerCount() const;
    std::string playersAt(int pos) const;
    std::vector<std::string> leftOverNames() const;
    bool inLine(Player* person) const;
    int linePosition(Player* person) const;
    void addTimsPerson(Player* person, int times=0);

    // Methods to help in output formatting
    // These should be private but are not since the operator function overload is not apart of the class
    std::string alignAt(int pos, std::ostream& out) const;
    std::string alignImps(int pos, std::ostream& out) const;
    std::string alignOwner(int pos, std::ostream& out) const;

    // Methods that affect game play
    bool move(int curPlayer, Dice* die);
    virtual void trade(Player* person);
    virtual void auction(Property* prop, std::string exclude);
    virtual void notify(int position, Player* person);

    // Methods to decode and encode board to a string for file saving
    static std::string encode(Board* board);
    static std::unique_ptr<Board> decode(std::string boardEncode, std::shared_ptr<IOManager> io, bool fairBidding);
};

export std::ostream& operator<<(std::ostream&, const Board&);
