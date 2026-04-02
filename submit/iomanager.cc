export module iomanager;

import <iostream>;
import <string>;
import <vector>;

export class IOManager {
    std::istream& in;
    std::ostream& out;

    int getNumHead(std::string prompt, int min, int max, bool followMin, bool followMax) const;

    public:

    std::ostream& getOut() const;
    bool fail() const;
    void clear() const;
    void wait() const;

    IOManager(std::istream &in, std::ostream &out);
    int getNum(std::string prompt, int min, int max) const;
    int getNum(std::string prompt, int max) const;
    int getNumWithMin(std::string prompt, int min) const;
    int getNum(std::string prompt) const;
    std::string getString(std::string prompt, std::vector<std::string> options = {}) const;
    std::string getStringLine(std::string prompt, std::vector<std::string> options = {}) const;
};

