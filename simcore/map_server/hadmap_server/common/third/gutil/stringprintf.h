// Copyright 2002 and onwards Google Inc.
//
// Printf variants that place their output in a C++ string.
//
// Usage:
//      string result = StringPrintf("%d %s\n", 10, "hello");
//      SStringPrintf(&result, "%d %s\n", 10, "hello");
//      StringAppendF(&result, "%d %s\n", 20, "there");

#ifndef _BASE_STRINGPRINTF_H
#define _BASE_STRINGPRINTF_H

#include <stdarg.h>
#include <string>
#include <vector>

#include "common/gutil/port.h"

// Return a C++ string
extern std::string StringPrintf(const char* format, ...)
    // Tell the compiler to do printf format string checking.
    PRINTF_ATTRIBUTE(1, 2);

// Store result into a supplied string and return it
extern const std::string& SStringPrintf(std::string* dst, const char* format, ...)
    // Tell the compiler to do printf format string checking.
    PRINTF_ATTRIBUTE(2, 3);

// Append result to a supplied string
extern void StringAppendF(std::string* dst, const char* format, ...)
    // Tell the compiler to do printf format string checking.
    PRINTF_ATTRIBUTE(2, 3);

// Lower-level routine that takes a va_list and appends to a specified
// string.  All other routines are just convenience wrappers around it.
extern void StringAppendV(std::string* dst, const char* format, va_list ap);

// The max arguments supported by StringPrintfVector
extern const int kStringPrintfVectorMaxArgs;

// You can use this version when all your arguments are strings, but
// you don't know how many arguments you'll have at compile time.
// StringPrintfVector will LOG(FATAL) if v.size() > kStringPrintfVectorMaxArgs
extern std::string StringPrintfVector(const char* format, const std::vector<std::string>& v);

#endif /* _BASE_STRINGPRINTF_H */
