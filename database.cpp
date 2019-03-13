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
    // karaliste
    // 
    // mümkün harfler
    // abn, abr, anr, bnr, ooo 0
    //
    // baban
    // 4
    //
    // abnor arobono       // bilgisayar
    // 11111
    // abn, ooo, abr, bnr, aoo, boo, noo, roo, aob, aon, aor, bon, bor, nor 
    // 
    // abklo   kolba         // insan
    // 
    // kullancı bilgisayarın tuttuğu kelimedeki harf sayısına puan verecek 5 puan
    // sadece ooo verdiğimizde ab ve r harflerinin olmadığı kelimeleri de seçecek
    // Sorulacak sorular: 3 5
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
    }else
        randomPick = iter->word.back();
}

void Database::start(){
    importDatabase();
    pickRandom(root);
    cout << randomPick << endl;
    char ch;
    cin >>ch;
}

void Database::narrow( int canbe, int pos, string newStr ){
    for(int i=pos; i<str.size(); i++){
        narrow(canbe, ++pos, newStr);
        if( canbe - values[i] >= 0 ){
            newStr.push_back(str[i]);
            canbe -= values[i];
        }
        if( canbe == 0){
            for(auto str : allStr) if( str == newStr ) return;
            allStr.push_back(newStr);
        }
        cout << newStr << endl;
    }
}

void Database::printAllStr(){
    cout << endl << "all str : " << endl;
    for(auto str : allStr)
        cout << str << endl;
}