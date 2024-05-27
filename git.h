#pragma once
#ifndef GIT_H
#define GIT_H

#include<iostream>
#include<string>

using namespace std;

class Account
{
private:
	string username, password;
	static int totalAccounts;
	friend class Git;
public:
	bool registerUser(string username, string password); 
};


class Git
{
private:
	Account* accounts;
	int hashFunction(string username, int size) const;
public:
	bool CheckLogin(string user, string pass);
};


class Node
{
public:
	string data;
	int ch;
	Node* childs;
	int comits;
	Node() : comits(0), childs(nullptr) {} 
};



class Repos
{
private:
	Node* node;
	void Tree(string x);  
public:
	void addToRepo(string user);
	bool Repo(string user, string repoName, string x); 
	bool File(string user, string repoName, string fileName, string x);	
};

#endif
