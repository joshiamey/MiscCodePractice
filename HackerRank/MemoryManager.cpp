#include <iostream>
#include <memory>
#include <list>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cstdint>

using namespace std;

class MemoryManager
{

private:
    struct memBlock
    {
        bool available;
        memBlock():available(true){};
    };
    size_t m_blocksize;
    size_t m_poolSize;
    std::list<memBlock*> blocks;
    unordered_map<void*,list<memBlock*>::iterator> use_map;
    void* memPool;
public:
    MemoryManager(unsigned long num_blocks = 50,unsigned long block_size = 1024);
    ~MemoryManager();
    void createPool(long size);
    void* allocate(unsigned long size);
    void deallocate(void* free_ptr);
};

MemoryManager::MemoryManager(unsigned long num_blocks,unsigned long block_size)
{
    m_blocksize = block_size;
    m_poolSize = num_blocks * (m_blocksize + sizeof(struct memBlock));
    memPool = ::operator new(m_poolSize);

    void* curr = memPool;
    if(memPool)
    {
        for(unsigned long i = 0 ; i < num_blocks; ++i)
        {
            struct memBlock* mb = (struct memBlock* )((char *)curr + i * (m_blocksize + sizeof(struct memBlock)));
            mb->available = true;
            blocks.push_front(mb);
        }
    }
}

MemoryManager::~MemoryManager()
{
    if(memPool)
    {
        ::operator delete(memPool);
        memPool = nullptr;
    }    
}

void* MemoryManager::allocate(unsigned long size)
{
    if(!blocks.front()->available)
    {
        throw runtime_error("No block available in mem pool for allocation.\n");
    }

    if(size > m_blocksize || memPool == nullptr)
    {
        return ::operator new(size);
    }
    void* alloc_block;
    auto mem_block = blocks.front();
    blocks.pop_front();
    mem_block->available = false;

    blocks.push_back(mem_block);

    alloc_block = (void*)((char*)mem_block + sizeof(struct memBlock));
    use_map.emplace(alloc_block,prev(blocks.end()));

    return alloc_block;
}

void MemoryManager::deallocate(void* ptr)
{
    void* end = (void *)((char *)memPool + m_poolSize);
    // check the given pointer is within the memPool boundary
    if(memPool < ptr && ptr < end)
    {
        auto use_block_iter = use_map.find(ptr);

        if(use_block_iter != use_map.end())
        {
            // (*use_block_iter->second)->available = true;
            auto mb = use_block_iter->second ;
            (*mb)->available = true;
            
            // available now, move the block to the front of the list
            blocks.splice(blocks.begin(),blocks,use_block_iter->second);

            use_map.erase(use_block_iter);
        }
    }
    else
    {
        ::operator delete(ptr);
    }
    
}

MemoryManager mm(10,2048 * sizeof(char));
class TestClass
{
private:
   
public:
    char test_buff[2048];
    void * operator new(unsigned long size)
    {
        return mm.allocate(size);
    }

    void operator delete(void *p)
    {
        mm.deallocate(p);
    }
};


int main(int argc, char const *argv[])
{
   
    TestClass* tp = new TestClass;

    strncpy(tp->test_buff,"abcd",sizeof("abcd"));
    delete tp;
    return 0;
}
