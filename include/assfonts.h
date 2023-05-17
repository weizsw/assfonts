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

#ifndef ASSFONTS_ASSFONTS_H_
#define ASSFONTS_ASSFONTS_H_

enum ASSFONTS_LOG_LEVEL { ASSFONTS_INFO = 0, ASSFONTS_WARN, ASSFONTS_ERROR };

extern "C" {

typedef void (*AssfontsLogCallback)(const char* msg, const unsigned int len,
                                    const unsigned int log_level);

void AssfontsBuildDB(const char* fonts_path, const char* db_path,
                     const AssfontsLogCallback cb,
                     const unsigned int log_level);

void AssfontsRun(const char** input_paths, const unsigned int num_paths,
                 const char* output_path, const char* fonts_path,
                 const char* db_path, const unsigned int brightness,
                 const unsigned int is_subset_only,
                 const unsigned int is_embed_only, const AssfontsLogCallback cb,
                 const unsigned int log_level);
}

#endif