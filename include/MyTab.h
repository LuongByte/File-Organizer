#pragma once

#include <wx/wx.h>
#include <wx/aui/aui.h>



class MyTab : public wxScrolledWindow
{
    public:
        MyTab(wxAuiNotebook* notebook, MyTab **ptr, std::string* name);
        void SetClosed();
    private:
        wxAuiNotebook* notebook;
        bool activeState;
        MyTab** selfPtr;
        std::string* tabName;
        wxString fullName;
        void OnOpen(wxCommandEvent& event);
        void OnName(wxCommandEvent& event);

};