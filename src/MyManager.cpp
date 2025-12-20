#include <MyManager.h>
#include <wx/wx.h>

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

std::vector<wxComboBox*>& MyManager::GetSecondCondition()
{
    return second_condition;
}

void MyManager::searchFolder()
{

}

void MyManager::checkFile()
{

}

void MyManager::moveFile()
{

}

