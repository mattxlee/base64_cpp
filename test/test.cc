#include <cstring>
#include <gtest/gtest.h>

#include "base64.h"

#define STRING_SOURCE                                                                                                  \
    "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust "  \
    "of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, "      \
    "exceeds the short vehemence of any carnal pleasure."

#define STRING_BASE64                                                                                                  \
    "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"                                     \
    "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"                                     \
    "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"                                     \
    "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"                                     \
    "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="

TEST(base64_test, to_base64)
{
    EXPECT_EQ(STRING_BASE64, base64::Encode(STRING_SOURCE, strlen(STRING_SOURCE)));
}

TEST(base64_test, from_base64)
{
    auto _buff = base64::Decode(STRING_BASE64);
    EXPECT_EQ(0, std::memcmp(_buff.first.get(), STRING_SOURCE, strlen(STRING_SOURCE)));
}
