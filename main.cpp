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


///////////////////////////////////////////////////////////////////////////////////////////

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



//finds p and q values of n = pq
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

    //totient(n) = (p-1)*(q-1)
    int tN = (q - 1)*(q - 1);
    gcd = std::gcd(e,tN);
    if (gcd != 1) {
        return false;
    }


    return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

int decryptNum(int encryptedChar, int d, int n) {
    int decryptedNum = 1;

    // Perform modular exponentiation: decryptedNum = (encryptedChar^d) % n
    for (int i = 0; i < d; i++) {
        decryptedNum = (decryptedNum * encryptedChar) % n;
    }

    return decryptedNum;
}
std::vector<int> decryptMessageInts(std::vector<int> encryptedMessage, int d, int n) {
    std::vector<int> messageString;

    for (auto& encryptedChar : encryptedMessage) {
        int decryptedInt = decryptNum(encryptedChar, d, n);
        messageString.push_back(decryptedInt);
    }

    return messageString;
}



std::string messageToString(std::vector<int> messageString) {
    std::string decryptedString;

    for (auto& decryptedChar : messageString) {
        switch (decryptedChar) {
            case 7:
                decryptedString += 'A';
                break;
            case 8:
                decryptedString += 'B';
                break;
            case 9:
                decryptedString += 'C';
                break;
            case 10:
                decryptedString += 'D';
                break;
            case 11:
                decryptedString += 'E';
                break;
            case 12:
                decryptedString += 'F';
                break;
            case 13:
                decryptedString += 'G';
                break;
            case 14:
                decryptedString += 'H';
                break;
            case 15:
                decryptedString += 'I';
                break;
            case 16:
                decryptedString += 'J';
                break;
            case 17:
                decryptedString += 'K';
                break;
            case 18:
                decryptedString += 'L';
                break;
            case 19:
                decryptedString += 'M';
                break;
            case 20:
                decryptedString += 'N';
                break;
            case 21:
                decryptedString += 'O';
                break;
            case 22:
                decryptedString += 'P';
                break;
            case 23:
                decryptedString += 'Q';
                break;
            case 24:
                decryptedString += 'R';
                break;
            case 25:
                decryptedString += 'S';
                break;
            case 26:
                decryptedString += 'T';
                break;
            case 27:
                decryptedString += 'U';
                break;
            case 28:
                decryptedString += 'V';
                break;
            case 29:
                decryptedString += 'W';
                break;
            case 30:
                decryptedString += 'X';
                break;
            case 31:
                decryptedString += 'Y';
                break;
            case 32:
                decryptedString += 'Z';
                break;
            case 33:
                decryptedString += ' ';
                break;
            case 34:   
                decryptedString += '\"';
                break;
            case 35:
                decryptedString += ',';
                break;
            case 36:
                decryptedString += '.';
                break;
            case 37:
                decryptedString += '\'';
                break;
            default:
                break;
        }
    }

    return decryptedString;
}






int main() {
    std::vector<std::vector<int>> input = processInput();
    std::vector<int> publicKey = input[0]; //(e,n)
    std::vector<int> encryptedMessage = input[1];

    int e = publicKey[0];
    int n = publicKey[1];

    //find p and q values of n = pq 
    std::vector<int> pqTuple = findPrimeFactors(n);
    int p = pqTuple[0];
    int q = pqTuple[1];


    //check if the public key is valid
    if (!isPublicKeyValid(e, pqTuple)) {
        std::cout << "Public key is not valid!";
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

    std::vector<int> messageInts = decryptMessageInts(encryptedMessage, inverseD, n);
    std::string messageString = messageToString(messageInts);



    std::cout << p  << " " << q << " " << tN << " " << inverseD << std::endl;

    for(auto& i : messageInts){
        std::cout << i << " ";
    }

    std::cout << std::endl; 

    std::cout << messageString << std::endl;

    


    

    return 0;
}
