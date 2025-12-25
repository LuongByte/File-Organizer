#include <MyFileInput.h>
#include <wx/dirdlg.h>

MyFileInput::MyFileInput(wxScrolledWindow *window, std::vector<wxTextCtrl*>& v) : MyInput(window), folders(v)
{
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");
    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);
    this->Add(addButtonSizer, 0, wxEXPAND);
    addfileButton->Bind(wxEVT_BUTTON, &MyFileInput::OnAdd, this);
    wxCommandEvent dummyEvent;
    OnAdd(dummyEvent);
}

void MyFileInput::OnAdd(wxCommandEvent& event)
{
    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    folders.push_back(fileBox);
    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");
    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);

    foldButton->SetClientData(fileBox);
    foldButton->Bind(wxEVT_BUTTON, &MyFileInput::OnSelect, this);
    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));
    list.push_back(fileBox);
}

void MyFileInput::OnSelect(wxCommandEvent& event)
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxDirDialog dirDialog(parent, "Select a Folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    
    if(dirDialog.ShowModal() == wxID_OK){
        wxTextCtrl* textBox = static_cast<wxTextCtrl*>(button->GetClientData());
        wxString path = dirDialog.GetPath();
        wxLogMessage("Select Folder: %s", path);
        textBox->SetValue(path);
    }
    
}