#pragma once
#include <string>

class FileManager
{
public:
    // 读取文本文件
    static std::string readFile(const std::string& filePath);

    // 将查重结果写入文件
    static bool writeResult(const std::string& filePath, double result);
};
