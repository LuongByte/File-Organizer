#include <wx/wx.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <MyFrame.h>
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
 
bool MyApp::OnInit()
{   
  /*
      std::string input_path;
      std::cout << "Enter a file path: ";
      
      std::cin >> input_path;
      std::filesystem::path dirPath = input_path;
      
      std::filesystem::create_directories(dirPath);*/
    MyFrame *frame = new MyFrame();
    frame->SetBackgroundColour(wxColour(30, 30, 30));
    frame->SetForegroundColour(wxColour(220, 220, 220));
    frame->Show(true);
    
    return true;
}