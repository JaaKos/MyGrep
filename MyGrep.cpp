#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void noArgs(std::string& source, std::string& search);
int searchString(std::string source, std::string search, const bool& ignoreCase);

int main(int argc, char* argv[])
{
    std::string source;
    std::string search;
    if (argc == 1) noArgs(source, search);
    else if (argc > 2) 
    {
        bool printLineNumbers = false;
        bool printOccurrenceAmount = false;
        bool ignoreCase = false;
        bool reverseSearchResults = false;
        if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'o')
        {
            std::string options(argv[1]);
            for (int i = 2; i < options.length(); i++)
            {
                if (options[i] == 'l') printLineNumbers = true;
                if (options[i] == 'o') printOccurrenceAmount = true;
                if (options[i] == 'i') ignoreCase = true;
                if (options[i] == 'r') reverseSearchResults = true;
            }
        }
        search = argv[argc-2];
        std::ifstream File;
        File.open(argv[argc-1]);
        if (!File.is_open()) 
        {
        std::cerr << "Error: File not found";
        return 1;
        } 
        std::vector<int> lineCounts;
        std::vector<std::string> matchingLines;
        int lineCount = 0;
        while (true)
        {
            lineCount++;
            std::getline(File, source);
            int value;
            value = searchString(source, search, ignoreCase);
            if ((!reverseSearchResults && value != -1) || (reverseSearchResults && value == -1)) 
            {
                lineCounts.push_back(lineCount);
                matchingLines.push_back(source);
            }
            if (File.eof()) break;
        }
        File.close();
        if (!matchingLines.empty())
        {
            if (printLineNumbers) for (int i = 0; i < matchingLines.size(); i++) std::cout << lineCounts[i] << "\t" << matchingLines[i] << "\n";
            else for (int i = 0; i < matchingLines.size(); i++) std::cout << "\t" << matchingLines[i] << "\n";
            std::cout << std::endl;
            if(printOccurrenceAmount)
            {
                if (reverseSearchResults) std::cout << "Occurrences of lines NOT containing \"" << argv[argc-2] << "\": ";
                else std::cout << "Occurrences of lines containing \"" << argv[argc-2] << "\": ";
                std::cout << matchingLines.size() << std::endl;
            } 
        } 
        else std::cout << search << " NOT found in " << argv[argc-1] << std::endl;
    }
}

int searchString(std::string source, std::string search, const bool& ignoreCase)
{
    if (ignoreCase)
    {
        for (int i = 0; i < search.length(); i++) search[i] = std::tolower(search[i]);
        for (int i = 0; i < source.length(); i++) source[i] = std::tolower(source[i]);
    }
    for (int i = 0; i < source.length(); i++)
    {
        if (source[i] == search[0])
        {
            std::string temp = source.substr(i, search.length());
            if (temp == search) 
            {
                int position = i;
                return position;
            }
        }
    }
    return -1;
}

void noArgs(std::string& source, std::string& search) 
{
    std::cout << "Give a string from which to search for: ";
    std::getline(std::cin, source);
    std::cout << "Give search string: ";
    std::getline(std::cin, search);
    int value = searchString(source, search, 0);
    if (value != -1)
    {
        std::cout << search << " found in " << source << " in position: ";
        std::cout << value;
        std::cout << std::endl;
    } 
    else std::cout << search << " NOT found in " << source << std::endl;
}
