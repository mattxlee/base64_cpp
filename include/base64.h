#ifndef __BASE64_H__
#define __BASE64_H__

#include <memory>
#include <string>
#include <utility>

namespace base64
{

typedef std::shared_ptr<char> Ptr;
typedef std::pair<Ptr, std::size_t> Buffer;

template <typename T>
T PaddingCount(T size, T base)
{
  auto m = base - (size % base);
  return m == base ? 0 : m;
}

std::string Encode(const char *p, std::size_t size);
Buffer Decode(std::string const &str);

} // namespace base64

#endif // __BASE64_H__
