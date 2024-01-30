#include <iostream>
#include <cmath>
#include <numeric>
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

   

    //read the next line of input for size m 
    std::getline(std::cin, input);
    int m = std::stoi(input);

    

    //read the next line of input for the message
    std::getline(std::cin, input);
    std::string messageString = input;

    //convert the message into an array of integers 
    std::vector<int> encryptedMessage(m);
    encryptedMessage = splitStringInts(messageString);

    result.push_back(publicKey);
    result.push_back(encryptedMessage);

    //output test to confirm proper input processing 
    /*std::cout << "Public key: (" << result[0][0] << ", " << result[0][1] << ")" << std::endl;
    std::cout << "Encrypted message size " << m << ": ";
    for (auto& i : result[1]) {
        std::cout << i << " ";
    }
    std::cout << std::endl;*/

    return result;
}

//To check primality of found p 
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}



//finds p and q values
std::vector<int> findPrimeFactors(int n) {
    int p = 0, q = 0;

    // Check for prime factors up to square root of n
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0 && isPrime(i)) {
            p = i;
            q = n / i;
            break;
        }
    }

    std::vector<int> primeFactors = { p, q };
    return primeFactors;
}



bool isPublicKeyValid(int e, std::vector<int> pqTuple) {
    // Check that the public key has exactly two elements
    if (pqTuple.size() != 2) {
        return false;
    }

    int p = pqTuple[0];
    int q = pqTuple[1];


    // Check that p and q are not equal
    if (p == q) {
        return false;
    }

    // Check that p and q are relatively prime
    int gcd = std::gcd(p , q );
    if (gcd != 1) {
        return false;
    }

    // Check that p*q is greater than 255
    if (p * q <= 255) {
        return false;
    }

    int tN = (q - 1)*(q - 1);
    gcd = std::gcd(e,tN);
    if (gcd != 1) {
        return false;
    }


    return true;
}


int decryptChar(int encryptedChar, int d, int n) {
    int decryptedChar = 0;

    //decryptedChar = encryptedChar^d mod n
    decryptedChar = static_cast<int>(pow(encryptedChar, d)) % n;

    return decryptedChar;
}









int main() {
    std::vector<std::vector<int>> input = processInput();
    std::vector<int> publicKey = input[0]; //(e,n)
    std::vector<int> encryptedMessage = input[1];

    int e = publicKey[0];
    int n = publicKey[1];

    std::vector<int> pqTuple = findPrimeFactors(n);
    int p = pqTuple[0];
    int q = pqTuple[1];


    //check if the public key is valid
    if (!isPublicKeyValid(e, pqTuple)) {
        std::cout << "Public key is not valid!" << std::endl;
        return 0;
    }

    // Find the inverse of e mod((p-1)*(q-1))
    //inverse = value * e such that (value * e) % ((p-1)*(q-1)) == 1
    int tN = (p - 1) * (q - 1);
    int inverseD = 0;
    for (int i = 1; i < tN; i++) {
        if ((e * i) % tN == 1) {
            inverseD = i;
            break;
        }
    }

    std::cout << "p = " << p << ", q = " << q << "toitent(n), " << tN << ", d = " << inverseD << std::endl;


    

    return 0;
}
