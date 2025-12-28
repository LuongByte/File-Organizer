#include <wx/combobox.h>
#include <MyCheckInput.h>


MyCheckInput::MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c1, std::vector<wxTextCtrl*>& c2) : MyInput(window), firstCond(c1), secondCond(c2)
{
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");
    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);
    this->Add(addButtonSizer, 0, wxEXPAND);
    addfileButton->Bind(wxEVT_BUTTON, &MyCheckInput::OnAdd, this);
    wxCommandEvent dummyEvent;
    OnAdd(dummyEvent);
}

void MyCheckInput::OnAdd(wxCommandEvent& event)
{
    checkOptions.Add("File Type");
    checkOptions.Add("Date Modified");
    
    wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(300, 60),
                                            checkOptions, wxCB_READONLY);
    
    wxTextCtrl* checkBox = new wxTextCtrl(parent, wxID_ANY, "");
    checkBox->SetHint("Helpful");

    firstCond.push_back(checkButton);
    secondCond.push_back(checkBox);
    wxButton *datePicker = new wxButton(parent, wxID_ANY, "Select");
    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(checkButton, 0, wxALL, 5);
    topRowSizer->Add(checkBox, 0, wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(datePicker, 0, wxALL, 5);
    topRowSizer->Add(closeButton, 0, wxALL, 5);
    
    closeButton->Bind(wxEVT_BUTTON, &MyCheckInput::OnDelete, this);
    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));
}

void MyCheckInput::OnDelete(wxCommandEvent& event)
{
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(button->GetContainingSizer());
  wxSizerItemList &list = sizer->GetChildren();
  for(int i = 0; i < list.size(); i++){
    if(list[i]->IsWindow() == true){
      wxWindow* test = list[i]->GetWindow();
      if(wxComboBox* combobox = wxDynamicCast(test, wxComboBox))
        firstCond.erase(std::remove(firstCond.begin(), firstCond.end(), combobox), firstCond.end());
      else if(wxTextCtrl* text = wxDynamicCast(test, wxTextCtrl))
        secondCond.erase(std::remove(secondCond.begin(), secondCond.end(), text), secondCond.end());
    }
  }
  this->Detach(sizer);
  sizer->Clear(true);
  delete sizer;
  parent->Layout();
  parent->FitInside();
  parent->AdjustScrollbars();
}

void MyCheckInput::OnSwitch(wxCommandEvent& event)
{
  wxComboBox* box = dynamic_cast<wxComboBox*>(event.GetEventObject());
  wxString option = box->GetValue();
  if(option == "File Type"){

  }
  else if(option == "Date Modified"){

  }
}