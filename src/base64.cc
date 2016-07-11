#include "base64.h"

#include <assert.h>

#include <bitset>

#include "base64_specs.h"

namespace base64
{

std::string Encode(const char *p, std::size_t size)
{
  std::string result;
  // 循环取出每三个字符作为一组
  std::size_t curr = 0;
  while (curr < size) {
    std::string bin_str;
    int padding_chars = 0;
    for (std::size_t i = 0; i < 3; ++i) {
      if (curr + i < size) {
        // 该字节的数据存在，直接转成二进制字符串
        std::bitset<8> b(p[curr + i]);
        bin_str += b.to_string();
      } else {
        // 该字节的数据不存在，直接增加8个零
        ++padding_chars;
      }
    }
    // 补齐6的差数
    auto padding_indexes = PaddingCount(static_cast<int>(bin_str.size()), 6);
    for (int i = 0; i < padding_indexes; ++i)
      bin_str += "0";
    // 循环每6个位一组转换成为序号
    std::size_t idx = 0;
    while (idx < bin_str.size()) {
      auto six = bin_str.substr(idx, 6);
      std::bitset<6> b(six);
      result += specs::IndexToChar(static_cast<int>(b.to_ulong()));
      idx += 6;
    }
    // 补齐=号
    for (int i = 0; i < padding_chars; ++i)
      result += '=';
    // 下一组
    curr += 3;
  }
  return result;
}

Buffer Decode(std::string const &str)
{
  // 首先，str的长度一定是4的倍数
  if (str.size() % 4 != 0) {
    // input string length is invalid!
    return Buffer();
  }
  // 计算出真正的长度，并且分配存储空间
  std::size_t real_size =
      str.size() * 6 / 8 -
      std::count(str.begin(), str.end(), '='); // 真正的缓冲的长度
  Ptr p(new char[real_size], [](char *p) { delete[] p; });
  // 4个字符取出转换为3个字节的数据，然后保存到临时的buff中
  std::size_t curr = 0, out_p = 0;
  while (curr < str.size()) {
    std::string bin_str;
    std::size_t padding_chars = 0;
    for (int i = 0; i < 4; ++i) {
      if (str[curr + i] != '=')
        bin_str +=
            std::bitset<6>(specs::CharToIndex(str[curr + i])).to_string();
      else
        ++padding_chars;
    }
    for (std::size_t i = 0; i < 3 - padding_chars; ++i) {
      p.get()[out_p++] = static_cast<char>(
          std::bitset<8>(bin_str.substr(i * 8, 8)).to_ulong());
    }
    curr += 4;
  }
  // 返回结果
  return std::make_pair(p, real_size);
}

} // namespace base64
