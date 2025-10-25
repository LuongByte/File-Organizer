#pragma once

#include <wx/wx.h>
#include <wx/aui/aui.h>



class MyTab : public wxPanel
{
    public:
        MyTab(wxAuiNotebook* notebook, std::string name);
    private:
        wxAuiNotebook* notebook;
        bool activeState;
        std::string tabName;
        void OnOpen(wxCommandEvent& event);
        void OnName(wxCommandEvent& event);

};