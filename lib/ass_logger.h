/*  This file is part of assfonts.
 *
 *  assfonts is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation,
 *  either version 2 of the License,
 *  or (at your option) any later version.
 *
 *  assfonts is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with assfonts. If not, see <https://www.gnu.org/licenses/>.
 *  
 *  written by wyzdwdz (https://github.com/wyzdwdz)
 */

#ifndef ASSFONTS_ASSLOGGER_H_
#define ASSFONTS_ASSLOGGER_H_

#include <string>
#include <utility>

#include <fmt/core.h>

#include "ass_string.h"
#include "assfonts.h"

namespace ass {

class Logger {
 public:
  Logger(AssfontsLogCallback cb, unsigned int log_level)
      : cb_(cb), log_level_(log_level){};
  ~Logger() = default;

  template <typename... T>
  void Info(fmt::format_string<T...> fmt, T&&... args) {
    if (log_level_ <= ASSFONTS_INFO) {
      Log(ASSFONTS_INFO, fmt, std::forward<T>(args)...);
    }
  }

  template <typename... T>
  void Warn(fmt::format_string<T...> fmt, T&&... args) {
    if (log_level_ <= ASSFONTS_WARN) {
      Log(ASSFONTS_WARN, fmt, std::forward<T>(args)...);
    }
  }

  template <typename... T>
  void Error(fmt::format_string<T...> fmt, T&&... args) {
    if (log_level_ <= ASSFONTS_ERROR) {
      Log(ASSFONTS_ERROR, fmt, std::forward<T>(args)...);
    }
  }

 private:
  AssfontsLogCallback cb_;
  unsigned int log_level_;

  template <typename... T>
  void Log(unsigned int log_level, fmt::format_string<T...> fmt, T&&... args) {
    std::string msg;

    switch (log_level) {
      case ASSFONTS_INFO:
        msg = "[INFO] ";
        break;

      case ASSFONTS_WARN:
        msg = "[WARN] ";
        break;

      case ASSFONTS_ERROR:
        msg = "[ERROR] ";
        break;

      default:
        break;
    }

#ifdef _WIN32
    msg.append(WideToU8(fmt::format(fmt, std::forward<T>(args)...)));
#else
    msg.append(fmt::format(fmt, std::forward<T>(args)...));
#endif

    msg.push_back('\n');

    cb_(msg.c_str(), msg.size(), log_level);
  }
};

}  // namespace ass

#endif