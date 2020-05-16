#include "MyGui.hpp"
#include "MyTextCompleter.hpp"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <fstream>
#include <sstream>
#include <algorithm>

// event table
wxBEGIN_EVENT_TABLE(MyGui, wxFrame)
	EVT_MENU(wxID_EXIT, onExit)
	EVT_MENU(wxID_OPEN, onOpenFile)
    EVT_SEARCH(_ID_SEARCH_CTRL, onSearch)
    EVT_BUTTON(_ID_BTN_PRE, onClickToPrevious)
    EVT_BUTTON(_ID_BTN_NEXT, onClickToNext)
wxEND_EVENT_TABLE()

const std::string MyGui::_SEARCH_CAPTION_DEFAULT = "No Results";

void MyGui::_initSearch() {
    std::string term = _searchCtrl->GetValue().ToStdString();
    std::transform(term.begin(), term.end(), term.begin(), ::tolower);
    yoku::IndexNode* node = _htable.find(term);
    _lookupIndex = 0;
    if (node != NULL) {
        _lookupNode = node; // no need to delete bcz of yoku::~HashTable()
        std::vector<std::size_t> vec = _lookupNode->getPositionVector();
        _textCtrl->SetFocus();
        std::size_t position = vec.at(_lookupIndex);
        _textCtrl->ShowPosition(position);
        _textCtrl->SetSelection(position, position + term.length());
        std::ostringstream label;
        label << _lookupIndex + 1 << " of " << vec.size();
        _searchCaption->SetLabelText(label.str());
    }
    else {
        _searchCaption->SetLabelText(_SEARCH_CAPTION_DEFAULT);
        _lookupNode = NULL;
    }
}

MyGui::MyGui(const char *title, int width, int height)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height)),
    _lookupIndex(0),
    _lookupNode(NULL) {

    _file = new wxMenu();
    _file->Append(wxID_OPEN, "Open");
    _file->Append(wxID_EXIT, "Exit");

    _menuBar = new wxMenuBar();
    _menuBar->Append(_file, "File");
    this->SetMenuBar(_menuBar);

    _panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vBoxSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    _searchCtrl = new wxSearchCtrl(_panel, _ID_SEARCH_CTRL);

    _btnToPrevious = new wxButton(_panel, _ID_BTN_PRE, "To Previous");
    _btnToNext = new wxButton(_panel, _ID_BTN_NEXT, "To Next");
    _searchCaption = new wxStaticText(_panel, wxID_ANY,
            _SEARCH_CAPTION_DEFAULT);

    _textCtrl = new wxTextCtrl(_panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
            wxDefaultSize, wxTE_MULTILINE | wxHSCROLL | wxTE_READONLY);
    const wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    _textCtrl->SetFont(font);

    hBoxSizer->Add(_searchCtrl, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
    hBoxSizer->Add(_btnToPrevious, 0, wxEXPAND | wxALL, 5);
    hBoxSizer->Add(_btnToNext, 0, wxEXPAND | wxUP | wxDOWN, 5);
    vBoxSizer->Add(hBoxSizer, 0, wxEXPAND);
    vBoxSizer->Add(_searchCaption, 0, wxEXPAND | wxLEFT | wxRIGHT | wxDOWN , 5);
    vBoxSizer->Add(_textCtrl, 1, wxEXPAND);
    _panel->SetSizer(vBoxSizer);

    this->SetMinSize(wxSize(800, 600));
    this->Centre();
}

void MyGui::onExit(wxCommandEvent &event) {
	this->Close(true);
}

void MyGui::onOpenFile(wxCommandEvent &event) {

    wxFileDialog *open = new wxFileDialog(this, "Open");
    open->SetWindowStyle(wxFD_FILE_MUST_EXIST);
    open->SetWildcard("Text File|*.txt");
    if (open->ShowModal() == wxID_OK)
    {
        _textCtrl->Clear();
        _htable.clear();
        wxString path = open->GetPath();

        std::ifstream fin(path, std::ios::binary);
        if (fin.is_open()) {
            std::string str;
            std::size_t position = fin.tellg();
            while (fin >> str) {

                // convert to lower case
                transform(str.begin(), str.end(), str.begin(), ::tolower);

                // remove special characters
                for (std::size_t i = 0; i < str.length(); i++) {
                    if (str.at(i) == ',' || str.at(i) == '.') {
                        str.erase(i, 1);
                    }
                }
                _htable.insert(str, position);
                position = fin.tellg();
                position++;
            }
        }
        fin.close();

        std::string buffer;
        std::string temp;
        std::ifstream fin2(path, std::ios::binary);
        while(getline(fin2, temp)) {
            buffer += temp + "\n";
        }
        fin2.close();

        _textCtrl->SetValue(buffer);

        _searchCtrl->AutoComplete(new MyTextCompleter(path.ToStdString()));
    }
    delete open;
}

void MyGui::onSearch(wxCommandEvent &event) {
    _initSearch();
}

void MyGui::onClickToPrevious(wxCommandEvent &event) {
    wxString term = _searchCtrl->GetValue();
    std::transform(term.begin(), term.end(), term.begin(), ::tolower);
    if (_lookupNode != NULL && _lookupNode->getKey() == term) {
        std::vector<std::size_t> vec = _lookupNode->getPositionVector();
        if (_lookupIndex == 0) {
            _lookupIndex = vec.size() - 1;
        }
        else {
            _lookupIndex--;
        }
        _textCtrl->SetFocus();
        std::size_t position = vec.at(_lookupIndex);
        _textCtrl->ShowPosition(position);
        std::string term = _lookupNode->getKey();
        _textCtrl->SetSelection(position, position + term.length());
        std::ostringstream label;
        label << _lookupIndex + 1 << " of " << vec.size();
        _searchCaption->SetLabelText(label.str());
    }
}

void MyGui::onClickToNext(wxCommandEvent &event) {
    wxString term = _searchCtrl->GetValue();
    std::transform(term.begin(), term.end(), term.begin(), ::tolower);
    if (_lookupNode != NULL && _lookupNode->getKey() == term) {
        std::vector<std::size_t> vec = _lookupNode->getPositionVector();
        _lookupIndex = (_lookupIndex + 1) % vec.size();
        _textCtrl->SetFocus();
        std::size_t position = vec.at(_lookupIndex);
        _textCtrl->ShowPosition(position);
        std::string term = _lookupNode->getKey();
        _textCtrl->SetSelection(position, position + term.length());
        std::ostringstream label;
        label << _lookupIndex + 1 << " of " << vec.size();
        _searchCaption->SetLabelText(label.str());
    }
    else {
        _initSearch();
    }
}