#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector> 

//splits a line into vector of string then converts to ints 
std::vector<int> splitStringInts(const std::string& input) {
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    // Split by space into vector
    while (std::getline(ss, token, ' ')) { 
        tokens.push_back(token);
    }

    // Convert to int vector 
    std::vector<int> numbers;
    for (const auto& token : tokens) {
        int number = std::stoi(token);
        numbers.push_back(number);
    }

    return numbers;
}

bool isPublicKeyValid(const std::vector<int>& publicKey) {
    // Check that the public key has exactly two elements
    if (publicKey.size() != 2) {
        return false;
    }

    int e = publicKey[0];
    int n = publicKey[1];

    // Check that e and n are both greater than 1
    if (e <= 1 || n <= 1) {
        return false;
    }

    return true;
}

std::vector<std::vector<int>> processInput() {
    std::vector<std::vector<int>> result;

    std::string input; //input string holding public key and message

    //e and n are the public keys
    std::getline(std::cin, input); // Use getline to read line by line 
    //take and split the input of e and n
    std::vector<int> publicKey;
    publicKey = splitStringInts(input);
    //store the values as ints
    int e = publicKey[0];
    int n = publicKey[1];

    std::cout << std::endl << "e: " << e << " n: " << n << std::endl;

    if (!isPublicKeyValid(publicKey)) {
        std::cout << "Public key is not valid!" << std::endl;
        return result;
    }

    //read the next line of input for size m 
    std::getline(std::cin, input);
    int m = std::stoi(input);

    std::cout << "m: " << m << std::endl;

    //read the next line of input for the message
    std::getline(std::cin, input);
    std::string messageString = input;
    std::cout << "message: " << input << std::endl;

    //convert the message into an array of integers 
    std::vector<int> encryptedMessage(m);
    encryptedMessage = splitStringInts(messageString);

    result.push_back(publicKey);
    result.push_back(encryptedMessage);

    return result;
}



int main() {
    std::vector<std::vector<int>> input = processInput();
    std::vector<int> publicKey = input[0];
    std::vector<int> encryptedMessage = input[1];





    return 0;
}
