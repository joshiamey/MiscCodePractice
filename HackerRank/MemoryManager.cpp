#include <iostream>
#include <memory>
#include <list>
#include <unordered_map>
using namespace std;

class MemoryManager
{
struct memBlock
{
    void* block;
    bool available;
    memBlock(void* ptr):block(ptr),available(true){};
};

private:
    size_t blockSize;
    std::list<memBlock> blocks;
    unordered_map<void*,list<memBlock>::iterator> use_map;
    void* memPool;
public:
    MemoryManager(/* args */);
    ~MemoryManager();

    void createPool(long size);
    void* allocate();
    void deallocate(void* free_ptr);
};

MemoryManager::MemoryManager(/* args */):blockSize(4096)
{
}

MemoryManager::~MemoryManager()
{
    if(memPool)
    {
        ::operator delete(memPool);
        memPool = nullptr;
    }    
}

void MemoryManager::createPool(long size)
{
    if(!memPool)
    {
        memPool = ::operator new(sizeof(char) * size);
    }

    auto numBlocks = size / blockSize;

    void* curr = memPool;

    for(int i = 0 ; i < numBlocks; ++i)
    {
        blocks.emplace_back(curr);
        curr = curr + blockSize;
    }
}

void* MemoryManager::allocate()
{
    if(!blocks.front().available)
    {
        throw runtime_error("No block available in mem pool for allocation.\n");
    }

    auto mem_block = blocks.front();
    blocks.pop_front();
    mem_block.available = false;

    blocks.push_back(mem_block);

    use_map.emplace(mem_block.block,prev(blocks.end()));

    return mem_block.block;
}

void MemoryManager::deallocate(void* ptr)
{
    auto use_block_iter = use_map.find(ptr);

    if(use_block_iter != use_map.end())
    {
        use_block_iter->second->available = true;
        // move the list iterator to the front as its 
        // available now
        blocks.splice(blocks.begin(),blocks,use_block_iter->second);

        use_map.erase(use_block_iter);
    }
    
}


int main(int argc, char const *argv[])
{
    MemoryManager mm;

    mm.createPool(512 * 1000);
    double arr[514];

    void* ptr1 = mm.allocate();
    cout << sizeof(ptr1) << endl;
    ptr1 = &arr;
    void* ptr2 = mm.allocate();
    void* ptr3 = mm.allocate();

    mm.deallocate(ptr2);

    return 0;
}
