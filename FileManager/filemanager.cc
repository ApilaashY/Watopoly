export module filemanager;

import board;
import iomanager;

import <string>;
import <memory>;

export class FileManager {
    public:
    
    static bool save(Board* board, std::string file);
    static std::unique_ptr<Board> load(std::string input, std::shared_ptr<IOManager> io, bool fairBidding);
};
