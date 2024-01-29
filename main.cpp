#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector> 

std::vector<std::string> splitString(const std::string& input) {
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ' ')) { // Split by space
        tokens.push_back(token);
    }

    return tokens;
}



int main() {
    
    std::string input; 
    std::getline(std::cin, input); // Use getline to read a whole line, not just one word


    std::vector<std::string> tokens = splitString(input);

    

    std::vector<int> numbers;
    // Print out the tokens as integers
    for (const auto& token : tokens) {
        int number = std::stoi(token);
        numbers.push_back(number);
    }

    int e = numbers[0];
    int n = numbers[1];





    return 0;
}
