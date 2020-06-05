#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

/**
 * exercise 11.1
 * vector 是顺序容器，map是关联容器。两类容器的根本差别在于，顺序容器中的元素是“顺序”存储的（虽然不是在内存中连续存储的，但是仍然
 * 是按顺序存储的）。理解顺序的关键在于理解容器支持的操作以及效率
 * 顺序容器的元素按顺序存储，每个元素有唯一对应的位子编号，所有操作都是按编号（位置）进行的。例如获取元素，插入元素，遍历元素。
 * 底层的数据结构是数组、链表，简单但是能保证上面操作的高效。但是对于依赖于‘值’的元素访问，例如查找给定值（find），这种数据结构的实
 * 现是要通过遍历完成的，效率不佳
 * 关联容器的map，就是为了高效的事项“用值访问”这种操作设计的。为了达到这一目的，容器中的元素是按关键字值来存储的，关键字值与元素数
 * 据建立对应的关系，这就是关联的意思。底层数据结构是红黑树，哈希表，可高效的实现按关键字值查找，添加，删除元素的操作*/

/**
 * exercise 11.2
 * For list: 元素数量预先不知道或者是在程序运行过程中频繁变化，元素大（不如大的类的对象），对于元素的访问是是顺序访问很多元素或者是全
 * 部元素。
 * For vector: 元素数量大致可预知，在程序运行过程中不会剧烈变化，元素小（如int），对于元素的访问是随机位置的元素，大部分只在元素尾
 * 部添加和删除元素。
 * For deque: 与vector类似，可以频繁在头尾添加或者删除元素
 * For map: 通过元素的默写特征来访问元素。学生的名字来查询学生的其他信息，学生的名字作为关键字，学生的信息作为元素值。
 * For set: 是集合类型。*/

/**
 * exercise 11.3*/
void exercise11_3()
{
    std::fstream in("words.txt");
    if(!in)
    {
        std::cout << "fail to open file!" << std::endl;
        exit(1);
    }
    std::map<std::string, size_t> words;
    std::string word;
    while(in >> word)
    {
        ++words[word];
    }
    for(const auto& i : words)
        std::cout << i.first << " " << i.second <<"\t";
}

/**
 * exercise11.4*/
std::string& trans(std::string& s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] >= 'A' && s[i] <='Z')
            s[i] -= ('A' - 'a');
        else if(s[i] == ',' || s[i] == '.')
            s.erase(i, 1);
    }
    return s;
}
void exercise11_4()
{
    std::fstream in("words_trans.txt");
    if(!in)
    {
        std::cout << "fail to open file!" << std::endl;
        exit(1);
    }
    std::map<std::string, size_t> words;
    std::string word;
    while(in >> word)
    {
        ++words[trans(word)];
    }
    for(const auto& i : words)
        std::cout << i.first << " " << i.second <<"\t";
}


int main() {
    exercise11_4()
    ;
    return 0;
}
