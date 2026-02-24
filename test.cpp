// Copyright Contributors to the Pystring project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/imageworks/pystring/blob/master/LICENSE

#include <iostream>

#include "pystring.h"
#include "unittest.h"

// Helper wrappers (for pystring functions that don't have direct return values)

namespace {
static std::vector<std::string> pystring_split(const std::string& s, int maxsplit)
    { std::vector<std::string> r; pystring::split(s, r, "", maxsplit); return r; }
static std::vector<std::string> pystring_split(const std::string& s, const std::string& sep, int maxsplit)
    { std::vector<std::string> r; pystring::split(s, r, sep, maxsplit); return r; }
static std::vector<std::string> pystring_rsplit(const std::string& s, int maxsplit)
    { std::vector<std::string> r; pystring::rsplit(s, r, "", maxsplit); return r; }
static std::vector<std::string> pystring_rsplit(const std::string& s, const std::string& sep, int maxsplit)
    { std::vector<std::string> r; pystring::rsplit(s, r, sep, maxsplit); return r; }
static std::vector<std::string> pystring_partition(const std::string& s, const std::string& sep)
    { std::vector<std::string> r; pystring::partition(s, sep, r); return r; }
static std::vector<std::string> pystring_rpartition(const std::string& s, const std::string& sep)
    { std::vector<std::string> r; pystring::rpartition(s, sep, r); return r; }
static std::vector<std::string> pystring_splitlines(const std::string& s, bool keepends)
    { std::vector<std::string> r; pystring::splitlines(s, r, keepends); return r; }
} // namespace

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

PYSTRING_ADD_TEST(pystring, isupper)
{
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("abc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("AB-C"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("HELLO 123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("123"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("HELLO!"), true);
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

PYSTRING_ADD_TEST(pystring, removeprefix)
{
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("abcdef", "abc"), "def");
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("abcdef", "bcd"), "abcdef");
}

PYSTRING_ADD_TEST(pystring, removesuffix)
{
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("abcdef", "def"), "abc");
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("abcdef", "cde"), "abcdef");
}

PYSTRING_ADD_TEST(pystring, replace)
{
    PYSTRING_CHECK_EQUAL(pystring::replace("abcdef", "foo", "bar"), "abcdef");
    PYSTRING_CHECK_EQUAL(pystring::replace("abcdef", "ab", "cd"), "cdcdef");
    PYSTRING_CHECK_EQUAL(pystring::replace("abcdef", "ab", ""), "cdef");
    PYSTRING_CHECK_EQUAL(pystring::replace("abcabc", "ab", ""), "cc");
    PYSTRING_CHECK_EQUAL(pystring::replace("abcdef", "", ""), "abcdef");
    PYSTRING_CHECK_EQUAL(pystring::replace("abcdef", "", "."), ".a.b.c.d.e.f.");
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

PYSTRING_ADD_TEST(pystring, split)
{
    std::vector< std::string > result;
    
    {
        result.clear();
        pystring::split("", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
        }
    }
    
    {
        result.clear();
        pystring::split("/", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    {
        result.clear();
        pystring::split(" ", result, " ", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    {
        result.clear();
        pystring::split(" /", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " ");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    {
        result.clear();
        pystring::split(" //", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " ");
            PYSTRING_CHECK_EQUAL(result[1], "/");
        }
    }
    
    {
        result.clear();
        pystring::split("a  ", result, " ", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "a");
            PYSTRING_CHECK_EQUAL(result[1], " ");
        }
    }
    
    {
        result.clear();
        pystring::split("//as//rew//gdf", result, "//");
        PYSTRING_CHECK_EQUAL(result.size(), 4);
        if(result.size()==4)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "as");
            PYSTRING_CHECK_EQUAL(result[2], "rew");
            PYSTRING_CHECK_EQUAL(result[3], "gdf");
        }
    }
    
    {
        result.clear();
        pystring::split("/root", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
        }
    }
    
    {
        result.clear();
        pystring::split("/root/world", result, "/", 0);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], "/root/world");
        }
    }
    
    {
        result.clear();
        pystring::split("/root/world", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root/world");
        }
    }
    
    {
        result.clear();
        pystring::split("/root/world", result, "/", 2);
        PYSTRING_CHECK_EQUAL(result.size(), 3);
        if(result.size()==3)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
            PYSTRING_CHECK_EQUAL(result[2], "world");
        }
    }
    
    {
        result.clear();
        pystring::split("/root/world", result, "/", -1);
        PYSTRING_CHECK_EQUAL(result.size(), 3);
        if(result.size()==3)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
            PYSTRING_CHECK_EQUAL(result[2], "world");
        }
    }
}

PYSTRING_ADD_TEST(pystring, rsplit)
{
    std::vector< std::string > result;
    {
        result.clear();
        pystring::rsplit("", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
        }
    }
    
    {
        // "".rsplit(None, 1)
        result.clear();
        pystring::rsplit("", result, "", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 0);
    }
    
    {
        // " ".rsplit(None, 1)
        result.clear();
        pystring::rsplit(" ", result, "", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 0);
    }
    
    {
        result.clear();
        pystring::rsplit("  ", result, "", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 0);
    }
    
    {
        result.clear();
        pystring::rsplit("/", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    
    {
        result.clear();
        pystring::rsplit(" /", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " ");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    {
        result.clear();
        pystring::rsplit(" //", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " /");
            PYSTRING_CHECK_EQUAL(result[1], "");
        }
    }
    
    {
        result.clear();
        pystring::rsplit("/root", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
        }
    }
    
    {
        result.clear();
        pystring::rsplit("/root/world", result, "/", 0);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], "/root/world");
        }
    }
    
    {
        result.clear();
        pystring::rsplit("/root/world", result, "/", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "/root");
            PYSTRING_CHECK_EQUAL(result[1], "world");
        }
    }
    
    {
        result.clear();
        pystring::rsplit("/root/world", result, "/", 2);
        PYSTRING_CHECK_EQUAL(result.size(), 3);
        if(result.size()==3)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
            PYSTRING_CHECK_EQUAL(result[2], "world");
        }
    }
    
    {
        result.clear();
        pystring::rsplit("/root/world", result, "/", -1);
        PYSTRING_CHECK_EQUAL(result.size(), 3);
        if(result.size()==3)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
            PYSTRING_CHECK_EQUAL(result[2], "world");
        }
    }
    
    {
        // " root world".rsplit(None, 0)
        result.clear();
        pystring::rsplit(" root world", result, "", 0);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], " root world");
        }
    }
    
    {
        // " root world".rsplit(None, 1)
        result.clear();
        pystring::rsplit(" root world", result, "", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " root");
            PYSTRING_CHECK_EQUAL(result[1], "world");
        }
    }
    
    {
        // " root world".rsplit(None, 2)
        result.clear();
        pystring::rsplit(" root world", result, "", 2);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], "root");
            PYSTRING_CHECK_EQUAL(result[1], "world");
        }
    }
    
    
    {
        // " root world".rsplit(" ", 0)
        result.clear();
        pystring::rsplit(" root world", result, " ", 0);
        PYSTRING_CHECK_EQUAL(result.size(), 1);
        if(result.size()==1)
        {
            PYSTRING_CHECK_EQUAL(result[0], " root world");
        }
    }
    
    {
        // " root world".rsplit(" ", 1)
        result.clear();
        pystring::rsplit(" root world", result, " ", 1);
        PYSTRING_CHECK_EQUAL(result.size(), 2);
        if(result.size()==2)
        {
            PYSTRING_CHECK_EQUAL(result[0], " root");
            PYSTRING_CHECK_EQUAL(result[1], "world");
        }
    }
    
    {
        // " root world".rsplit(" ", 2)
        result.clear();
        pystring::rsplit(" root world", result, " ", 2);
        PYSTRING_CHECK_EQUAL(result.size(), 3);
        if(result.size()==3)
        {
            PYSTRING_CHECK_EQUAL(result[0], "");
            PYSTRING_CHECK_EQUAL(result[1], "root");
            PYSTRING_CHECK_EQUAL(result[2], "world");
        }
    }
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
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_posix("", "/net"), "/net");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_posix("../jeremys", "/net/soft_scratch/users/stevel"), "/net/soft_scratch/users/jeremys");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_posix("../../../../tmp/a", "/net/soft_scratch/users/stevel"), "/tmp/a");
 
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_nt("", "c:\\net"), "c:\\net");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_nt("..\\jeremys", "c:\\net\\soft_scratch\\users\\stevel"), "c:\\net\\soft_scratch\\users\\jeremys");
    PYSTRING_CHECK_EQUAL(pystring::os::path::abspath_nt("..\\..\\..\\..\\tmp\\a", "c:\\net\\soft_scratch\\users\\stevel"), "c:\\tmp\\a"); 
}

PYSTRING_ADD_TEST(pystring_os_path, splitdrive)
{
    using namespace pystring::os::path;
    
    std::string drivespec, pathspec;
    splitdrive_posix(drivespec, pathspec, "/Users/test"); PYSTRING_CHECK_EQUAL(drivespec, ""); PYSTRING_CHECK_EQUAL(pathspec, "/Users/test");
    splitdrive_nt(drivespec, pathspec, "C:\\Users\\test"); PYSTRING_CHECK_EQUAL(drivespec, "C:" ); PYSTRING_CHECK_EQUAL(pathspec, "\\Users\\test" );
    splitdrive_nt(drivespec, pathspec, "\\Users\\test"); PYSTRING_CHECK_EQUAL(drivespec, "" ); PYSTRING_CHECK_EQUAL(pathspec, "\\Users\\test" );
}

PYSTRING_ADD_TEST(pystring_os_path, isabs)
{
    using namespace pystring::os::path;
    
    PYSTRING_CHECK_EQUAL(isabs_posix("/Users/test"), true );
    PYSTRING_CHECK_EQUAL(isabs_posix("\\Users\\test"), false);
    PYSTRING_CHECK_EQUAL(isabs_posix("../Users"), false);
    PYSTRING_CHECK_EQUAL(isabs_posix("Users"), false);
    
    PYSTRING_CHECK_EQUAL(isabs_nt("C:\\Users\\test"), true);
    PYSTRING_CHECK_EQUAL(isabs_nt("C:/Users"), true);
    PYSTRING_CHECK_EQUAL(isabs_nt("/Users"), true);
    PYSTRING_CHECK_EQUAL(isabs_nt("../Users"), false);
    PYSTRING_CHECK_EQUAL(isabs_nt("..\\Users"), false);
}

PYSTRING_ADD_TEST(pystring_os_path, join)
{
    using namespace pystring::os::path;
    
    PYSTRING_CHECK_EQUAL(join_posix("a","b"), "a/b" );
    PYSTRING_CHECK_EQUAL(join_posix("/a","b"), "/a/b" );
    PYSTRING_CHECK_EQUAL(join_posix("/a","/b"), "/b" );
    PYSTRING_CHECK_EQUAL(join_posix("a","/b"), "/b" );
    PYSTRING_CHECK_EQUAL(join_posix("//a","b"), "//a/b" );
    PYSTRING_CHECK_EQUAL(join_posix("//a","b//"), "//a/b//" );
    PYSTRING_CHECK_EQUAL(join_posix("../a","/b"), "/b" );
    PYSTRING_CHECK_EQUAL(join_posix("../a","b"), "../a/b" );
    
    std::vector< std::string > paths;
    PYSTRING_CHECK_EQUAL(join_posix(paths), "" );
    paths.push_back("/a");
    PYSTRING_CHECK_EQUAL(join_posix(paths), "/a" );
    paths.push_back("b");
    PYSTRING_CHECK_EQUAL(join_posix(paths), "/a/b" );
    paths.push_back("c/");
    PYSTRING_CHECK_EQUAL(join_posix(paths), "/a/b/c/" );
    paths.push_back("d");
    PYSTRING_CHECK_EQUAL(join_posix(paths), "/a/b/c/d" );
    paths.push_back("/e");
    PYSTRING_CHECK_EQUAL(join_posix(paths), "/e" );
    
    PYSTRING_CHECK_EQUAL(join_nt("c:","/a"), "c:/a" );
    PYSTRING_CHECK_EQUAL(join_nt("c:/","/a"), "c:/a" );
    PYSTRING_CHECK_EQUAL(join_nt("c:/a","/b"), "/b" );
    PYSTRING_CHECK_EQUAL(join_nt("c:","d:/"), "d:/" );
    PYSTRING_CHECK_EQUAL(join_nt("c:/","d:/"), "d:/" );
    PYSTRING_CHECK_EQUAL(join_nt("a","b"), "a\\b" );
    PYSTRING_CHECK_EQUAL(join_nt("\\a","b"), "\\a\\b" );
    PYSTRING_CHECK_EQUAL(join_nt("c:\\a","b"), "c:\\a\\b" );
    PYSTRING_CHECK_EQUAL(join_nt("c:\\a","c:\\b"), "c:\\b" );
    PYSTRING_CHECK_EQUAL(join_nt("..\\a","b"), "..\\a\\b" );
}

PYSTRING_ADD_TEST(pystring_os_path, normpath)
{
    using namespace pystring::os::path;
    
    PYSTRING_CHECK_EQUAL(normpath_posix("A//B"), "A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("A/./B"), "A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("A/foo/../B"), "A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("/A//B"), "/A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("//A//B"), "//A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("///A//B"), "/A/B" );
    PYSTRING_CHECK_EQUAL(normpath_posix("../A"), "../A" );
    PYSTRING_CHECK_EQUAL(normpath_posix("../A../"), "../A.." );
    PYSTRING_CHECK_EQUAL(normpath_posix("FOO/../A../././B"), "A../B" );
    
    PYSTRING_CHECK_EQUAL(normpath_nt(""), "." );
    PYSTRING_CHECK_EQUAL(normpath_nt("A"), "A" );
    PYSTRING_CHECK_EQUAL(normpath_nt("A./B"), "A.\\B" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:\\"), "C:\\" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:\\A"), "C:\\A" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:/A"), "C:\\A" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:/A..\\"), "C:\\A.." );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:/A..\\..\\"), "C:\\" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:\\\\A"), "C:\\A" );
    PYSTRING_CHECK_EQUAL(normpath_nt("C:\\\\\\A\\\\B"), "C:\\A\\B" );
}

PYSTRING_ADD_TEST(pystring_os_path, split)
{
    using namespace pystring::os::path;
    
    std::string head, tail;
    split_posix(head, tail, "");  PYSTRING_CHECK_EQUAL(head, "" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_posix(head, tail, "/");  PYSTRING_CHECK_EQUAL(head, "/" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_posix(head, tail, "a");  PYSTRING_CHECK_EQUAL(head, "" );  PYSTRING_CHECK_EQUAL(tail, "a" );
    split_posix(head, tail, "a/");  PYSTRING_CHECK_EQUAL(head, "a" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_posix(head, tail, "/a");  PYSTRING_CHECK_EQUAL(head, "/" );  PYSTRING_CHECK_EQUAL(tail, "a" );
    split_posix(head, tail, "/a/b/");  PYSTRING_CHECK_EQUAL(head, "/a/b" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_posix(head, tail, "/a/b");  PYSTRING_CHECK_EQUAL(head, "/a" );  PYSTRING_CHECK_EQUAL(tail, "b" );
    split_posix(head, tail, "/a/b//");  PYSTRING_CHECK_EQUAL(head, "/a/b" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_posix(head, tail, "/a/b/////////////");  PYSTRING_CHECK_EQUAL(head, "/a/b" );  PYSTRING_CHECK_EQUAL(tail, "" );

    
    split_nt(head, tail, "");  PYSTRING_CHECK_EQUAL(head, "" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_nt(head, tail, "\\");  PYSTRING_CHECK_EQUAL(head, "\\" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_nt(head, tail, "a");  PYSTRING_CHECK_EQUAL(head, "" );  PYSTRING_CHECK_EQUAL(tail, "a" );
    split_nt(head, tail, "a\\");  PYSTRING_CHECK_EQUAL(head, "a" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_nt(head, tail, "c:\\a");  PYSTRING_CHECK_EQUAL(head, "c:\\" );  PYSTRING_CHECK_EQUAL(tail, "a" );
    split_nt(head, tail, "c:\\a\\b");  PYSTRING_CHECK_EQUAL(head, "c:\\a" );  PYSTRING_CHECK_EQUAL(tail, "b" );
    split_nt(head, tail, "c:\\a\\b\\");  PYSTRING_CHECK_EQUAL(head, "c:\\a\\b" );  PYSTRING_CHECK_EQUAL(tail, "" );
    split_nt(head, tail, "D:\\dir\\\\");  PYSTRING_CHECK_EQUAL(head, "D:\\dir" );  PYSTRING_CHECK_EQUAL(tail, "" );

}

PYSTRING_ADD_TEST(pystring_os_path, splitext)
{
    using namespace pystring::os::path;
    
    std::string root, ext;
    splitext_nt(root, ext, ""); PYSTRING_CHECK_EQUAL(root, ""); PYSTRING_CHECK_EQUAL(ext, "");
    splitext_nt(root, ext, "."); PYSTRING_CHECK_EQUAL(root, "."); PYSTRING_CHECK_EQUAL(ext, "");
    splitext_nt(root, ext, ".foo"); PYSTRING_CHECK_EQUAL(root, ".foo"); PYSTRING_CHECK_EQUAL(ext, "");
    splitext_nt(root, ext, ".foo."); PYSTRING_CHECK_EQUAL(root, ".foo"); PYSTRING_CHECK_EQUAL(ext, ".");
    splitext_nt(root, ext, ".foo.e"); PYSTRING_CHECK_EQUAL(root, ".foo"); PYSTRING_CHECK_EQUAL(ext, ".e");
    splitext_nt(root, ext, "c"); PYSTRING_CHECK_EQUAL(root, "c"); PYSTRING_CHECK_EQUAL(ext, "");
    splitext_nt(root, ext, "a_b.c"); PYSTRING_CHECK_EQUAL(root, "a_b"); PYSTRING_CHECK_EQUAL(ext, ".c");
    splitext_nt(root, ext, "c:\\a.b.c"); PYSTRING_CHECK_EQUAL(root, "c:\\a.b"); PYSTRING_CHECK_EQUAL(ext, ".c");
    splitext_nt(root, ext, "c:\\a_b.c"); PYSTRING_CHECK_EQUAL(root, "c:\\a_b"); PYSTRING_CHECK_EQUAL(ext, ".c");
}

// the python3_compat tests were auto generated from python
// to make sure that our functions exactly match the values that are being returned in python 3.11

PYSTRING_ADD_TEST(python3_compat, capitalize)
{
    PYSTRING_CHECK_EQUAL(pystring::capitalize(""), "");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("hello"), "Hello");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("HELLO"), "Hello");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("Hello World"), "Hello world");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("hello123"), "Hello123");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("123"), "123");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("hElLo"), "Hello");
    PYSTRING_CHECK_EQUAL(pystring::capitalize("hello world!"), "Hello world!");
}

PYSTRING_ADD_TEST(python3_compat, center)
{
    PYSTRING_CHECK_EQUAL(pystring::center("hello", 10), "  hello   ");
    PYSTRING_CHECK_EQUAL(pystring::center("hello", 3), "hello");
    PYSTRING_CHECK_EQUAL(pystring::center("", 5), "     ");
    PYSTRING_CHECK_EQUAL(pystring::center("hello", 5), "hello");
}

PYSTRING_ADD_TEST(python3_compat, count_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::count("", "", 0), 1);
    PYSTRING_CHECK_EQUAL(pystring::count("bob", ""), 4);    
    PYSTRING_CHECK_EQUAL(pystring::count("", "bob"), 0);    
    PYSTRING_CHECK_EQUAL(pystring::count("hello world", "o", 0), 2);
    PYSTRING_CHECK_EQUAL(pystring::count("hello world", "l", 0), 3);
    PYSTRING_CHECK_EQUAL(pystring::count("hello world", "xyz", 0), 0);
    PYSTRING_CHECK_EQUAL(pystring::count("hello world", "", 0), 12);
    PYSTRING_CHECK_EQUAL(pystring::count("aaa", "a", 0), 3);
    PYSTRING_CHECK_EQUAL(pystring::count("aaa", "aa", 0), 1);
    PYSTRING_CHECK_EQUAL(pystring::count("hello", "l", 2, 5), 2);
}

PYSTRING_ADD_TEST(python3_compat, endswith_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "hello", 0), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "world", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "hello", 1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "ello", 1), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello", "hello world", 0), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "world", 0, 5), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello world", "hello", 0, 5), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("", "", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("hello", "hello", 0), true);
}

PYSTRING_ADD_TEST(python3_compat, expandtabs)
{
    PYSTRING_CHECK_EQUAL(pystring::expandtabs("hello\tworld", 8), "hello   world");
    PYSTRING_CHECK_EQUAL(pystring::expandtabs("hello\tworld", 4), "hello   world");
    PYSTRING_CHECK_EQUAL(pystring::expandtabs("\t\t", 4), "        ");
    PYSTRING_CHECK_EQUAL(pystring::expandtabs("no tabs", 4), "no tabs");
    PYSTRING_CHECK_EQUAL(pystring::expandtabs("a\tb\tc", 4), "a   b   c");
}

PYSTRING_ADD_TEST(python3_compat, find_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "world", 0), 6);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "hello", 0), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "xyz", 0), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "", 0), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "o", 0), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "o", 5), 7);
    PYSTRING_CHECK_EQUAL(pystring::find("hello world", "o", 0, 5), 4);
    PYSTRING_CHECK_EQUAL(pystring::find("", "hello", 0), -1);
    PYSTRING_CHECK_EQUAL(pystring::find("hello", "", 0), 0);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabc", "bc", 0), 1);
    PYSTRING_CHECK_EQUAL(pystring::find("abcabc", "bc", 2), 4);
}

PYSTRING_ADD_TEST(python3_compat, isalnum)
{
    PYSTRING_CHECK_EQUAL(pystring::isalnum(""), false);
    PYSTRING_CHECK_EQUAL(pystring::isalnum("abc"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalnum("123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalnum("abc123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalnum("abc!"), false);
    PYSTRING_CHECK_EQUAL(pystring::isalnum(" "), false);
    PYSTRING_CHECK_EQUAL(pystring::isalnum("abc 123"), false);
}

PYSTRING_ADD_TEST(python3_compat, isalpha)
{
    PYSTRING_CHECK_EQUAL(pystring::isalpha(""), false);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("abc"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("ABC"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("abcABC"), true);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("abc1"), false);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("abc!"), false);
    PYSTRING_CHECK_EQUAL(pystring::isalpha(" "), false);
    PYSTRING_CHECK_EQUAL(pystring::isalpha("a b"), false);
}

PYSTRING_ADD_TEST(python3_compat, isdigit)
{
    PYSTRING_CHECK_EQUAL(pystring::isdigit(""), false);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("0"), true);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("12.3"), false);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("12 3"), false);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("abc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isdigit("123abc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isdigit(" "), false);
}

PYSTRING_ADD_TEST(python3_compat, islower)
{
    PYSTRING_CHECK_EQUAL(pystring::islower(""), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("a"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("A"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("abc"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("ABC"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("abC"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("abc123"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("123"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("abc 123"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("hello!"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("HELLO!"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower(" "), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("abc\n"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("!@#$"), false);
    PYSTRING_CHECK_EQUAL(pystring::islower("a!b"), true);
    PYSTRING_CHECK_EQUAL(pystring::islower("1a"), true);
}

PYSTRING_ADD_TEST(python3_compat, isspace)
{
    PYSTRING_CHECK_EQUAL(pystring::isspace(""), false);
    PYSTRING_CHECK_EQUAL(pystring::isspace(" "), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace("   "), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace("\t"), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace("\n"), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace("\r"), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace(" \t\n"), true);
    PYSTRING_CHECK_EQUAL(pystring::isspace("a"), false);
    PYSTRING_CHECK_EQUAL(pystring::isspace(" a "), false);
    PYSTRING_CHECK_EQUAL(pystring::isspace("  a"), false);
}

PYSTRING_ADD_TEST(python3_compat, istitle)
{
    PYSTRING_CHECK_EQUAL(pystring::istitle(""), false);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Title"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Title Case"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("title"), false);
    PYSTRING_CHECK_EQUAL(pystring::istitle("TITLE"), false);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Title123"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("A"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("a"), false);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Title Case Here"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Title  Case"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("123 Title"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("Already A Title"), true);
    PYSTRING_CHECK_EQUAL(pystring::istitle("not A Title"), false);
}

PYSTRING_ADD_TEST(python3_compat, isupper)
{
    PYSTRING_CHECK_EQUAL(pystring::isupper(""), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("A"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("a"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("abc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABc"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("123"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC 123"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("HELLO!"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("hello!"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper(" "), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC\n"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("ABC\tDEF"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("!@#$"), false);
    PYSTRING_CHECK_EQUAL(pystring::isupper("A!B"), true);
    PYSTRING_CHECK_EQUAL(pystring::isupper("1A"), true);
}

PYSTRING_ADD_TEST(python3_compat, join_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::join(",", {}), "");
    PYSTRING_CHECK_EQUAL(pystring::join(",", {""}), "");
    PYSTRING_CHECK_EQUAL(pystring::join(",", {"a"}), "a");
    PYSTRING_CHECK_EQUAL(pystring::join(",", {"a", "b", "c"}), "a,b,c");
    PYSTRING_CHECK_EQUAL(pystring::join("", {"a", "b", "c"}), "abc");
    PYSTRING_CHECK_EQUAL(pystring::join(", ", {"hello", "world"}), "hello, world");
    PYSTRING_CHECK_EQUAL(pystring::join("-", {"one", "two", "three"}), "one-two-three");
    PYSTRING_CHECK_EQUAL(pystring::join("/", {"path", "to", "file"}), "path/to/file");
}

PYSTRING_ADD_TEST(python3_compat, ljust)
{
    PYSTRING_CHECK_EQUAL(pystring::ljust("hello", 10), "hello     ");
    PYSTRING_CHECK_EQUAL(pystring::ljust("hello", 3), "hello");
    PYSTRING_CHECK_EQUAL(pystring::ljust("", 5), "     ");
    PYSTRING_CHECK_EQUAL(pystring::ljust("hello", 5), "hello");
}

PYSTRING_ADD_TEST(python3_compat, lower)
{
    PYSTRING_CHECK_EQUAL(pystring::lower(""), "");
    PYSTRING_CHECK_EQUAL(pystring::lower("hello"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::lower("HELLO"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::lower("Hello World"), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::lower("hello123"), "hello123");
    PYSTRING_CHECK_EQUAL(pystring::lower("123"), "123");
    PYSTRING_CHECK_EQUAL(pystring::lower("hElLo"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::lower("hello world!"), "hello world!");
}

PYSTRING_ADD_TEST(python3_compat, lstrip)
{
    PYSTRING_CHECK_EQUAL(pystring::lstrip(""), "");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("  hello  "), "hello  ");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("  hello  ", " "), "hello  ");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("xxhelloxx", "x"), "helloxx");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("\t\nhello\t\n"), "hello\t\n");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("hello"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("   "), "");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("aabbcc", "ac"), "bbcc");
    PYSTRING_CHECK_EQUAL(pystring::lstrip("hello world  "), "hello world  ");
}

PYSTRING_ADD_TEST(python3_compat, mul)
{
    PYSTRING_CHECK_EQUAL(pystring::mul("ab", 3), "ababab");
    PYSTRING_CHECK_EQUAL(pystring::mul("ab", 0), "");
    PYSTRING_CHECK_EQUAL(pystring::mul("ab", 1), "ab");
    PYSTRING_CHECK_EQUAL(pystring::mul("", 5), "");
    PYSTRING_CHECK_EQUAL(pystring::mul("x", 5), "xxxxx");
}


PYSTRING_ADD_TEST(python3_compat, removeprefix_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("hello world", "hello "), "world");
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("hello world", "xyz"), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("hello world", ""), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("hello", "hello"), "");
    PYSTRING_CHECK_EQUAL(pystring::removeprefix("", "x"), "");
}

PYSTRING_ADD_TEST(python3_compat, removesuffix_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("hello world", "hello "), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("hello world", "xyz"), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("hello world", ""), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("hello", "hello"), "");
    PYSTRING_CHECK_EQUAL(pystring::removesuffix("", "x"), "");
}

PYSTRING_ADD_TEST(python3_compat, replace_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::replace("hello world", "world", "python", -1), "hello python");
    PYSTRING_CHECK_EQUAL(pystring::replace("hello world", "o", "0", -1), "hell0 w0rld");
    PYSTRING_CHECK_EQUAL(pystring::replace("hello world", "o", "0", 1), "hell0 world");
    PYSTRING_CHECK_EQUAL(pystring::replace("hello world", "xyz", "abc", -1), "hello world");
    PYSTRING_CHECK_EQUAL(pystring::replace("hello world", "", "_", -1), "_h_e_l_l_o_ _w_o_r_l_d_");
    PYSTRING_CHECK_EQUAL(pystring::replace("aaa", "a", "bb", -1), "bbbbbb");
    PYSTRING_CHECK_EQUAL(pystring::replace("aaa", "a", "bb", 2), "bbbba");
    PYSTRING_CHECK_EQUAL(pystring::replace("", "a", "b", -1), "");
    PYSTRING_CHECK_EQUAL(pystring::replace("hello", "hello", "", -1), "");
}

PYSTRING_ADD_TEST(python3_compat, rfind_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "world", 0), 6);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "hello", 0), 0);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "xyz", 0), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "", 0), 11);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "o", 0), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "o", 5), 7);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello world", "o", 0, 5), 4);
    PYSTRING_CHECK_EQUAL(pystring::rfind("", "hello", 0), -1);
    PYSTRING_CHECK_EQUAL(pystring::rfind("hello", "", 0), 5);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabc", "bc", 0), 4);
    PYSTRING_CHECK_EQUAL(pystring::rfind("abcabc", "bc", 2), 4);
}

PYSTRING_ADD_TEST(python3_compat, rjust)
{
    PYSTRING_CHECK_EQUAL(pystring::rjust("hello", 10), "     hello");
    PYSTRING_CHECK_EQUAL(pystring::rjust("hello", 3), "hello");
    PYSTRING_CHECK_EQUAL(pystring::rjust("", 5), "     ");
    PYSTRING_CHECK_EQUAL(pystring::rjust("hello", 5), "hello");
}


PYSTRING_ADD_TEST(python3_compat, rstrip)
{
    PYSTRING_CHECK_EQUAL(pystring::rstrip(""), "");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("  hello  "), "  hello");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("  hello  ", " "), "  hello");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("xxhelloxx", "x"), "xxhello");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("\t\nhello\t\n"), "\t\nhello");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("hello"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("   "), "");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("aabbcc", "ac"), "aabb");
    PYSTRING_CHECK_EQUAL(pystring::rstrip("hello world  "), "hello world");
}

PYSTRING_ADD_TEST(python3_compat, slice_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", 0, 5), "hello");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", 1, 4), "ell");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", 0, -1), "hell");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", -3, -1), "ll");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", 2, 2), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello", 3, 1), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("", 0, 0), "");
    PYSTRING_CHECK_EQUAL(pystring::slice("hello world", 6, 11), "world");
}


PYSTRING_ADD_TEST(python3_compat, startswith_python3)
{
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "hello", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "world", 0), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "hello", 1), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "ello", 1), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello", "hello world", 0), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "world", 0, 5), false);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello world", "hello", 0, 5), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("", "", 0), true);
    PYSTRING_CHECK_EQUAL(pystring::startswith("hello", "hello", 0), true);
}

PYSTRING_ADD_TEST(python3_compat, strip)
{
    PYSTRING_CHECK_EQUAL(pystring::strip(""), "");
    PYSTRING_CHECK_EQUAL(pystring::strip("  hello  "), "hello");
    PYSTRING_CHECK_EQUAL(pystring::strip("  hello  ", " "), "hello");
    PYSTRING_CHECK_EQUAL(pystring::strip("xxhelloxx", "x"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::strip("\t\nhello\t\n"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::strip("hello"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::strip("   "), "");
    PYSTRING_CHECK_EQUAL(pystring::strip("aabbcc", "ac"), "bb");
    PYSTRING_CHECK_EQUAL(pystring::strip("hello world  "), "hello world");
}

PYSTRING_ADD_TEST(python3_compat, swapcase)
{
    PYSTRING_CHECK_EQUAL(pystring::swapcase(""), "");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("hello"), "HELLO");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("HELLO"), "hello");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("Hello World"), "hELLO wORLD");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("hello123"), "HELLO123");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("123"), "123");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("hElLo"), "HeLlO");
    PYSTRING_CHECK_EQUAL(pystring::swapcase("hello world!"), "HELLO WORLD!");
}

PYSTRING_ADD_TEST(python3_compat, title)
{
    PYSTRING_CHECK_EQUAL(pystring::title(""), "");
    PYSTRING_CHECK_EQUAL(pystring::title("hello world"), "Hello World");
    PYSTRING_CHECK_EQUAL(pystring::title("HELLO WORLD"), "Hello World");
    PYSTRING_CHECK_EQUAL(pystring::title("hello"), "Hello");
    PYSTRING_CHECK_EQUAL(pystring::title("it's a test"), "It'S A Test");
    PYSTRING_CHECK_EQUAL(pystring::title("they're bill's friends from the UK"), "They'Re Bill'S Friends From The Uk");
    PYSTRING_CHECK_EQUAL(pystring::title("hello123world"), "Hello123World");
}

PYSTRING_ADD_TEST(python3_compat, upper)
{
    PYSTRING_CHECK_EQUAL(pystring::upper(""), "");
    PYSTRING_CHECK_EQUAL(pystring::upper("hello"), "HELLO");
    PYSTRING_CHECK_EQUAL(pystring::upper("HELLO"), "HELLO");
    PYSTRING_CHECK_EQUAL(pystring::upper("Hello World"), "HELLO WORLD");
    PYSTRING_CHECK_EQUAL(pystring::upper("hello123"), "HELLO123");
    PYSTRING_CHECK_EQUAL(pystring::upper("123"), "123");
    PYSTRING_CHECK_EQUAL(pystring::upper("hElLo"), "HELLO");
    PYSTRING_CHECK_EQUAL(pystring::upper("hello world!"), "HELLO WORLD!");
}

PYSTRING_ADD_TEST(python3_compat, zfill)
{
    PYSTRING_CHECK_EQUAL(pystring::zfill("42", 5), "00042");
    PYSTRING_CHECK_EQUAL(pystring::zfill("42", 2), "42");
    PYSTRING_CHECK_EQUAL(pystring::zfill("-42", 5), "-0042");
    PYSTRING_CHECK_EQUAL(pystring::zfill("+42", 5), "+0042");
    PYSTRING_CHECK_EQUAL(pystring::zfill("hello", 8), "000hello");
    PYSTRING_CHECK_EQUAL(pystring::zfill("", 3), "000");
}


PYSTRING_ADD_TEST(python3_compat, rpartition_python3)
{
    {
        std::vector<std::string> _e17 = {"hello", " ", "world"};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("hello world", " ")) == _e17);
    }
    {
        std::vector<std::string> _e19 = {"", "", "hello world"};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("hello world", "xyz")) == _e19);
    }
    {
        std::vector<std::string> _e21 = {"", "hello", ""};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("hello", "hello")) == _e21);
    }
    {
        std::vector<std::string> _e23 = {"", "", ""};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("", "x")) == _e23);
    }
    {
        std::vector<std::string> _e25 = {"aXb", "X", "c"};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("aXbXc", "X")) == _e25);
    }
    {
        std::vector<std::string> _e27 = {"hello ", "world", ""};
        PYSTRING_CHECK_ASSERT((pystring_rpartition("hello world", "world")) == _e27);
    }
}


PYSTRING_ADD_TEST(python3_compat, rsplit_python3)
{
    {
        std::vector<std::string> _e12 = {"hello world", "foo"};
        PYSTRING_CHECK_ASSERT((pystring_rsplit("hello world foo", " ", 1)) == _e12);
    }
    {
        std::vector<std::string> _e13 = {"a,b", "c", "d"};
        PYSTRING_CHECK_ASSERT((pystring_rsplit("a,b,c,d", ",", 2)) == _e13);
    }
    {
        std::vector<std::string> _e14 = {"  hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_rsplit("  hello  world  ", 1)) == _e14);
    }
    {
        std::vector<std::string> _e15 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_rsplit("hello world", -1)) == _e15);
    }
}


PYSTRING_ADD_TEST(python3_compat, split_python3)
{
    {
        std::vector<std::string> _e0 = {};
        PYSTRING_CHECK_ASSERT((pystring_split("", -1)) == _e0);
    }
    {
        std::vector<std::string> _e1 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_split("hello world", -1)) == _e1);
    }
    {
        std::vector<std::string> _e2 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_split("  hello  world  ", -1)) == _e2);
    }
    {
        std::vector<std::string> _e3 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_split("hello world", " ", -1)) == _e3);
    }
    {
        std::vector<std::string> _e4 = {"hello world"};
        PYSTRING_CHECK_ASSERT((pystring_split("hello world", " ", 0)) == _e4);
    }
    {
        std::vector<std::string> _e5 = {"hello", "world foo"};
        PYSTRING_CHECK_ASSERT((pystring_split("hello world foo", " ", 1)) == _e5);
    }
    {
        std::vector<std::string> _e6 = {"a", "b", "c", "d"};
        PYSTRING_CHECK_ASSERT((pystring_split("a,b,c,d", ",", -1)) == _e6);
    }
    {
        std::vector<std::string> _e7 = {"a", "b", "c,d"};
        PYSTRING_CHECK_ASSERT((pystring_split("a,b,c,d", ",", 2)) == _e7);
    }
    {
        std::vector<std::string> _e8 = {"a", "b", "c"};
        PYSTRING_CHECK_ASSERT((pystring_split("aXXbXXc", "XX", -1)) == _e8);
    }
    {
        std::vector<std::string> _e9 = {"hello"};
        PYSTRING_CHECK_ASSERT((pystring_split("hello", "x", -1)) == _e9);
    }
    {
        std::vector<std::string> _e10 = {};
        PYSTRING_CHECK_ASSERT((pystring_split("   ", -1)) == _e10);
    }
    {
        std::vector<std::string> _e11 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_split("\thello\tworld\t", -1)) == _e11);
    }
}



PYSTRING_ADD_TEST(python3_compat, splitlines)
{
    {
        std::vector<std::string> _e28 = {};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("", false)) == _e28);
    }
    {
        std::vector<std::string> _e29 = {};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("", true)) == _e29);
    }
    {
        std::vector<std::string> _e30 = {"hello"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello", false)) == _e30);
    }
    {
        std::vector<std::string> _e31 = {"hello"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello", true)) == _e31);
    }
    {
        std::vector<std::string> _e32 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\nworld", false)) == _e32);
    }
    {
        std::vector<std::string> _e33 = {"hello\n", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\nworld", true)) == _e33);
    }
    {
        std::vector<std::string> _e34 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\r\nworld", false)) == _e34);
    }
    {
        std::vector<std::string> _e35 = {"hello\r\n", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\r\nworld", true)) == _e35);
    }
    {
        std::vector<std::string> _e36 = {"hello", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\rworld", false)) == _e36);
    }
    {
        std::vector<std::string> _e37 = {"hello\r", "world"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\rworld", true)) == _e37);
    }
    {
        std::vector<std::string> _e38 = {"line1", "line2", "line3"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("line1\nline2\nline3", false)) == _e38);
    }
    {
        std::vector<std::string> _e39 = {"line1\n", "line2\n", "line3"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("line1\nline2\nline3", true)) == _e39);
    }
    {
        std::vector<std::string> _e40 = {"hello"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\n", false)) == _e40);
    }
    {
        std::vector<std::string> _e41 = {"hello\n"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("hello\n", true)) == _e41);
    }
    {
        std::vector<std::string> _e42 = {"", "hello"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("\nhello", false)) == _e42);
    }
    {
        std::vector<std::string> _e43 = {"\n", "hello"};
        PYSTRING_CHECK_ASSERT((pystring_splitlines("\nhello", true)) == _e43);
    }
}

