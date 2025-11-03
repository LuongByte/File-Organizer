#include <wx/wx.h>
#include <MyFileInput.h>


MyFileInput::MyFileInput(wxScrolledWindow *window) : MyInput(window)
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
    wxButton *foldButton = new wxButton(parent, wxID_ANY, "...");
    wxBoxSizer *topRowSizer = new wxBoxSizer(wxHORIZONTAL);
    topRowSizer->Add(fileBox, 1, wxEXPAND | wxALL, 5);
    topRowSizer->Add(foldButton, 0, wxALL, 5);

    this->Insert(this->GetItemCount() - 1, topRowSizer, 0, wxEXPAND);
    parent->Layout();
    parent->FitInside();
    parent->Scroll(0, parent->GetScrollRange(wxVERTICAL));
    list.push_back(fileBox);
}