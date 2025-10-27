#include <wx/wx.h>
#include <wx/combobox.h>
#include <MyMoveInput.h>


MyMoveInput::MyMoveInput(wxPanel *panel) : MyInput(panel)
{
    wxArrayString moveOptions;
    moveOptions.Add("Move To");
    moveOptions.Add("Move To Recycle Bin");
    moveOptions.Add("Delete");



    wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(200, 30),
                                            moveOptions, wxCB_READONLY);

    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");

    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(checkButton, 0, wxALL, 5);
    topRowSizer->Add(fileBox, 0, wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(closeButton, 0, wxALL, 5);
    

    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);

    this->Add(topRowSizer, 0, wxEXPAND);
    this->Add(addButtonSizer, 0, wxEXPAND);
}