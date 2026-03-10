#pragma once
#include <vector>
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include "MyManager.h"


class MyTab : public wxScrolledWindow
{
    public:
        MyTab(wxAuiNotebook* notebook, MyTab **ptr, std::string* name, MyManager* manager);
        ~MyTab();
    private:
        wxAuiNotebook* notebook;
        bool activeState;
        MyTab** selfPtr;
        std::string* tabName;
        wxString fullName;
        MyManager* manager;
        void OnName(wxCommandEvent& event);
};