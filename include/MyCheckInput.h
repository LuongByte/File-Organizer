#include <wx/wx.h>
#include <vector>
#include <MyInput.h>


class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c1, std::vector<wxComboBox*>& c2);
        void OnUpdate();
    
    protected:
        void OnAdd(wxCommandEvent &event) override;
    private:
        std::string desc[3];
        std::vector<wxComboBox*>& firstCond;
        std::vector<wxComboBox*>& secondCond;
        wxStaticText* descText;
        void OnEdit(wxCommandEvent& event);
        void OnSwitch(wxCommandEvent& event);
};