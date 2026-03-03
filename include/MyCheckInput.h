#include <wx/wx.h>
#include <vector>
#include <wx/dateevt.h>
#include "MyInput.h"
#include "CustomTypes.h"

class MyCheckInput : public MyInput
{
    public:
        MyCheckInput(wxScrolledWindow *window, std::vector<wxComboBox*>& c, std::vector<FileCondition>& ch);
        void OnUpdate();

    
    protected:
        void OnAdd(wxCommandEvent &event) override;
        void OnDelete(wxCommandEvent &event) override;
        void OnReopen() override;
    private:
        std::vector<wxComboBox*>& checkCondition;
        std::vector<FileCondition>& history;
        wxArrayString checkOptions;
        void OnSwitch(wxCommandEvent& event);
        void OnSelect(wxDateEvent& event);
};