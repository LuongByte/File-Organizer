#include <wx/wx.h>
#include <wx/wxprec.h>

class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};