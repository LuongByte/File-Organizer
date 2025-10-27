#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/aui/aui.h>
#include <MyRule.h>

class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    int tabs = 0;
    std::vector<MyRule*> ruleBook;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxAuiNotebookEvent& event);
    void OnSwitch(wxAuiNotebookEvent& event);
    void OnCreate(wxCommandEvent& event, wxPanel *parent, wxAuiNotebook *notebook);
};

enum
{
    ID_HOME_PAGE = 1001
};