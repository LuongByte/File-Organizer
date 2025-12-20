#include <MyFrame.h>
#include <MyTabArt.h>
#include <MyRule.h>
#include <MyTab.h>
#include <wx/wx.h>
#include <wx/aui/aui.h>

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    SetBackgroundColour(wxColour(0, 0, 0));
    Maximize(true);
    wxMenu *menuFile = new wxMenu;
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

    wxPanel *home = new wxPanel(notebook, ID_HOME_PAGE);
    notebook->AddPage(home, "Home");
    wxBoxSizer *homeSizer = new wxBoxSizer(wxVERTICAL);
    home->SetSizer(homeSizer);

    wxPanel *headPanel = new wxPanel(home, wxID_ANY);
    headPanel->SetBackgroundColour(wxColour(100, 100, 100));
    wxBoxSizer *headSizer = new wxBoxSizer(wxHORIZONTAL);
    headPanel->SetSizer(headSizer);

    wxPanel *headButPanel = new wxPanel(headPanel, wxID_ANY);
    wxBoxSizer *headButSizer = new wxBoxSizer(wxHORIZONTAL);
    headButPanel->SetSizer(headButSizer);
    wxButton *addCondition = new wxButton(headButPanel, wxID_ANY, "Add Condition", wxDefaultPosition , wxSize(120, 40));
    
    
    headButSizer->Add(addCondition, 0, wxALIGN_LEFT | wxALL, 15);
    headSizer->Add(headButPanel, 0, wxALIGN_LEFT | wxLEFT, 50);
    homeSizer->Add(headPanel, 0,  wxEXPAND);


    wxPanel *plusPanel = new wxPanel(home, wxID_ANY);
    plusPanel->SetBackgroundColour(wxColour(255, 255, 255));
    wxButton *plusButton = new wxButton(plusPanel, wxID_ANY, "+", wxDefaultPosition, wxSize(80, 80));

    wxBoxSizer *plusSizer = new wxBoxSizer(wxHORIZONTAL);
    plusPanel->SetSizer(plusSizer);
    plusSizer->AddStretchSpacer(1);
    plusSizer->Add(plusButton, 0, wxALL, 10);
    plusSizer->AddStretchSpacer(1);
    homeSizer->Add(plusPanel, 0, wxEXPAND);
    
    addCondition->Bind(wxEVT_BUTTON, std::bind(&MyFrame::OnCreate, this, std::placeholders::_1, home, notebook));
    plusButton->Bind(wxEVT_BUTTON, std::bind(&MyFrame::OnCreate, this, std::placeholders::_1, home, notebook));
    notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &MyFrame::OnClose, this);
    notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &MyFrame::OnSwitch, this);
}

void MyFrame::OnCreate(wxCommandEvent& event, wxPanel *parent, wxAuiNotebook *notebook)
{
    MyRule *newRule = new MyRule(parent, notebook);
    wxBoxSizer *sizer = dynamic_cast<wxBoxSizer*>(parent->GetSizer());
    sizer->Insert(sizer->GetItemCount() - 1, newRule, 0, wxEXPAND);
    parent->Layout();
}

void MyFrame::OnClose(wxAuiNotebookEvent& event)
{
    wxAuiNotebook *notebook = dynamic_cast<wxAuiNotebook*>(event.GetEventObject());
    int ind = notebook->GetSelection();
    if(ind == 0)
        event.Veto();
    MyTab *tab = dynamic_cast<MyTab*>(notebook->GetPage(ind));
    tab->SetClosed();
}

void MyFrame::OnSwitch(wxAuiNotebookEvent& event)
{
    int ind = event.GetSelection();
    wxAuiNotebook *notebook = dynamic_cast<wxAuiNotebook*>(event.GetEventObject());
    wxPanel *selected = dynamic_cast<wxPanel*>(notebook->GetPage(ind));

    if(selected->GetId() == ID_HOME_PAGE){
        for(int i = 0; i < MyRule::GetBook().size(); i++)
            MyRule::GetBook()[i]->OnUpdate();
    }

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a FolderOrdr", "A File Manager", wxOK | wxICON_INFORMATION);
}