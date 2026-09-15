#include <string>

class TextPreprocessor
{
public:
    // 文本预处理
    static std::string process(const std::string& text);

private:
    //判断字符是否为中文标点
    static bool isPunctuation(const std::string& ch);
    // 判断字符是否为空白字符
    static bool isWhitespace(unsigned char ch);

    // 判断字符是否为英文大写字母
    static bool isUpperCase(unsigned char ch);

    // 将英文大写字母转换为小写
    static char toLowerCase(unsigned char ch);
};
