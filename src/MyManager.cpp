#include <filesystem>
#include <iostream>
#include <wx/datectrl.h>
#include "MyManager.h"

namespace fs = std::filesystem;


MyManager::MyManager()
{
    tabOpen = false;
}


std::vector<wxTextCtrl*>& MyManager::GetSelectFolder()
{
    return search_folders;
}

std::vector<wxComboBox*>& MyManager::GetCondition()
{
    return check_condition;
}

std::vector<wxString>& MyManager::GetFileHistory()
{
    return folder_history;
}

std::vector<FileCondition>& MyManager::GetCondHistory()
{
    return activeConditions;
}

wxString& MyManager::GetMoveOption()
{
    return move_options;
}

wxString& MyManager::GetMoveFolder()
{
    return move_folders;
}


void MyManager::manageFiles()
{   
    fs::path dest = move_folders.ToStdString(wxConvUTF8).c_str();
    if(tabOpen == true){
        std::vector<std::string> folderLocations = SearchFolder();
        try{
            if(fs::exists(dest) != true && move_options.ToStdString(wxConvUTF8) != "Completely Delete")
                fs::create_directories(dest);
            CheckFile();
            if(move_options.ToStdString(wxConvUTF8) == "Move To Folder")
                MoveFile(folderLocations, dest);
            else if(move_options.ToStdString(wxConvUTF8) == "Completely Delete")
                DeleteFile(folderLocations);
        }
        catch(const fs::filesystem_error& e){}
    }
    else{
        std::vector<std::string> folderLocations;
        try{
            if(fs::exists(dest) != true && move_options.ToStdString(wxConvUTF8) != "Completely Delete")
                fs::create_directories(dest);
            for(const auto&input : folder_history)
                folderLocations.push_back(input.ToStdString(wxConvUTF8));
            if(move_options.ToStdString(wxConvUTF8) == "Move To Folder")
                MoveFile(folderLocations, dest);
            else if(move_options.ToStdString(wxConvUTF8) == "Completely Delete")
                DeleteFile(folderLocations);
        }
        catch(const fs::filesystem_error& e){}        
    }
}

std::vector<std::string> MyManager::SearchFolder()
{   
    std::vector<std::string> folderLocations;
    folder_history.clear();
    for(const auto&input : search_folders){
        folderLocations.push_back((input->GetValue()).ToStdString(wxConvUTF8));
        folder_history.push_back((input->GetValue()));
    }   
    return folderLocations;
}
 
void MyManager::CheckFile()
{
    activeConditions.clear();
    for(const auto&input : check_condition){
        RowWidgets* rowData = static_cast<RowWidgets*>(input->GetClientData());
        wxDatePickerCtrl* datePicker = rowData->datePicker;
        wxTextCtrl* fileType = rowData->fileType;

        wxString selectedOption = input->GetValue();

        if(selectedOption == "Date Modified"){
            FileCondition condition;
            condition.type = "Date Modified";
            condition.date = datePicker->GetValue();
            activeConditions.push_back(condition);
        }
        else if(selectedOption == "File Type"){
            FileCondition condition;
            condition.type = "File Type";
            condition.fileExt = fileType->GetValue().ToStdString(wxConvUTF8);
            activeConditions.push_back(condition);
        }
    }
}

bool MyManager::MatchesConditions(const fs::path& filePath)
{
    bool hasFileTypeCondition = false;
    bool fileTypeMatched = false;

    bool hasDateCondition = false;
    bool dateMatched = false;

    for(const auto& condition : activeConditions){
        if(condition.type == "File Type"){
            hasFileTypeCondition = true;
            std::string ext = filePath.extension().string();
            if(ext == condition.fileExt)
                fileTypeMatched = true;
        }
        else if(condition.type == "Date Modified"){
            hasDateCondition = true;
            std::filesystem::file_time_type fileTime = fs::last_write_time(filePath);
            std::chrono::system_clock::time_point timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>
                                                            (fileTime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
            std::time_t clockFileTime = std::chrono::system_clock::to_time_t(timePoint);
            wxDateTime fileDate(clockFileTime);

            if(fileDate.FormatISODate() == condition.date.FormatISODate())  
                dateMatched = true;
        }
    }
    if(hasFileTypeCondition && !fileTypeMatched)
        return false;

    if(hasDateCondition && !dateMatched)
        return false;

    return true;
}

void MyManager::MoveFile(const std::vector<std::string> folderLocations, const fs::path& dest)
{
    for(const auto& folder : folderLocations){
        for(const auto& file : fs::directory_iterator(folder)){
            const fs::path& filePath = file.path();
            if(fs::is_regular_file(filePath)){
                if(MatchesConditions(filePath) == false)
                    continue;
                fs::path newLocation = dest / filePath.filename();

                if(fs::exists(newLocation))
                    fs::remove(newLocation);
                fs::rename(filePath, newLocation);
            }
        }
    }
}


void MyManager::DeleteFile(std::vector<std::string> folderLocations)
{
    for(const auto& folder : folderLocations){
        for(const auto& file : fs::directory_iterator(folder)){
            const fs::path& filePath = file.path();
            if(fs::is_regular_file(filePath)){
                if(MatchesConditions(filePath) == false)
                    continue;
                fs::remove(filePath);
            }
        }
    }
}

void MyManager::OnTabClose()
{
    tabOpen = false;
}


void MyManager::OnTabOpen()
{
    tabOpen = true;
}
