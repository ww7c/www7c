#include <string>
#include <set>

class TextSimilarity
{
public:
    // 生成文本的 3-Gram 集合
    static std::set<std::string> generateNGram(const std::string& text,int n = 3);

    // 计算 Jaccard 相似度
    static double calculateJaccard(const std::set<std::string>& setA,const std::set<std::string>& setB);

    // 直接计算两段文本的相似度
    static double calculateSimilarity(const std::string& textA,const std::string& textB,int n = 3);
};
