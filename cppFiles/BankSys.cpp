#include "transfer.h"
#include <iostream>
#include <fstream>
#include <string>

// Encrypt and decrypt functions
std::string encryptPassword(const std::string& password) {
    std::string encryptedPassword;
    for (size_t i = 0; i < password.length(); i++) {
        encryptedPassword += password[i] + 7;
    }
    return encryptedPassword;
}

std::string decryptPassword(const std::string& encryptedPassword) {
    std::string decryptedPassword;
    for (size_t i = 0; i < encryptedPassword.length(); i++) {
        decryptedPassword += encryptedPassword[i] - 7;
    }
    return decryptedPassword;
}

int main() {
    std::string choice, username, password, inputUsername, inputPassword;

    std::cout << "Do you want to register, login, or delete an account? \n";
    std::cin >> choice;

    if (choice == "Register" || choice == "register") {
        std::cout << "Please enter your desired Username: \n";
        std::cin >> username;
        std::string filename = "txtFiles/" + username + "_Account.txt";
        std::ofstream userFile(filename);

        if (!userFile) {
            std::cerr << "Error creating file." << std::endl;
            return 1;
        }

        std::cout << "Please enter your desired Password: \n";
        std::cin >> password;
        std::string encryptedPassword = encryptPassword(password);

        userFile << "Username: " << username << std::endl;
        userFile << "Password: " << encryptedPassword << std::endl;
        userFile << "Balance: " << "1000$" << std::endl;
        userFile.close();

        std::cout << "Registration successful!" << std::endl;
    } 
    else if (choice == "Login" || choice == "login") {
        std::cout << "Please enter your Username: \n";
        std::cin >> inputUsername;
        std::string filename = inputUsername + "_Account.txt";
        std::ifstream userFile(filename);

        if (!userFile) {
            std::cerr << "Account not found." << std::endl;
            return 1;
        }

        std::string fileUsername, filePassword;
        userFile >> fileUsername >> fileUsername;
        userFile >> filePassword >> filePassword;
        userFile.close();

        std::cout << "Please enter your Password: \n";
        std::cin >> inputPassword;

        if (decryptPassword(filePassword) == inputPassword) {
            std::cout << "Login successful!" << std::endl;
            std::cout << "Choose an option:\n1. View account details\n2. Manage transfers\n";
            int option;
            std::cin >> option;

            if (option == 1) {
                userFile.open(filename);
                std::string line;
                while (std::getline(userFile, line)) {
                    std::cout << line << std::endl;
                }
                userFile.close();
            } else if (option == 2) {
                std::string recipientUsername;
                double amount;
                std::cout << "Enter recipient's username: ";
                std::cin >> recipientUsername;
                std::cout << "Enter amount to transfer: ";
                std::cin >> amount;

                transferFunds(filename, recipientUsername, amount);
            } else {
                std::cout << "Invalid option." << std::endl;
            }
        } else {
            std::cerr << "Wrong username or password!" << std::endl;
        }
    }
    else if (choice == "Delete" || choice == "delete") {
        std::cout << "Please enter your Username: \n";
        std::cin >> inputUsername;
        std::string filename = inputUsername + "_Account.txt";
        std::ifstream userFile(filename);

        if (!userFile) {
            std::cerr << "Account not found." << std::endl;
            return 1;
        }

        std::string fileUsername, filePassword;
        userFile >> fileUsername >> fileUsername;
        userFile >> filePassword >> filePassword;
        userFile.close();

        std::cout << "Please enter your Password to confirm deletion: \n";
        std::cin >> inputPassword;

        if (decryptPassword(filePassword) == inputPassword) {
            if (std::remove(filename.c_str()) == 0) {
                std::cout << "Account deleted successfully." << std::endl;
            } else {
                std::cerr << "Error deleting account." << std::endl;
            }
        } else {
            std::cerr << "Incorrect password. Deletion failed." << std::endl;
        }
    }
    else {
        std::cerr << "Invalid option." << std::endl;
    }

    return 0;
}