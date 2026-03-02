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
        std::vector<wxString>& GetFileHistory();
        void manageFiles();
        void OnTabClose();
        void OnTabOpen();
        struct FileCondition
        {
            std::string type;
            std::string fileExt;
            wxDateTime date;
        };
        
    private:
        bool tabOpen;
        std::vector<wxTextCtrl*> search_folders;
        std::vector<wxComboBox*> check_condition;
        std::vector<wxString> folder_history;
        wxString move_options;
        wxString move_folders;
        std::vector<FileCondition> activeConditions;
        std::vector<std::string> SearchFolder();
        void CheckFile(const std::filesystem::path& testDest);

        bool MatchesConditions(const std::filesystem::path& filePath);
        void MoveFile(std::vector<std::string> folderLocations, const std::filesystem::path& testDest);
};