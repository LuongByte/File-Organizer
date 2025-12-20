#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <MyTab.h>
#include <MyManager.h>
#pragma once


class MyRule : public wxPanel
{
    public:
        MyRule(wxPanel* parent, wxAuiNotebook* notebook);
        void OnUpdate();
        static const std::vector<MyRule*>& GetBook();
    private:
        static std::vector<MyRule*> ruleBook;
        std::string desc[3];
        MyManager* manager; 
        wxStaticText* descText;
        bool activeState;
        wxAuiNotebook* notebook;
        MyTab *tab;
        void OnSwitch(wxCommandEvent& event);
        void OnEdit(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
};