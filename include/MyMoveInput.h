#include <wx/wx.h>
#include <MyInput.h>
#pragma once


class MyMoveInput : public MyInput
{
    public:
        MyMoveInput(wxScrolledWindow *window);
    protected:
        void OnAdd(wxCommandEvent &event) override;
        
};