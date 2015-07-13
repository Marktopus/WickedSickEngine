#pragma once
#include <string>
#include "stdint.h"
#include <unordered_map>
#include "Utility/SuperFastHash.h"
#include "Utility/MemoryManager/MemoryManager.h"
#include "Debugging/DebugInterface.h"
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

    template<typename T> 
    static uint32_t HashType(T val)
    {
      const char* str = ToCharStar(val);
      return SuperFastHash(str, strlen(str));
    }

    class Entry
    {
    public:
      Entry() : key(*new Key()),
                type(*new Type())
      {
        WSError("Something in the HashMap broke. I sure hope you don't plan on commenting this out....");
      }

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

      Slot( const Key& key, 
            const Type& type)
            : key_(key),
              type_(type),
              index_(-1),
              next_(nullptr),
              prev_(nullptr)
      {
        hash_ = HashMap<Key, Type>::HashType(key_);
      }

      Slot(const Entry& entry)
            : key_(entry.key),
              type_(entry.type),
              index_(-1),
              next_(nullptr),
              prev_(nullptr)
      {
        hash_ = HashMap<Key, Type>::HashType(key_);
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
        return *this;
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
        WSAssert(type_, "Incrementing Invalid Iterator!");
        WSAssert(type_->next_, "Incrementing End Iterator!");
        type_ = type_->next_;
        return *this;
      }


      Iterator operator++(int)
      {
        WSAssert(type_, "Incrementing Invalid Iterator!");
        WSAssert(type_->next_, "Incrementing End Iterator!");
        Iterator toReturn(type_);
        type_ = type_->next_;
        return toReturn;
      }

      Iterator& operator--()
      {
        WSAssert(type_, "Decrementing Invalid Iterator!");
        WSAssert(type_->next_, "Decrementing Begin Iterator!");
        type_ = type_->prev_;
        return *this;
      }

      Iterator operator--(int)
      {
        WSAssert(type_, "Decrementing Invalid Iterator!");
        WSAssert(type_->next_, "Decrementing Begin Iterator!");
        Iterator toReturn(type_);
        type_ = type_->prev_;
        return toReturn;
      }


      Entry operator*() const
      {
        WSAssert(type_, "Content of Invalid Iterator!");
        return Entry(type_->key_, type_->type_);
      }

      bool is_valid() const
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

    class ConstIterator
    {
    public:
      ConstIterator() : type_(nullptr)
      {
        
      }

      ConstIterator(Slot* slot ) 
                    : type_(slot)
      {

      }

      ConstIterator(const ConstIterator& rhs) : type_(rhs.type_)
      {
        
      }

      ConstIterator& operator=(const ConstIterator& rhs)
      {
        type_ = rhs.type_;
        return *this;
      }

      bool operator==(const ConstIterator& rhs) const
      {
        return type_ == rhs.type_;
      }

      bool operator!=(const ConstIterator& rhs) const
      {
        return type_ != rhs.type_;
      }

      ConstIterator& operator++()
      {
        WSAssert(type_, "Incrementing Invalid Iterator!");
        WSAssert(type_->next_, "Incrementing End Iterator!");
        type_ = type_->next_;
        return *this;
      }


      ConstIterator operator++(int)
      {
        WSAssert(type_, "Incrementing Invalid Iterator!");
        WSAssert(type_->next_, "Incrementing End Iterator!");
        ConstIterator toReturn(type_);
        type_ = type_->next_;
        return toReturn;
      }

      ConstIterator& operator--()
      {
        WSAssert(type_, "Decrementing Invalid Iterator!");
        WSAssert(type_->prev_, "Decrementing Begin Iterator!");
        type_ = type_->prev_;
        return *this;
      }

      ConstIterator operator--(int)
      {
        WSAssert(type_, "Decrementing Invalid Iterator!");
        WSAssert(type_->prev_, "Decrementing Begin Iterator!");
        ConstIterator toReturn(type_);
        type_ = type_->prev_;
        return toReturn;
      }


      const Entry operator*() const
      {
        WSAssert(type_, "Taking content of invalid iterator");
        return Entry(type_->key_, type_->type_);
      }

      bool is_valid() const
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
      reinterpret_cast<Slot*>(end_slot_)->index_ = -1;
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

    ~HashMap()
    {
      for (size_t i = 0; i < capacity_; ++i)
      {
        if (map_[i])
        {
          manager_.Delete(map_[i]);
        }
        
      }
      delete[] map_;
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
      memset(map_, 0, capacity_ * sizeof(Slot*));

      size_ = 0;
      last_ = first_ = invalid_index_;
      for (unsigned i = 0; i < oldSize; ++i)
      {
        if (oldMap[i])
        {
          insert(oldMap[i]);
        }
        
      }
      delete[] oldMap;
    }

    Iterator insert(const Key& key, const Type& type)
    {
      recalc_load_factor();
      if (load_factor_ >= max_load_factor_)
      {
        resize(static_cast<size_t>(std::max(8.0f, capacity_ * (1.0f + max_load_factor_))));
      }
      ++size_;
      int index = HashType(key) % capacity_;
      if (map_[index])
      {
        if (map_[index]->key_ == key)
        {
          return Iterator(map_[index]);
        }
        else
        {
          for (int i = index + 1; i != index; i = (i + 1) % capacity_)
          {
            if (!map_[i])
            {
              map_[i] = manager_.New(key, type);
              map_[i]->index_ = i;
              index = i;
              break;
            }
          }
        }
      }
      else
      {
        map_[index] = manager_.New(key, type);
        map_[index]->index_ = index;
      }

      if (first_ == invalid_index_)
      {
        first_ = index;
        last_ = first_;
        map_[last_]->next_ = reinterpret_cast<Slot*>(end_slot_);
        map_[first_]->prev_ = nullptr;
        reinterpret_cast<Slot*>(end_slot_)->prev_ = map_[last_];
      }
      else
      {
        map_[index]->prev_ = map_[last_];
        map_[last_]->next_ = map_[index];
        last_ = index;
        map_[last_]->next_ = reinterpret_cast<Slot*>(end_slot_);
      }
      
      return Iterator(map_[index]);
    }

    Iterator insert(const Entry& elem)
    {
      return insert(elem.key, elem.type);
    }

    Iterator insert(const Iterator& source)
    {
      return insert(*source);
    }

    Iterator insert(Slot& source)
    {
      return insert(Entry(source.key_, source.type_));
    }

    Iterator erase(const Iterator& what)
    {
      return erase((*what).key_);
    }

    Iterator erase(const Key& what)
    {
      int index = HashType(what) % capacity_;
      
      
      if (map_[index] && map_[index]->key_ == what)
      {
        return erase_element(index);
      }
      else
      {
        for (int i = index + 1; i != index; i = (i + 1) % capacity_)
        {
          if (map_[i] && map_[i]->key_ == what)
          {
            return erase_element(i);
          }
        }
      }
      
      //todo: get rid of this print
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

    Type& at(const Key& key)
    {
      size_t index = HashType(key) % capacity_;
      WSAssert(map_[index], "No element found with this key");
      return map_[index]->type_;
    }


    Type& operator[](const Key& key)
    {
      size_t index = HashType(key) % capacity_;
      if (!map_[index])
      {
        map_[index] = manager_.New(key, Type());
      }
      return map_[index]->type_;
    }

    Iterator find(const Key& key)
    {
      size_t index = HashType(key) % capacity_;
      if (map_[index])
      {
        return Iterator(map_[index]);
      }
      return end();
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

    Iterator erase_element(unsigned index)
    {
      Iterator toReturn;
      if (map_[index]->next_ && map_[index]->prev_)
      {
        toReturn = Iterator(map_[index]->prev_);
        map_[index]->next_->prev_ = map_[index]->prev_;
        map_[index]->prev_->next_ = map_[index]->next_;
          
      }
      else if (!map_[index]->next_ && map_[index]->prev_)
      {
        toReturn = Iterator(map_[index]->prev_);
        last_ = map_[index]->prev_->index_;
        map_[index]->prev_->next_ = map_[index]->next_;
      }
      else if (map_[index]->next_ && !map_[index]->prev_)
      {
        first_ = map_[index]->next_->index_;
        map_[index]->next_->prev_ = map_[index]->prev_;
        toReturn = begin();
        if (map_[index]->next_ == reinterpret_cast<Slot*>(end_slot_))
        {
          last_ = invalid_index_;
        }
      }
      else
      {
        toReturn = begin();
        last_ = first_ = invalid_index_;
      }

      manager_.Delete(map_[index]);
      map_[index] = nullptr;
        
      --size_;
      recalc_load_factor();
      return toReturn;
    }

    void recalc_load_factor()
    {
      if (!capacity_)
      {
        load_factor_ = 1.0f;
      }
      else
      {
        load_factor_ = (float)size_ / (float)capacity_;
      }
    }

    const int invalid_index_ = -1;

    float   load_factor_;
    float   max_load_factor_;
    size_t  capacity_;
    size_t  size_;
    size_t  slot_number_;

    Iterator end_;
    char end_slot_[sizeof(Slot)];

    static MemoryManager<Slot> manager_;
    int     first_;
    int     last_;
    Slot**  map_;
  };

#define MAPSLOT HashMap<Key, Type>::Slot

  template<typename Key, typename Type>
  MemoryManager<typename HashMap<Key, Type>::Slot> HashMap<Key, Type>::manager_;
}


