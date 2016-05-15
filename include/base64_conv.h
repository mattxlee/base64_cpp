#ifndef __BASE64_CONV_H__
#define __BASE64_CONV_H__

#include "base64_common.h"

NS_BASE64_BEGIN

class base64_conv {
  public:
    base64_conv();

    char index_to_char(byte index) const;

    byte char_to_index(char ch) const;
};

NS_BASE64_END

#endif
