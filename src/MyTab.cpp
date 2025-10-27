#include <MyTab.h>
#include <MyFileInput.h>
#include <MyCheckInput.h>
#include <MyMoveInput.h>
#include <wx/wx.h>

MyTab::MyTab(wxAuiNotebook* notebook, MyTab **ptr, std::string* name) : wxScrolledWindow(notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL)
{
    this->notebook = notebook;
    this->tabName = name;
    this->selfPtr = ptr;
    SetName(wxString(*tabName));
    notebook->SetPageText(notebook->FindPage(this), wxString(*tabName));
    wxBoxSizer *tabSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(tabSizer);
    this->SetFont(GetFont().Scale(3));
    
    SetScrollRate(10, 10);
    FitInside();

    Bind(wxEVT_SIZE, [this](wxSizeEvent& event) {
        this->FitInside();
        event.Skip();
    });

    wxStaticText *nameDesc = new wxStaticText(this, wxID_ANY, "Name Rule");
    nameDesc->SetForegroundColour(wxColour(255, 255, 255));
    nameDesc->SetFocus();
    wxTextCtrl *nameBox = new wxTextCtrl(this, wxID_ANY, "");
    wxBoxSizer *nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameBox->SetHint("Enter Name ");

    wxBoxSizer *fileSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *fileDesc = new wxStaticText(this, wxID_ANY, "Select Folders");
    fileDesc->SetForegroundColour(wxColour(255, 255, 255));
    wxPanel *fileContain = new wxPanel(this, wxID_ANY);
    fileContain->SetBackgroundColour(wxColour(255, 255, 255));
    MyFileInput *fileContainSizer = new MyFileInput(fileContain);
    fileContain->SetSizer(fileContainSizer);

    wxBoxSizer *checkSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *checkDesc = new wxStaticText(this, wxID_ANY, "Check files");
    checkDesc->SetForegroundColour(wxColour(255, 255, 255));
    wxPanel *checkContain = new wxPanel(this, wxID_ANY);
    checkContain->SetBackgroundColour(wxColour(255, 255, 255));
    MyCheckInput *checkContainSizer = new MyCheckInput(checkContain);
    checkContain->SetSizer(checkContainSizer);

    wxBoxSizer *moveSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *moveDesc = new wxStaticText(this, wxID_ANY, "Move files");
    moveDesc->SetForegroundColour(wxColour(255, 255, 255));
    wxPanel *moveContain = new wxPanel(this, wxID_ANY);
    moveContain->SetBackgroundColour(wxColour(255, 255, 255));
    MyMoveInput *moveContainSizer = new MyMoveInput(moveContain);
    moveContain->SetSizer(moveContainSizer);
    
    nameSizer->Add(nameDesc, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 50);
    nameSizer->AddSpacer(20);
    nameSizer->Add(nameBox, 1, wxEXPAND | wxALL, 30);
    fileSizer->Add(fileDesc, 0, wxALIGN_LEFT  | wxALIGN_CENTER_VERTICAL | wxALL, 50);
    fileSizer->AddSpacer(20);
    fileSizer->Add(fileContain, 1, wxEXPAND | wxALL, 30);
    checkSizer->Add(checkDesc, 0, wxALIGN_LEFT  | wxALIGN_CENTER_VERTICAL | wxALL, 50);
    checkSizer->AddSpacer(20);
    checkSizer->Add(checkContain, 1, wxEXPAND | wxALL, 30);
    moveSizer->Add(moveDesc, 0, wxALIGN_LEFT  | wxALIGN_CENTER_VERTICAL | wxALL, 50);
    moveSizer->AddSpacer(20);
    moveSizer->Add(moveContain, 1, wxEXPAND | wxALL, 30);
    
    nameDesc->SetMinSize(wxSize(250, -1));
    fileDesc->SetMinSize(wxSize(250, -1));
    checkDesc->SetMinSize(wxSize(250, -1));
    moveDesc->SetMinSize(wxSize(250, -1));
    tabSizer->Add(nameSizer, 0, wxEXPAND | wxALL, 10);
    tabSizer->Add(fileSizer, 0, wxEXPAND | wxALL, 10);
    tabSizer->Add(checkSizer, 0, wxEXPAND | wxALL, 10);
    tabSizer->Add(moveSizer, 0, wxEXPAND | wxALL, 10);

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