#include <wx/combobox.h>
#include <MyMoveInput.h>


MyMoveInput::MyMoveInput(wxScrolledWindow *window, std::vector<wxComboBox*>& m1, std::vector<wxTextCtrl*>& m2) : MyInput(window), moveChoice(m1), moveFolder(m2)
{
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");
    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);
    this->Add(addButtonSizer, 0, wxEXPAND);
    addfileButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnAdd, this);
    moveOptions.Add("Move To Folder");
    moveOptions.Add("Move To Recycle Bin");
    moveOptions.Add("Completely Delete");
    wxCommandEvent dummyEvent;
    OnAdd(dummyEvent);
}

void MyMoveInput::OnAdd(wxCommandEvent& event)
{
    wxComboBox *moveButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(300, 60),
                                            moveOptions, wxCB_READONLY);
                                            
    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    moveChoice.push_back(moveButton);
    moveFolder.push_back(fileBox);

    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");
    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(moveButton, 0, wxALL, 5);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    //topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(foldButton, 0, wxALL, 5);
    topRowSizer->Add(closeButton, 0, wxALL, 5);

    moveButton->SetClientData(foldButton);
    foldButton->SetClientData(fileBox);

    closeButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnDelete, this);
    moveButton->Bind(wxEVT_COMBOBOX_CLOSEUP, &MyMoveInput::OnSwitch, this);
    foldButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnSelect, this);

    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));
}

void MyMoveInput::OnDelete(wxCommandEvent& event)
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(button->GetContainingSizer());
    wxSizerItemList &list = sizer->GetChildren();
    for(int i = 0; i < list.size(); i++){
      if(list[i]->IsWindow() == true){
        wxWindow* test = list[i]->GetWindow();
        if(wxComboBox* combobox = wxDynamicCast(test, wxComboBox))
          moveChoice.erase(std::remove(moveChoice.begin(), moveChoice.end(), combobox), moveChoice.end());
        else if(wxTextCtrl* text = wxDynamicCast(test, wxTextCtrl))
          moveFolder.erase(std::remove(moveFolder.begin(), moveFolder.end(), text), moveFolder.end());
      }
    }
    this->Detach(sizer);
    sizer->Clear(true);
    delete sizer;
    parent->Layout();
    parent->FitInside();
    parent->AdjustScrollbars();
}

void MyMoveInput::OnSwitch(wxCommandEvent& event)
{
    wxComboBox* box = dynamic_cast<wxComboBox*>(event.GetEventObject());
    wxButton* button = static_cast<wxButton*>(box->GetClientData());
    wxTextCtrl* text = static_cast<wxTextCtrl*>(button->GetClientData());
    wxString option = box->GetValue();
    if(option == "Move To Folder"){
      button->Show(true);
      text->Show(true);
    }
    else{
      button->Show(false);
      text->Show(false);
    }
}

void MyMoveInput::OnSelect(wxCommandEvent& event)
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