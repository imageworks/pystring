// Copyright Contributors to the Pystring project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/imageworks/pystring/blob/master/LICENSE

#ifndef INCLUDED_PYSTRING_UNITTEST_H
#define INCLUDED_PYSTRING_UNITTEST_H

#include <iostream>
#include <cmath>
#include <vector>

extern int unit_test_failures;

void unittest_fail();

typedef void (*PYSTRINGTestFunc)();

struct PYSTRINGTest
{
    PYSTRINGTest(std::string testgroup, std::string testname, PYSTRINGTestFunc test) :
        group(testgroup), name(testname), function(test) { };
    std::string group, name;
    PYSTRINGTestFunc function;
};

typedef std::vector<PYSTRINGTest*> UnitTests;

UnitTests& GetUnitTests();

struct AddTest { AddTest(PYSTRINGTest* test); };

/// PYSTRING_CHECK_* macros checks if the conditions is met, and if not,
/// prints an error message indicating the module and line where the
/// error occurred, but does NOT abort.  This is helpful for unit tests
/// where we do not want one failure.
#define PYSTRING_CHECK_ASSERT(x)                                            \
    ((x) ? ((void)0)                                                    \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
                       << "FAILED: " << #x << "\n"),                    \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_EQUAL(x,y)                                           \
    (((x) == (y)) ? ((void)0)                                           \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " == " << #y << "\n"                \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_NE(x,y)                                              \
    (((x) != (y)) ? ((void)0)                                           \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " != " << #y << "\n"                \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_LT(x,y)                                              \
    (((x) < (y)) ? ((void)0)                                            \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " < " << #y << "\n"                 \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_GT(x,y)                                              \
    (((x) > (y)) ? ((void)0)                                            \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " > " << #y << "\n"                 \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_LE(x,y)                                              \
    (((x) <= (y)) ? ((void)0)                                           \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " <= " << #y << "\n"                \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_GE(x,y)                                              \
    (((x) >= (y)) ? ((void)0)                                           \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: " << #x << " >= " << #y << "\n"                \
             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_CLOSE(x,y,tol)                                       \
    ((std::abs((x) - (y)) < tol) ? ((void)0)                            \
         : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"          \
             << "FAILED: abs(" << #x << " - " << #y << ") < " << #tol << "\n" \
             << "\tvalues were '" << (x) << "', '" << (y) << "' and '" << (tol) << "'\n"), \
            (void)++unit_test_failures))

#define PYSTRING_CHECK_THOW(S, E)                                           \
    try { S; throw "throwanything"; } catch( E const& ex ) { } catch (...) { \
        std::cout << __FILE__ << ":" << __LINE__ << ":\n"               \
        << "FAILED: " << #E << " is expected to be thrown\n";           \
        ++unit_test_failures; }

#define PYSTRING_CHECK_NO_THOW(S)                                           \
    try { S; } catch (...) {                                            \
        std::cout << __FILE__ << ":" << __LINE__ << ":\n"               \
        << "FAILED: exception thrown from " << #S <<"\n";               \
        ++unit_test_failures; }

#define PYSTRING_ADD_TEST(group, name)                                      \
    static void pystringtest_##group##_##name();                            \
    AddTest pystringaddtest_##group##_##name(new PYSTRINGTest(#group, #name, pystringtest_##group##_##name)); \
    static void pystringtest_##group##_##name()

#define PYSTRING_TEST_SETUP() \
    int unit_test_failures = 0

#define PYSTRING_TEST_APP(app)                                              \
    std::vector<PYSTRINGTest*>& GetUnitTests() {                            \
        static std::vector<PYSTRINGTest*> pystring_unit_tests;                  \
        return pystring_unit_tests; }                                       \
    AddTest::AddTest(PYSTRINGTest* test){GetUnitTests().push_back(test);};  \
    PYSTRING_TEST_SETUP(); \
    int main(int, char **) { std::cerr << "\n" << #app <<"\n\n";        \
        for(size_t i = 0; i < GetUnitTests().size(); ++i) {             \
            int _tmp = unit_test_failures; GetUnitTests()[i]->function(); \
            std::cerr << "Test [" << GetUnitTests()[i]->group << "] [" << GetUnitTests()[i]->name << "] - "; \
            std::cerr << (_tmp == unit_test_failures ? "PASSED" : "FAILED") << "\n"; } \
        std::cerr << "\n" << unit_test_failures << " tests failed\n\n";   \
        return unit_test_failures; }

#endif
