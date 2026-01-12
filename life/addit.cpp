#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <getopt.h>

class Cell {
public:
    bool isAlive;
    Cell(bool alive = false) : isAlive(alive) {}
};

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int rows;
    int cols;

public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        cells.resize(rows, std::vector<Cell>(cols));
    }

    void setCell(int row, int col, bool alive) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            cells[row][col].isAlive = alive;
        }
    }

    bool getCell(int row, int col) const {
        row = (row + rows) % rows; // Toroidal wrapping for rows and columns
        col = (col + cols) % cols;
        return cells[row][col].isAlive;
    }

    int countLiveNeighbors(int row, int col) const {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                if (getCell(row + i, col + j)) {
                    ++count;
                }
            }
        }
        return count;
    }

    void print() const {
        for (const auto& row : cells) {
            for (const auto& cell : row) {
                std::cout << (cell.isAlive ? "O" : ".");
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<Cell>>& getCells() {
        return cells;
    }
};

class GameOfLife {
private:
    Grid grid;
    std::vector<int> birthRules;
    std::vector<int> survivalRules;
    std::string universeName;
    int rows;
    int cols;
    int currentIteration;

public:
    GameOfLife(int rows, int cols, const std::vector<int>& birthRules, const std::vector<int>& survivalRules, const std::string& universeName)
        : grid(rows, cols), birthRules(birthRules), survivalRules(survivalRules), universeName(universeName), rows(rows), cols(cols), currentIteration(0) {}

    void PrintUnInfo() const {
        std::cout << "Universe name: " << universeName << std::endl;
        std::cout << "Size: " << rows << " x " << cols << std::endl;
    }

    void setCell(int row, int col, bool alive) {
        grid.setCell(row, col, alive);
    }

    void step() {
        std::vector<std::vector<Cell>> newCells = grid.getCells();

        for (int i = 0; i < grid.getCells().size(); ++i) {
            for (int j = 0; j < grid.getCells()[0].size(); ++j) {
                int liveNeighbors = grid.countLiveNeighbors(i, j);
                bool isAlive = grid.getCell(i, j);

                if (isAlive) {
                    newCells[i][j].isAlive = std::find(survivalRules.begin(), survivalRules.end(), liveNeighbors) != survivalRules.end();
                } else {
                    newCells[i][j].isAlive = std::find(birthRules.begin(), birthRules.end(), liveNeighbors) != birthRules.end();
                }
            }
        }
        grid.getCells() = newCells;
        ++currentIteration;
    }

    void print() const {
        grid.print();
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for writing");
        }

        file << "#Life 1.06\n";
        file << "#N " << universeName << "\n";
        file << "#R B" << birthRules[0];
        for (size_t i = 1; i < birthRules.size(); ++i) {
            file << birthRules[i];
        }
        file << "/S" << survivalRules[0];
        for (size_t i = 1; i < survivalRules.size(); ++i) {
            file << survivalRules[i];
        }
        file << "\n";
        file << "#S " << cols << " " << rows << "\n";

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid.getCell(i, j)) {
                    file << i << " " << j << "\n";
                }
            }
        }

        file.close();
    }

    void printInfo() const {
        std::cout << "Universe name: " << universeName << std::endl;
        std::cout << "Rules: B";
        for (int rule : birthRules) {
            std::cout << rule;
        }
        std::cout << "/S";
        for (int rule : survivalRules) {
            std::cout << rule;
        }
        std::cout << std::endl;
        std::cout << "Iteration: " << currentIteration << std::endl;
    }
};

class Parser {
public:
    static GameOfLife parseFile(const std::string& filename) {
        std::string universeName;
        std::string rule;
        int width, height;
        std::vector<std::pair<int, int>> liveCells = read_cells(filename, universeName, rule, width, height);

        if (liveCells.empty()) {
            throw std::runtime_error("Failed to parse file");
        }

        std::vector<int> birthRules, survivalRules;
        size_t slashPos = rule.find('/');
        std::string birth = rule.substr(0, slashPos);
        std::string survive = rule.substr(slashPos + 1);

        for (char c : birth) {
            if (isdigit(c)) {
                birthRules.push_back(c - '0');
            }
        }

        for (char c : survive) {
            if (isdigit(c)) {
                survivalRules.push_back(c - '0');
            }
        }

        GameOfLife game(height, width, birthRules, survivalRules, universeName);
        for (const auto& cell : liveCells) {
            game.setCell(cell.first, cell.second, true);
        }

        return game;
    }

private:
    static std::vector<std::pair<int, int>> read_cells(const std::string& filename, std::string& universeName, std::string& rule, int& width, int& height) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
            return {};
        }

        std::string line;
        std::vector<std::pair<int, int>> liveCells;

        // Read the first line and check if it starts with "#Life"
        std::getline(file, line);
        if (line.substr(0, 6) != "#Life ") {
            std::cerr << "Incorrect file format: missing #Life" << std::endl;
            return {};
        }

        // Read the second line and check if it starts with "#N"
        std::getline(file, line);
        if (line.substr(0, 3) != "#N ") {
            std::cerr << "Incorrect file format: missing #N" << std::endl;
            return {};
        }
        universeName = line.substr(3);

        // Read the third line and check if it starts with "#R"
        std::getline(file, line);
        if (line.substr(0, 3) != "#R ") {
            std::cerr << "Incorrect file format: missing #R" << std::endl;
            return {};
        }
        rule = line.substr(3);

        // Read the fourth line and check if it starts with "#S"
        std::getline(file, line);
        if (line.substr(0, 3) != "#S ") {
            std::cerr << "Incorrect file format: missing #S" << std::endl;
            return {};
        }
        if (sscanf(line.c_str() + 3, "%d %d", &width, &height) != 2) {
            std::cerr << "Incorrect file format: invalid #S line" << std::endl;
            return {};
        }

        // Read the coordinates of live cells
        while (std::getline(file, line)) {
            int x, y;
            if (sscanf(line.c_str(), "%d %d", &x, &y) == 2) {
                liveCells.emplace_back(x, y);
            }
        }

        file.close();
        return liveCells;
    }
};

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void printHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "dump <filename> - save the universe to a file" << std::endl;
    std::cout << "tick <n=1> (or t <n=1>) - calculate n (default 1) iterations and print the result" << std::endl;
    std::cout << "exit - exit the game" << std::endl;
    std::cout << "help - print this help message" << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> files = {"un1.txt", "un2.txt", "un3.txt"};
    std::string inputFile;
    std::string outputFile;
    int iterations = 0;
    bool offlineMode = false;

    int opt;
    static struct option long_options[] = {
        {"iterations", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int long_index = 0;
    while ((opt = getopt_long(argc, argv, "i:o:", long_options, &long_index)) != -1) {
        switch (opt) {
            case 'i':
                iterations = std::stoi(optarg);
                offlineMode = true;
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -i <iterations> -o <outputFile>" << std::endl;
                return 1;
        }
    }

    if (offlineMode) {
        if (outputFile.empty()) {
            std::cerr << "Output file must be specified in offline mode" << std::endl;
            return 1;
        }
        if (optind >= argc) {
            std::cerr << "Input file must be specified" << std::endl;
            return 1;
        }
        inputFile = argv[optind];
    } else {
        std::cout << "Do you have game's file? (y/n)";
        char answ;
        std::cin >> answ;

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        if (answ == 'n') {
            int num = std::rand() % files.size();
            inputFile = files[num];
        } else {
            std::cout << "Enter the filename: ";
            std::cin >> inputFile;
        }
    }

    try {
        GameOfLife game = Parser::parseFile(inputFile);

        if (offlineMode) {
            for (int i = 0; i < iterations; ++i) {
                game.step();
            }
            game.saveToFile(outputFile);
            std::cout << "Universe saved to " << outputFile << std::endl;
        } else {
            game.PrintUnInfo();
            game.print();
            std::cout << std::endl;

            std::string command;
            while (true) {
                std::cout << "Enter command: ";
                std::cin >> command;

                if (command == "dump") {
                    std::string filename;
                    std::cin >> filename;
                    game.saveToFile(filename);
                    std::cout << "Universe saved to " << filename << std::endl;
                } else if (command == "tick" || command == "t") {
                    int n = 1;
                    if (std::cin.peek() != '\n') {
                        std::cin >> n;
                    }
                    for (int i = 0; i < n; ++i) {
                        game.step();
                    }
                    clearScreen();
                    game.printInfo();
                    game.print();
                    std::cout << std::endl;
                } else if (command == "exit") {
                    break;
                } else if (command == "help") {
                    printHelp();
                } else {
                    std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
