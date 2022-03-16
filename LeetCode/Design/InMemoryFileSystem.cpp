/*
Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. If it is a directory path, return the list of file and directory names in this directory. Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory according to the path. If the middle directories in the path don't exist either, you should create them as well. This function has void return type.

addContentToFile: Given a file path and file content in string format. If the file doesn't exist, you need to create that file containing given content. If the file already exists, you need to append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

Example 1:
Input:
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
Output: [null,[],null,null,["a"],"hello"]
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

enum FileType
{
    Directory,
    File
};

class Files
{
private:
    string basename;
    FileType type;
    unordered_map<string, string> file_content;
    vector<string> sub_dirs_files;

public:
    Files() : basename(),
              type(),
              file_content(),
              sub_dirs_files(){};
    Files(string name, FileType in_type) : basename(name),
                                           type(in_type),
                                           file_content(),
                                           sub_dirs_files(){};

    ~Files(){};

    void set_data(string name, FileType in_type)
    {
        basename = name;
        type = in_type;
    }

    void addContentToFile(const string &f_name, const string &content)
    {
        auto file_name = file_content.find(f_name);

        if (file_name != file_content.end())
        {
            file_name->second += content;
            return;
        }

        sub_dirs_files.push_back(f_name);
        file_content.emplace(f_name, content);
    }

    string readContentFromFile(const string &f_name)
    {
        return file_content[f_name];
    }

    vector<string> list_sub_dirs_files()
    {
        sort(sub_dirs_files.begin(),sub_dirs_files.end());
        return sub_dirs_files;
    }

    void add_sub_dir(const string &sub_dir)
    {
        if (sub_dir.empty())
            return;
        sub_dirs_files.push_back(sub_dir);
    }
};

class FileSystem
{
private:
    Files root_directory;
    unordered_map<string, Files> inode_map;

public:
    FileSystem() : root_directory("/", FileType::Directory),
                   inode_map()
    {
        inode_map.emplace("/", root_directory);
    }

    ~FileSystem(){};

    void mkdir(const string &path)
    {
        stringstream ss(path);
        string basename;

        Files &ab = inode_map["/"];
        string curr_path = "";
        while (getline(ss, basename, '/'))
        {
            if (basename.empty())
            {
                continue;
            }
            if (curr_path.empty())
            {
                inode_map["/"].add_sub_dir(basename);
            }
            else
            {
                inode_map[curr_path].add_sub_dir(basename);
            }
            curr_path += "/" + basename;
            auto f_ptr = inode_map.find(curr_path);

            if (f_ptr == inode_map.end())
            {
                Files dir(basename, FileType::Directory);
                inode_map.emplace(curr_path, dir);
            }
        }
    }

    vector<string> ls(const string &full_path)
    {
        auto iter = inode_map.find(full_path);
        vector<string> result;
        if (iter != inode_map.end())
        {
            return iter->second.list_sub_dirs_files();
        }
        else
        {
            // its a file , just return the string from last slash to end
            auto delim_pos = full_path.rfind('/');
            result.push_back(full_path.substr(delim_pos + 1, full_path.length() - 1));
        }

        return result;
    }

    void addContentToFile(const string &full_path, const string &content)
    {
        auto delim_pos = full_path.rfind('/');
        auto f_name = full_path;
        if (delim_pos != string::npos)
        {
            f_name = full_path.substr(delim_pos + 1, full_path.length() - 1);
            auto dir_path = full_path.substr(0, delim_pos);
            if (!dir_path.empty())
            {
                inode_map[dir_path].addContentToFile(f_name, content);
            }
            else
            {
                root_directory.addContentToFile(f_name, content);
            }
        }
        else
        {
            root_directory.addContentToFile(f_name, content);
        }
    }

    string readContentFromFile(const string &full_path)
    {
        auto delim_pos = full_path.rfind('/');

        if (delim_pos != string::npos)
        {
            auto f_name = full_path.substr(delim_pos + 1, full_path.length() - 1);
            auto dir_path = full_path.substr(0, delim_pos);
            if (!dir_path.empty())
            {
                return inode_map[dir_path].readContentFromFile(f_name);
            }
            else
            {
                return root_directory.readContentFromFile(f_name);
            }
        }

        return root_directory.readContentFromFile(full_path);
    }
};

int main(int argc, char const *argv[])
{
    FileSystem fs;

    auto vec = fs.ls("/");

    cout << "vec: " << vec.size() << endl;

    fs.mkdir("/a/b/c");

    fs.addContentToFile("/a/b/c/d", "hello");

    fs.addContentToFile("/a/marion", "hello marion");
    fs.addContentToFile("/a/cedar", "hello cedar");
    fs.addContentToFile("/a/hiawath", "hello hiaw");
    fs.addContentToFile("/a/las", "hello vegas");

    vec = fs.ls("/");

    cout << "vec: " << vec.size() << endl;

    vec = fs.ls("/a");

    cout << "vec: " << vec.size() << endl;

    cout << fs.readContentFromFile("/a/b/c/d") << endl;

    return 0;
}
