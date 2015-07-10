#pragma once

#include <utility>
#include <type_traits>

#ifdef _DEBUG

#define PADSIZE 4
#else
#define PADSIZE 0
#endif
namespace WickedSick
{

  template <typename Type, int ElementsPerPage = 20>
  class MemoryManager
  {
  public:


    // page class
    class Page
    {
    public:

      struct Object
      {
        Object()
        {

        }
        enum MemState
        {
          Padding = 0xDD,
          Uninitialized = 0xCD,
          Allocated = 0xFF,
          Unallocated = 0xAA,
          Deleted = 0xFE
        };

        MemState state;
        //const char prePad[5]  = {[0 ... (5 - 1)] = Padding};
        char object[sizeof(Type)];
        //const char postPad[5] = {[0 ... (5 - 1)] = Padding};
      };


      Page() : allocated_objects_(0)
      {
        for (auto& it : object_pool_)
        {
          it.state = Object::Unallocated;
          #ifdef _DEBUG
            memset(it.object, Object::Unallocated, sizeof(it.object));
          #endif
        }
      }

      Page(const Page& rhs);

      bool HasSpace()
      {
        return allocated_objects_ < ElementsPerPage;
      }

      Type* Allocate()
      {
        Type* toReturn = nullptr;
        if (HasSpace())
        {
          int i = 0;
          while (object_pool_[i].state == Object::Allocated)
          {
            ++i;
          }

          toReturn = (Type*)&(object_pool_[i].object);//first get our pointer

          object_pool_[i].state = Object::Allocated;//set the state to allocated

          ++allocated_objects_;
        }
        return toReturn;
      }

      void Deallocate(Type* toDelete)
      {
        Object* object = ((char*)toDelete) - (PADSIZE + sizeof(Object::MemState));
        
        switch (object->state)
        {
        case Object::Deleted:
          __debugbreak();//double delete!
          break;
        case Object::Unallocated:
          __debugbreak();//how did you even get this pointer what
          break;
        case Object::Allocated:
          object->state = Object::Deleted;
          memset(object->object, Object::Deleted, sizeof(Type));
          --allocated_objects_;
          break;
        default:
          __debugbreak();
          //dude you're doing some weird ass shit here....
        }
        
      }

      Object* GetObjectPool()
      {
        return &object_pool_[0];
      }

    private:
      Object object_pool_[ElementsPerPage];
      int allocated_objects_;

    };
    //end page class




    MemoryManager()
    {
      page_pool_.push_back(new Page());
    }

    MemoryManager(const MemoryManager& rhs);//unimplemented for good reason
    ~MemoryManager()
    {
      //delete stuff!
      for (auto& it : page_pool_)
      {
        delete it;
      }
    }

    size_t BytesBetween()
    {
      return sizeof(Object);
    }

    template<typename ...Types>
    Type* New(const Types&... herp)
    {
      
      Type* newObject = nullptr;
      for (auto it : page_pool_)
      {
        newObject = it->Allocate();
        if (newObject)
        {
          return newObject;
        }
      }

      page_pool_.push_back(new Page());
      ++pages_allocated_;
      ++pages_active_;
      newObject = page_pool_.back()->Allocate();
      new (newObject) Type(herp...);
      return newObject;
    }


    //Type* New()
    //{
    //  Type* newObject = nullptr;
    //  for (auto it : page_pool_)
    //  {
    //    newObject = it->Allocate();
    //    if (newObject)
    //    {
    //      return newObject;
    //    }
    //  }
    //  page_pool_.push_back(new Page());
    //  ++pages_allocated_;
    //  ++pages_active_;
    //  return page_pool_.back()->Allocate();
    //}

    void Delete(Type* type)
    {
      //call destructor
      type->~Type();

      char* basicPtr = (char*)type;
      char* pagePtr;
      for (auto& it : page_pool_)
      {
        pagePtr = (char*)it->GetObjectPool();
        if ((basicPtr > pagePtr) &&
            (basicPtr < (pagePtr + sizeof(Page))))
        {
          it->Deallocate(type);
          ++total_deletions_;
          --currently_allocated_;
          return;
        }
      }
      __debugbreak();
      //NOT A VALID POINTER
    }


  private:

    int currently_allocated_;
    int total_allocations_;
    int total_deletions_;
    int pages_allocated_;
    int pages_active_;
    

    std::vector<Page*> page_pool_;

  };
}