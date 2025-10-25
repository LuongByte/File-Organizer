#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/aui/aui.h>


class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnCreate(wxCommandEvent& event, wxPanel *parent, wxAuiNotebook *notebook);
};

enum
{
    ID_Hello = 1
};