#include "GameOfLife.hpp"

void parseArguments(int argc, char* argv[], int& iterations, std::string& outputFile, bool& offlineMode, std::string& inputFile);
void interactive_mode(const std::string& inputFile);
void offline_mode(const std::string& inputFile, const std::string& outputFile, int iterations);

int main(int argc, char* argv[]) 
{
    int iterations = 0;
    std::string outputFile;
    bool offlineMode = false;
    std::string inputFile;

    try 
    {
        parseArguments(argc, argv, iterations, outputFile, offlineMode, inputFile);

        if (offlineMode) {
            offline_mode(inputFile, outputFile, iterations);
        } else {
            interactive_mode(inputFile);
        }
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void parseArguments(int argc, char* argv[], int& iterations, std::string& outputFile, bool& offlineMode, std::string& inputFile) 
{
    int opt;
    static struct option long_options[] = {
        {"iterations", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int long_index = 0;
    while ((opt = getopt_long(argc, argv, "i:o:", long_options, &long_index)) != -1) 
    {
        switch (opt) 
        {
            case 'i':
                iterations = std::stoi(optarg);
                offlineMode = true;
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -i <iterations> -o <outputFile>" << std::endl;
                throw std::invalid_argument("Invalid arguments");
        }
    }

    if (offlineMode) 
    {
        if (outputFile.empty()) {
            throw std::invalid_argument("Output file must be specified in offline mode");
        }
        if (optind >= argc) {
            throw std::invalid_argument("Input file must be specified");
        }
        inputFile = argv[optind];
    } 
    else 
    {
        std::cout << "Do you have game's file? (y/n)";
        char answ;
        std::cin >> answ;

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        if (answ == 'n') 
        {
            std::vector<std::string> files = {
                "/home/ezhsluny/Documents/life/un1.txt", 
                "/home/ezhsluny/Documents/life/un2.txt", 
                "/home/ezhsluny/Documents/life/un3.txt"};
            int num = std::rand() % files.size();
            inputFile = files[num];
        } 
        else 
        {
            std::cout << "Enter the filename: ";
            std::cin >> inputFile;
            inputFile = "/home/ezhsluny/Documents/life/" + inputFile;
        }
    }
}

void interactive_mode(const std::string& inputFile) 
{
    GameOfLife game = Parser::parseFile(inputFile);
    game.PrintUnInfo();
    game.print();
    std::cout << std::endl;

    std::string command;
    while (true) 
    {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "dump") 
        {
            std::string filename;
            std::cin >> filename;
            filename = "/home/ezhsluny/Documents/life/" + filename;
            game.saveToFile(filename);
            std::cout << "Universe saved to " << filename << std::endl;
        } 
        else if (command == "tick" || command == "t") 
        {
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
        } 
        else if (command == "exit") 
        { break; } 
        else if (command == "help")
        { printHelp(); } 
        else 
        {
            std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
        }
    }
}

void offline_mode(const std::string& inputFile, const std::string& outputFile, int iterations) 
{
    GameOfLife game = Parser::parseFile(inputFile);
    for (int i = 0; i < iterations; ++i) {
        game.step();
    }
    game.saveToFile(outputFile);
    std::cout << "Universe saved to " << outputFile << std::endl;
}
