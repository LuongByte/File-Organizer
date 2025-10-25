#include <MyFrame.h>
#include <MyTabArt.h>
#include <MyRule.h>
#include <wx/wx.h>
#include <wx/aui/aui.h>

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    SetBackgroundColour(wxColour(0, 0, 0));
    Maximize(true);
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to FolderOrdr!");

    wxAuiNotebook* notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                                   wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxTC_MULTILINE);

    notebook->SetArtProvider(new MyTabArt());
    notebook->SetTabCtrlHeight(70);

    wxPanel *home = new wxPanel(notebook, wxID_ANY); 
    notebook->AddPage(home, "Home");
    wxBoxSizer *homeSizer = new wxBoxSizer(wxVERTICAL);
    home->SetSizer(homeSizer);

    wxPanel *plusPanel = new wxPanel(home, wxID_ANY);
    plusPanel->SetBackgroundColour(wxColour(255, 255, 255));
    wxButton *plusButton = new wxButton(plusPanel, wxID_ANY, "+", wxDefaultPosition, wxSize(80, 80));

    wxBoxSizer *plusSizer = new wxBoxSizer(wxHORIZONTAL);
    plusPanel->SetSizer(plusSizer);
    plusSizer->AddStretchSpacer(1);
    plusSizer->Add(plusButton, 0, wxALL, 10);
    plusSizer->AddStretchSpacer(1);
    homeSizer->Add(plusPanel, 0, wxEXPAND);
    
    
    plusButton->Bind(wxEVT_BUTTON, std::bind(&MyFrame::OnCreate, this, std::placeholders::_1, home, notebook));
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnCreate(wxCommandEvent& event, wxPanel *parent, wxAuiNotebook *notebook)
{
    MyRule *newRule = new MyRule(parent, notebook);
    wxBoxSizer *sizer = dynamic_cast<wxBoxSizer*>(parent->GetSizer());
    sizer->Insert(sizer->GetItemCount() - 1, newRule, 0, wxEXPAND);
    parent->Layout();
}


void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a FolderOrdr", "A File Manager", wxOK | wxICON_INFORMATION);
}