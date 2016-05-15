#ifndef __BASE64_KERNEL_H__
#define __BASE64_KERNEL_H__

#include <bitset>
#include <string>
#include <utility>

#include "base64_common.h"

NS_BASE64_BEGIN

template <typename Base64Converter> class base64 {
  public:
    /**
     * @brief encode buffer to base64 string
     *
     * @param p buffer
     * @param size size of buffer
     *
     * @return base64 string
     */
    std::string encode(char const *p, std::size_t size) const
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
                }
                else {
                    // 该字节的数据不存在，直接增加8个零
                    ++padding_chars;
                }
            }
            // 补齐6的差数
            auto padding_indexes = padding_count(static_cast<int>(bin_str.size()), 6);
            for (int i = 0; i < padding_indexes; ++i)
                bin_str += "0";
            // 循环每6个位一组转换成为序号
            std::size_t idx = 0;
            while (idx < bin_str.size()) {
                auto six = bin_str.substr(idx, 6);
                std::bitset<6> b(six);
                result += conv_.index_to_char(static_cast<byte>(b.to_ulong()));
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

    /**
     * @brief decode base64 string to buffer object
     *
     * @param str base64 string
     *
     * @return decoded buffer object
     */
    buffer decode(std::string const &str) const
    {
        // 首先，str的长度一定是4的倍数
        if (str.size() % 4 != 0)
            throw base64_error("input string length is invalid!");
        // 计算出真正的长度，并且分配存储空间
        std::size_t real_size = str.size() * 6 / 8 - std::count(str.begin(), str.end(), '='); // 真正的缓冲的长度
        ptr p(new char[real_size], delete_array_func());
        // 4个字符取出转换为3个字节的数据，然后保存到临时的buff中
        std::size_t curr = 0, out_p = 0;
        while (curr < str.size()) {
            std::string bin_str;
            std::size_t padding_chars = 0;
            for (int i = 0; i < 4; ++i) {
                if (str[curr + i] != '=')
                    bin_str += std::bitset<6>(conv_.char_to_index(str[curr + i])).to_string();
                else
                    ++padding_chars;
            }
            for (std::size_t i = 0; i < 3 - padding_chars; ++i) {
                p.get()[out_p++] = static_cast<char>(std::bitset<8>(bin_str.substr(i * 8, 8)).to_ulong());
            }
            curr += 4;
        }
        // 返回结果
        return std::make_pair(p, real_size);
    }

  private:
    template <typename T> T padding_count(T size, T base) const
    {
        auto m = base - (size % base);
        return m == base ? 0 : m;
    }

  private:
    Base64Converter conv_;
};

#include "base64_conv.h"
typedef base64<base64_conv> base64_codec;

NS_BASE64_END

#endif
