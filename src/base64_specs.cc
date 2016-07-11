#include "base64_specs.h"

#include <assert.h>

namespace base64
{
namespace specs
{

char IndexToChar(int index)
{
  const char *chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  if (index >= 0 && index <= 63) {
    return chars[index];
  } else {
    // Invalid index value.
    assert(false);
    return '\0';
  }
}

int CharToIndex(char ch)
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
  else {
    // Invalid character.
    assert(false);
    return -1;
  }
}

} // namespace specs
} // namespace base64
