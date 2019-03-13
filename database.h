#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

struct Node{
    char ch; 
    vector<string> word;
    vector<Node*> children;
    Node(){ word.clear(); }
    Node(char c){ ch = c; word.clear(); }
};

class Database{
public:
    Node* root;
    Database();
    void start();
    void importDatabase();
    void addToTree(string str, string sorted, Node* iter, int letterPos);
    void pickRandom(Node* iter);
    void narrow(int canbe, int pos, string newStr);
    void printAllStr();
private:
    string randomPick;
    wchar_t alphabet[23];

    string str = "abnor"; 
    vector<int> values = {1,1,1,3,1};
    vector<string> allStr;
};