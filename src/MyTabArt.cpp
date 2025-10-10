#include <MyTabArt.h>
#include <wx/wx.h>
#include <wx/aui/aui.h>

MyTabArt::MyTabArt()
{

}

void MyTabArt::DrawTab(wxDC& dc, wxWindow* wnd, const wxAuiNotebookPage& page, const wxRect& inRect, 
    int closeState, wxRect* outTabRect, wxRect* outButtonRect, int* xExtent)
{
    const int padding = 10;
    const int closeSize = 16;

    wxString title = page.caption;
    wxFont font = dc.GetFont();
    dc.SetFont(font);
    wxSize size = dc.GetTextExtent(title);

    int baseTabWidth = size.x + 2 * padding + (closeState != wxAUI_BUTTON_STATE_HIDDEN ? closeSize + padding : 0);
    int tabWidth = baseTabWidth * 2;
    wxRect tabRect(inRect.x, inRect.y, tabWidth, inRect.height * 2);

    if(outTabRect != nullptr)
        *outTabRect = tabRect;

    if(xExtent != nullptr)
        *xExtent = tabRect.width;

    bool selected = page.active;

    wxColor backCol = selected ? wxColour(177, 177, 177) : wxColour(220, 220, 220);
    wxColor borderCol = selected ? wxColour(105, 105, 105) : wxColour(150, 150, 150);

    dc.SetBrush(wxBrush(backCol));
    dc.SetPen(wxPen(borderCol));
    dc.DrawRectangle(tabRect);

    font.SetWeight(selected ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);
    dc.SetTextForeground(*wxBLACK);
    
    int textY = tabRect.y + (inRect.height - size.y)/2;
    int textX = tabRect.x + size.x * 0.25;
    dc.DrawText(title, textX, textY);
    
    int ind = FindPageIndex(page);
    bool closable = true;
    if(ind == 0)
        closable = false;

    if(closable && closeState != wxAUI_BUTTON_STATE_HIDDEN){
        wxRect closeRect(tabRect.x + tabRect.width - closeSize - padding, tabRect.y + (inRect.height - closeSize)/2, closeSize, closeSize);

        if(outButtonRect != nullptr)
            *outButtonRect = closeRect;

        dc.SetPen(*wxBLACK_PEN);
        dc.DrawLine(closeRect.x, closeRect.y,
                    closeRect.x + closeRect.width, closeRect.y + closeRect.height);
        dc.DrawLine(closeRect.x + closeRect.width, closeRect.y,
                    closeRect.x, closeRect.y + closeRect.height);
    }
    else if(outButtonRect != nullptr)
        *outButtonRect = wxRect();
    
}

int MyTabArt::FindPageIndex(const wxAuiNotebookPage& page)
{
    wxAuiNotebook* notebook = wxDynamicCast(page.window->GetParent(), wxAuiNotebook);
    if(notebook == nullptr)
        return -1;

    for(int i = 0; i < notebook->GetPageCount(); i++){
        if(notebook->GetPage(i) == page.window)
            return static_cast<int>(i);
    }
    return -1;
}

wxAuiTabArt* MyTabArt::Clone(){
    return new MyTabArt();
}