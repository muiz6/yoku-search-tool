#ifndef MY_GUI_H
#define MY_GUI_H

#include "yoku/InvertedIndex.hpp"
#include <wx/wx.h>
#include <wx/srchctrl.h>

class MyGui: public wxFrame {
    private:
        static const int _ID_SEARCH_CTRL = 10;
        static const int _ID_BTN_PRE = 12;
        static const int _ID_BTN_NEXT = 14;
        static const std::string _SEARCH_CAPTION_DEFAULT;

        wxMenuBar *_menuBar;
        wxMenu *_file;
        wxPanel *_panel;
        wxSearchCtrl *_searchCtrl;
        wxStaticText *_searchCaption;
        wxButton *_btnToNext;
        wxButton *_btnToPrevious;
        wxTextCtrl *_textCtrl;
        yoku::InvertedIndex _htable;

        // to store current query index
        int _lookupIndex;

        // to store current query result
        // for use with next and prev btns
        yoku::IndexNode *_lookupNode;
        wxString _lookupTerm;

        void _initSearch();

    public:
        MyGui(const char *title, int width, int height);
        void onExit(wxCommandEvent &event);
        void onOpenFile(wxCommandEvent &event);
        void onSearch(wxCommandEvent &event);
        void onClickToPrevious(wxCommandEvent &event);
        void onClickToNext(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
};

#endif // GUI_H