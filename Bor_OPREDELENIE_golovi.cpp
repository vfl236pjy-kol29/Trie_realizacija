#include <iostream>
#include "Bor_golova.h"
#include<vector>
#include <string>
using namespace std;

struct Node
{
    Node* links[26]; bool flag = false;

    int path;//количество повторений символа в использовании подсчёта количества строк с префиксом символьной строки
    int End;//строка или префикс, заканчивающаяся данным символом
    string Controlword;//контрольное слово для подсчёта конкретного введённого слова или префикса
    Node()
    {
        Node* node = new Node;
        node->isEnd();
        for (int i = 0; i < 26; i++)
        {
            node->links[i] = nullptr;
        }
        int path = 0;  int End = 0;
        Controlword = " ";
    }


    bool  containsKey(char ch)
    {
        return links[ch - 'a'];
        //if(links[ch-'a']) return true;
    }

    Node* get(char ch)
    {
        return links[ch - 'a'];
    }

    void put(char ch, Node* node)
    {
        links[ch - 'a'] = node;
    }

    void setEnd()
    {
        flag = true;
    }

    bool isEnd()
    {
        return flag;
    }

};

class Trie
{
private:
    Node* root;
public:
    Trie() { root = new Node(); }


    bool isEmpty(Node* root)
    {
        for (int i = 0; i < 26; i++)
            if (root->links[i])
                return false;
        return true;
    }

    void  insert(string word)
    {
        if (word == " ")
            return;
        Node* node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();//установка логического утверждения окончания введённого слова или префикса
        node->path++;//через этот узел есть путь. переменная нужна для подсчёта таковых путей
        node->End++;//подсчёт количества именно конкретного введённого слова, т.е. строки или префикса, заканчивающаяся данным символом
        node->Controlword = word;
    }

    int search(string word)//поиск количества вхождений данного слова
    {
        if (word == " ")
            return;
        Node* node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();//установка логического утверждения окончания введённого слова или префикса
        node->path++;//через этот узел есть путь. переменная нужна для подсчёта таковых путей
        node->End++;//подсчёт количества именно конкретного введённого слова, т.е. строки или префикса, заканчивающаяся данным символом
        node->Controlword = word;
        if (node != nullptr)
        {
            return node->End;
        }
        else return 0;
    }

    void Delete(string word)// метод удаления слова целиком
    {
        if (word == "")
            return;
        Node* node = root;
        Node* tmp;
        for (int i = 0; i < word.length(); i++)
        {
            
            tmp = node->get(word[i]);
            if (--node->get(word[i])->path == 0)
            {
                delete node->get(word[i]);
            }
            node = tmp;
        }
        node->End--;
    }

    Node* remove(Node* root, string key, int depth = 0)// удаление ключа из дерева
    {
        if (!root)
            return nullptr;
        if (depth == key.length())
                     {
                        if (root->isEnd()) { root->flag= false; }
                        if (isEmpty(root)) { delete(root); root = nullptr; }
                        return root;
                     }
         remove(root->get(key[depth]), key, depth + 1);
         if (isEmpty(root) && root->isEnd() == false) { delete(root); root = nullptr; }
         return root;
    }

    void Print(Node* node)//печать отдельного узла
    {
        if (node == nullptr)
            return;
        if (node->Controlword != "")
        {
            cout << node->Controlword << " " << node->path << endl;
        }
        for (int i = 0; i < 26; i++)
        {
            Print(node->links[i]);
        }
    }

    void printPre(string Prefix)//печать префикса или слова целиком
    {
        if (Prefix== "")
            return;
        Node* node = root;
        for (int i = 0; i < Prefix.length(); i++)
        {
            if (node->get(Prefix[i]) == nullptr)
            {
                return ;
            }
            node->get(Prefix[i]);
        }
        Print(node);
    }

    void printAll()
    {
        Print(root);
    }


    bool checkIfPrefixExist(string Prefix)
    {
        bool fl = true;  Node* node = root; int i;
        for (int i = 0; i < Prefix.length(); i++)
        {
            if (node->containsKey(Prefix[i]))
            {
                node = node->get(Prefix[i]);
                if (node->isEnd() == false) return false;
            }
            return false;
        }
        return true;
    }

    /*string CompleteString(vector<string>& a)
    {
        Trie trie;
        for (auto& it : a) { trie.insert(it); }
        string longest = "";
        for (auto& it : a)
        {
            if (bool checkIfPrefixExist(string Prefix))
            {
                if (it.length() > longest.length()) { longest = it; }
                else if (it.length() == longest.length() && it < longest) { longest = it; }
            }
        }
        if (longest == "") return "None";
        return longest;
    }*/

};



 