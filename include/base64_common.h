#ifndef __BASE64_H__
#define __BASE64_H__

#include <memory>
#include <utility>
#include <stdexcept>

#define NS_BASE64_BEGIN namespace b64 {
#define NS_BASE64_END }

NS_BASE64_BEGIN

typedef unsigned char byte;
typedef std::shared_ptr<char> ptr;
typedef std::pair<ptr, std::size_t> buffer;

/**
 * @brief release array memory
 */
struct delete_array_func {
    void operator()(char *p) const
    {
        delete[] p;
    }
};

/**
 * @brief base exception
 */
class base64_error : public std::runtime_error {
  public:
    base64_error(char const *error) : std::runtime_error(error)
    {
    }
};

/**
 * @brief make a buffer from existing memory pointer
 *
 * @param p pointer
 * @param size size of the buffer
 *
 * @return buffer object
 */
inline buffer make_buffer(ptr p, std::size_t size)
{
    return std::make_pair(p, size);
}

NS_BASE64_END

#endif
