#include <vector>
#include <wx/wx.h>
#pragma once

class MyManager
{
    public:
        MyManager();
        std::vector<wxTextCtrl*>& GetSelectFolder();
        std::vector<wxTextCtrl*>& GetMoveFolder();
        std::vector<wxComboBox*>& GetMoveOption();
        std::vector<wxComboBox*>& GetFirstCondition();
        std::vector<wxComboBox*>& GetSecondCondition();
    private:
        std::vector<wxTextCtrl*> search_folders;
        std::vector<wxComboBox*> first_condition;
        std::vector<wxComboBox*> second_condition;
        std::vector<wxComboBox*> move_options;
        std::vector<wxTextCtrl*> move_folders;
        void searchFolder();
        void checkFile();
        void moveFile();
};