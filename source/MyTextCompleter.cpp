#include "MyTextCompleter.hpp"
#include <fstream>

MyTextCompleter::MyTextCompleter(std::string path) {
    std::ifstream fin(path.c_str());
    std::string str;

    if (fin.is_open()) {
        while (fin >> str) {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            std::string result;
            for (std::string::size_type i = 0; i < str.size(); i++) {
                char ch = str.at(i);
                // std::string::erase() not working for index 0
                if (ch >= 'a' && ch <= 'z') {
                    result += ch;
                }
            }
            if (result.size() > 3) _trie.insert(result);
            str.clear();
        }
    }
    fin.close();
}

MyTextCompleter::~MyTextCompleter() {}

void MyTextCompleter::GetCompletions(const wxString& prefix,
        wxArrayString &result) {
    std::vector<std::string> suggestions =
            _trie.getSuggestions(prefix.ToStdString());
    for (std::size_t i = 0; i < suggestions.size(); i++) {
        result.Add(suggestions.at(i));
    }
}