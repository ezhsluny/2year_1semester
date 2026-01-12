#include <gtest/gtest.h>
#include "../GameOfLife.hpp"
#include <fstream>
#include <iostream>


TEST(GameOfLife_Grid, Constructor)
{
    EXPECT_THROW(Grid(-3, -8), std::invalid_argument);
    EXPECT_NO_THROW(Grid(10, 10));
}

TEST(GameOfLife_Grid, setCell)
{
    Grid test_grid(10, 10);
    EXPECT_THROW(test_grid.setCell(-1, -1, true), std::out_of_range);
    EXPECT_THROW(test_grid.setCell(15, 15, true), std::out_of_range);
    EXPECT_NO_THROW(test_grid.setCell(1, 1, false));
}

TEST(GameOfLife_class, Constructor)
{
    std::vector<int> birthRules = {2, 3};
    std::vector<int> surviveRules = {2, 3};
    std::string unName = "test universe";
    EXPECT_THROW(GameOfLife(-1, -1, birthRules, surviveRules, unName), std::invalid_argument);
    EXPECT_NO_THROW(GameOfLife(10, 10, birthRules, surviveRules, unName));

    birthRules = {};
    EXPECT_THROW(GameOfLife(10, 10, birthRules, surviveRules, unName), std::invalid_argument);

    surviveRules = {};
    birthRules = {1};
    EXPECT_THROW(GameOfLife(10, 10, birthRules, surviveRules, unName), std::invalid_argument);
}

TEST(GameOfLife_class, Initialization) 
{
    GameOfLife game(5, 5, {3}, {2, 3}, "TestUniverse");
    EXPECT_EQ(game.getRows(), 5);
    EXPECT_EQ(game.getCols(), 5);
    EXPECT_EQ(game.getUniverseName(), "TestUniverse");
}

TEST(GameOfLife_class, SetCell) 
{
    GameOfLife game(5, 5, {3}, {2, 3}, "TestUniverse");
    game.setCell(2, 2, true);
    EXPECT_TRUE(game.getCell(2, 2));
}

TEST(GameOfLife_class, Step) 
{
    GameOfLife game(5, 5, {3}, {2, 3}, "TestUniverse");
    game.setCell(1, 2, true);
    game.setCell(2, 2, true);
    game.setCell(3, 2, true);
    game.step();

    EXPECT_TRUE(game.getCell(2, 2));
    EXPECT_FALSE(game.getCell(1, 2));
    EXPECT_FALSE(game.getCell(3, 2));
}

TEST(GameOfLife_class, SaveToFile) 
{
    GameOfLife game(5, 5, {3}, {2, 3}, "TestUniverse");
    game.setCell(2, 2, true);
    game.saveToFile("/home/ezhsluny/Documents/life/test_output.txt");

    std::ifstream file("/home/ezhsluny/Documents/life/test_output.txt");
    ASSERT_TRUE(file.is_open());
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "#Life 1.06");
    file.close();
}

TEST(Parser_class, ParseFile) 
{
    GameOfLife game = Parser::parseFile("/home/ezhsluny/Documents/life/test_input.txt");
    EXPECT_EQ(game.getRows(), 5);
    EXPECT_EQ(game.getCols(), 5);
    EXPECT_EQ(game.getUniverseName(), "TestUniverse");
    EXPECT_TRUE(game.getCell(2, 2));
}

TEST(Parser_class, ParseFileCorrect) 
{
    GameOfLife game = Parser::parseFile("/home/ezhsluny/Documents/life/test_input.txt");
    EXPECT_EQ(game.getRows(), 5);
    EXPECT_EQ(game.getCols(), 5);
    EXPECT_EQ(game.getUniverseName(), "TestUniverse");
    EXPECT_TRUE(game.getCell(2, 2));
}

TEST(Parser_class, ParseFileFileNotFound) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/nonexistent_file.txt"), std::runtime_error);
}

TEST(Parser_class, ParseFileMissingLife) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/test_input_missing_life.txt"), std::runtime_error);
}

TEST(Parser_class, ParseFileMissingN) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/test_input_missing_n.txt"), std::runtime_error);
}

TEST(Parser_class, ParseFileMissingR) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/test_input_missing_r.txt"), std::runtime_error);
}

TEST(Parser_class, ParseFileMissingS) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/test_input_missing_s.txt"), std::runtime_error);
}

TEST(Parser_class, ParseFileInvalidCellCoordinates) 
{
    EXPECT_THROW(Parser::parseFile("/home/ezhsluny/Documents/life/test_input_invalid_cells.txt"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
