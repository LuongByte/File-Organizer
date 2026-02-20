#include <MyManager.h>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

MyManager::MyManager()
{

}



std::vector<wxTextCtrl*>& MyManager::GetSelectFolder()
{
    return search_folders;
}

std::vector<wxComboBox*>& MyManager::GetFirstCondition()
{
    return first_condition;
}

std::vector<wxTextCtrl*>& MyManager::GetSecondCondition()
{
    return second_condition;
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
    if(!fs::exists(testDest))
        fs::create_directories(testDest);
}

void MyManager::moveFile(const std::vector<std::string>& folderLocations, const fs::path& testDest)
{
    for(const auto&folder : folderLocations){
            // printf("%s", input.c_str());    
            for(const auto& file : fs::directory_iterator(folder)){
                const fs::path& filePath = file.path();
                if(fs::is_regular_file(filePath)){
                    fs::path newLocation = testDest/filePath.filename();  
                    if(fs::exists(newLocation))             
                        fs::remove(newLocation);
                    fs::rename(filePath, newLocation);
                }
            }
        }
}

