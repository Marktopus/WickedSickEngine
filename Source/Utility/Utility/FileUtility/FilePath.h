#pragma once

#include <string>
#include <chrono>
#include <filesystem>

#include "UtilityDLL.h"


namespace WickedSick
{
  class FilePath
  {
  public:
    UTILITYDLL_API FilePath();
    UTILITYDLL_API FilePath(const std::string& filepath);
    UTILITYDLL_API FilePath(const FilePath& p);
    UTILITYDLL_API FilePath(FilePath&& p);
    UTILITYDLL_API const FilePath& operator=(FilePath p);
    UTILITYDLL_API const FilePath& operator=(const std::string& p);

    UTILITYDLL_API bool Writable();

    UTILITYDLL_API std::string Path();

    UTILITYDLL_API ~FilePath();


    UTILITYDLL_API bool WasModified();

  private:

    std::experimental::filesystem::path path_;
    std::chrono::time_point<std::chrono::system_clock> last_modified_;
  };
}
