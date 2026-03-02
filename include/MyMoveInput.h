#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyMoveInput : public MyInput
{
    public:
        MyMoveInput(wxScrolledWindow *window, wxString& m1, wxString& m2);

    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
        void OnReopen() override;
    private:
        wxString& moveChoice;
        wxString& moveFolder;
        wxArrayString moveOptions;
        void OnSwitch(wxCommandEvent& event);
        void OnSelect(wxCommandEvent& event);
};