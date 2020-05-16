#ifndef MY_TEXT_COMPLETER_H
#define MY_TEXT_COMPLETER_H

#include "yoku/Trie.hpp"
#include <wx/wx.h>
#include <wx/textcompleter.h>
#include <string>

class MyTextCompleter: public wxTextCompleterSimple  {
    private:
        yoku::Trie _trie;

    public:
        MyTextCompleter(std::string path);
        virtual ~MyTextCompleter();
        virtual void GetCompletions(const wxString& prefix, wxArrayString& result) override;
};

#endif // MY_TEXT_COMPLETER_H