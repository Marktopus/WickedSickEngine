#include "MetaPrecompiled.h"
#include "ExternalTypes.h"

#include "Function/Function.h"

RegisterExternalType(std, string)
  typedef std::string __this;
  //RegisterConstructor("default");
  //RegisterConstructor("copy", std::string);
  //RegisterConstructor("ptr_init", const char*);
  std::string& (std::string::*a)(const std::string&) = &std::string::assign;
  RegisterMethod("assign_string", a);
  std::string& (std::string::*luastr)(const char*) = &std::string::assign;
  RegisterMethod("assign_ptr", luastr);
  std::string& (std::string::*appendluastr)(const char*) = &std::string::append;
  RegisterMethod("append_ptr", appendluastr);

  std::string& (std::string::*appendstdstring)(const std::string&) = &std::string::append;
  RegisterMethod("append_string", appendstdstring);
  RegisterMethod("size", &std::string::size);
  RegisterMethod("capacity", &std::string::capacity);
  std::string& (std::string::*b)(const std::string&, unsigned, unsigned) = &std::string::assign;
  RegisterMethod("assign_string_unsigned_unsigned", b);
  RegisterMethod("c_str", &std::string::c_str);

}
