#include <MyRule.h>
#include <wx/wx.h>

MyRule::MyRule(wxPanel *parent, wxAuiNotebook* notebook) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *ruleSizer = new wxBoxSizer(wxVERTICAL);
    this->notebook = notebook;
    this->activeState = true;
    this->SetSizer(ruleSizer);
    this->SetBackgroundColour(wxColour(255, 255, 255));
    this->desc[0] = "New Rule";
    this->desc[1] = "Line 2";
    this->desc[2] = "Line 3";
    this->descText = new wxStaticText(this, wxID_ANY, desc[0] + "\n" + desc[1] + "\n" + desc[2]);
    wxFont ruleFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer *itemSizer = new wxBoxSizer(wxHORIZONTAL);
    wxCheckBox *stateCheck = new wxCheckBox(this, wxID_ANY, " ");
    stateCheck->SetValue(activeState);
    wxButton *modifyRule = new wxButton(this, wxID_ANY, "Modify", wxDefaultPosition , wxSize(120, 40));

    modifyRule->Bind(wxEVT_BUTTON, &MyRule::OnModify, this);
    stateCheck->Bind(wxEVT_CHECKBOX, &MyRule::OnSwitch, this);
    this->SetFont(ruleFont);
    itemSizer->Add(stateCheck, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
    itemSizer->Add(descText, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(modifyRule, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
    ruleSizer->Add(itemSizer, 0, wxEXPAND | wxALL, 5);
    
}

void MyRule::OnSwitch(wxCommandEvent& event)
{
    activeState = !activeState;
    if(activeState == true)
        descText->SetForegroundColour(wxColour(0, 0, 0));
    else
        descText->SetForegroundColour(wxColour(255, 0, 0));

    descText->Refresh();
    descText->Update();
}

void MyRule::OnModify(wxCommandEvent& event)
{
    
}