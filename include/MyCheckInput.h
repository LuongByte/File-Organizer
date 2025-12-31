#include <wx/wx.h>
#include <vector>
#include <MyInput.h>
#include <wx/dateevt.h>

class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c1, std::vector<wxTextCtrl*>& c2);
        void OnUpdate();
    
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
    private:
        std::vector<wxComboBox*>& firstCond;
        std::vector<wxTextCtrl*>& secondCond;
        wxArrayString checkOptions;
        void OnSwitch(wxCommandEvent& event);
        void OnSelect(wxDateEvent& event);
};