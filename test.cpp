#include <iostream>

#include "pystring.h"
#include "unittest.h"

PYSTRING_TEST_APP(PyStringUnitTests)


PYSTRING_ADD_TEST(pystring, endswith)
{
    PYSTRING_CHECK_EQUAL(pystring::endswith("", ".mesh"), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith("help", ".mesh"), false);
    PYSTRING_CHECK_EQUAL(pystring::endswith(".mesh", ".mesh"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("a.mesh", ".mesh"), true);
    PYSTRING_CHECK_EQUAL(pystring::endswith("a.", "."), true);
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
