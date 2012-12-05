#ifndef MOREUNITTEST_CHECK_MACROS_H
#define MOREUNITTEST_CHECK_MACROS_H


#include <CheckMacros.h>
#include <MoreChecks.h>

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