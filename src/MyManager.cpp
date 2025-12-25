#include <MyManager.h>

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

std::vector<wxComboBox*>& MyManager::GetMoveOption()
{
    return move_options;
}

std::vector<wxTextCtrl*>& MyManager::GetMoveFolder()
{
    return move_folders;
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

