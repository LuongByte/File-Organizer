#include <vector>
#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyFileInput : public MyInput
{
    public:
        MyFileInput(wxScrolledWindow *window, std::vector<wxTextCtrl*>& v);
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
    private:
        std::vector<wxTextCtrl*>& folders;
        void OnSelect(wxCommandEvent &event);
}; 