#include "database.h"

Database::Database(){
    wchar_t alphabet2[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
                            'r', 's', 't', 'u', 'v', 'y', 'z' };
    /*
    wchar_t alphabet2[] = { 'a', 'b', 'c', 'ç', 'd', 'e', 'f', 'g', 'h', 'ı',
                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'ö', 'p', 'r',
                            's', 'ş', 't', 'u', 'ü', 'v', 'y', 'z' };
    */

    for(int i=0; i<23; i++){
        alphabet[i] = alphabet2[i];
    }

    root = new Node;

    srand(time(NULL));
}

void Database::importDatabase(){
    ifstream file;
    file.open("wordlist.txt");
    cout << "İçe aktarılıyor..." << endl;
    string str;
    while( !file.eof() ){
        getline(file, str);
        
        string sorted = str;
        sort(sorted.begin(), sorted.end());
        
//        cout << str << " " << sorted << endl; 
        //cout << sorted << " ekleniyor." << endl; 
        addToTree(str, sorted, root, 0);
    }
    cout << "İçe aktarma tamamlandı!" << endl;
    file.close();
}

void Database::addToTree(string str, string sorted, Node* iter, int letterPos){ 
    //cout << "addToTree çalıştı." << endl;
    if( !(iter->children.empty()) ){
        //cout << "iter->children boş değil" << endl;
        for( auto child : iter->children ){
            if( child->ch == sorted[letterPos] ){
                //cout << "child->ch node'u iter'in çocuklarında var" << endl;
                if( letterPos+1 == sorted.size() ){
                    //cout << "kelime eklendi" << endl;
                    iter->word = str;
                    return;
                }
                iter = child;
                letterPos++;
                addToTree(str, sorted, iter, letterPos);
                return;
            }
        }
    }

    iter->children.push_back(new Node(sorted[letterPos]));
    //cout << "children.pushback çalıştı: " << sorted[letterPos] << endl;

    iter = iter->children.back();
    if( letterPos+1 == sorted.size() ){
        iter->word = str;
        //cout << "kelime eklendi: " << iter->word << endl << endl;
        return;
    }
    letterPos++;
    addToTree(str, sorted, iter, letterPos);
    return;
}


void Database::pickRandom(Node* iter){
    if( !iter->children.empty() ){
        int num = rand()%iter->children.size();
        iter = iter->children[num];
        pickRandom(iter);
    }else
        randomPick = iter->word;
}

void Database::start(){
    importDatabase();
    pickRandom(root);
    cout << randomPick << endl;
    char ch;
    cin >>ch;
}