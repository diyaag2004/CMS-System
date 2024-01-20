#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

class User
{
public:
    std::string username;
    std::string password;
    int age;

    User(const std::string &uname, const std::string &pwd, int a) : username(uname), password(pwd), age(a) {}
};

class AuthenticationSystem
{
private:
    std::vector<User> users;
    const std::string filename = "user_data.txt";

public:
    AuthenticationSystem()
    {
        loadUsersFromFile();
    }

    ~AuthenticationSystem()
    {
        saveUsersToFile();
    }

    void showMenu()
    {
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Change Password\n";
        std::cout << "4. Change Age\n";
        std::cout << "5. Delete Account\n";
        std::cout << "6. Display Users\n";
        std::cout << "7. Quit\n";
    }

    void processUserChoice()
    {
        int choice;
        do
        {
            showMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                handleRegistration();
                break;
            case 2:
                handleLogin();
                break;
            case 3:
                handleChangePassword();
                break;
            case 4:
                handleChangeAge();
                break;
            case 5:
                handleDeleteAccount();
                break;
            case 6:
                displayUsers();
                break;
            case 7:
                std::cout << "Goodbye!\n\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n\n";
            }
        } while (choice != 7);
    }

private:
    void handleRegistration()
    {
        std::string username, password;
        int age;

        std::cout << "Enter your desired username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;
        std::cout << "Enter your age: ";
        std::cin >> age;

        registerUser(username, password, age);
    }

    void handleLogin()
    {
        std::string username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        loginUser(username, password);
    }

    void handleChangePassword()
    {
        std::string username, oldPassword, newPassword;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your old password: ";
        std::cin >> oldPassword;

        auto it = findUser(username, oldPassword);

        if (it != users.end())
        {
            std::cout << "Enter your new password: ";
            std::cin >> newPassword;
            it->password = newPassword;
            std::cout << "Password changed successfully!\n\n";
        }
    }

    void handleChangeAge()
    {
        std::string username, password;
        int newAge;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        auto it = findUser(username, password);

        if (it != users.end())
        {
            std::cout << "Enter your new age: ";
            std::cin >> newAge;
            it->age = newAge;
            std::cout << "Age changed successfully!\n\n";
        }
    }

    void handleDeleteAccount()
    {
        std::string username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        auto it = findUser(username, password);

        if (it != users.end())
        {
            users.erase(it);
            std::cout << "Account deleted successfully!\n\n";
        }
    }

    void registerUser(const std::string &username, const std::string &password, int age)
    {
        if (findUser(username) != users.end())
        {
            std::cout << "Username already taken. Please choose a different one.\n\n";
            return;
        }

        users.emplace_back(username, password, age);
        std::cout << "Registration successful!\n\n";
    }

    void loginUser(const std::string &username, const std::string &password)
    {
        auto it = findUser(username, password);

        if (it != users.end())
        {
            std::cout << "Login successful!\n";
            std::cout << "Welcome, " << it->username << "!\n";
            std::cout << "Age: " << it->age << "\n\n";
        }
        else
        {
            std::cout << "Invalid username or password. Please try again.\n\n";
        }
    }

    std::vector<User>::iterator findUser(const std::string &username)
    {
        return std::find_if(users.begin(), users.end(), [&username](const User &user)
                            { return user.username == username; });
    }

    std::vector<User>::iterator findUser(const std::string &username, const std::string &password)
    {
        return std::find_if(users.begin(), users.end(), [&username, &password](const User &user)
                            { return user.username == username && user.password == password; });
    }

    void displayUsers()
    {
        std::cout << std::setw(15) << "Username" << std::setw(15) << "Age" << "\n";
        std::cout << "----------------------------------\n";
        for (const auto &user : users)
        {
            std::cout << std::setw(15) << user.username << std::setw(15) << user.age << "\n";
        }
        std::cout << "\n";
    }

    void loadUsersFromFile()
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string username, password;
        int age;
        while (file >> username >> password >> age)
        {
            users.emplace_back(username, password, age);
        }

        file.close();
    }

    void saveUsersToFile()
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        for (const auto &user : users)
        {
            file << user.username << " " << user.password << " " << user.age << std::endl;
        }

        file.close();
    }
};

int main()
{
    AuthenticationSystem authSystem;
    authSystem.processUserChoice();

    return 0;
}

