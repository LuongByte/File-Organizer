#include <wx/wx.h>
#include <MyFileInput.h>


MyFileInput::MyFileInput(wxPanel *panel) : MyInput(panel)
{
    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);

    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);

    this->Add(topRowSizer, 0, wxEXPAND);
    this->Add(addButtonSizer, 0, wxEXPAND);
}