///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        2/11/2014
//Description: STAR COUNTING YAY
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef INDIRECTION_COUNT_H
#define INDIRECTION_COUNT_H

template<typename T>
struct IndirectionCount
{
   static const unsigned short value = 0;
};

template<typename U>
struct IndirectionCount<U*>
{
   static const unsigned short value = 1 + IndirectionCount<U>::value;
};

template<typename T>
struct RefCount
{
   static const unsigned short value = 0;
};

template<typename U>
struct RefCount<U&>
{
   static const unsigned short value = 1 + RefCount<U>::value;
};


template<typename T>
T& dereference(T& ptr)
{
  return ptr;
}

template<typename T>
const T& dereference(const T& ptr)
{
  return ptr;
}

template<typename T>
T& dereference(T* ptr)
{
  return dereference(*ptr);
}

template<typename T>
T& dereference(const T* ptr)
{
  return dereference(*ptr);
}

void* blind_dereference(void* ptr, int derefs = 1);

template<typename T>
T& referenceDereference(T& ptr, void*& ref)
{
  if(ref)
  {
    ref = &ptr;
  }
  return ptr;
}

template<>
const char& referenceDereference(const char& ptr, void*& ref)
{
  if(ref)
  {
    ref = (void*)&ptr;
  }
  return ptr;
}

template<typename T>
const T& referenceDereference(const T& ptr, void*& ref)
{
  ref = nullptr;
  return ptr;
}



template<typename T>
T& referenceDereference(T* ptr, void*& ref)
{
  ref = ptr;
  referenceDereference(*ptr, ref);
  T& fuck = referenceDereference(*ptr, ref);
  return fuck;
}

template<typename T>
T& referenceDereference(const T* ptr, void*& ref)
{
  ref = const_cast<T*>(ptr);
  return referenceDereference(*const_cast<T*>(ptr), ref);
}


#endif