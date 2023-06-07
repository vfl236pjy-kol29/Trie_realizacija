#pragma once
#include <iostream>

#include<vector>
#include <string>
using namespace std;

struct Node
{
    Node* links[26]; bool flag = false; int path=0; int End=0; string Controlword;
    Node() {};
        bool containsKey(char ch);
        Node* get(char ch);
        void put(char ch, Node* node);
        void setEnd();
        bool isEnd();
};

class Trie
{
            private:
                        Node* root;
            public:
                Trie() {};
                        bool isEmpty(Node* root);

                        void insert(string word);
                        int search(string word);

                        bool checkIfPrefixExist(string Prefix);
                        string CompleteString( vector<string>& a);

                        void printPre(string Prefix);
                        void Print(Node* node);
                        void printAll();

                        void Delete(string word);
                        Node* remove(Node* root, string key, int depth = 0);

};






