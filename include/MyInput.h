#include <wx/wx.h>
#pragma once


class MyInput : public wxBoxSizer
{
    public:
        MyInput(wxScrolledWindow *window);
        
    protected:
        std::vector<wxTextCtrl*> list;
        wxScrolledWindow* parent;
        virtual void OnAdd(wxCommandEvent& event);

    private:
        void OnDelete(wxCommandEvent& event);
};