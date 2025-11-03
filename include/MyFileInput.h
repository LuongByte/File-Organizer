#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyFileInput : public MyInput
{
    public:
        MyFileInput(wxScrolledWindow *window);
    protected:
        void OnAdd(wxCommandEvent &event) override;
};