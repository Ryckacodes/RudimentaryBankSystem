#include "transfer.h"
#include <iostream>
#include <fstream>
#include <string>

void transferFunds(const std::string& senderFilename, const std::string& recipientUsername, double amount) {
    std::string recipientFilename = recipientUsername + "_Account.txt";

    // Open sender's file to read balance
    std::ifstream senderFile(senderFilename);
    if (!senderFile) {
        std::cerr << "Sender account file not found." << std::endl;
        return;
    }

    // Read sender's current balance
    std::string line, senderBalanceStr;
    double senderBalance = 0.0;
    while (std::getline(senderFile, line)) {
        if (line.find("Balance: ") != std::string::npos) {
            senderBalanceStr = line.substr(9);  // Skip "Balance: "
            senderBalance = std::stod(senderBalanceStr.substr(0, senderBalanceStr.size() - 1)); // Remove "$" sign
            break;
        }
    }
    senderFile.close();

    // Check if sender has enough balance
    if (senderBalance < amount) {
        std::cerr << "Insufficient balance for transfer." << std::endl;
        return;
    }

    // Open recipient's file to read balance
    std::ifstream recipientFile(recipientFilename);
    if (!recipientFile) {
        std::cerr << "Recipient account not found." << std::endl;
        return;
    }

    // Read recipient's current balance
    std::string recipientBalanceStr;
    double recipientBalance = 0.0;
    while (std::getline(recipientFile, line)) {
        if (line.find("Balance: ") != std::string::npos) {
            recipientBalanceStr = line.substr(9);
            recipientBalance = std::stod(recipientBalanceStr.substr(0, recipientBalanceStr.size() - 1));
            break;
        }
    }
    recipientFile.close();

    // Update balances after transfer
    senderBalance -= amount;
    recipientBalance += amount;

    // Update sender's file
    std::ofstream senderOutFile(senderFilename, std::ios::trunc);
    senderOutFile << "Username: " << senderFilename.substr(0, senderFilename.find("_Account.txt")) << std::endl;
    senderOutFile << "Password: " << "ENCRYPTED_PASSWORD" << std::endl; // Replace with actual password handling
    senderOutFile << "Balance: " << senderBalance << "$" << std::endl;
    senderOutFile.close();

    // Update recipient's file
    std::ofstream recipientOutFile(recipientFilename, std::ios::trunc);
    recipientOutFile << "Username: " << recipientUsername << std::endl;
    recipientOutFile << "Password: " << "ENCRYPTED_PASSWORD" << std::endl; // Replace with actual password handling
    recipientOutFile << "Balance: " << recipientBalance << "$" << std::endl;
    recipientOutFile.close();

    std::cout << "Transfer of " << amount << "$ to " << recipientUsername << " was successful!" << std::endl;
}