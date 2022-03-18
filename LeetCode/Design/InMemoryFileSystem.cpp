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
#include <list>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

enum EntryType
{
    DIR_ENTRY,
    FILE_ENTRY
};

class InodeEntry 
{
private:
    string basename;
    EntryType type;
public:
    InodeEntry():basename(),type(EntryType::DIR_ENTRY){}
    InodeEntry(const string& name, EntryType in_type):
        basename(name),
        type(in_type)
        {}
    
    void set_data(string name, EntryType in_type)
    {
        basename = name;
        type = in_type;
    }
    virtual void addContentToFile(const string &content) {}
    virtual string readContentFromFile() {return "";}
    virtual list<string> get_sub_dirs_files() {return {};}
    virtual void add_sub_dir(const string &sub_dir){};
    EntryType getEntryType() {return type;};
    string getBaseName() {return basename;};

    virtual ~InodeEntry() {};
};

class Directory : public InodeEntry
{
private:
    list<string> sub_dirs_files;

public:
    Directory():
        InodeEntry(),
        sub_dirs_files()
     {}

    Directory(const string& name, const EntryType& in_type):
        InodeEntry(name,in_type),
        sub_dirs_files()
        {}

    virtual ~Directory(){};

    list<string> get_sub_dirs_files() final
    {
        // the sub_dirs are already sorted based on 
        return sub_dirs_files;
    }

    void add_sub_dir(const string &sub_dir) final
    {
        if (sub_dir.empty())
            return;

        // Insert in appropriate position based on lexographic order
        auto iter = find_if(sub_dirs_files.begin(),sub_dirs_files.end(),
                    [&](const auto& a)
                    {
                        return a > sub_dir;
                    });
        
        sub_dirs_files.insert(iter,sub_dir);
        
    }
};

class File : public InodeEntry
{
private:
    string file_content;

public:
    File():
        InodeEntry(),
        file_content()
     {}

    File(const string& name, const EntryType& in_type):
        InodeEntry(name,in_type),
        file_content()
        {}

    virtual ~File(){};


    void addContentToFile(const string &content)  final
    {
        file_content += content;
    }

    string readContentFromFile() final
    {
        return file_content;
    }

};

class FileSystem
{
private:
    string root;
    unordered_map<string, unique_ptr<InodeEntry>> inode_map;

public:
    FileSystem() : inode_map(),root("/")
    {
        unique_ptr<InodeEntry> root_ptr = make_unique<Directory>(root,EntryType::DIR_ENTRY);

        inode_map.emplace(root, std::move(root_ptr));
    }

    ~FileSystem(){};

    void mkdir(const string &path)
    {
        stringstream ss(path);
        string basename;

        string curr_path = "";
        while (getline(ss, basename, '/'))
        {
            if (basename.empty())
            {
                continue;
            }
            if (curr_path.empty())
            {
                inode_map[root]->add_sub_dir(basename);
            }
            else
            {
                inode_map[curr_path]->add_sub_dir(basename);
            }
            curr_path += "/" + basename;
            auto f_ptr = inode_map.find(curr_path);

            if (f_ptr == inode_map.end())
            {
                unique_ptr<InodeEntry> dir = make_unique<Directory>(basename,EntryType::DIR_ENTRY);
                inode_map.emplace(curr_path, std::move(dir));
            }
        }
    }

    list<string> ls(const string &full_path)
    {
        auto iter = inode_map.find(full_path);
        if (iter != inode_map.end())
        {
            InodeEntry* entry = iter->second.get();
            if(entry->getEntryType() == EntryType::FILE_ENTRY)
            {
                return {entry->getBaseName()};
            }
            else
            {
                return iter->second->get_sub_dirs_files();
            }           
        }


        return {};
    }

    void addContentToFile(const string &full_path, const string &content)
    {
        auto it = inode_map.find(full_path);

        if(it != inode_map.end())
        {
            it->second->addContentToFile(content);
            return;
        }

        auto delim_pos = full_path.rfind('/');
        auto f_name = full_path;
        if (delim_pos != string::npos)
        {
            f_name = full_path.substr(delim_pos + 1, full_path.length() - 1);
            auto dir_path = full_path.substr(0, delim_pos);
            if (!dir_path.empty())
            {
                inode_map[dir_path]->add_sub_dir(f_name);
            }
            else
            {
                inode_map[root]->add_sub_dir(f_name);
            }
        }
        else
        {
            inode_map[root]->add_sub_dir(f_name);
        }

        unique_ptr<InodeEntry> fil = make_unique<File>(f_name,EntryType::FILE_ENTRY);
        fil->addContentToFile(content);

        inode_map.emplace(full_path,std::move(fil));
    }

    string readContentFromFile(const string &full_path)
    {
        auto it = inode_map.find(full_path);

        if(it != inode_map.end())
        {
            return it->second->readContentFromFile();
        }

        return "";
    }   
};

namespace ListPrinter
{
    template<typename T>

    void print_list(const list<T> vec)
    {
        for_each(vec.begin(),
                 vec.end(),
                 [&](const auto& elem)
                 {
                     cout << elem << endl;
                 });
        
        cout << endl;

    }
} // namespace ListPrinter

int main(int argc, char const *argv[])
{
    FileSystem fs;

    auto vec = fs.ls("/");

    ListPrinter::print_list<string>(vec);

    fs.mkdir("/a/b/c");

    vec = fs.ls("/");

    ListPrinter::print_list<string>(vec);

    fs.addContentToFile("/a/b/c/d", "hello");

    fs.addContentToFile("/a/marion", "hello marion");
    fs.addContentToFile("/a/cedar", "hello cedar");
    fs.addContentToFile("/a/hiawath", "hello hiaw");
    fs.addContentToFile("/a/las", "hello vegas");

    vec = fs.ls("/a");

    ListPrinter::print_list<string>(vec);

    fs.addContentToFile("/las", "hello las baby");

    cout << fs.readContentFromFile("/a/b/c/d") << endl;
    vec = fs.ls("/");

    ListPrinter::print_list<string>(vec);

    cout << fs.readContentFromFile("/las") << endl;

    cout << fs.readContentFromFile("/a/las") << endl;

    vec = fs.ls("/a/las");

    ListPrinter::print_list<string>(vec);
    return 0;
}
