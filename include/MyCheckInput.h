#include <wx/wx.h>
#include <MyInput.h>


class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxPanel* parent);
        void OnUpdate();
        
    private:
        std::string desc[3];
        wxStaticText* descText;
        bool activeState;
        void OnEdit(wxCommandEvent& event);
        void OnSwitch(wxCommandEvent& event);
};