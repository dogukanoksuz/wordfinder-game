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
                    // TODO: üzerine yazma işlemini kontrol et
                    //cout << "kelime eklendi" << endl;
                    iter->word.push_back(str);
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
        iter->word.push_back(str);
        //cout << "kelime eklendi: " << iter->word << endl << endl;
        return;
    }
    letterPos++;
    addToTree(str, sorted, iter, letterPos);
    return;
}

// Sözlükten rastgele bir kelime seçer
void Database::pickRandom(Node* iter){
    if( !iter->children.empty() ){
        int num = rand()%iter->children.size();
        iter = iter->children[num];
        pickRandom(iter);
    }else{
        randomPick = iter->word.back();
        auto tempStr = randomPick;
        sort(tempStr.begin(), tempStr.end());
        for( auto ch1 : tempStr ){
            bool check = true;  // kelimede bu harf var mı kontrolü
            for( auto ch2 : randomPickSorted ){
                if( ch1 == ch2 )
                    check = false;
            }
            if( check )
                randomPickSorted.push_back(ch1);
        }
    
        values.resize(randomPickSorted.size());

        int i=0;
        int counter = 0;
        for( auto ch1 : randomPickSorted ){
            for( auto ch2 : tempStr ){
                if( ch1 == ch2 ){
                    counter++;
                }
            }
            values[i] = counter;
            counter = 0;
            i++;
        }
    }
}

void Database::start(){
    importDatabase();
    pickRandom(root);
    cout << randomPick << endl;
    cout << randomPickSorted << endl;
    for(auto val : values)
        cout << val;
    cout << endl << "Score : ";
    int score;
    cin >> score;

    setSubsets(score, 0, "");
}

void Database::setSubsets( int score, int pos = 0, string newStr = "" ){
    for(int i=pos; i<randomPickSorted.size(); i++){
        setSubsets(score, ++pos, newStr);
        if( score - values[i] >= 0 ){
            newStr.push_back(randomPickSorted[i]);
            score -= values[i];
        }
        if( score == 0){
            for(auto str : possibleLetters) if( str == newStr ) return;
            possibleLetters.push_back(newStr);
        }
    }
}

void Database::printAllStr(){
    cout << endl << "all str : " << endl;
    for(auto str : possibleLetters)
        cout << str << endl;
}