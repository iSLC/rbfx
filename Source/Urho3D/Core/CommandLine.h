//
// Copyright (c) 2017-2020 the rbfx project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#if DESKTOP

#include <sstream>
#include <EASTL/vector.h>
#include <EASTL/string.h>

namespace CLI
{

inline std::istringstream& operator>>(std::istringstream &in, ea::string& val)
{
    const std::string tmp(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>{});
    val = tmp.c_str();
    return in;
}

inline std::stringstream& operator<<(std::stringstream &out, ea::string& val)
{
    out << val.c_str();
    return out;
}

}

#include <CLI11/CLI11.hpp>


namespace CLI
{

namespace detail
{

template <> constexpr const char *type_name<ea::string>() { return "TEXT"; }

}

}

#endif  // defined(DESKTOP)
