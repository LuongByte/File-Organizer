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
        wxString& GetMoveFolder();
        wxString& GetMoveOption();
        std::vector<wxComboBox*>& GetCondition();
        void manageFiles();
        struct FileCondition
        {
            std::string type;
            std::string fileExt;
            wxDateTime date;
        };
        
    private:
        std::vector<wxTextCtrl*> search_folders;
        std::vector<wxComboBox*> check_condition;
        wxString move_options;
        wxString move_folders;
        std::vector<FileCondition> activeConditions;
        std::vector<std::string> searchFolder();
        void checkFile(const std::filesystem::path& testDest);
        bool matchesConditions(const std::filesystem::path& filePath);
        void moveFile(const std::vector<std::string>& folderLocations, const std::filesystem::path& testDest);
};