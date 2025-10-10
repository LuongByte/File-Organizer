#include <wx/aui/auibook.h>
#include <vector>

class MyTabArt : public wxAuiDefaultTabArt
{
public:
    MyTabArt();
    
    wxAuiTabArt* Clone() override;

    void DrawTab(wxDC& dc, wxWindow* wnd, const wxAuiNotebookPage& page, const wxRect& rect, 
        int closeState, wxRect* outTabRect,wxRect* outButtonRect, int* xExtent) override;

private:
    std::vector<bool> m_closableFlags;
    int FindPageIndex(const wxAuiNotebookPage& page);
};
