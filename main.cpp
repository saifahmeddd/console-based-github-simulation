#include "git.h"       
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>

using namespace std;

class Graph {
private:
    static const int MAX_USERS = 1000; 
    vector<vector<int>> adjList;
    vector<int> followerCounts;

public:
    Graph() : adjList(MAX_USERS), followerCounts(MAX_USERS, 0) {}

    void addUser(const string& username) {
     
        int userId = getUserId(username);
        if (userId == -1) {
            cerr << "Error: Maximum number of users reached." << endl;
            return;
        }
    }

    void addFollow(const string& follower, const string& followee) {
       
        int followerId = getUserId(follower);
        int followeeId = getUserId(followee);
        if (followerId != -1 && followeeId != -1) {
            adjList[followerId].push_back(followeeId);
            followerCounts[followeeId]++;
        }
    }

    void removeFollow(const string& follower, const string& followee) {
   
        int followerId = getUserId(follower);
        int followeeId = getUserId(followee);
        if (followerId != -1 && followeeId != -1) {
            auto& followers = adjList[followerId];
            followers.erase(remove(followers.begin(), followers.end(), followeeId), followers.end());
            followerCounts[followeeId]--;
        }
    }

    bool isFollowing(const string& follower, const string& followee) const {
    
        int followerId = getUserId(follower);
        int followeeId = getUserId(followee);
        if (followerId != -1 && followeeId != -1) {
            const auto& followers = adjList[followerId];
            return find(followers.begin(), followers.end(), followeeId) != followers.end();
        }
        return false;

    }

    int getFollowerCount(const string& username) const {

        int userId = getUserId(username);
        if (userId != -1) {
            return followerCounts[userId];
        }
        return 0;
    }

private:
    int getUserId(const string& username) const {
   
        int hashValue = 0;
        for (char ch : username) {
            hashValue = (hashValue * 31 + ch) % MAX_USERS; // Hash function: djb2
        }
        return hashValue;
    }

};

void displaySocialMenu(Graph& socialGraph, const string& currentUser) {
    int choice;
    string followee;

    cout << "\n\n==> SOCIAL MENU <==" << endl;
    cout << "====> 1. FOLLOW USER" << endl;
    cout << "====> 2. UNFOLLOW USER" << endl;
    cout << "====> 3. BACK TO MAIN MENU" << endl;
    cout << "\nEnter choice: ";

    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Enter username to follow: ";
        cin >> followee;
        socialGraph.addFollow(currentUser, followee);
        cout << "You are now following " << followee << endl;
        break;
    case 2:
        cout << "Enter username to unfollow: ";
        cin >> followee;
        socialGraph.removeFollow(currentUser, followee);
        cout << "You have unfollowed " << followee << endl;
        break;
    case 3:
        // Return to main menu
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}



int main() {
    string user, pass, repoName, fileName;
    int val;
    Account account;    // Account Class Variable
    Git git{};          // Git Class Variable
    Repos repos{};      // Repos Class Variable
    bool log = false;
    Graph socialGraph;  // Social Graph Variable


    do {
        system("cls");
        system("color A");
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        string github =
            "\t\t\t" + string(41, '=') + "\n" +
            "\t\t\t" + string(10, ' ') + "   GITHUB SIMULATOR" + string(10, ' ') + "\n" +
            "\t\t\t" + string(41, '=') + "\n";

        cout << github << endl;
        cout << endl;
   
        cout << "                                    developed by: SAIF" << endl;
        cout << endl;
        cout << endl;        cout << endl;

        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
            


        system("pause");
        system("cls");
        system("color A");
        cout << "==> PLEASE SELECT AN OPTION: " << endl << endl;
        cout << "====> 1. New User? Sign up Here." << endl;
        cout << "====> 2. Already have an account? Login Here!" << endl;
        cout << "====> 3. EXIT" << endl;


        cout << "\nEnter:   ";
        cin >> val;

        if (val == 1) {
            system("pause");
            system("cls");
            system("color B");
            cout << endl << endl;
            cout<< "Enter Username: ";
            cin >> user;
            cin.ignore(); // Clear input buffer
            cout << endl << endl << "Enter Password: ";
            cin >> pass;
            cin.ignore(); // Clear input buffer
            cout << endl;
            if (account.registerUser(user, pass)) {
                cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                cout << "\t\t\t\t      !!--SUCCESSFULLY SIGNEDUP--!!" << endl;
                cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
            }
            else {
                cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                cout << "\t\t\t\t         !!--INVALID USERNAME--!!" << endl;
                cout << "\t\t\t\t<-------------------------------------------->" << endl << endl;
            }
            system("pause");
        }
        else if (val == 2) {
            system("pause");
            system("cls");
            system("color B");
            cout << endl << endl << "--> Enter Username :  ";
            cin >> user;
            cout << endl;
            cin.ignore(); // Clear input buffer
            cout << endl << endl << "--> Enter Password : ";
            cin >> pass;
            cin.ignore(); // Clear input buffer
            cout << endl;
            log = git.CheckLogin(user, pass);
            if (log) {
                cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                cout << "\t\t\t\t       !!--SUCCESSFULLY SIGNEDIN--!!" << endl;
                cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
            }
            else {
                cout << "\t\t\t\<---------------------------------------->" << endl;
                cout << "\t\t\t\t !!--INVALID USERNAME/PASSWORD--!!" << endl;
                cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
            }
            system("pause");
        }
        if (log) {
            int val2;
            do {
                system("cls");
                cout << "\t\t\t\t<---------------------------------------->" << endl;
                cout << "\t\t\t\t\t   --GITHUB SIMULATOR--   " << endl;
                cout << "\t\t\t\t<---------------------------------------->" << endl << endl << endl << endl;
                cout << "\n\n==> PLEASE SELECT AN OPTION:" << endl << endl;
                cout << "====> 1. CREATE REPOSITORY" << endl;
                cout << "====> 2. REMOVE REPOSITORY" << endl;
                cout << "====> 3. CREATE FILE IN REPOSITORY" << endl;
                cout << "====> 4. REMOVE FILE FROM REPOSITORY" << endl;
                cout << "====> 5. SEARCH A REPOSITORY" << endl;
                cout << "====> 6. SEARCH A FILE IN REPOSITORY" << endl;
                cout << "====> 7. COMMIT IN REPOSITORY" << endl;
                cout << "====> 8. SOCIAL MENU" << endl; 
                cout << "====> 9. LOGOUT" << endl;      
                cout << "\nEnter: ";

                cin >> val2;
                cout << endl << endl;
                system("pause");
                system("cls");
                cout << "\t\t\t\t<---------------------------------------->" << endl;
                cout << "\t\t\t\t\t\t --GITHUB SIMULATION--" << endl;
                cout << "\t\t\t\t<---------------------------------------->" << endl << endl << endl << endl;
                
                if (val2 != 8) {
                    cout << "==> Enter Repo Name:\n====> ";
                    cin >> repoName;
                }

                if (val2 == 1) {
                    repos.Repo(user, repoName, "add");
                    cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                    cout << "\t\t\t\t       !!--REPOSITORY ADDED--!!" << endl;
                    cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
                }
                else if (val2 == 2) {
                    if (repos.Repo(user, repoName, "delete")) {
                        cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                        cout << "\t\t\t\t\t\t\t !!--REPOSITORY DELETED--!!" << endl;
                        cout << "\t\t\t\t\t\t<---------------------------------------->" << endl << endl;
                    }
                    else
                    {
                        cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                        cout << "\t\t\t\t !!--REPOSITORY NOT DELETED--!!" << endl;
                        cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
                    }
                }
                else if (val2 == 3)
                {
                    cout << endl << endl << "==> Enter File Name:\n====> ";
                    cin >> fileName;
                    repos.File(user, repoName, fileName, "add");
                    cout << "\n\n\t\t\t\t<---------------------------------------->" << endl;
                    cout << "\t\t\t\t !!--FILE ADDED--!!" << endl;
                    cout << "\t\t\t\t<---------------------------------------->" << endl << endl;
                }
                else if (val2 == 4)
                {
                    cout << endl << endl << "==> Enter File Name:\n====> ";
                    cin >> fileName;
                    if (repos.File(user, repoName, fileName, "delete"))
                    {
                        cout << "\n\n\t\t\t\t<=====================>" << endl;
                        cout << "\t\t\t\t !!--FILE DELETED--!!" << endl;
                        cout << "\t\t\t\t<=====================>" << endl << endl;
                    }
                    else
                    {
                        cout << "\n\n\t\t\t\t<=====================>" << endl;
                        cout << "\t\t\t\t !!--FILE NOT DELETED--!!" << endl;
                        cout << "\t\t\t\t<=====================>" << endl << endl;
                    }
                }
                else if (val2 == 5)
                {
                    if (!repos.Repo(" ", repoName, "searchRepoDetails"))
                    {
                        cout << "\n\n\t\t\t\<=====================>" << endl;
                            cout << "\t\t\t\t !!--REPOSITORY NOT FOUND--!!" << endl;
                        cout << "\t\t\t\t<=====================>" << endl << endl;
                    }
                }
                else if (val2 == 6)
                {
                    cout << endl << endl << "==> Enter File Name:\n====> ";
                    cin >> fileName;
                    if (!repos.File(" ", repoName, fileName, "searchRepoDetails"))
                    {
                        cout << "\n\n\t\t\t\t<=====================>" << endl;
                        cout << "\t\t\t\t !!--File NOT FOUND--!!" << endl;
                        cout << "\t\t\t\t<=====================>" << endl << endl;
                    }
                    else
                    {
                        cout << "\n\n\t\t\t\t<=====================>" << endl;
                        cout << "\t\t\t\t !!--File FOUND--!!" << endl;
                        cout << "\t\t\t\t<=====================>" << endl << endl;
                    }
                }
                else if (val2 == 7)
                {
                    repos.Repo(" ", repoName, "commit");
                    cout << "\n\n\t\t\t\t<=====================>" << endl;
                    cout << "\t\t\t\t !!--REPOSITORY COMMITED--!!" << endl;
                    cout << "\t\t\t\t<=====================>" << endl << endl;
                }
                else if (val2 == 8)
                {
                    displaySocialMenu(socialGraph, user);
                }
                cout << endl;
                system("pause");
            } while (val2!=9);
        }
    } while (val != 3);

    system("pause");
    return 0;
}