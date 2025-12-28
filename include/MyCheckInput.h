#include <wx/wx.h>
#include <vector>
#include <MyInput.h>


class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c1, std::vector<wxTextCtrl*>& c2);
        void OnUpdate();
    
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
    private:
        std::string desc[3];
        std::vector<wxComboBox*>& firstCond;
        std::vector<wxTextCtrl*>& secondCond;
        wxArrayString checkOptions;
        wxButton *datePicker;
        void OnEdit(wxCommandEvent& event);
        void OnSwitch(wxCommandEvent& event);
};