#include "TextPreprocessor.h"
#include<set>
#include <cctype>

// ============================
// 文本预处理
// ============================
std::string TextPreprocessor::process(const std::string& text)
{
    std::string result;

    for (size_t i = 0; i < text.length();)
    {
        unsigned char ch =
            static_cast<unsigned char>(text[i]);
        // ASCII 字符
        if (ch < 128)
        {
            // 去除空白
            if (isWhitespace(ch))
            {
                ++i;
                continue;
            }

            // 大写字母转换成小写
            if (isUpperCase(ch))
            {
                result += toLowerCase(ch);
                ++i;
                continue;
            }

            // ASCII 标点
            std::string current(1, text[i]);

            if (isPunctuation(current))
            {
                ++i;
                continue;
            }

            // 普通 ASCII 字符
            result += text[i];
            ++i;
        }
        // UTF-8 中文字符
        else
        {
            size_t charLength;

            // 2 字节 UTF-8
            if ((ch & 0xE0) == 0xC0)
            {
                charLength = 2;
            }
            // 3 字节 UTF-8
            else if ((ch & 0xF0) == 0xE0)
            {
                charLength = 3;
            }
            // 4 字节 UTF-8
            else if ((ch & 0xF8) == 0xF0)
            {
                charLength = 4;
            }
            else
            {
                // 非法 UTF-8
                ++i;
                continue;
            }

            // 防止越界
            if (i + charLength > text.length())
            {
                break;
            }

            // 取出完整 UTF-8 字符
            std::string current =
                text.substr(i, charLength);

            // 判断中文标点
            if (isPunctuation(current))
            {
                i += charLength;
                continue;
            }

            // 普通中文字符
            result += current;
            i += charLength;
        }
    }

    return result;
}




bool TextPreprocessor::isPunctuation(const std::string& ch)
{
    static const std::set<std::string> punctuation =
    { 
        "，", "。", "！", "？","：", "；","“", "”", "‘","’", "、",// 中文标点
    };

    return punctuation.count(ch) > 0;
}

// 判断是否为空白字符
bool TextPreprocessor::isWhitespace(unsigned char ch)
{
    return std::isspace(ch);
}


// 判断是否为英文大写字母
bool TextPreprocessor::isUpperCase(unsigned char ch)
{
    return ch >= 'A' && ch <= 'Z';
}


// ============================
// 英文大写转换为小写
// ============================
char TextPreprocessor::toLowerCase(unsigned char ch)
{
    return static_cast<char>(ch + ('a' - 'A'));
}
