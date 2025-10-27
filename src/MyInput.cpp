#include <wx/wx.h>
#include <MyInput.h>


MyInput::MyInput(wxPanel *panel) : wxBoxSizer(wxVERTICAL)
{
    this->parent = panel;
}