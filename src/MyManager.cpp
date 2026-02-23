#include <MyManager.h>
#include <filesystem>
#include <iostream>
#include <wx/datectrl.h>

namespace fs = std::filesystem;

struct RowWidgets
{
    wxDatePickerCtrl* datePicker;
    wxTextCtrl* fileType;
};


MyManager::MyManager()
{

}



std::vector<wxTextCtrl*>& MyManager::GetSelectFolder()
{
    return search_folders;
}

std::vector<wxComboBox*>& MyManager::GetCondition()
{
    return check_condition;
}

std::vector<wxComboBox*>& MyManager::GetMoveOption()
{
    return move_options;
}

std::vector<wxTextCtrl*>& MyManager::GetMoveFolder()
{
    return move_folders;
}

void MyManager::manageFiles()
{
    fs::path testDest = "C:/Users/Conta/OneDrive/Desktop/Career/Personal Projects/File-Organizer/Move";   
    std::vector<std::string> folderLocations = searchFolder();
    try{
        checkFile(testDest);
        moveFile(folderLocations, testDest);
    }
    catch(const fs::filesystem_error& e){}
}

std::vector<std::string> MyManager::searchFolder()
{   
    std::vector<std::string> folderLocations;
    for(const auto&input : search_folders){
        folderLocations.push_back((input->GetValue()).ToStdString(wxConvUTF8));
    }   
    return folderLocations;
}
 
void MyManager::checkFile(const fs::path& testDest)
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
    

    
    if(!fs::exists(testDest))
        fs::create_directories(testDest);
}

bool MyManager::matchesConditions(const fs::path& filePath)
{
    bool hasFileTypeCondition = false;
    bool fileTypeMatched = false;

    bool hasDateCondition = false;
    bool dateMatched = false;

    for (const auto& condition : activeConditions){
        if(condition.type == "File Type"){
            hasFileTypeCondition = true;
            std::string ext = filePath.extension().string();
            if(ext == condition.fileExt)
                fileTypeMatched = true;
        }
        else if (condition.type == "Date Modified"){
            hasDateCondition = true;
            std::filesystem::file_time_type fileTime = fs::last_write_time(filePath);
            std::chrono::system_clock::time_point timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>
                                                            (fileTime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
            std::time_t clockFileTime = std::chrono::system_clock::to_time_t(timePoint);
            wxDateTime fileDate(clockFileTime);

            if (fileDate.FormatISODate() == condition.date.FormatISODate())  
                dateMatched = true;
        }
    }
    if(hasFileTypeCondition && !fileTypeMatched)
        return false;

    if(hasDateCondition && !dateMatched)
        return false;

    return true;
}

void MyManager::moveFile(const std::vector<std::string>& folderLocations, const fs::path& testDest)
{
    for(const auto& folder : folderLocations){
        for(const auto& file : fs::directory_iterator(folder)){
            const fs::path& filePath = file.path();
            if(fs::is_regular_file(filePath)){
                if(matchesConditions(filePath) == false)
                    continue;
                fs::path newLocation = testDest / filePath.filename();
                if(fs::exists(newLocation))
                    fs::remove(newLocation);
                fs::rename(filePath, newLocation);
            }
        }
    }
}

