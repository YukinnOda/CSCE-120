# include "functions.h"
// add any includes

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    cout << "Please enter obfuscated sentence: ";
    string s = "";
    cin >> s;
    cout << "Please enter deobfuscation details: ";
    int word_len;
    cin >> word_len;
    int len_store = word_len % 10;
    int count = 0;
    while(word_len != 0) {
        s.insert(s.size() - (len_store + count), " ");
        count += len_store + 1;
        word_len = word_len / 10;
        len_store = word_len % 10;
    }
    cout << "Deobfuscated sentence:";
    int s_size = s.size();
    for(int i = 0; i < s_size; i++) {
        cout << s.at(i);
    }
    cout << endl;
}

void wordFilter() {
    cout << "Please enter the sentence: ";
    string s = "";
    getline(cin, s);
    cout << "Please enter the filter word: ";
    string filter = "";
    cin >> filter;
    int s_size = s.size();
    int f_size = filter.size();
    for(int i = 0; i < s_size - f_size; i++) {
        string store = s.substr(i, f_size);
        if(store == filter) {
            for(int r = 0; r < f_size; r++) {
                s.replace(i + r, 1, "#");
            }
        }
    }
    cout << "Filtered sentence: " << s << endl;
}

void passwordConverter() {
    // TODO
}

void wordCalculator() {
    // TODO
}

void palindromeCounter() {
    // TODO
}