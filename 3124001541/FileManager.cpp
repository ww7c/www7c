#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// 读取文本文件
std::string FileManager::readFile(const std::string& filePath)
{
    // 打开文件
    std::ifstream file(filePath);

    // 判断文件是否打开成功
    if (!file.is_open())
    {
        return "";
    }

    //保存整个文件内容
    std::stringstream buffer;
    buffer << file.rdbuf();

    // 关闭文件
    file.close();

    return buffer.str();
}


// 将查重结果写入文件
bool FileManager::writeResult(const std::string& filePath,double result)
{
    // 打开输出文件
    std::ofstream file(filePath);

    // 判断文件是否打开成功
    if (!file.is_open())
    {
        return false;
    }

    // 设置输出为固定小数格式，并保留两位小数
    file << std::fixed << std::setprecision(2);

    // 写入查重结果
    file << result;

    // 关闭文件
    file.close();

    return true;
}
