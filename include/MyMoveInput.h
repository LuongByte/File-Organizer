#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyMoveInput : public MyInput
{
    public:
        MyMoveInput(wxScrolledWindow *window, std::vector<wxComboBox*>& m1, std::vector<wxTextCtrl*>& m2);

    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
    private:
        std::vector<wxComboBox*>& moveChoice;
        std::vector<wxTextCtrl*>& moveFolder;
};