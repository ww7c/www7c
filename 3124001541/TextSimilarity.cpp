#include "TextSimilarity.h"

#include<iostream>
#include <algorithm>
#include <iterator>
#include<vector>
// ============================================================
// 按照 UTF-8 字符进行切分，生成3-Gram集合
// ============================================================
std::set<std::string> TextSimilarity::generateNGram(const std::string& text,int n)
{
    std::set<std::string> nGramSet;

    // N-Gram 长度必须大于 0
    if (n <= 0)
    {
        return nGramSet;
    }

    // --------------------------------------------------------
    // 第一步：将 UTF-8 字符切分出来
    // --------------------------------------------------------
    std::vector<std::string> chars;

    for (size_t i = 0; i < text.length();)
    {
        unsigned char ch =static_cast<unsigned char>(text[i]);

        size_t charLength = 1;

        // ASCII 字符
        if ((ch & 0x80) == 0)
        {
            charLength = 1;
        }
        // 2 字节 UTF-8 字符
        else if ((ch & 0xE0) == 0xC0)
        {
            charLength = 2;
        }
        // 3 字节 UTF-8 字符
        else if ((ch & 0xF0) == 0xE0)
        {
            charLength = 3;
        }
        // 4 字节 UTF-8 字符
        else if ((ch & 0xF8) == 0xF0)
        {
            charLength = 4;
        }
        else
        {
            // 无法识别的 UTF-8 字 当作一个字节处理
            charLength = 1;
        }

        // 防止字符串越界
        if (i + charLength > text.length())
        {
            charLength = 1;
        }

        chars.push_back(text.substr(i, charLength));

        i += charLength;
    }

    // --------------------------------------------------------
    // 第二步：按照 UTF-8 字符生成 N-Gram
    // --------------------------------------------------------
    if (chars.size() < static_cast<size_t>(n))
    {
        return nGramSet;
    }

    for (size_t i = 0;
        i + static_cast<size_t>(n) <= chars.size();
        ++i)
    {
        std::string gram;

        for (int j = 0; j < n; ++j)
        {
            gram += chars[i + j];
        }
        //std::cout << gram << "/"; // 输出gram，而不是原始chars

        nGramSet.insert(gram);
    }

    return nGramSet;
}


// ============================================================
// 功能：计算两个集合的 Jaccard 相似度
// ============================================================
double TextSimilarity::calculateJaccard(
    const std::set<std::string>& setA,
    const std::set<std::string>& setB)
{
    // 两个集合都为空
    if (setA.empty() && setB.empty())
    {
        return 1.0;
    }

    // 计算交集大小
    std::set<std::string> intersectionSet;

    std::set_intersection(
        setA.begin(),
        setA.end(),
        setB.begin(),
        setB.end(),
        std::inserter(
            intersectionSet,
            intersectionSet.begin()
        )
    );

    // 计算并集大小
    std::set<std::string> unionSet;

    std::set_union(
        setA.begin(),
        setA.end(),
        setB.begin(),
        setB.end(),
        std::inserter(
            unionSet,
            unionSet.begin()
        )
    );

    // 防止除零
    if (unionSet.empty())
    {
        return 0.0;
    }

    return static_cast<double>(intersectionSet.size()) / static_cast<double>(unionSet.size());
}


// 功能：直接计算两段文本的相似度
double TextSimilarity::calculateSimilarity(
    const std::string& textA,
    const std::string& textB,
    int n)
{
    // 生成文本 A 的 N-Gram 集合
    std::set<std::string> setA =
        generateNGram(textA, n);

    // 生成文本 B 的 N-Gram 集合
    std::set<std::string> setB =
        generateNGram(textB, n);

    // 计算 Jaccard 相似度
    return calculateJaccard(setA, setB);
}