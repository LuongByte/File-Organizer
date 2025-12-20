#include <MyRule.h>
#include <wx/wx.h>

std::vector<MyRule*> MyRule::ruleBook;

MyRule::MyRule(wxPanel *parent, wxAuiNotebook* notebook) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *ruleSizer = new wxBoxSizer(wxVERTICAL);
    this->tab = nullptr;
    this->notebook = notebook;
    this->activeState = true;
    this->manager = new MyManager();
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
    wxButton *deleteRule = new wxButton(this, wxID_ANY, "Delete", wxDefaultPosition , wxSize(120, 40));
    modifyRule->Bind(wxEVT_BUTTON, &MyRule::OnEdit, this);
    stateCheck->Bind(wxEVT_CHECKBOX, &MyRule::OnSwitch, this);
    deleteRule->Bind(wxEVT_BUTTON, &MyRule::OnDelete, this);

    this->SetFont(ruleFont);
    itemSizer->Add(stateCheck, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
    itemSizer->Add(descText, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 10);
    itemSizer->AddStretchSpacer(1);
    itemSizer->Add(modifyRule, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
    itemSizer->Add(deleteRule, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
    ruleSizer->Add(itemSizer, 0, wxEXPAND | wxALL, 5);
    ruleBook.push_back(this);
}

const std::vector<MyRule*>& MyRule::GetBook()
{
    return ruleBook;
}

void MyRule::OnDelete(wxCommandEvent& event)
{
    wxWindow* parent = this->GetParent();
    wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(parent->GetSizer());
    sizer->Detach(this);
    this->Destroy();
    parent->Layout();

    if(tab != nullptr){
        int ind = notebook->FindPage(tab);
        if(ind != wxNOT_FOUND){
            notebook->DeletePage(ind);
            tab = nullptr;
        }
    }
}
void MyRule::OnEdit(wxCommandEvent& event)
{
    if(tab != nullptr){
        int ind = notebook->FindPage(tab);
        notebook->SetSelection(ind);
    }
    else{
        MyTab *newTab = new MyTab(notebook, &tab, &desc[0], manager);
        notebook->AddPage(newTab, "New Tab");
        notebook->SetSelection(notebook->GetPageCount() - 1);
        tab = newTab;
    }
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

void MyRule::OnUpdate()
{
    descText->SetLabel(desc[0] + "\n" + desc[1] + "\n" + desc[2]);
}

