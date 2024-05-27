#include "git.h"
#include <fstream>
#include <iostream>

using namespace std;


int Git::hashFunction(string username, int size) const
{
    int totalSum = 0;
    for (int i = 0; i < username.length(); i++)
    {
        totalSum += int(username[i]); 
    }
    int hashValue = totalSum % size;
    while (accounts[hashValue].username != " ")
    {
        hashValue++;
        if (hashValue == size) 
        {
            hashValue = 0;
        }
    }
    return hashValue;
}


bool Git::CheckLogin(string user, string pass)
{
    int count;
    ifstream in;
    in.open("Count.txt");
    in >> count;
    in.close();

    accounts = new Account[count * 2]; // Allocate memory for accounts

    for (int i = 0; i < count * 2; i++)
    {
        accounts[i].username = " ";
    }

    in.open("Users.txt");

    int index;
    string userr, passs;
    for (int i = 0; i < count; i++)
    {
        in >> userr >> passs;
        index = hashFunction(userr, count * 2);
        accounts[index].username = userr;
        accounts[index].password = passs;
    }
    in.close();

    int totalSum = 0;
    for (int i = 0; i < user.length(); i++)
    {
        totalSum += int(user[i]); 
    }
    int hashValue = totalSum % (count * 2);
    while (accounts[hashValue].username != " " && accounts[hashValue].username != user)
    {
        if (hashValue == count * 2) 
        {
            hashValue = 0;
        }
        hashValue++;
    }
    if (accounts[hashValue].username == user && accounts[hashValue].password == pass)
    {
        return true; 
    }
    return false; 
}


bool Account::registerUser(string username, string password)
{
    Repos rp;
    ifstream in;
    in.open("Users.txt");

    string usrr, pss;
    while (in >> usrr >> pss) 
    {
        if (username == usrr)
        {
            in.close();
            return false;
        }
    }
    in.close();

    ofstream out;
    out.open("Users.txt", ios::app);
    out << username << endl << password << endl;
    out.close();

    int count;
    in.open("Count.txt");
    in >> count;
    in.close();

    out.open("Count.txt");
    count++;
    out << count;
    out.close();

    rp.addToRepo(username); 

    return true;
}


void Repos::Tree(string x)
{
    if (x == "load") 
    {
        if (node != nullptr) 
            delete[] node->childs;

        ifstream in("Repositories.txt");
        if (!in.is_open()) {
            cerr << "Error: Unable to open Repositories.txt for loading." << endl;
            return;
        }

        int users, repos, files;
        string str;
        in >> users;
        node = new Node;
        node->childs = new Node[users];
        node->ch = users;

        for (int i = 0; i < users; i++)
        {
            in >> str;
            node->childs[i].data = str;
            in >> repos;
            node->childs[i].childs = new Node[repos];
            node->childs[i].ch = repos;
            for (int j = 0; j < repos; j++)
            {
                in >> str;
                node->childs[i].childs[j].data = str;
                in >> files;
                node->childs[i].childs[j].childs = new Node[files];
                node->childs[i].childs[j].ch = files;
                for (int k = 0; k < files; k++)
                {
                    in >> str;
                    node->childs[i].childs[j].childs[k].data = str;
                }
            }
        }
        in.close();
    }
    else if (x == "unload") // UnLoad Tree
    {
        ofstream out("Repositories.txt");
        if (!out.is_open()) {
            cerr << "Error: Unable to open Repositories.txt for unloading." << endl;
            return;
        }

        out << node->ch << endl;

        for (int i = 0; i < node->ch; i++)
        {
            out << node->childs[i].data << endl;
            out << node->childs[i].ch << endl;
            for (int j = 0; j < node->childs[i].ch; j++)
            {
                out << node->childs[i].childs[j].data << endl;
                out << node->childs[i].childs[j].ch << endl;
                for (int k = 0; k < node->childs[i].childs[j].ch; k++)
                {
                    out << node->childs[i].childs[j].childs[k].data << endl;
                }
            }
        }
    }
}


void Repos::addToRepo(string user)
{

    ofstream out("Repositories.txt", ios::app);
    if (!out.is_open()) {
        cerr << "Error: Unable to open Repositories.txt for adding user." << endl;
        return;
    }

    
    out << endl << user << endl << 0 << endl;
    out.close();

   
    ofstream repoData("repodata.txt", ios::app);
    if (!repoData.is_open()) {
        cerr << "Error: Unable to open repodata.txt for adding repository data." << endl;
        return;
    }


    repoData << "Repository Name: " << user << endl;
    repoData << "Number of Files: 0" << endl;
    repoData.close();
}


bool Repos::Repo(string user, string repoName, string x)
{
    Tree("load");
    if (x == "add")			// Add Repo
    {
        ifstream in("Repositories.txt");
        if (!in.is_open()) {
            cerr << "Error: Unable to open Repositories.txt for adding repository." << endl;
            return false;
        }

        int users, repos, files;
        string str;
        in >> users;
        node = new Node;
        node->childs = new Node[users];
        node->ch = users;

        for (int i = 0; i < users; i++)
        {
            in >> str;
            node->childs[i].data = str;
            in >> repos;
            if (str == user)
            {
                repos++;
            }
            node->childs[i].childs = new Node[repos];
            node->childs[i].ch = repos;
            for (int j = 0; j < repos; j++)
            {
                if (node->childs[i].data == user && j == repos - 1)
                {
                    node->childs[i].childs[j].data = repoName;
                    node->childs[i].childs[j].ch = 0;
                }
                else
                {
                    in >> str;
                    node->childs[i].childs[j].data = str;
                    in >> files;
                    node->childs[i].childs[j].childs = new Node[files];
                    node->childs[i].childs[j].ch = files;
                    for (int k = 0; k < files; k++)
                    {
                        in >> str;
                        node->childs[i].childs[j].childs[k].data = str;
                    }
                }
            }
        }
        in.close();
        Tree("unload");
        return true;
    }
    
    return false;
}

bool Repos::File(string user, string repoName, string fileName, string x)
{
    if (x == "add")
    {
        ifstream in;
        in.open("Repositories.txt");

        int users, repos, files;
        string str;
        in >> users;
        node = new Node;
        node->childs = new Node[users];
        node->ch = users;

        for (int i = 0; i < users; i++)
        {
            in >> str;
            node->childs[i].data = str;
            in >> repos;
            node->childs[i].childs = new Node[repos];
            node->childs[i].ch = repos;
            for (int j = 0; j < repos; j++)
            {
                in >> str;
                node->childs[i].childs[j].data = str;
                in >> files;
                if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName)
                {
                    files++;
                }
                node->childs[i].childs[j].childs = new Node[files];
                node->childs[i].childs[j].ch = files;
                for (int k = 0; k < files; k++)
                {
                    if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && k == files - 1)
                    {
                        node->childs[i].childs[j].childs[k].data = fileName;
                    }
                    else
                    {
                        in >> str;
                        node->childs[i].childs[j].childs[k].data = str;
                    }
                }
            }
        }
        in.close();
        Tree("unload");
    }
    else if (x == "delete")
    {
        Tree("load");

        if (!File(user, repoName, fileName, "search"))
        {
            return false;
        }

        ofstream out;
        out.open("Repositories.txt");

        out << node->ch << endl;
        for (int i = 0; i < node->ch; i++)
        {
            out << node->childs[i].data << endl;
            out << node->childs[i].ch << endl;
            for (int j = 0; j < node->childs[i].ch; j++)
            {
                out << node->childs[i].childs[j].data << endl;
                if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName)
                {
                    out << node->childs[i].childs[j].ch - 1 << endl;
                }
                else
                {
                    out << node->childs[i].childs[j].ch << endl;
                }
                for (int k = 0; k < node->childs[i].childs[j].ch; k++)
                {
                    if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && node->childs[i].childs[j].childs[k].data == fileName)
                    {
                    }
                    else
                    {
                        out << node->childs[i].childs[j].childs[k].data << endl;
                    }
                }
            }
        }
        return true;
    }
    else if (x == "search")
    {
        for (int i = 0; i < node->ch; i++)
        {
            for (int j = 0; j < node->childs[i].ch; j++)
            {
                for (int k = 0; k < node->childs[i].childs[j].ch; k++)
                {
                    if (node->childs[i].data != user || node->childs[i].childs[j].data != repoName)
                    {
                        break;
                    }
                    else if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && node->childs[i].childs[j].childs[k].data == fileName)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}