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
    wxCommandEvent dummyEvent;
    OnAdd(dummyEvent);
}

void MyMoveInput::OnAdd(wxCommandEvent& event)
{
    wxArrayString moveOptions;
    moveOptions.Add("Move To");
    moveOptions.Add("Move To Recycle Bin");
    moveOptions.Add("Delete");


    wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(200, 30),
                                            moveOptions, wxCB_READONLY);
    wxTextCtrl *fileBox = new wxTextCtrl(parent, wxID_ANY, "");
    moveChoice.push_back(checkButton);
    moveFolder.push_back(fileBox);

    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");
    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(checkButton, 0, wxALL, 5);
    topRowSizer->Add(fileBox, 0, wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(closeButton, 0, wxALL, 5);
    closeButton->Bind(wxEVT_BUTTON, &MyMoveInput::OnDelete, this);
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