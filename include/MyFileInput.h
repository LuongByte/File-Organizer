#include <vector>
#include <wx/wx.h>
#include "MyInput.h"
#pragma once


class MyFileInput : public MyInput
{
    public:
        MyFileInput(wxScrolledWindow *window, std::vector<wxTextCtrl*>& v, std::vector<wxString>& fh);
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
        void OnReopen() override;
    private:
        std::vector<wxString>& history;
        std::vector<wxTextCtrl*>& folders;
        void OnSelect(wxCommandEvent &event);
        
}; 