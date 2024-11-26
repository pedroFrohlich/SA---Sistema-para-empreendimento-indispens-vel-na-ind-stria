#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class User {
public:
  bool active = true;
  std::string name;
  std::string email;
  std::string password;

  User(std::string name, std::string email, std::string password) {
    this->name = name;
    this->email = email;
    this->password = password;
  }
  ~User() = default;

  void displayUser() const {
    std::cout << "Name: " << name << "\nEmail:" << email << "\nActive:" << (active ? "Yes" : "No") << std::endl;
  }

  void editUser() {
    std::string newName, newEmail, newPassword;
    std::cout << "Actual name: " << name << "\nNew name:\n";
    std::cin >> newName;

    std::cout << "Actual email: " << email << "\nNew email:\n";
    std::cin >> newEmail;

    std::cout << "Actual password: " << password << "\nNew password:\n";
    std::cin >> newPassword;

    name = newName;
    email = newEmail;
    password = newPassword;
  }

  void saveToFile(std::ofstream& outFile) const {
    outFile << name << "\n" << email << "\n" << password << "\n" << active << "\n*********************************\n";
  }
};

std::vector<User> users = {};

void saveUserToFile(const User& user) {
  std::ofstream outFile("teste.txt", std::ios::app);
    if (outFile.is_open()) {
      user.saveToFile(outFile);
      outFile.close();
    } else {
      std::cerr << "Unable to open file to save user data.\n";
    }
}

void addUser() {
  std::string name, email, password;

  std::cout << "Name:\n";
  std::cin >> name;

  std::cout << "Email:\n";
  std::cin >> email;

  std::cout << "Password:\n";
  std::cin >> password;

  User newUser(name, email, password);
  users.push_back(newUser);
  saveUserToFile(newUser);
}

void listUsers() {
  for(const auto& user : users) {
    user.displayUser();
    std::cout << "\n***************************************\n";
  }
}

void editUser() {
  std::string email;
  std::cout << "Email:\n";
  std::cin >> email;

  for (auto& user : users) {
    if (user.email == email) {
      user.editUser();
      std::ofstream outFile("teste.txt");
      if (outFile.is_open()) {
        for (const auto& usr : users) {
          usr.saveToFile(outFile);
        }
        outFile.close();
      } else {
        std::cerr << "Unable to open file to update user data.\n";
      }
      break;
    }
  }
}

void deactivateUser() {
  std::string email;
  std::cout << "Email:\n";
  std::cin >> email;

  for (auto& user : users) {
    if (user.email == email) {
      user.active = false;
      std::ofstream outFile("teste.txt");
      if (outFile.is_open()) {
        for (const auto& usr : users) {
          usr.saveToFile(outFile);
        }
        outFile.close();
      } else {
        std::cerr << "Unable to open file to update user data.\n";
      }
      break;
    }
  }
}

int main(int argc, char** argv) {
  int x = 0;
  do {
    std::cout << "Select the desired operation:\n1. Add new user.\n2. List users.\n3. Edit user.\n4. Deactivate user.\n5. Exit\n";
    std::cin >> x;

    switch(x) {
    case 1:
      addUser();
      break;
    case 2:
      listUsers();
      break;
    case 3:
      editUser();
      break;
    case 4:
      deactivateUser();
      break;
    case 5:
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Operation not listed.\n";
      break;
    }
  } while (x != 5);
  return 0;
}
