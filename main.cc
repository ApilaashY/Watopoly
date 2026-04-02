import dice;
import testdice;
import board;
import iomanager;
import filemanager;

import <iostream>;
import <memory>;
import <vector>;

using namespace std;

int main(int argc, char* argv[]) {
    auto io = make_shared<IOManager>(cin, cout);
    bool testing = false;
    bool fairBidding = true;
    string loadFile = "";
    auto die = make_unique<Dice>();
    auto tdie = make_unique<TestDice>(io);

    // Grab command line arguments
    for (int i = 0; i<argc; ++i) {
        if (string{argv[i]} == "-testing") testing = true;
        else if (string{argv[i]} == "-load") {
            i++;
            loadFile = string{argv[i]};
        } else if (string{argv[i]} == "-no-fair-bidding") {
            fairBidding = false;
        }
    }

    // Create the board object depending on whether 
    // a load file exists
    auto board = (loadFile == "") ? make_unique<Board>(io, fairBidding) : FileManager::load(loadFile, io, fairBidding);
    int playerCount = board->playerCount();

    // If the board isn't coming from a file, ask the user for player information
    if (loadFile == "") {
        playerCount = io->getNum("How many players are playing?(2-6): ", 2, 6);
        io->getStringLine(""); // Clear input
        for (int i = 0; i<playerCount; ++i) {
            // Display Name options
            for (auto name: board->leftOverNames()) {
                io->getOut() << "    - " << name << endl;
            }

            io->getOut() << "Player " << i+1 << ", ";
            string name = io->getStringLine("Choose one of the names above: ");
            if (!board->addUser(name)) {
                i--;
                io->getOut() << "Name is not in selection" << endl;
            } else {
                io->getOut() << "Player " << i+1 << " has chosen " << name << endl << endl;
            }
        }
    }

    // Run while the game is still going
    // i.e. when the player count is not 1
    string command;
    int curPlayer = 0;
    bool rolled = false;
    while (playerCount > 1 && !io->fail()) {
        io->getOut() << *board;
        io->getOut() << board->getUser(curPlayer)->getName() << "'s turn, select one of the options" << endl;
        io->getOut() << " - roll: Roll the dice for your turn" << endl;
        io->getOut() << " - next: Go to the next player's turn, only if already rolled dice" << endl;
        io->getOut() << " - trade <name> <give> <receive>: Offer to give <name> <give> in return they will give <receive>" << endl;
        io->getOut() << " - mortgage <property>: Attempt to mortgage <property>" << endl;
        io->getOut() << " - unmortgage <property>: Attempt to unmortgage <property>" << endl;
        io->getOut() << " - assets: List all of your cash and assets" << endl;
        io->getOut() << " - all: List the cash and assets of all the players" << endl;
        io->getOut() << " - save <filename>: Save game data to <filename>" << endl;
        if (testing) {
            io->getOut() << "Testing commands:" << endl;
            io->getOut() << "- addCash <amount>" << endl;
            io->getOut() << "- exit" << endl;
            io->getOut() << "- charge <amount>" << endl;
            io->getOut() << "- chargeForce <amount>" << endl;
        }
        command = io->getString("Command: ");

        // Run commands
        if (command == "roll") { // Roll Command
            // Checked if the user already rolled for their turn
            if (!rolled) {
                if (testing) {
                    rolled = !board->move(curPlayer, tdie.get());
                } else {
                    rolled = !board->move(curPlayer, die.get());
                }
            } else {
                io->getOut() << "You have already rolled for your turn, enter \"next\" if you would like to end your turn and go to the next person" << endl;
            }
        } else if (command == "trade") {
            board->trade(board->getUser(curPlayer));
        } else if (command == "improve") {
            string prop = io->getString("");
            string op = io->getString("");

            if (op == "buy") {
                board->getUser(curPlayer)->manageImprove(prop, io, true);
            } else if (op == "sell") {
                board->getUser(curPlayer)->manageImprove(prop, io, false);
            } else {
                io->getOut() << "Operation must be either buy or sell" << endl;
            }
        } else if (command == "mortgage") {
            string prop = io->getString("");

            board->getUser(curPlayer)->mortgage(prop, io);
        } else if (command == "unmortgage") {
            string prop = io->getString("");

            board->getUser(curPlayer)->unMortgage(prop, io);
        } else if (command == "assets") {
            io->getOut() << board->getUser(curPlayer)->showAssets();
        } else if (command == "all") {
            for (int i = 0; i<playerCount; ++i) {
                io->getOut() << board->getUser(i)->getName() << "'s Assets:" << endl;
                io->getOut() << board->getUser(i)->showAssets() << endl;
            }
        } else if (command == "save") {
            string file = io->getString("");
            if (FileManager::save(board.get(), file)) {
                io->getOut() << "Successfully saved game data to " << file << endl;
            }
        }
        
        else if (testing && command == "addCash") { // Command to aid in testing
            int cash = io->getNum("", -10000, 10000);
            board->getUser(curPlayer)->addCash(cash);
        } else if (testing && command == "stop") {
            break;
        } else if (command == "next") {
            // Make sure the user has already rolled for their turn
            if (!rolled) {
                io->getOut() << "You must roll before going to the next person" << endl;
            } else {
                io->getOut() << "Moving on to next player" << endl;
                curPlayer++;
                rolled = false;
            }
        } else if (testing && command == "charge") {
            int amount = io->getNum("", 0, 20000);
            board->getUser(curPlayer)->charge(amount, io, false);
        } else if (testing && command == "chargeForce") {
            int amount = io->getNum("", 0, 20000);
            board->getUser(curPlayer)->charge(amount, io, true);
        } else { // Invalid Command
            io->getOut() << "Invalid command, try again" << endl;
        }

        // Refresh the number of players
        playerCount = board->playerCount();

        // Check if current player overflowed
        if (curPlayer >= playerCount) {
            curPlayer = 0;
        }

        // Pause and wait till the user presses enter to continue
        io->getOut() << endl << "Press Enter to Continue" << endl;
        io->clear();
        io->wait();
        io->getOut() << endl << endl;
    }

    // Announce winner if exists
    if (playerCount == 1) {
        io->getOut() << "WINNER IS " << board->getUser(0)->getName() << "!" << endl;
    } else {
        io->getOut() << "No winner for this game" << endl;
    }

    return 0;
}
