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
    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");
    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);
    topRowSizer->Add(closeButton, 0, wxALL, 5);

    foldButton->SetClientData(fileBox);
    foldButton->Bind(wxEVT_BUTTON, &MyFileInput::OnSelect, this);
    closeButton->Bind(wxEVT_BUTTON, &MyFileInput::OnDelete, this);
    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));
}

void MyFileInput::OnDelete(wxCommandEvent& event)
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(button->GetContainingSizer());
    wxSizerItemList &list = sizer->GetChildren();
    for(int i = 0; i < list.size(); i++){
      if(list[i]->IsWindow() == true){
        wxWindow* test = list[i]->GetWindow();
          if(wxTextCtrl* text = wxDynamicCast(test, wxTextCtrl))
              folders.erase(std::remove(folders.begin(), folders.end(), text), folders.end());
      }
    }
    this->Detach(sizer);
    sizer->Clear(true);
    delete sizer;
    parent->Layout();
    parent->FitInside();
    parent->AdjustScrollbars();
}

void MyFileInput::OnSelect(wxCommandEvent& event)
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxDirDialog dirDialog(parent, "Select a Folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
      
    if(dirDialog.ShowModal() == wxID_OK){
      wxTextCtrl* textBox = static_cast<wxTextCtrl*>(button->GetClientData());
      wxString path = dirDialog.GetPath();
      //wxLogMessage("Select Folder: %s", path);
      textBox->SetValue(path);
    }
}