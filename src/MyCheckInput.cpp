#include <wx/combobox.h>
#include <wx/datectrl.h>
#include "MyCheckInput.h"


MyCheckInput::MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c, std::vector<FileCondition>& ch) : MyInput(window), checkCondition(c), history(ch)
{
    wxButton *addfileButton = new wxButton(parent, wxID_ANY, "+");
    wxBoxSizer *addButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButtonSizer->AddStretchSpacer(1);
    addButtonSizer->Add(addfileButton, 0, wxALIGN_CENTER | wxALL, 5);
    addButtonSizer->AddStretchSpacer(1);
    this->Add(addButtonSizer, 0, wxEXPAND);
    addfileButton->Bind(wxEVT_BUTTON, &MyCheckInput::OnAdd, this);
    checkOptions.Add("Date Modified");
    checkOptions.Add("File Type");
    if(history.empty() == true){
      wxCommandEvent dummyEvent;
      OnAdd(dummyEvent);
    }
    else
      OnReopen();
}

void MyCheckInput::OnReopen()
{
    for(const auto&cond : history){
      wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                              wxPoint(10, 10), wxSize(300, 60),
                                              checkOptions, wxCB_READONLY);

      
      wxDatePickerCtrl* datePicker = new wxDatePickerCtrl(parent, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,
                                                          wxDP_DROPDOWN | wxDP_SHOWCENTURY);
      datePicker->SetMinSize(wxSize(300, 60));
      

      wxTextCtrl *fileType = new wxTextCtrl(parent, wxID_ANY, "");
      fileType->SetMinSize(wxSize(300, 60));
      fileType->SetHint(".png");
      fileType->Hide();

      
        
      wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");

      wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
      topRowSizer->Add(checkButton, 0, wxALL, 5);
      topRowSizer->AddStretchSpacer(1);
      topRowSizer->Add(datePicker, 0, wxALL, 5);
      topRowSizer->Add(fileType, 0, wxALL, 5);
      topRowSizer->Add(closeButton, 0, wxALL, 5);
      

      
      RowWidgets* rowData = new RowWidgets{datePicker, fileType};
      checkButton->SetClientData(rowData);
      checkButton->Bind(wxEVT_COMBOBOX_CLOSEUP, &MyCheckInput::OnSwitch, this);
      closeButton->Bind(wxEVT_BUTTON, &MyCheckInput::OnDelete, this);
      datePicker->Bind(wxEVT_DATE_CHANGED, &MyCheckInput::OnSelect, this);
      this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
      parent->Layout();
      parent->FitInside();
      parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));

      checkButton->SetStringSelection(cond.type);
      if(cond.type == "Date Modified")
        datePicker->SetValue(cond.date);
      else{
        datePicker->Hide();
        fileType->Show();
        fileType->SetValue(cond.fileExt);
      }

      checkCondition.push_back(checkButton);
    }
}

void MyCheckInput::OnAdd(wxCommandEvent& event)
{
    wxComboBox *checkButton = new wxComboBox(parent, wxID_ANY, wxEmptyString,
                                            wxPoint(10, 10), wxSize(300, 60),
                                            checkOptions, wxCB_READONLY);

    
    wxDatePickerCtrl* datePicker = new wxDatePickerCtrl(parent, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,
                                                        wxDP_DROPDOWN | wxDP_SHOWCENTURY);
    datePicker->SetMinSize(wxSize(300, 60));

    wxTextCtrl *fileType = new wxTextCtrl(parent, wxID_ANY, "");
    fileType->SetMinSize(wxSize(300, 60));
    fileType->SetHint(".png");
    fileType->Hide();

    wxButton *closeButton = new wxButton(parent, wxID_ANY, "X");

    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(checkButton, 0, wxALL, 5);
    topRowSizer->AddStretchSpacer(1);
    topRowSizer->Add(datePicker, 0, wxALL, 5);
    topRowSizer->Add(fileType, 0, wxALL, 5);
    topRowSizer->Add(closeButton, 0, wxALL, 5);
    

    
    RowWidgets* rowData = new RowWidgets{datePicker, fileType};
    checkButton->SetClientData(rowData);
    checkButton->Bind(wxEVT_COMBOBOX_CLOSEUP, &MyCheckInput::OnSwitch, this);
    closeButton->Bind(wxEVT_BUTTON, &MyCheckInput::OnDelete, this);
    datePicker->Bind(wxEVT_DATE_CHANGED, &MyCheckInput::OnSelect, this);
    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));

    checkCondition.push_back(checkButton);
}

void MyCheckInput::OnDelete(wxCommandEvent& event)
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    wxBoxSizer* sizer = dynamic_cast<wxBoxSizer*>(button->GetContainingSizer());
    wxSizerItemList &list = sizer->GetChildren();
    for(int i = 0; i < list.size(); i++){
      if(list[i]->IsWindow() == true){
        wxWindow* test = list[i]->GetWindow();
        if(wxComboBox* combobox = wxDynamicCast(test, wxComboBox)){
          checkCondition.erase(std::remove(checkCondition.begin(), checkCondition.end(), combobox), checkCondition.end());
          RowWidgets* data = static_cast<RowWidgets*>(combobox->GetClientData());
          delete data;
        }
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
    RowWidgets* rowData = static_cast<RowWidgets*>(box->GetClientData());
    wxString option = box->GetValue();
    if(option == "File Type"){
      rowData->datePicker->Hide();
      rowData->fileType->Show();
    }
    else if(option == "Date Modified"){
      rowData->fileType->Hide();
      rowData->datePicker->Show();
    }

    parent->Layout();
    parent->FitInside();
}

void MyCheckInput::OnSelect(wxDateEvent& event)
{
    wxDatePickerCtrl* picker = dynamic_cast<wxDatePickerCtrl*>(event.GetEventObject());
    wxDateTime date = picker->GetValue();
    //wxTextCtrl* text = static_cast<wxTextCtrl*>(picker->GetClientData());
    //text->SetValue(date.Format(wxT("%d-%m-%Y")));
} 