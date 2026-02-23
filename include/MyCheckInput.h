#include <wx/wx.h>
#include <vector>
#include <MyInput.h>
#include <wx/dateevt.h>

class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c);
        void OnUpdate();
    
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
    private:
        std::vector<wxComboBox*>& checkCondition;
        wxArrayString checkOptions;
        void OnSwitch(wxCommandEvent& event);
        void OnSelect(wxDateEvent& event);
};