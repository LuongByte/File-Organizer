#include <wx/wx.h>
#include <vector>
#pragma once


class MyInput : public wxBoxSizer
{
    public:
        MyInput(wxScrolledWindow *window);
        
    protected:
        wxScrolledWindow* parent;
        virtual void OnAdd(wxCommandEvent& event);
        virtual void OnDelete(wxCommandEvent& event);
};