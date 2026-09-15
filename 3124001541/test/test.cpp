#include <iostream>
#include <windows.h>
#include <cassert>
#include <set>
#include <cmath>
#include "TextPreprocessor.h"
#include "TextSimilarity.h"

// 测试1：测试 generateNGram() 正常情况
void  test_GenerateNGram()
{
    std::string text = "123456";

    std::set<std::string> result =
        TextSimilarity::generateNGram(text, 3);

    // 检查数量
    assert(result.size() == 4);

    // 检查具体内容
    assert(result.count("123") == 1);
    assert(result.count("234") == 1);
    assert(result.count("345") == 1);
    assert(result.count("456") == 1);

    std::cout << "测试1：generateNGram测试通过" << std::endl;
}

// 测试2：测试文本长度等于N-Gram长度
void  test_GenerateNGramLength()
{
    std::string text = "abc";

    std::set<std::string> result =
        TextSimilarity::generateNGram(text, 3);

    assert(result.size() == 1);
    assert(result.count("abc") == 1);

    std::cout << "测试2：文本长度等于n测试通过" << std::endl;
}

// 测试3：测试文本长度小于N-Gram长度
void  test_GenerateNGramShortText()
{
    std::string text = "ab";

    std::set<std::string> result =
        TextSimilarity::generateNGram(text, 3);

    assert(result.empty());

    std::cout << "测试3：文本长度小于n测试通过" << std::endl;
}


// 测试5：测试Jaccard相似度完全相同
void  test_JaccardSame()
{
    std::set<std::string>text1 = {"我喜欢编程" };

    std::set<std::string>text2 = { "我喜欢编程" };

    double result =
        TextSimilarity::calculateJaccard(text1, text2);

    if(result==1)  std::cout << "测试5：Jaccard完全相同测试通过" << std::endl;
}

// 测试6：测试Jaccard相似度完全不同
void  test_JaccardDifferent()
{
    std::set<std::string> A =
    {
        "我喜欢编程"
    };

    std::set<std::string> B =
    {
        "晚上吃什么"
    };

    double result =
        TextSimilarity::calculateJaccard(A, B);

    if(result==0) std::cout << "测试6：Jaccard完全不同测试通过" << std::endl;
}

// 测试7：测试Jaccard相似度——部分相同
void  test_JaccardPartial()
{
    std::set<std::string> A =
    { "abc","bcd", "cde"};

    std::set<std::string> B =
    {"abc", "bcd"};
    double result =TextSimilarity::calculateJaccard(A, B);//预期结果2/3
    if(std::fabs(result - 2.0 / 3.0) < 0.0001)std::cout << "测试7：Jaccard部分相同测试通过" << std::endl;
}

// ============================================================
// 测试8：测试两个空集合
// ============================================================
void  test_JaccardEmpty()
{
    std::set<std::string> A;
    std::set<std::string> B;

    double result =
        TextSimilarity::calculateJaccard(A, B);

    // 如果你的函数规定两个空集合相似度为0
    assert(result == 0.0);

    std::cout << "测试8：Jaccard空集合测试通过" << std::endl;
}
//测试9: 测试两个文本
void  test_calculateSimilarity()
{
    std::string originalText = "我喜欢。c++编程，";
    std::string plagiarismText = "我喜欢，java编程。";
    // ============================
    // 4. 文本预处理
    // ============================
    originalText = TextPreprocessor::process(originalText);
    plagiarismText = TextPreprocessor::process(plagiarismText);

    std::cout << "--- 预处理后的原文内容 ---" << std::endl;
    std::cout << originalText << std::endl;

    std::cout << "--- 预处理后的抄袭文内容 ---" << std::endl;
    std::cout << plagiarismText << std::endl;

    // ============================
    // 5. 设置 N-gram 参数 使用 3-gram
    const int N = 3;

    // ============================
    // 6. 生成3-gram 集合
    // ============================
    auto originalNGram =
        TextSimilarity::generateNGram(originalText, N);

    auto plagiarismNGram =
        TextSimilarity::generateNGram(plagiarismText, N);

    // ============================
    // 7. 计算 Jaccard 相似度
    // ============================
    double similarity =
        TextSimilarity::calculateJaccard(originalNGram, plagiarismNGram);

    std::cout << "结果相似度为" << similarity << std::endl;
}
// ============================================================
// main：运行所有测试
// ============================================================
int main()
{
    SetConsoleOutputCP(65001); // 将控制台输出编码设置为 UTF-8
    std::cout << "========== TextSimilarity 单元测试 =========="
        << std::endl;

    test_GenerateNGram();
    test_GenerateNGramLength();
    test_GenerateNGramShortText();
    test_JaccardSame();
    test_JaccardDifferent();
    test_JaccardPartial();
    test_JaccardEmpty();
    test_calculateSimilarity();

    std::cout << "============================================"
        << std::endl;

    std::cout << "所有单元测试通过！"
        << std::endl;

    return 0;
}