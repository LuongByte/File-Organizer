#include <wx/combobox.h>
#include "MyMoveInput.h"


MyMoveInput::MyMoveInput(wxScrolledWindow *window, wxString& m1, wxString& m2) : MyInput(window), moveChoice(m1), moveFolder(m2)
{
    moveOptions.Add("Move To Folder");
    moveOptions.Add("Move To Recycle Bin");
    moveOptions.Add("Completely Delete");
    if(moveChoice.empty() == true){
      wxCommandEvent dummyEvent;
      OnAdd(dummyEvent);
    }
    else
      OnReopen();
}

void MyMoveInput::OnReopen()
{
    wxComboBox *moveButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(375, 60),
                                            moveOptions, wxCB_READONLY);
      
    moveButton->SetStringSelection(moveChoice);

    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    fileBox->SetValue(moveFolder);
    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(moveButton, 0, wxALL, 5);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(foldButton, 0, wxALL, 5);

    moveButton->SetClientData(foldButton);
    foldButton->SetClientData(fileBox);

    moveButton->Bind(wxEVT_COMBOBOX_CLOSEUP, &MyMoveInput::OnSwitch, this);
    foldButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnSelect, this);


    this->Add(topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
}


void MyMoveInput::OnAdd(wxCommandEvent& event)
{
    wxComboBox *moveButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(375, 60),
                                            moveOptions, wxCB_READONLY);
                                            
    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");

    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(moveButton, 0, wxALL, 5);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(foldButton, 0, wxALL, 5);

    moveButton->SetClientData(foldButton);
    foldButton->SetClientData(fileBox);

    moveButton->Bind(wxEVT_COMBOBOX_CLOSEUP, &MyMoveInput::OnSwitch, this);
    foldButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnSelect, this);

    this->Add(topRowSizer, 0, wxEXPAND);

    parent->Layout();
    parent->FitInside();
}


void MyMoveInput::OnDelete(wxCommandEvent& event)
{
  //  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
 //   wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(button->GetContainingSizer());
  //  wxSizerItemList &list = sizer->GetChildren();
    
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

    moveChoice = box->GetValue();
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
      moveChoice = textBox->GetValue();
    }
}