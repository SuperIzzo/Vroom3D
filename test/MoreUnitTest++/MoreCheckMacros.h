/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  Copyright (c) 2013   Hristoz S. Stefanov                                 |Z
Z|                                                                           |Z
Z|  Permission is hereby granted, free of charge, to any person              |Z
Z|  obtaining a copy of this software and associated documentation files     |Z
Z|  (the "Software"), to deal in the Software without restriction,           |Z
Z|  including without limitation the rights to use, copy, modify, merge,     |Z
Z|  publish, distribute, sublicense, and/or sell copies of the Software,     |Z
Z|  and to permit persons to whom the Software is furnished to do so,        |Z
Z|  subject to the following conditions:                                     |Z
Z|                                                                           |Z
Z|  The above copyright notice and this permission notice shall be included  |Z
Z|  in all copies or substantial portions of the Software.                   |Z
Z|                                                                           |Z
Z|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |Z
Z|  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |Z
Z|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |Z
Z|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     |Z
Z|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     |Z
Z|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        |Z
Z|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   |Z
Z|                                                                           |Z
\*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*/
#ifndef MOREUNITTEST_CHECK_MACROS_H
#define MOREUNITTEST_CHECK_MACROS_H


#include <CheckMacros.h>
#include <MoreChecks.h>

#define CHECK_NOT(value) \
    do \
    { \
        try { \
            if (UnitTest::Check(value)) \
                UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), #value); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_NOT(" #value ")"); \
        } \
    } while (0)

#define CHECK_NULL(pointer) \
    do \
    { \
        try { \
            MoreUnitTest::CheckNull(*UnitTest::CurrentTest::Results(), pointer, UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_NULL(" #pointer ")"); \
        } \
    } while (0)

#define CHECK_NOT_NULL(pointer) \
    do \
    { \
        try { \
            MoreUnitTest::CheckNotNull(*UnitTest::CurrentTest::Results(), pointer, UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_NOT_NULL(" #pointer ")"); \
        } \
    } while (0)

#define CHECK_NOT_EQUAL(unexpected, actual) \
    do \
    { \
        try { \
            MoreUnitTest::CheckEqual(*UnitTest::CurrentTest::Results(), unexpected, actual, UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_NOT_EQUAL(" #unexpected ", " #actual ")"); \
        } \
    } while (0)


#endif
