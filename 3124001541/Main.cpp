#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "FileManager.h"
#include "TextPreprocessor.h"
#include "TextSimilarity.h"

int main(int argc, char* argv[])
{

    SetConsoleOutputCP(65001); // 将控制台输出编码设置为 UTF-8
    // 1. 检查命令行参数
    if (argc != 4)
    {
        std::cout << "参数错误！" << std::endl;
        std::cout << "使用方法：" << std::endl;
        std::cout << "program.exe 原论文路径 抄袭论文路径 答案路径" << std::endl;
        return 1;
    }

    // 获取三个文件路径
    std::string originalPath = argv[1];
    std::string plagiarismPath = argv[2];
    std::string outputPath = argv[3];

    // ============================
    // 2. 读取原论文
    // ============================
    std::string originalText = FileManager::readFile(originalPath);

    if (originalText.empty())
    {
        std::cout << "无法读取原论文文件：" << originalPath << std::endl;
        return 1;
    }

    // 3. 读取抄袭论文
    std::string plagiarismText = FileManager::readFile(plagiarismPath);

    if (plagiarismText.empty())
    {
        std::cout << "无法读取抄袭论文文件：" << plagiarismPath << std::endl;
        return 1;
    }

    // 4. 文本预处理
    originalText = TextPreprocessor::process(originalText);
    plagiarismText = TextPreprocessor::process(plagiarismText);
   
    // 5. 设置 N-gram 参数 使用 3-gram
    const int N = 3;

    // 6. 生成3-gram 集合
    auto originalNGram =
        TextSimilarity::generateNGram(originalText, N);

    auto plagiarismNGram =
        TextSimilarity::generateNGram(plagiarismText, N);

    // 7. 计算 Jaccard 相似度
    double similarity =
        TextSimilarity::calculateJaccard( originalNGram, plagiarismNGram);

    // 8. 输出结果到答案文件
    if (!FileManager::writeResult(outputPath, similarity))
    {
        std::cout << "写入失败：" << outputPath << std::endl;
        return 1;
    }

    // 9. 程序运行成功
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "论文查重完成！" << std::endl;
    std::cout << "相似度：" << similarity << std::endl;

    return 0;
}