#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isLowercase(char c) {
    return c >= 'a' && c <= 'z';
}

bool isUppercase(char c) {
    return c >= 'A' && c <= 'Z';
}

int main() {
    ifstream inputFile("hasla.txt");
    ofstream outputFile("wyniki_hasla.txt");
    
    string password;
    unordered_set<string> passwordsSet;
    unordered_set<string> duplicatePasswords;
    unordered_set<string> passwordsWithFourCharsASCII;
    int passwordsWithDigitsCount = 0;
    int complexPasswordsCount = 0;

    while (getline(inputFile, password)) {
        bool onlyDigits = all_of(password.begin(), password.end(), isDigit);
        if (onlyDigits)
            passwordsWithDigitsCount++;

        if (!passwordsSet.insert(password).second)
            duplicatePasswords.insert(password);

        for (size_t i = 0; i <= password.size() - 4; ++i) {
            string sub = password.substr(i, 4);
            if (all_of(sub.begin(), sub.end(), [](char c) { return isalnum(c); }))
                passwordsWithFourCharsASCII.insert(sub);
        }

        if (any_of(password.begin(), password.end(), isDigit) &&
            any_of(password.begin(), password.end(), isLowercase) &&
            any_of(password.begin(), password.end(), isUppercase))
            complexPasswordsCount++;
    }

    outputFile << "74.1. " << passwordsWithDigitsCount << endl;

    outputFile << "74.2. ";
    for (const auto &pw : duplicatePasswords)
        outputFile << pw << endl;

    outputFile << "74.3. " << passwordsWithFourCharsASCII.size() << endl;

    outputFile << "74.4. " << complexPasswordsCount << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
