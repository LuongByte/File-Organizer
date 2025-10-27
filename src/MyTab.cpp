#include <MyTab.h>
#include <wx/wx.h>

MyTab::MyTab(wxAuiNotebook* notebook, MyTab **ptr, std::string* name) : wxPanel(notebook, wxID_ANY)
{
    this->notebook = notebook;
    this->tabName = name;
    this->selfPtr = ptr;
    SetName(wxString(*tabName));
    notebook->SetPageText(notebook->FindPage(this), wxString(*tabName));
    wxBoxSizer *tabSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(tabSizer);
    this->SetFont(GetFont().Scale(3));
    
    wxStaticText *nameDesc = new wxStaticText(this, wxID_ANY, "Name Rule");
    nameDesc->SetForegroundColour(wxColour(255, 255, 255));
    nameDesc->SetFocus();
    wxTextCtrl *nameBox = new wxTextCtrl(this, wxID_ANY, "");
    wxBoxSizer *nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameBox->SetHint("Enter Name ");

    nameSizer->Add(nameDesc, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 50);
    nameSizer->AddSpacer(20);
    nameSizer->Add(nameBox, 1, wxEXPAND | wxALL, 30);
    
    tabSizer->Add(nameSizer, 0, wxEXPAND | wxALL, 10);

    nameBox->Bind(wxEVT_TEXT, &MyTab::OnName, this);
}

void MyTab::SetClosed()
{
    *selfPtr = nullptr;
}

void MyTab::OnOpen(wxCommandEvent& event)
{
    wxDirDialog openDir(NULL, "Select Folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if(openDir.ShowModal() == wxID_CANCEL)
        return;
    else
        wxString path = openDir.GetPath();
}

void MyTab::OnName(wxCommandEvent& event)
{
    wxTextCtrl *textBox = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
    wxString fullName = textBox->GetValue();
    int ind = notebook->FindPage(this);
    //printf("%s\n", tabName->c_str());
    if(fullName == "")
        fullName = "Rule " + std::to_string(ind);

    SetName(fullName);
    *tabName = fullName.ToStdString();
    if(strlen(tabName->c_str()) > 17){
        *tabName = *tabName + "...";
    }

    if(strlen(tabName->c_str()) <= 21)
        notebook->SetPageText(ind, wxString(*tabName));
}