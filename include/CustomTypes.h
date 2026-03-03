#ifndef CUSTOMTYPES_H 
#define CUSTOMTYPES_H 
#include <string>
#include <wx/wx.h>
#include <wx/datectrl.h>

struct FileCondition 
{
    std::string type;
    std::string fileExt;
    wxDateTime date;  
}; 

struct RowWidgets
{
    wxDatePickerCtrl* datePicker;
    wxTextCtrl* fileType;
};

#endif