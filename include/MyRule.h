#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <MyTab.h>
#pragma once


class MyRule : public wxPanel
{
    public:
        MyRule(wxPanel* parent, wxAuiNotebook* notebook);
        void OnUpdate();
        
    private:
        std::string desc[3];
        wxStaticText* descText;
        bool activeState;
        wxAuiNotebook* notebook;
        MyTab *tab;
        void OnSwitch(wxCommandEvent& event);
        void OnEdit(wxCommandEvent& event);
};