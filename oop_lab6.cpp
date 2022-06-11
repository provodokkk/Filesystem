#include <iostream>

#include "file_system.h"

int main()
{
    FileSystem* root = new Folder("Root");
    FileSystem* folder_1 = new Folder("Folder_1");
    FileSystem* folder_2 = new Folder("Folder_2");
    FileSystem* folder_3 = new Folder("Folder_3");

    FileSystem* file_1 = new File("File_1");
    FileSystem* file_2 = new File("File_2");
    FileSystem* file_3 = new File("File_3");

    folder_1->add(file_1);
    folder_1->add(file_2);

    //folder_2->add(folder_1);
    folder_2->add(file_3);
    folder_3->add(folder_1);

    root->add(folder_3);
    root->add(folder_2);

    // 1
    cout << endl << "// 1" << endl;
    cout << file_3->get_path() << endl;

    // 2
    cout << endl << "// 2" << endl;
    FileSystem* file = root->get_from_folder(folder_1, "File_1");
    cout << file->get_name() << endl;

    // 3
    cout << endl << "// 3" << endl;
    FileSystem* take_root = file_1->get_root();
    cout << "take_root->get_name() - " << take_root->get_name() << endl;

    // 4
    cout << endl << "// 4" << endl;
    cout << "file_1->is_folder   - " << file_1->is_folder() << endl;
    cout << "folder_1->is_folder - " << folder_1->is_folder() << endl;

    // 5
    cout << endl << "// 5";
    file_1->get_attributes();

    // 6
    cout << endl << "// 6" << endl;
    FileSystem* folder_4 = new Folder("Folder_4");
    root->add(folder_4);
    cout << "folder_4 path - " << folder_4->get_path() << endl;

    // 7
    cout << endl << "// 7" << endl;
    FileSystem* file_4 = new File("File_4");
    folder_4->add(file_4);
    cout << "file_4 path -   " << file_4->get_path() << endl;

    // 8
    cout << endl << "// 8" << endl;
    root->modify(folder_4, 64);
    cout << "folder_4 size - " << folder_4->get_size() << endl;

    // 9
    cout << endl << "// 9" << endl;
    root->remove(folder_1);
    cout << "folder_1 path - " << folder_1->get_path() << endl;

    // 10
    cout << endl << "// 10" << endl;
    root->rename(folder_4, "Folder_4_new_name");
    cout << "folder_4->get_name() - " << folder_4->get_name() << endl;
    
    // 11
    cout << endl << "// 11" << endl;
    cout << "path to folder before transfer - " << folder_4->get_path() << endl;
    root->move(folder_2, folder_4);
    cout << "path to folder after transfer -  " << folder_4->get_path() << endl;

    // 12
    cout << endl << "// 12" << endl;
    FileSystem* copy_folder_4 = root->copy(folder_3, folder_4, "copy_folder_4");
    cout << copy_folder_4->get_path() << endl;

    // 13
    cout << endl << "// 13" << endl;
    FileSystem* file_5 = new File("File_5");
    FileSystem* file_6 = new File("File_6");
    file_5->set_size(4);
    file_6->set_size(16);

    folder_2->add(file_5);
    folder_2->add(file_6);

    auto collection = root->search_by_size(folder_2, 8, 16);

    for (auto& object : collection) {
        cout << object->get_name() << endl;
    }

    // 14
    cout << endl << "// 14" << endl;
    root->system_visualization();
    cout << endl << endl;

    return 0;
}