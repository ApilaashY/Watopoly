module board;

import user;
import building;
import player;
import academicbuilding;
import residence;
import gym;
import timsline;
import moneychange;
import gototims;
import slc;
import needles;
import iomanager;

import <memory>;
import <vector>;
import <iostream>;
import <string>;
import <iomanip>;
import <algorithm>;
import <sstream>;
import <utility>;

Board::Board(std::shared_ptr<IOManager> io, bool fairBidding):
    IO{io},
    fairBidding{fairBidding} {
    
    // First add all of the buildings
    auto AL = std::make_unique<AcademicBuilding>("AL", 40, 50, "Arts", std::vector{2, 10, 30, 90, 160, 250});
    auto ML = std::make_unique<AcademicBuilding>("ML", 60, 50, "Arts", std::vector{4, 20, 60, 180, 320, 450});
    AL->addOther(ML.get());
    ML->addOther(AL.get());

    auto MKV = std::make_unique<Residence>("MKV");

    auto ECH = std::make_unique<AcademicBuilding>("ECH", 100, 50, "Arts2", std::vector{6, 30, 90, 270, 400, 550});
    auto PAS = std::make_unique<AcademicBuilding>("PAS", 100, 50, "Arts2", std::vector{6, 30, 90, 270, 400, 550});
    auto HH = std::make_unique<AcademicBuilding>("HH", 120, 50, "Arts2", std::vector{8, 40, 100, 300, 450, 600});
    ECH->addOther(PAS.get()); ECH->addOther(HH.get());
    PAS->addOther(ECH.get()); PAS->addOther(HH.get());
    HH->addOther(PAS.get()); HH->addOther(ECH.get());

    auto RCH = std::make_unique<AcademicBuilding>("RCH", 140, 100, "Eng", std::vector{10, 50, 150, 450, 625, 750});
    auto PAC = std::make_unique<Gym>("PAC");
    auto DWE = std::make_unique<AcademicBuilding>("DWE", 140, 100, "Eng", std::vector{10, 50, 150, 450, 625, 750});
    auto CPH = std::make_unique<AcademicBuilding>("CPH", 160, 100, "Eng", std::vector{12, 60, 180, 500, 700, 900});
    RCH->addOther(DWE.get()); RCH->addOther(CPH.get());
    DWE->addOther(RCH.get()); DWE->addOther(CPH.get());
    CPH->addOther(DWE.get()); CPH->addOther(RCH.get());

    auto UWP = std::make_unique<Residence>("UWP");
    MKV->addOther(UWP.get());
    UWP->addOther(MKV.get());

    auto LHI = std::make_unique<AcademicBuilding>("LHI", 180, 100, "Health", std::vector{14, 70, 200, 550, 750, 950});
    auto BMH = std::make_unique<AcademicBuilding>("BMH", 180, 100, "Health", std::vector{14, 70, 200, 550, 750, 950});
    auto OPT = std::make_unique<AcademicBuilding>("OPT", 200, 100, "Health", std::vector{16, 80, 220, 600, 800, 1000});
    LHI->addOther(BMH.get()); LHI->addOther(OPT.get());
    BMH->addOther(LHI.get()); BMH->addOther(OPT.get());
    OPT->addOther(LHI.get()); OPT->addOther(BMH.get());

    auto EV1 = std::make_unique<AcademicBuilding>("EV1", 220, 150, "Env", std::vector{18, 90, 250, 700, 875, 1050});
    auto EV2 = std::make_unique<AcademicBuilding>("EV2", 220, 150, "Env", std::vector{18, 90, 250, 700, 875, 1050});
    auto EV3 = std::make_unique<AcademicBuilding>("EV3", 240, 150, "Env", std::vector{20, 100, 300, 750, 925, 1100});
    EV1->addOther(EV2.get()); EV1->addOther(EV3.get());
    EV2->addOther(EV1.get()); EV2->addOther(EV3.get());
    EV3->addOther(EV2.get()); EV3->addOther(EV1.get());

    auto V1 = std::make_unique<Residence>("V1");
    V1->addOther(UWP.get());
    V1->addOther(MKV.get());
    UWP->addOther(V1.get());
    MKV->addOther(V1.get());

    auto PHYS = std::make_unique<AcademicBuilding>("PHYS", 260, 150, "Sci1", std::vector{22, 110, 330, 800, 975, 1150});
    auto B1 = std::make_unique<AcademicBuilding>("B1", 260, 150, "Sci1", std::vector{22, 110, 330, 800, 975, 1150});
    auto CIF = std::make_unique<Gym>("CIF");
    auto B2 = std::make_unique<AcademicBuilding>("B2", 280, 150, "Sci1", std::vector{24, 120, 360, 850, 1025, 1200});
    PHYS->addOther(B1.get()); PHYS->addOther(B2.get());
    B1->addOther(PHYS.get()); B1->addOther(B2.get());
    B2->addOther(B1.get()); B2->addOther(PHYS.get());

    CIF->addOther(PAC.get()); PAC->addOther(CIF.get());

    auto EIT = std::make_unique<AcademicBuilding>("EIT", 300, 200, "Sci2", std::vector{26, 130, 390, 900, 1100, 1270});
    auto ESC = std::make_unique<AcademicBuilding>("ESC", 300, 200, "Sci2", std::vector{26, 130, 390, 900, 1100, 1270});
    auto C2 = std::make_unique<AcademicBuilding>("C2", 320, 200, "Sci2", std::vector{28, 150, 450, 1000, 1200, 1400});
    EIT->addOther(ESC.get()); EIT->addOther(C2.get());
    ESC->addOther(EIT.get()); ESC->addOther(C2.get());
    C2->addOther(EIT.get()); C2->addOther(C2.get());

    auto REV = std::make_unique<Residence>("REV");
    V1->addOther(REV.get());
    UWP->addOther(REV.get());
    MKV->addOther(REV.get());
    REV->addOther(V1.get());
    REV->addOther(UWP.get());
    REV->addOther(MKV.get());

    auto MC = std::make_unique<AcademicBuilding>("MC", 350, 200, "Math", std::vector{35, 175, 500, 1100, 1300, 1500});
    auto DC = std::make_unique<AcademicBuilding>("DC", 400, 200, "Math", std::vector{50, 200, 600, 1400, 1700, 2000});
    MC->addOther(DC.get());
    DC->addOther(MC.get());

    // 0
    buildings.emplace_back(std::make_unique<MoneyChange>("Collect OSAP", 0, "Collect OSAP $200"));
    
    // 1
    buildings.emplace_back(std::move(AL));
    buildings.emplace_back(std::make_unique<SLC>(10, 0));
    buildings.emplace_back(std::move(ML));

    // 4
    buildings.emplace_back(std::make_unique<MoneyChange>("Tuition", -300, "Tuition Fees Taken", 10));
    buildings.emplace_back(std::move(MKV));

    // 6
    buildings.emplace_back(std::move(ECH));
    buildings.emplace_back(std::make_unique<Needles>());
    buildings.emplace_back(std::move(PAS));
    buildings.emplace_back(std::move(HH));

    // 10
    buildings.emplace_back(std::make_unique<TimsLine>("Tims Line"));

    // 11
    buildings.emplace_back(std::move(RCH));
    buildings.emplace_back(std::move(PAC));
    buildings.emplace_back(std::move(DWE));
    buildings.emplace_back(std::move(CPH));

    // 15
    buildings.emplace_back(std::move(UWP));

    // 16
    buildings.emplace_back(std::move(LHI));
    buildings.emplace_back(std::make_unique<SLC>(10, 0));
    buildings.emplace_back(std::move(BMH));
    buildings.emplace_back(std::move(OPT));

    // 20
    buildings.emplace_back(std::make_unique<MoneyChange>("Goose Nesting", 0, "A flock of geese attacked you!!!"));

    // 21
    buildings.emplace_back(std::move(EV1));
    buildings.emplace_back(std::make_unique<Needles>());
    buildings.emplace_back(std::move(EV2));
    buildings.emplace_back(std::move(EV3));

    // 25
    buildings.emplace_back(std::move(V1));

    // 26
    buildings.emplace_back(std::move(PHYS));
    buildings.emplace_back(std::move(B1));
    buildings.emplace_back(std::move(CIF));
    buildings.emplace_back(std::move(B2));

    // 30
    buildings.emplace_back(std::make_unique<GoToTims>("Go To Tims", 10));

    // 31
    buildings.emplace_back(std::move(EIT));
    buildings.emplace_back(std::move(ESC));
    buildings.emplace_back(std::make_unique<SLC>(10, 0));
    buildings.emplace_back(std::move(C2));

    // 35
    buildings.emplace_back(std::move(REV));

    // 36
    buildings.emplace_back(std::make_unique<Needles>());
    buildings.emplace_back(std::move(MC));
    buildings.emplace_back(std::make_unique<MoneyChange>("Coop Fees", -100, "Coop Fees Taken"));
    buildings.emplace_back(std::move(DC));
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
    out << "_________________________________________________________________________________________" << std::endl;
    out << "|Goose  |" << b.alignImps(21, out) << "|NEEDLES|" << b.alignImps(23, out) << "|" << b.alignImps(24, out) << "|V1     |" << b.alignImps(26, out) << "|" << b.alignImps(27, out) << "|CIF " << b.alignOwner(28, out) << "|" << b.alignImps(29, out) << "|GO TO  |" << std::endl;
    out << "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |" << std::endl;
    out << "|       |EV1 " << b.alignOwner(21, out) << "|       |EV2 " << b.alignOwner(23, out) << "|EV3 " << b.alignOwner(24, out) << "|       |PHYS" << b.alignOwner(26, out) << "|B1 " << b.alignOwner(27, out) << " |       |B2 " << b.alignOwner(29, out) << " |       |" << std::endl;
    out << "|" << b.alignAt(20, out) << "|" << b.alignAt(21, out) << "|" << b.alignAt(22, out) << "|" << b.alignAt(23, out) << "|" << b.alignAt(24, out) << "|" << b.alignAt(25, out) << "|" << b.alignAt(26, out) << "|" << b.alignAt(27, out) << "|" << b.alignAt(28, out) << "|" << b.alignAt(29, out) << "|" << b.alignAt(30, out) << "|" << std::endl;
    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
    out << "|" << b.alignImps(19, out) << "|                                                                       |" << b.alignImps(31, out) << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|OPT " << b.alignOwner(19, out) << "|                                                                       |EIT " << b.alignOwner(31, out) << "|" << std::endl;
    out << "|" << b.alignAt(19, out) << "|                                                                       |" << b.alignAt(31, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|" << b.alignImps(18, out) << "|                                                                       |" << b.alignImps(32, out) << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|BMH " << b.alignOwner(18, out) << "|                                                                       |ESC " << b.alignOwner(32, out) << "|" << std::endl;
    out << "|" << b.alignAt(18, out) << "|                                                                       |" << b.alignAt(32, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|SLC    |                                                                       |SLC    |" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|" << b.alignAt(17, out) << "|                                                                       |" << b.alignAt(33, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|" << b.alignImps(16, out) << "|                                                                       |" << b.alignImps(34, out) << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|LHI " << b.alignOwner(16, out) << "|                                                                       |C2 " << b.alignOwner(34, out) << " |" << std::endl;
    out << "|" << b.alignAt(16, out) << "|             _____________________________________________             |" << b.alignAt(34, out) << "|" << std::endl;
    out << "|_______|            |                                             |            |_______|" << std::endl;
    out << "|UWP " << b.alignOwner(15, out) << "|            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV " << b.alignOwner(35, out) << "|" << std::endl;
    out << "|       |            | #   # #  #   #   #   # #  # #   # #   #   # |            |       |" << std::endl;
    out << "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |" << std::endl;
    out << "|" << b.alignAt(15, out) << "|            | # # # #  #   #   #   # #    #   # #     #   |            |" << b.alignAt(35, out) << "|" << std::endl;
    out << "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|" << std::endl;
    out << "|" << b.alignImps(14, out) << "|            |_____________________________________________|            |NEEDLES|" << std::endl;
    out << "|-------|                                                                       |HALL   |" << std::endl;
    out << "|CPH " << b.alignOwner(14, out) << "|                                                                       |       |" << std::endl;
    out << "|" << b.alignAt(14, out) << "|                                                                       |" << b.alignAt(36, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|" << b.alignImps(13, out) << "|                                                                       |" << b.alignImps(37, out) << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|DWE " << b.alignOwner(13, out) << "|                                                                       |MC " << b.alignOwner(37, out) << " |" << std::endl;
    out << "|" << b.alignAt(13, out) << "|                                                                       |" << b.alignAt(37, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|PAC    |                                                                       |COOP   |" << std::endl;
    out << "|       |                                                                       |FEE    |" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|" << b.alignAt(12, out) << "|                                                                       |" << b.alignAt(38, out) << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|" << b.alignImps(11, out) << "|                                                                       |" << b.alignImps(39, out) << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|RCH " << b.alignOwner(11, out) << "|                                                                       |DC " << b.alignOwner(39, out) << " |" << std::endl;
    out << "|" << b.alignAt(11, out) << "|                                                                       |" << b.alignAt(39, out) << "|" << std::endl;
    out << "|_______|_______________________________________________________________________|_______|" << std::endl;
    out << "|DC Tims|" << b.alignImps(9, out) << "|" << b.alignImps(8, out) << "|NEEDLES|" << b.alignImps(6, out) << "|MKV    |TUITION|" << b.alignImps(3, out) << "|SLC    |" << b.alignImps(1, out) << "|COLLECT|" << std::endl;
    out << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << std::endl;
    out << "|       |HH " << b.alignOwner(9, out) << " |PAS " << b.alignOwner(8, out) << "|       |ECH " << b.alignOwner(6, out) << "|       |       |ML " << b.alignOwner(3, out) << " |       |AL " << b.alignOwner(1, out) << " |       |" << std::endl;
    out << "|" << b.alignAt(10, out) << "|" << b.alignAt(9, out) << "|" << b.alignAt(8, out) << "|" << b.alignAt(7, out) << "|" << b.alignAt(6, out) << "|" << b.alignAt(5, out) << "|" << b.alignAt(4, out) << "|" << b.alignAt(3, out) << "|" << b.alignAt(2, out) << "|" << b.alignAt(1, out) << "|" << b.alignAt(0, out) << "|" << std::endl;
    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
    return out;
}

std::vector<std::string> Board::leftOverNames() const {
    std::vector<std::string> leftOvers(NAMES);

    // Remove names in use
    for (auto& user: users) {
        auto iter = std::find(leftOvers.begin(), leftOvers.end(), user->getName());
        if (iter != leftOvers.end()) leftOvers.erase(iter, iter+1);
    }

    return leftOvers;
}

bool Board::inLine(Player* person) const {
    TimsLine* tims = dynamic_cast<TimsLine*>(buildings[JAILPOSITION].get());

    if (tims) {
        return tims->inLine(person);
    }
    return false;
}

int Board::linePosition(Player* person) const {
    TimsLine* tims = dynamic_cast<TimsLine*>(buildings[JAILPOSITION].get());

    if (tims) {
        return tims->linePosition(person);
    }
    return 0;
}

bool Board::addUser(std::string name) {
    std::vector<std::string> usables = leftOverNames();

    // See if the name and character is in the NAMES list
    if (std::find(usables.begin(), usables.end(), name) == usables.end()) return false;

    // Find the equivalent PIECE name from NAMES
    char piece = '?';
    for (unsigned long int i = 0; i<usables.size(); ++i) {
        if (usables[i] == name) {
            piece = PIECES[i];
        }
    }

    users.push_back(make_unique<User>(name, piece, this, 1500));
    return true;
}

bool Board::addUser(std::string name, char piece) {
    users.push_back(make_unique<User>(name, piece, this, 1500));
    return true;
}

bool Board::addUser(std::string name, char piece, int money, int position, int tims) {
    users.push_back(make_unique<User>(name, piece, this, money, position, tims));
    return true;
}

void Board::removeUser(User* user) {
    auto iter = users.begin();
    while (iter != users.end() && (*iter).get() != user) iter++;

    if (iter != users.end()) users.erase(iter, iter+1);
}

User* Board::getUser(long unsigned int index) const {
    if (index < 0 || index >= users.size()) return nullptr;
    return users[index].get();
}

User* Board::getUser(std::string name) const {
    for (auto& user: users) {
        if (user->getName() == name) return user.get();
    }

    return nullptr;
}

Building* Board::getBuilding(std::string name) const {
    for (auto& building: buildings) {
        if (building->getName() == name) return building.get();
    }

    return nullptr;
}

int Board::playerCount() const {
    return static_cast<int>(users.size());
}

std::string Board::playersAt(int pos) const {
    std::string total = "";

    for (auto& user: users) {
        if (user->getPosition() == pos) {
            total += user->getChar();
        }
    }

    return total;
}

void Board::addTimsPerson(Player* person, int times) {
    TimsLine* timsLine = dynamic_cast<TimsLine*>(buildings[JAILPOSITION].get());

    if (timsLine) {
        timsLine->addPerson(person, times);
    }
}

std::string Board::alignAt(int pos, std::ostream& out) const {
    out << std::left << std::setw(CELLSIZE);
    return playersAt(pos);
}

std::string Board::alignImps(int pos, std::ostream& out) const {
    std::string output = "";
    
    // Try to turn the building pointer to an academic building pointer
    // If it succeeds, turn the number of improvements into marks on the string
    // If it fails, then just return nothing
    AcademicBuilding* prop = dynamic_cast<AcademicBuilding*>(buildings[pos].get());
    if (prop != nullptr) {
        for (int i = 0; i<prop->getImprovements(); ++i) {
            output += "I";
        }
    } else {
        output = "";
    }

    // Format and output the improvements
    out << std::left << std::setw(CELLSIZE);
    return output;
}

std::string Board::alignOwner(int pos, std::ostream& out) const {
    // Try to turn the building pointer to an academic building pointer
    // If it succeeds, turn the number of improvements into marks on the string
    // If it fails, then just return nothing
    Property* prop = dynamic_cast<Property*>(buildings[pos].get());
    if (prop != nullptr && prop->getOwner() != nullptr) {
        out << '(' << prop->getOwner()->getChar() << ')';
    } else {
        out << "   ";
    }
    return "";
}

bool Board::move(int curPlayer, Dice* die) {
    int roll1 = die->roll();
    int roll2 = die->roll();

    // Tell user what they rolled
    IO->getOut() << std::endl << "You rolled a " << roll1 << " and a " << roll2 << " for a total of " << roll1+roll2 << std::endl;

    TimsLine* timsline = dynamic_cast<TimsLine*>(buildings[JAILPOSITION].get());
    // Check if the user is in the Tims Line and do nothing else if they are
    if (timsline != nullptr && timsline->inLine(users[curPlayer].get())) {
        // Notify the timsline and let it take care of the turn
        timsline->notifyNoLand(users[curPlayer].get(), IO, roll1, roll2);

        // Clear the doubles tracker
        lastDoubleTimes = 1;
        lastDoublePerson = nullptr;

        return false;
    } else {
        // Check if the curPlayer and the lastDoublePerson are the same
        // and update data as follows
        if (users[curPlayer].get() != lastDoublePerson) {
            lastDoubleTimes = 1;
            lastDoublePerson = users[curPlayer].get();
        }

        if (roll1 == roll2 && roll1 == lastDoubleNumber) {
            lastDoubleTimes++;
        } else if (roll1 == roll2) {
            lastDoubleNumber = roll1;
            lastDoubleTimes = 1;
        } else {
            lastDoubleTimes = 1;
        }

        
        // Figure out of the user should go to Tims Line based on the number of doubles
        if (lastDoubleTimes >= DOUBLESTILLJAIL) {
            IO->getOut() << "You have rolled " << DOUBLESTILLJAIL << " doubles in a row. GO TO JAIL!" << std::endl;
            users[curPlayer]->goTo(JAILPOSITION);

            return false;
        } else {
            // Move the user
            users[curPlayer]->move(roll1 + roll2, SQUARES);
            // Notify the building that a user landed on it
            // Using the Observer design pattern
            buildings[users[curPlayer]->getPosition()]->notifyLand(users[curPlayer].get(), IO, roll1, roll2);

            if (roll1 == roll2 && !timsline->inLine(users[curPlayer].get())) {
                IO->getOut() << "You rolled doubles, you can roll again" << std::endl;
                return true;
            } else {
                return false;
            }
        }
    }
}

void Board::trade(Player* person) {
    // Grab inputs
    std::string other, give, receive;
    other = IO->getString("");
    give = IO->getString("");
    receive = IO->getString("");

    // Try to cast person to User
    User* personP = dynamic_cast<User*>(person);
    if (personP) {
        personP->trade(getUser(other), give, receive, IO);
    } else {
        IO->getOut() << "Cannot do trade" << std::endl;
    }
}

void Board::auction(Property* prop, std::string exclude) {
    // Note: there is a loop and the totalBidders and bidders vectors because we need to account for the case
    // where someone bids more than they are able and get disqualified from bidding and we need to restart bidding;

    bool restart = true;
    std::vector<User*> totalBidders;

    // Copy over just the addresses of each user
    // This could of been done with the copy constructor but the users vector is a vector of unique ptrs
    // so it can't be copied
    // Leave out the exclude string
    for (auto& user: users) {
        if (user->getName() != exclude) totalBidders.push_back(user.get());
    }

    if (fairBidding) {
        std::vector<User*> bidders(totalBidders);
        std::vector<int> amounts(bidders.size(), 0);
        std::vector<bool> stillIn(bidders.size(), true);
        int currentBidder = 0;
        int highestBid = 0;

        while (std::count(stillIn.begin(), stillIn.end(), true) > 1) {
            // Check if the player doesn't want to bid anymore
            if (!stillIn[currentBidder]) continue;

            // Ask current bidder what they would like to do
            IO->getOut() << bidders[currentBidder]->getName() << ", the current bid is $" << highestBid << ", either bid an amount or enter \"stop\" to stop bidding: ";
            std::string op = IO->getString("");

            // Try to convert op to an integer
            try {
                int amount = stoi(op);

                // Check if bid is higher than current bid
                if (amount > highestBid) {
                    IO->getOut() << "New highest bid from " << bidders[currentBidder]->getName() << " of $" << amount << std::endl << std::endl;
                    highestBid = amount;
                    amounts[currentBidder] = amount;

                    currentBidder++;
                } else if (amount > amounts[currentBidder]) {
                    IO->getOut() << "Not highest bid but higher than personnal bid of $" << amounts[currentBidder] << std::endl << std::endl;
                    amounts[currentBidder] = amount;

                    currentBidder++;
                } else {
                    IO->getOut() << "Bid too small, must be atleast $" << amounts[currentBidder] << std::endl;
                }
            } catch (std::invalid_argument& err) {
                // If we got here, then the operation is a string
                if (op == "stop") {
                    IO->getOut() << bidders[currentBidder]->getName() << " has exited the bidding" << std::endl << std::endl;
                    stillIn[currentBidder] = false;

                    currentBidder++;
                } else {
                    IO->getOut() << "Invalid Choice" << std::endl;
                }
            }

            // Loop back to starting bidder
            if (currentBidder >= static_cast<int>(bidders.size())) currentBidder = 0;
        }

        // Clear everyone with zero values
        for (int i = 0; i<static_cast<int>(bidders.size()); ++i) {
            if (amounts[i] == 0) {
                bidders.erase(bidders.begin()+i, bidders.begin()+i+1);
                amounts.erase(amounts.begin()+i, amounts.begin()+i+1);
                stillIn.erase(stillIn.begin()+i, stillIn.begin()+i+1);
            }
        }

        // Ask every person from highest to lowest to pay their bid
        bool paid = false;
        while (!paid && bidders.size() > 0) {
            // Find highest bidder
            int max = 0;
            User* highestBidder;
            for (int i = 0; i<static_cast<int>(bidders.size()); ++i) {
                if (amounts[i] > max) {
                    max = amounts[i];
                    highestBidder = bidders[i];
                }
            }

            // Get the user to pay, if they don't move to the next person
            paid = highestBidder->charge(max, IO, false);
            if (paid) {
                highestBidder->addProperty(prop);
                IO->getOut() << prop->getName() << " has been sold to " << highestBidder->getName() << " for $" << highestBid << std::endl;
            }
        }

        if (!paid) {
            IO->getOut() << "No one has placed a valid bid, so the property will go to the bank" << std::endl;
            prop->setOwner(nullptr);
        }
    } else {
        while (restart) {
            int highestBid = 0;
            User* bidPlayer = nullptr;
            std::vector<User*> bidders(totalBidders);
            int currentBidder = 0;

            // Set restart value initially to false and set true only if player can't pay bid
            restart = false;

            // Go through bidding while there are still more than 1 bidder
            while (bidders.size() > 1 || (bidders.size() == 1 && highestBid == 0)) {
                // Ask current bidder what they would like to do
                IO->getOut() << bidders[currentBidder]->getName() << ", the current bid is $" << highestBid << ", either bid an amount or enter \"stop\" to stop bidding: ";
                std::string op = IO->getString("");

                // Try to convert op to an integer
                try {
                    int amount = stoi(op);

                    // Check if bid is higher than current bid
                    if (amount > highestBid) {
                        IO->getOut() << "New highest bid from " << bidders[currentBidder]->getName() << " of $" << amount << std::endl << std::endl;
                        highestBid = amount;
                        bidPlayer = bidders[currentBidder];

                        currentBidder++;
                    } else {
                        IO->getOut() << "Bid too small" << std::endl;
                    }
                } catch (std::invalid_argument& err) {
                    // If we got here, then the operation is a string
                    if (op == "stop") {
                        IO->getOut() << bidders[currentBidder]->getName() << " has exited the bidding" << std::endl << std::endl;
                        bidders.erase(bidders.begin()+currentBidder, bidders.begin()+currentBidder+1);

                    } else {
                        IO->getOut() << "Invalid Choice" << std::endl;
                    }
                }

                if (currentBidder >= static_cast<int>(bidders.size())) currentBidder = 0;
            }

            // If someone gets the building, give it to them
            // If not, then give the building back to the bank
            if (!bidders.empty() && bidPlayer != nullptr) {
                // Check if the player can actually pay off the bid amount, restart bidding if not
                if (!bidPlayer->charge(highestBid, IO, false)) {
                    // If they can't pay the bid amount, find the user in the totalBidders vector and remove them
                    auto person = totalBidders.begin();
                    while (person != totalBidders.end() && *person != bidPlayer) {
                        person++;
                    }

                    if (*person == bidPlayer) {
                        totalBidders.erase(person, person+1);
                        IO->getOut() << bidPlayer->getName() << " has been disqualified from bidding, bidding will now restart" << std::endl << std::endl;
                    }
                } else {
                    bidPlayer->addProperty(prop);
                    IO->getOut() << prop->getName() << " has been sold to " << bidPlayer->getName() << " for $" << highestBid << std::endl;
                }
            } else {
                IO->getOut() << "No one has placed a valid bid, so the property will go to the bank" << std::endl;
                prop->setOwner(nullptr);
            }
        }
    }
}

void Board::notify(int position, Player* person) {
    buildings[position]->notifyLand(person, IO, -1, -1);
}

std::string Board::encode(Board* board) {
    std::ostringstream output;

    // First add the user data
    output << board->users.size() << std::endl;
    for (auto& user: board->users) {
        output << user->getName() << " " << user->getChar() << " " << user->getRollUps() << " " << user->getCash() << " " << user->getPosition();

        // Add the tims line data if needed
        if (user->getPosition() == JAILPOSITION) {
            if (board->inLine(user.get())) {
                output << " 1 " << board->linePosition(user.get());
            } else {
                output << " 0";
            }
        }
        
        output << std::endl;
    }

    // Now add the building information
    for (auto& building: board->buildings) {
        // Try to convert the building to a property, if we get a nullptr, then the building is not a property and we can skip it
        Property* prop = dynamic_cast<Property*>(building.get());

        if (!prop) continue;

        // Calculate the improvement value
        int improvements = 0;
        if (prop->isMortgaged()) improvements = -1;
        else {
            // Try to convert the property to an Academic Building pointer and if it works get the number of improvements
            AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(prop);

            if (academic) {
                improvements = academic->getImprovements();
            }
        }

        // Output data to string
        output << prop->getName() << " " << (prop->getOwner()? prop->getOwner()->getName() : "BANK") << " " << improvements << std::endl;
    }

    return output.str();
}

std::unique_ptr<Board> Board::decode(std::string boardEncode, std::shared_ptr<IOManager> io, bool fairBidding) {
    auto board = std::make_unique<Board>(io, fairBidding);
    std::istringstream data{boardEncode};
    std::string line;

    // Get player count
    int players;
    data >> players;
    // Clear input
    getline(data, line);

    // Load player data
    for (int i = 0; i<players; i++) {
        getline(data, line);
        std::istringstream lineData{line};
        std::string name;
        char character;
        int rollUps, money, position;

        lineData >> name >> character >> rollUps >> money >> position;
        board->addUser(name, character, money, position, rollUps);

        // Add jail data if needed
        if (position == JAILPOSITION) {
            int notVisiting;
            lineData >> notVisiting;

            if (notVisiting == 1) {
                int position;
                lineData >> position;

                board->addTimsPerson(board->getUser(name), position);
            }
        }
    }

    // Load property data
    while (getline(data, line)) {
        std::istringstream lineData{line};
        std::string name, owner;
        int improvements;

        lineData >> name >> owner >> improvements;

        // Get property pointer, if it can't be found, skip
        Property* prop = dynamic_cast<Property*>(board->getBuilding(name));
        if (!prop) continue;

        // Get owner pointer if it exists and give it the property
        if (owner != "BANK") {
            User* user = board->getUser(owner);
            user->addProperty(prop);

            // If the property is an academic building, add the improvements
            AcademicBuilding* aprop = dynamic_cast<AcademicBuilding*>(prop);
            if (aprop) {
                if (improvements > 0) aprop->forceImprovement(improvements);
            }

            // Mortgage the property if it needs to be mortgaged
            if (improvements == -1) {
                prop->mortgage();
            }
        }
    }

    return board;
}

