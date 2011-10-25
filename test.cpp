#include <iostream>

#include "pystring.h"
#include "unittest.h"

PYSTRING_TEST_APP(PyStringUnitTests)


PYSTRING_ADD_TEST(pystring, endswith)
{
    PYSTRING_CHECK_EQUAL(pystring::endswith("", ""), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("", "a"), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("a", ""), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("", ".mesh"), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh"), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", 0), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", 1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", 1, 2), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", 1, 1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", 1, -1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh", -1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith(".mesh", ".mesh"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("a.mesh", ".mesh"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("a.", "."), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "ef"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "cdef"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "cdef", 2), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "cdef", 3), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "cdef", 2, 3), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("abcdef", "cdef", -10), true);
}

PYSTRING_ADD_TEST(pystring, find)
{
    PYSTRING_CHECK_EQUAL(pystring::find("", ""), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("", "a"), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("a", ""), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("a", "a"), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", ""), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "", -1), 5);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "", -2), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "", -5), 1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "", -6), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "", -7), 0);
    
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "def"), 3);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "def", 3), 3);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "def", 4), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "def", -5), 3);
    PYSTRING_CHECK_EQUAL(pystring::find("abcdef", "def", -1), -1);
    
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", -2), 7);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", -1), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 0), 1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 1), 1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 2), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 7), 7);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4, 3), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4, 4), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4, 5), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4, -1), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabcabc", "bc", 4, 6), 4);
}

PYSTRING_ADD_TEST(pystring, rfind)
{
    PYSTRING_CHECK_EQUAL(pystring::rfind("", ""), 0);
    PYSTRING_CHECK_EQUAL(pystring::rfind("", "a"), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("a", ""), 1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("a", "a"), 0);
    
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", ""), 6);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "", 0, 1), 1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "", 0, 5), 5);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "", 0,-1), 5);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "", 0,-3), 3);
    
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "def"), 3);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "def", 3), 3);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "def", 4), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "def", -5), 3);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcdef", "def", -1), -1);
    
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", -2), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", -1), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 0), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 1), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 4), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 7), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 4, -5), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 4, -10), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "bc", 4, 20), 7);
    
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabcabc", "abc", 6, 8), -1);
}

PYSTRING_ADD_TEST(pystring, slice)
{
    PYSTRING_CHECK_EQUAL(pystring::slice(""), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("", 1), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("", -1), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("", -1,2), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef"), "abcdef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",0), "abcdef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",1), "bcdef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2), "cdef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,2), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,3), "c");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,1), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,-1), "cde");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,-2), "cd");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,-3), "c");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,-4), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",2,-5), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-1), "f");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-2), "ef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-99), "abcdef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-99,-98), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-2, 3), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-2, 10), "ef");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",-1), "f");
    PYSTRING_CHECK_EQUAL(pystring::slice("abcdef",0,-1), "abcde");
}

PYSTRING_ADD_TEST(pystring, startswith)
{
    PYSTRING_CHECK_EQUAL(pystring::startswith("", ""), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("", "a"), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("a", ""), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abc", "ab"), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abc", "abc"), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abc", "abcd"), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abcdef", "abc"), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abcdef", "abc", 1), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("abcdef", "bc", 1), true);
}

PYSTRING_ADD_TEST(pystring, strip)
{
    PYSTRING_CHECK_EQUAL(pystring::strip(""), "");
    PYSTRING_CHECK_EQUAL(pystring::strip("a"), "a");
    PYSTRING_CHECK_EQUAL(pystring::strip("a "), "a");
    PYSTRING_CHECK_EQUAL(pystring::strip(" a"), "a");
    PYSTRING_CHECK_EQUAL(pystring::strip("\n a "), "a");
    PYSTRING_CHECK_EQUAL(pystring::strip("\r\n a \r\n"), "a");
    PYSTRING_CHECK_EQUAL(pystring::strip("\r\n a \r\n\t"), "a");
}

PYSTRING_ADD_TEST(pystring, translate)
{
    char t1data[256];
    for(int i=0; i<256; ++i) t1data[i] = (char)i;
    std::string t1(t1data, 256);
    PYSTRING_CHECK_EQUAL(pystring::translate("", t1), "");
    PYSTRING_CHECK_EQUAL(pystring::translate("cheese", t1), "cheese");
    PYSTRING_CHECK_EQUAL(pystring::translate("cheese", t1, "e"), "chs");
    
    char t2data[256];
    for(int i=0; i<256; ++i) t2data[i] = (char)i;
    t2data[101] = 111; // Map e -> o
    std::string t2(t2data, 256);
    PYSTRING_CHECK_EQUAL(pystring::translate("", t2), "");
    PYSTRING_CHECK_EQUAL(pystring::translate("cheese", t2), "chooso");
}


PYSTRING_ADD_TEST(pystring, abspath)
{
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath("", "/net"), "/net");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath("../jeremys", "/net/soft_scratch/users/stevel"), "/net/soft_scratch/users/jeremys");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath("../../../../tmp/a", "/net/soft_scratch/users/stevel"), "/tmp/a");
 
}
