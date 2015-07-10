#pragma once
#include <string>
#include "stdint.h"
#include <unordered_map>
#include "Utility/SuperFastHash.h"
#include "Utility/MemoryManager/MemoryManager.h"
namespace WickedSick
{

 

  template <typename Key, typename Type>
  class HashMap
  {
  public:

    template<typename T> 
    static const char* ToCharStar(const T& type)
    {
      return const_cast<const char*>(reinterpret_cast<char*>(&type));
    }

    template<typename T> 
    static const char* ToCharStar(const T* type)
    {
      return ToCharStar(*type);
    }
    template<typename T> 
    static const char* ToCharStar(const T*& type)
    {
      return ToCharStar(*type);
    }

    template <>
    static const char* ToCharStar<std::string>(const std::string& type)
    {
      return type.c_str();
    }


    class Entry
    {
    public:
      Entry(Key& myKey, 
            Type& myType)
            : key(myKey),
              type(myType)
      {
      }

      Entry(const Entry& entry)
            : key(entry.key),
              type(entry.type)
      {
      }

      Key& key;
      Type& type;
    };

    class Slot
    {
    public:

      Slot()  : hash_(0),
                index_(-1),
                next_(nullptr),
                prev_(nullptr)
      {
      }

      Slot( Key key, 
            Type type)
            : key_(key),
              type_(type),
              index_(-1),
              next_(nullptr),
              prev_(nullptr)
      {
        hash_ = SuperFastHash(ToCharStar(key_), sizeof(key_));
      }

      Slot(Entry entry)
            : key_(entry.key),
              type_(entry.type),
              index_(-1),
              next_(nullptr),
              prev_(nullptr)
      {
        hash_ = SuperFastHash(ToCharStar(key_), sizeof(key_));
      }

      Slot(const Slot& slot)
            : key_(slot.key_),
              type_(slot.type_),
              hash_(slot.hash_),
              index_(slot.index_),
              next_(slot.next_),
              prev_(slot.prev_)
      {

      }

      Key key_;
      Type type_;
      uint32_t hash_;
      int   index_;
      Slot* next_;
      Slot* prev_;
    };

    class Iterator
    {
    public:
      Iterator()  : type_(nullptr)
      {
        
      }

      Iterator( Slot* slot ) 
                : type_(slot)
      {

      }

      Iterator(const Iterator& rhs) : type_(rhs.type_)
      {
        
      }

      Iterator& operator=(const Iterator& rhs)
      {
        type_ = rhs.type_;
      }

      bool operator==(const Iterator& rhs) const
      {
        return type_ == rhs.type_;
      }

      bool operator!=(const Iterator& rhs) const
      {
        return type_ != rhs.type_;
      }

      Iterator& operator++()
      {
        if (type_)
        {
          if (type_->next_)
          {
            type_ = type_->next_;
          }
          else
          {
            ConsolePrint("Incrementing End Iterator!", ConsoleRed);
            __debugbreak();
          }
        }
        else
        {
          ConsolePrint("Incrementing Invalid Iterator!", ConsoleRed);
        }
        return *this;
      }


      Iterator operator++(int)
      {
        if (type_)
        {
          Iterator toReturn(type_);
          
          if (type_->next_)
          {
            type_ = type_->next_;
          }
          else
          {
            ConsolePrint("Incrementing End Iterator!", ConsoleRed);
            __debugbreak();
          }
          return toReturn;
        }
        else
        {
          ConsolePrint("Incrementing Invalid Iterator!", ConsoleRed);
          __debugbreak();
        }
        return Iterator();
      }

      Iterator& operator--()
      {
        if (type_)
        {
          if (type_->prev_)
          {
            type_ = type_->prev_;
          }
          else
          {
            ConsolePrint("Incrementing End Iterator!", ConsoleRed);
            __debugbreak();
          }
        }
        else
        {
          ConsolePrint("Incrementing Invalid Iterator!", ConsoleRed);
          __debugbreak();
        }
        return *this;
      }

      Iterator operator--(int)
      {
        if (type_)
        {
          Iterator toReturn(type_);
          
          if (type_->prev_)
          {
            type_ = type_->prev_;
          }
          else
          {
            ConsolePrint("Incrementing End Iterator!", ConsoleRed);
            __debugbreak();
          }
          return toReturn;
        }
        else
        {
          ConsolePrint("Incrementing Invalid Iterator!", ConsoleRed);
          __debugbreak();
        }
        return Iterator();
      }


      Entry operator*()
      {
        if (type_)
        { 
          return Entry(type_->key_, type_->type_);
        }
      }

      bool is_valid()
      {
        return type_;
      }

      void _set(Slot* newSlot)
      {
        type_ = newSlot;
      }
    private:


      Slot* type_;
    };

    HashMap() : load_factor_(0.0f),
                max_load_factor_(0.85f),
                map_(nullptr),
                capacity_(0),
                size_(0),
                first_(-1),
                last_(-1)
    {
      end_._set(reinterpret_cast<Slot*>(end_slot_));
      reinterpret_cast<Slot*>(end_slot_)->prev_ = nullptr;
      reinterpret_cast<Slot*>(end_slot_)->next_ = nullptr;
    }

    HashMap(const HashMap<Key, Type>& rhs) : max_load_factor_(rhs.max_load_factor_)                 
    {
      resize(rhs.capacity_);
      for (auto& it : rhs)
      {
        insert(it);
      }
    }
    
    HashMap& operator=(const HashMap& rhs)
    {
      max_load_factor_ = rhs.max_load_factor_;
      resize(rhs.capacity_);
      for (auto& it : rhs)
      {
        insert(it);
      }
    }

    //size related
    size_t size()
    {
      return size_;
    }

    size_t capacity()
    {
      return capacity_;
    }

    size_t slots_left()
    {
      return static_cast<int>(max_load_factor_ * capacity_) - static_cast<int>(load_factor_ * capacity_);
    }

    bool empty()
    {
      return !size_;
    }

    //modifiers
    void clear()
    {
      size_ = 0;
      load_factor_ = 0.0f;
      for (auto& it : map_)
      {
        if (it)
        {
          manager_.Delete(it);
        }
      }
      first_ = last_ = invalid_index_;
    }
    
    void resize(size_t newSize)
    {
      size_t oldSize = capacity_;
      if (((float)size_ / (float)newSize) > max_load_factor_)
      {
        ConsolePrint("new size too small, use shrink_to_fit to compact size", ConsoleRed);
        return;
      }
      capacity_ = newSize;
      recalc_load_factor();
      
      Slot** oldMap = map_;
      map_ = new Slot*[capacity_];

      for (unsigned i = 0; i < oldSize; ++i)
      {
        insert(oldMap[i]);
      }
      delete[] oldMap;
    }

    Iterator insert(Entry& elem)
    {
      ++size_;
      recalc_load_factor();
      if (load_factor_ >= max_load_factor_)
      {
        resize(static_cast<size_t>(capacity_ * max_load_factor_));
      }
      int index = SuperFastHash(ToCharStar(elem.key), sizeof(elem.key)) % capacity_;
      if (map_[index])
      {
        if (map_[index]->key_ == elem.key)
        {
          ConsolePrint("TWO ELEMENTS WITH THE SAME KEY!! PANIC!!", ConsoleRed);
          --size_;
          return begin();
        }

        for (int i = index + 1; i != index; index = (index + 1) % capacity_)
        {
          if (!map_[i])
          {
            map_[i] = manager_.New(elem);
            map_[i]->index_ = i;
            return Iterator(map_[i]);
          }
        }
      }
      else
      {
        map_[index] = manager_.New(elem);
        map_[index]->index_ = index;
      }

      if (first_ == invalid_index_)
      {
        first_ = index;
        last_ = first_;
        map_[first_]->next_ = reinterpret_cast<Slot*>(end_slot_);
        map_[first_]->prev_ = nullptr;
      }
      else
      {
        map_[index]->prev_ = map_[last_];
        map_[index]->next_ = nullptr;
        map_[last_]->next_ = map_[index];
        last_ = index;
      }
      
      return Iterator(map_[index]);
    }

    Iterator insert(Iterator source)
    {
      return insert(*source);
    }

    Iterator insert(Slot& source)
    {
      return insert(Entry(source.key_, source.type_));
    }

    Iterator erase(Iterator what)
    {
      return erase((*what).key_);
    }

    Iterator erase(Key what)
    {
      int index = SuperFastHash(what) % capacity_;
      
      Iterator toReturn;
      if (map_[index])
      {

        if (map_[index]->next_ && map_[index]->prev_)
        {
          toReturn = Iterator(map_[index]->prev_);
          map_[index]->next_->prev_ = map_[index]->prev_;
          map_[index]->prev_->next_ = map_[index]->next_;
          
        }
        else if (!map_[index]->next_ && map_[index]->prev_)
        {
          toReturn = Iterator(map_[index]->prev_);
          toReturn = map_[index]->prev_->index_;
          last_ = map_[index]->prev_->index_;
          map_[index]->prev_->next_ = map_[index]->next_;
        }
        else if (map_[index]->next_ && !map_[index]->prev_)
        {
          
          first_ = map_[index]->next_->index_;
          map_[index]->next_->prev_ = map_[index]->prev_;
          toReturn = begin();
        }
        else
        {
          toReturn = begin();
          last_ = first_ = invalid_index_;
        }

        manager_.Delete(map_[index]);
        
        
        --size_;
        recalc_load_factor();
        return toReturn;
      }
      ConsolePrint("Element with this key could not be found.", ConsoleRed);
      return end();
    }



    Iterator begin() const
    {
      if (map_)
      {
        if (first_ != invalid_index_)
        {
          return Iterator(map_[first_]);
        }
      }
      return end();
      
    }

    Iterator const& end() const
    {
      return end_;
    }

    //iterator at(Hash key);

    Type& operator[](Key key)
    {
      size_t index = SuperFastHash(key, sizeof(Key)) % capacity_;
      if (map_[index])
      {
        return map_[index]->type_;
      }
      else
      {
        ConsolePrint("Invalid key in Hash Map", ConsoleRed);
        __debugbreak();
      }
    }

    Iterator find(Key key)
    {
      size_t index = SuperFastHash(key, sizeof(Key)) % capacity_;
      if (map_[index])
      {
        return Iterator(map_[index]);
      }
      else
      {
        ConsolePrint("Invalid key in Hash Map", ConsoleRed);
        return end();
      }
    }

    bool operator==(const HashMap<Key, Type>& rhs)
    {
      for (int i = 0; i < capacity_; ++i)
      {
        if ((rhs.map_[i]->key_ != map_[i]->key_) ||
            (rhs.map_[i]->type_ != map_[i]->type_))
        {
          return false;
        }
      }
    }

    bool operator!=(const HashMap<Key, Type>& rhs)
    {
      return !(rhs == *this);
    }

    float load_factor()
    {
      return load_factor_;
    }


  private:

    void recalc_load_factor()
    {
      load_factor_ = (float)size_ / (float)capacity_;
    }

    const int invalid_index_ = -1;

    float   load_factor_;
    float   max_load_factor_;
    size_t  capacity_;
    size_t  size_;
    size_t  slot_number_;

    Iterator end_;
    char end_slot_[sizeof(Slot)];

    MemoryManager<Slot> manager_;
    int     first_;
    int     last_;
    Slot**  map_;
  };
}


