#include <wx/wx.h>
#include <wx/combobox.h>
#include <MyCheckInput.h>


MyCheckInput::MyCheckInput(wxPanel *panel) : MyInput(panel)
{
    wxArrayString checkOptions;
    checkOptions.Add("File Type");
    checkOptions.Add("Date Added");
    checkOptions.Add("Date Modified");

    wxArrayString checkOptions2;
    checkOptions2.Add("File Type");
    checkOptions2.Add("Date Added");
    checkOptions2.Add("Date Modified");


    wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(200, 30),
                                            checkOptions, wxCB_READONLY);

    wxComboBox *checkButton2 = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(200, 30),
                                            checkOptions2, wxCB_READONLY);
                                            
    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(checkButton, 0, wxALL, 5);
    topRowSizer->Add(checkButton2, 0, wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(closeButton, 0, wxALL, 5);
    

    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);

    this->Add(topRowSizer, 0, wxEXPAND);
    this->Add(addButtonSizer, 0, wxEXPAND);
}