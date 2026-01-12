#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

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

class Cell 
{
    public:
        bool isAlive;
        Cell(bool alive = false) : isAlive(alive) {}
};

class Grid 
{
    private:
        std::vector<std::vector<Cell>> cells;
        int rows;
        int cols;

    public:
        Grid(int rows, int cols);
        void setCell(int row, int col, bool alive);
        bool getCell(int row, int col) const;
        int countLiveNeighbors(int row, int col) const;
        void print() const;
        std::vector<std::vector<Cell>>& getCells();
};

class GameOfLife 
{
    private:
        Grid grid;
        std::vector<int> birthRules;
        std::vector<int> survivalRules;
        std::string universeName;
        int rows;
        int cols;
        int currentIteration;

    public:
        GameOfLife(int rows, int cols, const std::vector<int>& birthRules, const std::vector<int>& survivalRules, const std::string& universeName);
        void PrintUnInfo() const;
        void setCell(int row, int col, bool alive);
        void step();
        void print() const;
        void saveToFile(const std::string& filename) const;
        void printInfo() const;
        int getRows() const { return rows; }
        int getCols() const { return cols; }
        std::string getUniverseName() const { return universeName; }
        bool getCell(int row, int col) const { return grid.getCell(row, col); }
};

class Parser 
{
    public:
        static GameOfLife parseFile(const std::string& filename);

    private:
        static std::vector<std::pair<int, int>> read_cells(const std::string& filename, std::string& universeName, std::string& rule, int& width, int& height);
};

void clearScreen();
void printHelp();

#endif