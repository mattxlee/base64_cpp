#include "base64_conv.h"

NS_BASE64_BEGIN

base64_conv::base64_conv()
{
}

char base64_conv::index_to_char(byte index) const
{
    char const *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (index >= 0 && index <= 63)
        return chars[index];
    else
        throw base64_error("invalid index!");
}

byte base64_conv::char_to_index(char ch) const
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    else if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    else if (ch >= '0' && ch <= '9')
        return ch - '0' + 26 * 2;
    else if (ch == '+')
        return 26 * 2 + 10;
    else if (ch == '/')
        return 26 * 2 + 11;
    else
        throw base64_error("invalid char!");
}

NS_BASE64_END
