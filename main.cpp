#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <sstream>
#include <utility>
#include <iterator>

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

class iterator;

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

/**
 * exercise11.5
 * map 保存<关键字，值>这样的一对值，按关键字访问值。
 * set 保存值的集合，按给的值访问数据*/

/**
 * exercise11.6
 * set 和 list都可以元素的集合
 * set: 不需要保存元素的顺序的话就用set.
 * list：保存了元素的前后顺序。*/

/**
 * exercise11.7*/
void addFamily(std::map<std::string, std::vector<std::string>>& f, const std::string& s)
{
    if(f.find(s) == f.end())
        f[s] = std::vector<std::string>();
    else
        std::cout << "this family already exist!" << std::endl;
}
void addName(std::map<std::string, std::vector<std::string>>& f, const std::string& family, const std::string& name)
{
    if(f.find(family) == f.end())
        std::cout << "no such a family in Marklohe!" << std::endl;
    else
        f[family].push_back(name);
}
void exercise11_7()
{
    std::map<std::string, std::vector<std::string>> Marklohe;
    addFamily(Marklohe, "Olaf");
    addFamily(Marklohe, "Joerg");
    addName(Marklohe, "Olaf", "aaa");
    addName(Marklohe, "Olaf", "bbb");
    addName(Marklohe, "Joerg", "aaa");
    addName(Marklohe, "Joerg", "bbb");
    addName(Marklohe, "AAA", "aaa");

    for(const auto& i:Marklohe)
    {
        std::cout << i.first << " family have: " << "\t";
        for(const auto& j:i.second)
            std::cout << j << " ";
        std::cout << std::endl;
    }
}

/**
 * exercise11.8*/
void addWord(std::vector<std::string>& words, const std::string& word)
{
    if(find(words.begin(),words.end(),word) == words.end())
        words.push_back(word);
    else
        std::cout << "this word is already in the word list!" << std::endl;
}
void exercise11_8()
{
    std::vector<std::string> words;
    addWord(words, "aaa");
    addWord(words, "bbb");
    addWord(words, "aaa");
    addWord(words, "bbb");
    addWord(words, "ccc");
    for(const auto &i : words)
        std::cout << i << "\t";
}

void exercise11_8_set()
{
    std::set<std::string> words;
    words.insert("aaa");
    words.insert("bbb");
    words.insert("aaa");
    words.insert("bbb");
    words.insert("ccc");
    for(const auto& i : words)
        std::cout << i << "\t";
}

/**
 * exercise11.9*/
void exercise11_9()
{
    std::map<std::string, std::list<int>> wordLineNo;
    std::fstream in("paragraph.txt");
    std::string line;
    int lineNo = 0;
    std::string word;
    while(getline(in, line))
    {
        lineNo++;
        std::istringstream lineIn(line);
        while(lineIn >> word)
        {
            wordLineNo[word].push_back(lineNo);
        }
    }
    for(const auto& i : wordLineNo)
    {
        std::cout << i.first << " : ";
        for(const auto& j : i.second)
            std::cout << j << " ";
        std::cout << std::endl;
    }
}

/**
 * exercise11.10
 * map<vector<int>::interator, int> 是可以的，因为vector的迭代器是支持 < 操作的。
 * map<list<int>::interator, int>是不可以的，因为list的迭代器是不支持 < 操作的，因为list的元素不是连续储存的。*/

/**
 * exercise11.11, because we do not define the sales_data class so we comment this codes*/
/*void exercise11_11()
{
    bool* ptrCompareIsbn = &Sales_data::compareIsbn;
    map<Sales_data, ptrCompareIsbn> bookstore(compareIsbn);
}*/

/**
 * exercise11.12*/
void exercise11_12()
{
    std::vector<std::pair<std::string, int>> a;
    std::fstream in("string_int.txt");
    if(!in)
        std::cout << "fail to open file!" << std::endl;
    std::string str;
    int num;
    while(in >> str && in >> num)
    {
        a.push_back({str, num});
    }
    for(const auto& i : a)
        std::cout << i.first << " " << i.second << std::endl;
}

/**
 * exercise11.13*/
void exercise11_13()
{
    std::vector<std::pair<std::string, int>> a;
    std::fstream in("string_int.txt");
    if(!in)
        std::cout << "fail to open file!" << std::endl;
    std::string str;
    int num;
    while(in >> str && in >> num)
    {
        //there are three different ways to init a pair. i think using {} is the most easy way.
        /*a.push_back({str, num});
        a.push_back(std::pair<std::string, int>(str, num));
        a.push_back(make_pair(str, num));*/
    }
    for(const auto& i : a)
        std::cout << i.first << " " << i.second << std::endl;
}

/**
 * exercise11.14*/
void addFamilyWithBirthday(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& f, const std::string& s)
{
    if(f.find(s) == f.end())
        f[s] = std::vector<std::pair<std::string, std::string>>();
    else
        std::cout << "this family already exist!" << std::endl;
}
void addNameWithBirthday(std::map<std::string, std::vector<std::pair<std::string, std::string>>>& f, const std::string& family,
        const std::string& name, const std::string birthday)
{
    if(f.find(family) == f.end())
        std::cout << "no such a family in Marklohe!" << std::endl;
    else
        f[family].push_back({name, birthday});
}
void exercise11_14()
{
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> Marklohe;
    addFamilyWithBirthday(Marklohe, "James");
    addFamilyWithBirthday(Marklohe, "Smith");
    addNameWithBirthday(Marklohe, "James", "leo", "12.09.2011");
    addNameWithBirthday(Marklohe, "James", "tom", "18.03.2016");
    addNameWithBirthday(Marklohe, "Smith", "jack", "22.12.1998");
    addNameWithBirthday(Marklohe, "Smith", "ali", "24.09.1994");
    for(const auto& i : Marklohe)
    {
        std::cout << i.first << " : " << std::endl;
        for(const auto& j : i.second)
            std::cout << "name: " << j.first << ", birthday: " << j.second << std::endl;
    }
}

/**
 * exercise11.15
 * map<int, vector<int>>
 * mapped_type is vector<int>
 * key_type is int
 * value_type is pair<int, vector<int>>*/

/**
 * exercise11.16*/
void exercise11_16()
{
    std::map<int, int> a;
    auto it = a.begin();
    it->second = 1;
    std::cout << it->second << std::endl;
}

/**exercise11.17
 * std::multiset<std::string> c;
 * std::vector<std::string> v;
 * copy(v.begin(), v.end(), inserter(c, c.end())) is false
 * copy(v.begin(), v.end(), back_inserter(c)) is false
 * copy(c.begin(), c.end(), inserter(v, v,end())) is right
 * copy(c.begin(), c.end(), back_inserter(v))is right*/

/**
 * exercise 11.18*/
void exercise11_18()
{
    std::map<std::string, size_t> words;
    auto it = words.begin();
}

/**
 * exercise 11.19
 * please use auto, for exercise 18 I have tried with different iterator but no of them works*/

/**
 * exercise 11.20
 * by using insert() is more easy to understand*/
void exercise11_20()
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
        auto ret = words.insert({word, 1});
        if(!ret.second)
        {
            (*(ret.first)).second++;
        }
    }
    for(const auto& i : words)
        std::cout << i.first << " " << i.second <<"\t";
}

/**
 * exercise 11.21
 * combine insert() and if(){} in the previous exercise.*/

/**
 * exercise 11.22
 * parameter: pair<string, vector<int>>
 * return type: pair<map<string, vector<int>>::iterator, bool>*/

/**exercise 11.23*/
void addM(std::multimap<std::string, std::string>& m, const std::string& lastName, const std::string& firstName)
{
    m.insert(std::pair<std::string, std::string>(lastName, firstName));
/*    m.insert({lastName, firstName});
    m.insert(make_pair(lastName, firstName));*/
}
void exercise11_23()
{
    std::multimap<std::string, std::string> Marklohe;
    addM(Marklohe, "John", "Hand");
    addM(Marklohe, "John", "Schuhe");
    addM(Marklohe, "John", "Handy");
    addM(Marklohe, "Alfa", "JK");
    for(const auto& i : Marklohe)
        std::cout << i.first << " " << i.second << std::endl;
}

/**
 * exercise 11.24
 * if map it is already has a key 0, the the codes means to give the value to the key 0.
 * if map it is not has the key o, then it means to init a new pair<int, int> key value 0 and mapped value is 0(init).
 * then assign 1 to the mapped value.*/

/**
 * exercise 11.25
 * this will the change the first value of element of vector<int>.
 * but for this situation, there will be a error because there is no element in the vector<int> m. Can not assign a value
 * to the first element of m, because there is even no first element.*/

/**
 * exercise 11.26*/
void exercise11_26()
{
    std::map<int, int> m;
    m[1] = 11;
    m[2] = 22;
    int a = m[1];
    int b = m[2];
    auto c = m.at(2);

    std::cout << a << "\t" << b << std::endl;
    std::cout << m.at(1) << "\t" << c << m.at(3);
}

/**
 * exercise 11.27
 * m.find(k) 只返回指向第一个关键字是k的元素；而count(k), 返回有多少元素等于关键字*/

/**
 * exercise 11.28*/
void exercise11_28()
{
    std::map<std::string, std::vector<int>> m;
    std::map<std::string, std::vector<int>>::iterator it;
}

/**
 * exercise 11.29
 * upper_bound(k): the first element that bigger than k
 * lower_bound(k): the first element that not smaller than the k
 * equal_range(k): a pair<iterator a, iterator b> in the range of iterator a and b, all the elements are equal to k.*/

/**exercise 11.30
 * pos.first 如果存在的关键字的话，就是第一个等于这个关键字的元素。->就是这个元素中的值。也就是关键字所代表的这个作家的书。++pos.first
 * 就是把这个迭代器后移，一直到不等于关键字为止。*/

/**
 * exercise 11.31*/
void findAndDelete(std::multimap<std::string, std::string>& a, const std::string& author)
{
    int cnt = a.count(author);
    if(a.find(author) == a.end())
        std::cout << "no this author!" << std::endl;
    else
        while(cnt)
        {
            a.erase(a.find(author));
            --cnt;
        }

}

void findAndDeleteWithEqualRange(std::multimap<std::string, std::string>& a, const std::string& author)
{
    auto ret = a.equal_range(author);
    if(ret.first == ret.second){
        std::cout << "no this author!" << std::endl;
    } else{
        a.erase(ret.first, ret.second);
    }
}
void exercise11_31()
{
    std::multimap<std::string, std::string> authors;
    authors.insert({"a", "222"});
    authors.insert(std::pair<std::string, std::string>("a", "666"));
    authors.insert(std::make_pair("a", "111"));
    authors.insert({"b", "000"});
    authors.insert({"b", "888"});
    authors.insert({"d", "9090"});
    authors.insert({"c", "333"});
    authors.insert({"c", "444"});
    findAndDelete(authors, "aaa");
    findAndDelete(authors, "a");
    findAndDeleteWithEqualRange(authors, "bbb");
    findAndDeleteWithEqualRange(authors, "b");
    for(const auto& i : authors)
        std::cout << i.first << ": " << i.second << std::endl;
}

int main() {
    exercise11_31()
            ;
    return 0;
}
