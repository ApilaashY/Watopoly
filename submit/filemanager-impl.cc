module filemanager;

import board;
import iomanager;

import <string>;
import <fstream>;
import <memory>;

bool FileManager::save(Board* board, std::string file) {
    std::ofstream outFile{file};

    outFile << Board::encode(board);

    return outFile.good();
}

std::unique_ptr<Board> FileManager::load(std::string file, std::shared_ptr<IOManager> io, bool fairBidding) {
    std::ifstream inFile{file};

    std::string total = "";
    std::string line;

    while (getline(inFile, line)) {
        total += line += "\n";
    }

    return Board::decode(total, io, fairBidding);
}
