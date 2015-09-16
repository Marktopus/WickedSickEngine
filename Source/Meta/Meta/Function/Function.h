///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: generic function class definition
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef FUNCTION_H
#define FUNCTIONH

#include "Precompiled.h"
#include "Debug.h"
#include "MetaUtility.h"
#include "MetaManager.h"
#include "SimplifyType.h"
#include "FunctionPointer.h"
#include "LuaUserdata.h"

#include "IndexSequence.h"


#include <type_traits>


#define ARGTYPE_FINAL(arg) typedef SIMPLIFY_TYPE<arg> arg##Final

class Var;
class Metadata;
class Function
{
public:

  Function();
  ~Function();

  void operator()(Var* object, Var* returnValue, std::vector<Var*> args);

  template<typename ClassType, typename RetType, typename ...ArgType>
  Function(RetType (ClassType::*function)(ArgType...) volatile);

  template<typename ClassType, typename RetType, typename ...ArgType>
  Function(RetType (ClassType::*function)(ArgType...) const);

  template<typename ClassType, typename RetType, typename ...ArgType>
  Function(RetType (ClassType::*function)(ArgType...));

  template<typename ClassType, typename RetType>
  Function (RetType (ClassType::*function)() volatile);

  template<typename ClassType, typename RetType>
  Function (RetType (ClassType::*function)() const);

  template<typename ClassType, typename RetType>
  Function (RetType (ClassType::*function)());

  template<typename RetType>
  struct ReturnType
  {
    typedef typename RemoveRefs<RetType>::Type RetTypeFinal;
    
    ReturnType();
    ReturnType(RetTypeFinal&& in);
    ReturnType(const RetTypeFinal& in);
    
    void Set(RetTypeFinal&& in);
    void Set(const RetTypeFinal& in);
    
    void* Get() const;

    char object[sizeof(RetType)];
  };

  template <typename ClassType, typename RetType, typename ...ArgType>
  class FunctionData
  {
  public:

    typedef RetType (ClassType::*Method)(ArgType...);

    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...) volatile);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...) const);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...));

    static void Call(FunctionPointer& ptr, 
                     Var* object, 
                     Var* returnValue, 
                     std::vector<Var*> args);
    

    template<std::size_t ...Is>
    static void CallFinal(ReturnType<RetType>& toFill,
                          FunctionPointer& ptr, 
                          ClassType* c, 
                          std::vector<Var*> args, 
                          index_sequence<Is...>);
    
    template<typename ...ArgTypes>
    static RetType CallActualFinal(ClassType* c,
                                   Method method,
                                   ArgTypes*... args);

    /*template<typename ...ArgTypes>
    static RetType CallActualFinal(ClassType* c,
                                   Method method,
                                   void* badArg,
                                   ArgTypes*... args);

    template<>
    static RetType CallActualFinal(ClassType* c,
                                   Method method);*/
  };

  template <typename ClassType, typename RetType, typename ...ArgType>
  class FunctionData<ClassType, RetType, void, ArgType...>
  {
  public:


    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...) volatile);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...) const);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)(ArgType...));

    static void Call(FunctionPointer& ptr, 
                     Var* object, 
                     Var* returnValue, 
                     std::vector<Var*> args);
  };

  

  template <typename ClassType, typename RetType>
  class FunctionData<ClassType, RetType>
  {
  public:
    typedef typename RemoveReferences(RetType) RetTypeFinal;
    typedef RetType (ClassType::*Method)();
    

    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)() volatile);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)() const);
    static void Set(FunctionPointer& ptr, RetType (ClassType::*function)());

    static void Call(FunctionPointer& ptr, 
                     Var* object, 
                     Var* returnValue, 
                     std::vector<Var*> args);
  };


  template <typename ClassType, typename ...ArgType>
  class FunctionData<ClassType, void, ArgType...>
  {
  public:
    typedef void (ClassType::*Method)(ArgType...);

    static void Set(FunctionPointer& ptr, void (ClassType::*function)(ArgType...) volatile);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)(ArgType...) const);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)(ArgType...));

    static void Call(FunctionPointer& ptr, Var* object, Var* returnValue, std::vector<Var*> args);

    template<std::size_t ...Is>
    static void CallFinal(FunctionPointer& ptr, 
                          ClassType* c, 
                          std::vector<Var*> args, 
                          index_sequence<Is...>);


    template<typename ...ArgTypes>
    static void CallActualFinal(ClassType* c,
                                Method method,
                                ArgTypes*... args);

    //template<typename ...ArgTypes>
    //static void CallActualFinal(ClassType* c,
    //                            Method method,
    //                            void* badArg,
    //                            ArgTypes*... args);

    //template<>
    //static void CallActualFinal(ClassType* c,
    //                            Method method);
  };
 

  template <typename ClassType, typename ...ArgTypes>
  class FunctionData<ClassType, void, void, ArgTypes...>
  {
  public:
    typedef void (ClassType::*Method)();
    static void Set(FunctionPointer& ptr, void (ClassType::*function)() volatile);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)() const);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)());

    static void Call(FunctionPointer& ptr, Var* object, Var* returnValue, std::vector<Var*> args);
  };
  
  template <typename ClassType>
  class FunctionData<ClassType, void>
  {
  public:
    typedef void (ClassType::*Method)();

    static void Set(FunctionPointer& ptr, void (ClassType::*function)() volatile);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)() const);
    static void Set(FunctionPointer& ptr, void (ClassType::*function)());

    static void Call(FunctionPointer& ptr, Var* object, Var* returnValue, std::vector<Var*> args);

  };

  void (*caller)(FunctionPointer& ptr, 
                 Var* object, 
                 Var* returnValue, 
                 std::vector<Var*> args);
  Metadata* return_type_;
  std::vector<Metadata*> args_;
  FunctionPointer        function_;
};


#include "Function_Template.cpp"

#endif
