#include "UtilityPrecompiled.h"
#include "FilePath.h"
#include <fstream>

namespace WickedSick
{
  UTILITYDLL_API FilePath::FilePath()
  {
  }

  UTILITYDLL_API FilePath::FilePath(const std::string& filepath) : path_(filepath)
  {
    last_modified_ = std::experimental::filesystem::last_write_time(path_);
  }

  UTILITYDLL_API FilePath::FilePath(const FilePath & p) :  path_(p.path_),
                                            last_modified_(p.last_modified_)
  {

  }

  UTILITYDLL_API FilePath::FilePath(FilePath && p)
  {
    std::swap(p, *this);
  }

  UTILITYDLL_API const FilePath & FilePath::operator=(FilePath p)
  {
    std::swap(p, *this);
    return *this;
  }

  UTILITYDLL_API const FilePath & FilePath::operator=(const std::string & p)
  {
    new (this) FilePath(p);
    return *this;
  }

  UTILITYDLL_API bool FilePath::Writable()
  {
    auto fstream = std::fstream(path_.string());
    if (fstream.is_open())
    {
      fstream.close();
      return true;
    }
    return false;
  }

  UTILITYDLL_API std::string FilePath::Path()
  {
    
    return path_.string();
  }

  UTILITYDLL_API FilePath::~FilePath()
  {
  }

  UTILITYDLL_API bool FilePath::WasModified()
  {
    auto currentState = std::experimental::filesystem::last_write_time(path_);
    bool modified = currentState != last_modified_;
    if (modified)
    {
      last_modified_ = currentState;
      return true;
    }
    return false;
  }
}
