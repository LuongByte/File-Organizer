#include <wx/wx.h>
#include <MyInput.h>


MyInput::MyInput(wxScrolledWindow *window) : wxBoxSizer(wxVERTICAL)
{
    this->parent = window;
}

void MyInput::OnAdd(wxCommandEvent &event)
{}