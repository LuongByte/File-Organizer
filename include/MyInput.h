#include <wx/wx.h>
#pragma once


class MyInput : public wxBoxSizer
{
    public:
        MyInput(wxPanel* panel);
        
    protected:
        int ind;
        wxPanel* parent;

    private:
        void OnDelete(wxCommandEvent& event);
};