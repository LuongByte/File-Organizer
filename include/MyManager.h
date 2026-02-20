#pragma once
#include <vector>
#include <wx/wx.h>
#include <filesystem>
#include <string>


class MyManager
{
    public:
        MyManager();
        std::vector<wxTextCtrl*>& GetSelectFolder();
        std::vector<wxTextCtrl*>& GetMoveFolder();
        std::vector<wxComboBox*>& GetMoveOption();
        std::vector<wxComboBox*>& GetFirstCondition();
        std::vector<wxTextCtrl*>& GetSecondCondition();
        void manageFiles();
    private:
        std::vector<wxTextCtrl*> search_folders;
        std::vector<wxComboBox*> first_condition;
        std::vector<wxTextCtrl*> second_condition;
        std::vector<wxComboBox*> move_options;
        std::vector<wxTextCtrl*> move_folders;
        std::vector<std::string> searchFolder();
        void checkFile(const std::filesystem::path& testDest);
        void moveFile(const std::vector<std::string>& folderLocations, const std::filesystem::path& testDest);
};