#ifndef __POOL_HPP__
#define __POOL_HPP__

#include <vector>

template <typename TType>
class Pool
{
    private :

    std::vector<TType*> freeSlots;
    TType* memoryBlock;

    public :

    class Object
    {
        public :
        
        TType* data;

        TType* operator->();
    };

    ~Pool()
    {
        operator delete(memoryBlock);
    }

    void resize(const std::size_t& numberOfObjectStored)
    {
        void* temp = operator new(numberOfObjectStored * sizeof(TType));

        memoryBlock = static_cast<TType*>(temp);
    }

    template<typename... TArgs> 
    Object acquire(TArgs&&... p_args)
    {
        if (freeSlots.empty())
            return Object();

        TType* slot = freeSlots.back();
        freeSlots.pop_back();

        new (slot) TType(std::forward<TArgs>(p_args)...); 

        Object object;
        object.data = slot;

        return object;
    }
};

#endif
