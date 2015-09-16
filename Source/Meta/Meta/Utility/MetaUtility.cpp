///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: typecast function implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "MetaMacros.h"
#include "Component.h"
#include "PhysicsMesh.h"
#include "Texture.h"
typedef std::unordered_map< std::string , Marktopus::PhysicsMesh*> mapOfStringPhysicsMesh;



void GenericSetValue(Metadata* startType, void* start, Metadata* endType, void* end)
{ 
  if(startType->GetEnumConstants().size())
  {
    startType = FindType(int);
  }
  if(endType->GetEnumConstants().size())
  {
    endType = FindType(int);
  }
  
  if(endType == FindType(mapOfStringGameObject::iterator))
  {
    if(startType == FindType(mapOfStringGameObject::const_iterator))
    {
      __debugbreak();// HEY YOU. you can't convert from iterator to const iterator
    }
  }

  if(startType == FindType(mapOfStringGameObject::iterator))
  {
    if(endType == FindType(mapOfStringGameObject::const_iterator))
    {
      new (end) mapOfStringGameObject::const_iterator(*reinterpret_cast<mapOfStringGameObject::iterator*>(start));
      return;
    }
  }

  if(endType == FindType(mapOfStringPhysicsMesh::iterator))
  {
    if(startType == FindType(mapOfStringPhysicsMesh::const_iterator))
    {
      __debugbreak();// HEY YOU. you can't convert from iterator to const iterator
    }
  }

  if(startType == FindType(mapOfStringPhysicsMesh::iterator))
  {
    if(endType == FindType(mapOfStringPhysicsMesh::const_iterator))
    {
      new (end) mapOfStringPhysicsMesh::const_iterator(*reinterpret_cast<mapOfStringPhysicsMesh::iterator*>(start));
      return;
    }
  }

  if(endType == FindType(unordered_mapOfStringUnit::iterator))
  {
    if(startType == FindType(unordered_mapOfStringUnit::const_iterator))
    {
      __debugbreak();// HEY YOU. you can't convert from iterator to const iterator
    }
  }

  if(startType == FindType(unordered_mapOfStringUnit::iterator))
  {
    if(endType == FindType(unordered_mapOfStringUnit::const_iterator))
    {
      new (end) unordered_mapOfStringUnit::const_iterator(*reinterpret_cast<unordered_mapOfStringUnit::iterator*>(start));
      return;
    }
  }

  if(endType == FindType(unordered_mapOfStringTexture::iterator))
  {
    if(startType == FindType(unordered_mapOfStringTexture::const_iterator))
    {
      __debugbreak();// HEY YOU. you can't convert from iterator to const iterator
    }
  }

  if(startType == FindType(unordered_mapOfStringTexture::iterator))
  {
    if(endType == FindType(unordered_mapOfStringTexture::const_iterator))
    {
      new (end) unordered_mapOfStringTexture::const_iterator(*reinterpret_cast<unordered_mapOfStringTexture::iterator*>(start));
      return;
    }
  }

  if(endType == FindType(unordered_mapOfStringMap::iterator))
  {
    if(startType == FindType(unordered_mapOfStringMap::const_iterator))
    {
      __debugbreak();// HEY YOU. you can't convert from iterator to const iterator
    }
  }

  if(startType == FindType(unordered_mapOfStringMap::iterator))
  {
    if(endType == FindType(unordered_mapOfStringMap::const_iterator))
    {
      new (end) unordered_mapOfStringMap::const_iterator(*reinterpret_cast<unordered_mapOfStringMap::iterator*>(start));
      return;
    }
  }

  if(endType == startType)
  {
    memcpy(end, start, startType->GetSize());
  }
  else if(startType == FindType(char))
  {
    if(endType == FindType(std::string))
    {
      if(start)
      {
        new (end) std::string((char*)start);
      }
      else
      {
        new (end) std::string("");
      }
    }
  }
  else if(startType == FindType(std::string))
  {
    if(endType == FindType(char))
    {
      if(start)
      {
        const char* temp = reinterpret_cast<std::string*>(start)->c_str();
        memcpy(end, temp, reinterpret_cast<std::string*>(start)->size() + 1);
      }
      else
      {
        new (end) std::string("");
      }
    }
  }
  else if(startType == FindType(bool))
  {
    if(endType == FindType(bool))
    {
      new (end) bool(*reinterpret_cast<bool*>(start));
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<bool*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<bool*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {                                  
      int endtype = static_cast<int>(*reinterpret_cast<bool*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {                                  
      long endtype = static_cast<long>(*reinterpret_cast<bool*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<bool*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<bool*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<bool*>(start));
      new (end) unsigned(endtype);
    }  
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }
  else if(startType == FindType(char))
  {
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<char*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      new (end) char(*reinterpret_cast<char*>(start));
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<char*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {                                  
      int endtype = static_cast<int>(*reinterpret_cast<char*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {                                  
      long endtype = static_cast<long>(*reinterpret_cast<char*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<char*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<char*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<char*>(start));
      new (end) unsigned(endtype);
    }    
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }
  else if(startType == FindType(short))       
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<short*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<short*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      new (end) short(*reinterpret_cast<short*>(start));
    }
    else if(endType == FindType(int))         
    {                                  
      int endtype = static_cast<int>(*reinterpret_cast<short*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {                                  
      long endtype = static_cast<long>(*reinterpret_cast<short*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<short*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<short*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<short*>(start));
      new (end) unsigned(endtype);
    }    
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }
  else if(startType == FindType(int))         
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<int*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<int*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<int*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {            
      new (end) int(*reinterpret_cast<long*>(start));
    }                                  
    else if(endType == FindType(long))        
    {                                  
      long endtype = static_cast<long>(*reinterpret_cast<int*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<int*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<int*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<int*>(start));
      new (end) unsigned(endtype);
    }    
    else if(endType == FindType(uint16_t))
    {
      uint16_t endtype = static_cast<uint16_t>(*reinterpret_cast<int*>(start));
      new (end) uint16_t(endtype);
    }
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }                                  
  else if(startType == FindType(long))        
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<long*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<long*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<long*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {            
      int endtype = static_cast<int>(*reinterpret_cast<long*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {                                  
      new (end) long(*reinterpret_cast<long*>(start));
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<long*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<long*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<long*>(start));
      new (end) unsigned(endtype);
    }    
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }                                                              
  else if(startType == FindType(float))       
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<float*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<float*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<float*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {            
      int endtype = static_cast<int>(*reinterpret_cast<float*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {  
      long endtype = static_cast<long>(*reinterpret_cast<float*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      new (end) float(*reinterpret_cast<float*>(start));
    }                                  
    else if(endType == FindType(double))      
    {                                  
      double endtype = static_cast<double>(*reinterpret_cast<float*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<float*>(start));
      new (end) unsigned(endtype);
    }    
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }                                  
  else if(startType == FindType(double))      
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<double*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<double*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<double*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {            
      int endtype = static_cast<int>(*reinterpret_cast<double*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {  
      long endtype = static_cast<long>(*reinterpret_cast<double*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<double*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {                                  
      new (end) double(*reinterpret_cast<double*>(start));
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      unsigned endtype = static_cast<unsigned>(*reinterpret_cast<double*>(start));
      new (end) unsigned(endtype);
    }   
    else if(endType == FindType(uint16_t))
    {
      uint16_t endtype = static_cast<uint16_t>(*reinterpret_cast<double*>(start));
      new (end) uint16_t(endtype);
    }
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }                                         
  else if(startType == FindType(unsigned))    
  {                                  
    if(endType == FindType(bool))
    {
      bool endtype = static_cast<bool>(*reinterpret_cast<unsigned*>(start));
      new (end) bool(endtype);
    }
    else if(endType == FindType(char))
    {
      char endtype = static_cast<char>(*reinterpret_cast<unsigned*>(start));
      new (end) char(endtype);
    }
    else if(endType == FindType(short))       
    {          
      short endtype = static_cast<short>(*reinterpret_cast<unsigned*>(start));
      new (end) short(endtype);
    }
    else if(endType == FindType(int))         
    {            
      int endtype = static_cast<int>(*reinterpret_cast<unsigned*>(start));
      new (end) int(endtype);
    }                                  
    else if(endType == FindType(long))        
    {  
      long endtype = static_cast<long>(*reinterpret_cast<unsigned*>(start));
      new (end) long(endtype);
    }                                                            
    else if(endType == FindType(float))       
    {                                  
      float endtype = static_cast<float>(*reinterpret_cast<unsigned*>(start));
      new (end) float(endtype);
    }                                  
    else if(endType == FindType(double))      
    {    
      double endtype = static_cast<double>(*reinterpret_cast<unsigned*>(start));
      new (end) double(endtype);
    }                                                              
    else if(endType == FindType(unsigned))    
    {                                  
      new (end) unsigned(*reinterpret_cast<unsigned*>(start));
    }    
    else
    {
      Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
    }
  }
  else if(startType == FindType(uint16_t))
  {
    if(endType == FindType(double))      
    {    
      double endtype = static_cast<double>(*reinterpret_cast<uint16_t*>(start));
      new (end) double(endtype);
    }  
    else if(endType == FindType(int))         
    {            
      int endtype = static_cast<int>(*reinterpret_cast<uint16_t*>(start));
      new (end) int(endtype);
    }       
  }
  else
  {
    Marktopus::PopError("Meta Error", "Type not defined in GenericSetValue.");
  }
}

void StringToVal(std::string input, Metadata* outType, void* out)
{
  
  if(FindType(int) == outType)
  {
    *reinterpret_cast<int*>(out) = std::atoi(input.c_str());
  }
  else if(FindType(std::string) == outType)
  {
    *reinterpret_cast<std::string*>(out) = input;
  }
  else if(FindType(double) == outType)
  {
    *reinterpret_cast<double*>(out) = std::atof(input.c_str());
  }
  else if(FindType(float) == outType)
  {
    *reinterpret_cast<float*>(out) = static_cast<float>(std::atof(input.c_str()));
  }
  else if(FindType(long) == outType)
  {
    *reinterpret_cast<long*>(out) = std::atol(input.c_str());
  }
  else if(FindType(bool) == outType)
  {
    if(input == "true")
    {
      *reinterpret_cast<bool*>(out) = true;
    }
    else if(input == "false")
    {
      *reinterpret_cast<bool*>(out) = false;
    }
    else
    {
      Marktopus::Print("Wrong input for boolean value.\n");
    }

  }
  else
  {
    Marktopus::Print("Type doesn't match any listed type. Bound the wrong thing to a field?\n");
  }
}

std::string GetStringOf(Metadata* outType, void* out)
{
  if(!outType->GetEnumConstants().empty())
  {
    outType = FindType(int);
  }
  if(FindType(int) == outType)
  {
    return std::to_string(*reinterpret_cast<int*>(out));
  }
  else if(FindType(std::string) == outType)
  {
    return *reinterpret_cast<std::string*>(out);
  }
  else if(FindType(double) == outType)
  {
    return std::to_string(*reinterpret_cast<double*>(out));
  }
  else if(FindType(float) == outType)
  {
    return std::to_string(*reinterpret_cast<float*>(out));
  }
  else if(FindType(long) == outType)
  {
    return std::to_string(*reinterpret_cast<long*>(out));
  }
  else if(FindType(bool) == outType)
  {
    if(*reinterpret_cast<bool*>(out))
    {
      return "true";
    }
    return "false";
  }
  else
  {
    Marktopus::Print("Type doesn't match any listed type. Bound the wrong thing to a field?\n");
  }
  return "NO_TYPE";
}

void* resolveIndirection(int from, int to, void * fromPtr, void * toPtr)
{
  //this is levels of indirection
  //we at most only want pointers to whatever our things are
  //so we may -1 from each from and to
  --from;
  --to;
  if(from > to)
  {
    while (from > to)
    {
      fromPtr = *reinterpret_cast<void**>(fromPtr);
      --from;
    }
    return fromPtr;
  }
  else if(to > from)
  {
    while (to > from + 1)
    {
      toPtr = *reinterpret_cast<void**>(toPtr);
      --from;
    }
    *reinterpret_cast<void**>(toPtr) = fromPtr;
    return toPtr;
  }
  else
  {
    return fromPtr;
  }


  return nullptr;
}

unsigned int MetaHash(Metadata* meta, void* object)
{
  unsigned initial = SuperFastHash((char*)object, meta->GetSize());
  for(auto& it : meta->GetMembers())
  {
    if(it.second.GetType() == FindType(std::string))
    {
      std::string* string = (std::string*)((char*)object + it.second.GetOffset());
      initial += SuperFastHash(string->c_str(), string->size());
    }
  }
  return initial;
}
