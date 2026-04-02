module iomanager;

import <iostream>;
import <string>;
import <vector>;
import <algorithm>;

IOManager::IOManager(std::istream &in, std::ostream &out):
    in{in},
    out{out} {}

std::ostream& IOManager::getOut() const {
    return out;
}

bool IOManager::fail() const {
    return in.fail();
}

void IOManager::wait() const {
    std::string nothing;
    getline(in, nothing);
}

void IOManager::clear() const {
    std::string nothing;
    getline(in, nothing);
}

int IOManager::getNumHead(std::string prompt, int min, int max, bool followMin, bool followMax) const {
    int val;
    std::string clear;
    out << prompt;
    while (!(in >> val) || (followMin && val < min) || (followMax && val > max)) {
        // Clear an invalid answer
        if (in.fail()) {
            in.clear(); // reset state bits
            in.ignore(); // reads + throws away 1 char by default
            std::getline(in, clear);
        }
        out << prompt;
    }

    return val;
}

int IOManager::getNum(std::string prompt, int min, int max) const {
    return getNumHead(prompt, min, max, true, true);
}

int IOManager::getNum(std::string prompt, int max) const {
    return getNumHead(prompt, 0, max, false, true);
}

int IOManager::getNumWithMin(std::string prompt, int min) const {
    return getNumHead(prompt, min, 0, true, false);
}

int IOManager::getNum(std::string prompt) const {
    return getNumHead(prompt, 0, 0, false, false);
}

std::string IOManager::getString(std::string prompt, std::vector<std::string> options) const {
    std::string val;
    out << prompt;
    while (!(in >> val) || (options.size() != 0 && std::find(options.begin(), options.end(), val) == options.end())) {
        out << prompt;
    }

    return val;
}

std::string IOManager::getStringLine(std::string prompt, std::vector<std::string> options) const {
    std::string val;
    out << prompt;
    while (!(getline(in, val)) || (options.size() != 0 && std::find(options.begin(), options.end(), val) == options.end())) {
        out << prompt;
    }

    return val;
}

