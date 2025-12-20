#include <vector>
#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyFileInput : public MyInput
{
    public:
        MyFileInput(wxScrolledWindow *window, std::vector<wxTextCtrl*>& v);
    protected:
        std::vector<wxTextCtrl*>& folders;
        void OnAdd(wxCommandEvent &event) override;
};