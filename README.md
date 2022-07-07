<a id = "anchor_6"></a>
# File system

__Content list__
1. [About the program](#anchor_1)
2. [What is implemented in the program](#anchor_2)
3. [What technologies were used](#anchor_3)
4. [Some features of the code](#anchor_4)
5. [Program execution example](#anchor_5)

---
<a id = "anchor_1"></a>
### About the program
This project simulates the operation of the file system (hierarchy of files and folders).

<a id = "anchor_2"></a>
### What is implemented in the program
>- *All operations take into account that folders can be non-empty*

- Getting file/folder by full path
- Getting a file/folder by name in a given folder
- Getting the root folder
- Defining an object is a file or folder
- Getting file/folder attributes (name, creation date, last modification date, size, for folders number of nested elements (directly and in general))
- Adding a new folder
- Adding a new file
- File modification
- Deleting a file/folder
- Rename file/folder
- Transfer file/folder to some folder
- Copy file/folder
- Search all nested items in a folder by name and size
- Display folder structure


<a id = "anchor_3"></a>
### What technologies were used
- Pattern builder
- Pattern iterator


<a id = "anchor_4"></a>
### Some features of the code
- The root for everything is a folder, which must be created first and add unrelated elements to it
- For more convenient work with dates, a separate Date class was written, which includes methods for setting, getting and modifying the creation/modification time of a file system element.

<a id = "anchor_5"></a>
### Program execution example
![image](https://user-images.githubusercontent.com/105476685/177817809-78b0eec3-7045-4ab0-8544-e61e3c48c0b7.png)

[↑ UP ↑](#anchor_6)
