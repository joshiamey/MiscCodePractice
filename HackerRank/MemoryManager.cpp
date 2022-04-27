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
        void* block;
        bool available;
        memBlock():block(nullptr),available(true){};
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
:m_blocksize(block_size),
 m_poolSize(num_blocks * (sizeof(struct memBlock) + m_blocksize))
{
    try
    {
        memPool = ::operator new(m_poolSize);    
        for(unsigned long i = 0 ; i < num_blocks; ++i)
        {
            struct memBlock* mb = (struct memBlock* )((char *)memPool + i * (sizeof(struct memBlock) + m_blocksize));
            mb->available = true;
            // the void* block should point to address after entire struct address + sizeof(struct)
            mb->block = (void*)((char*)mb + sizeof(struct memBlock));
            blocks.push_front(mb);
        }
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Allocation of Mempool failed" << e.what() << '\n';
        throw;
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
    if(size > m_blocksize || memPool == nullptr)
    {
        return ::operator new(size);
    }

    if(!blocks.front()->available)
    {
        throw runtime_error("No block available in mem pool for allocation.\n");
    }

    auto mem_block = blocks.front();
    blocks.pop_front();
    mem_block->available = false;

    blocks.push_back(mem_block);

    use_map.emplace(mem_block->block,prev(blocks.end()));

    return mem_block->block;
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
            auto mb = use_block_iter->second ;
            (*mb)->available = true;
            memset((*mb)->block,0,m_blocksize);
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

MemoryManager mm(10,10);
class TestClass
{
private:
   
public:
    char test_buff[6];
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

    cout << sizeof(void*) << endl;
    return 0;
}
