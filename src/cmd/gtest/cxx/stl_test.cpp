#include "base/art_str.h"
#include "ut_config.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <complex>
#include <ctime>
#include <deque>
#include <filesystem>
#include <fstream>
#include <future>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

std::tuple<std::vector<std::string>, std::vector<std::string>>
listFsPrefix(const std::string& prefix)
{
    std::vector<std::string> dirs;
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(prefix))
    {
        // std::cout << "path: " << entry.path().string()
        //           << ", dir: " << (entry.is_directory() ? "true" : "false")
        //           << ", filename: " << entry.path().filename() << ", stem: " <<
        //           entry.path().stem()
        //           << ", extend: " << entry.path().extension() << std::endl;
        if (entry.is_directory())
        {
            dirs.push_back(entry.path().filename());
        }
        else
        {
            files.push_back(entry.path().filename());
        }
    }
    return std::make_tuple(dirs, files);
}

static void listFsBFS(const std::string& prefix)
{
    std::queue<std::string> pathQueue;
    pathQueue.push(prefix);
    while (!pathQueue.empty())
    {
        std::string curPath = pathQueue.front();
        pathQueue.pop();
        std::tuple<std::vector<std::string>, std::vector<std::string>> entries =
            listFsPrefix(curPath);

        for (auto& dir : std::get<0>(entries))
        {
            std::string newPrefix = (std::filesystem::path(curPath) / dir).string();
            pathQueue.push(newPrefix);
        }

        for (auto& file : std::get<1>(entries))
        {
            std::cout << "prefix: " << curPath << ", file: " << file << std::endl;
        }
    }
}

static void listFsDFS(const std::string& prefix)
{
    // 深度优先
    std::stack<std::string> pathStack;
    pathStack.push(prefix);

    while (!pathStack.empty())
    {
        std::string curPath = pathStack.top();
        pathStack.pop();

        auto [dirs, files] = listFsPrefix(curPath);

        for (auto it = dirs.rbegin(); it != dirs.rend(); ++it)
        {
            std::string newPrefix = (std::filesystem::path(curPath) / *it).string();
            pathStack.push(newPrefix);
        }

        for (auto& file : files)
        {
            std::cout << "prefix: " << curPath << ", file: " << file << std::endl;
        }
    }
}

TEST(listFsDFS, 001)
{
    // listFsBFS("/Users/wu.feihu/ws/art-cpp/deps");
}

#ifdef RUN_ALL_TEST_CASE
static std::string joinThreeIntValues(int a, int b, int c)
{
    std::string tmp = std::to_string(a) + "-" + std::to_string(b) + "-" + std::to_string(c);
    return tmp;
}

TEST(bind, 001)
{
    std::function<std::string(int, int)> f2 =
        std::bind(joinThreeIntValues, 10, std::placeholders::_1, std::placeholders::_2);
    EXPECT_EQ(f2(20, 30), "10-20-30");

    std::function<std::string(int, int)> f3 =
        std::bind(joinThreeIntValues, 10, std::placeholders::_2, std::placeholders::_1);
    EXPECT_EQ(f3(20, 30), "10-30-20");

    class Calculator
    {
    public:
        Calculator(std::string prefix) : _prefix(prefix) {}
        std::string join(int a, double b, const std::string& c)
        {
            return _prefix + "-" + std::to_string(a) + "-" + std::to_string(b) + "-" + c;
        }

    private:
        std::string _prefix;
    };
    Calculator calc("haha");

    std::function<std::string(int, double, const std::string&)> f4 =
        std::bind(&Calculator::join, &calc, std::placeholders::_1, std::placeholders::_2,
                  std::placeholders::_3);
    EXPECT_EQ(f4(3, 3.14, "world"), "haha-3-3.140000-world");

    std::function<std::string(int, double, const std::string&)> f5 =
        std::bind(&Calculator::join, std::make_shared<Calculator>("hi"), std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3);
    EXPECT_EQ(f5(3, 3.14, "world"), "hi-3-3.140000-world");
}

static std::string demangle(const char* name)
{
    int status = -1;
    std::unique_ptr<char, void (*)(void*)> res(abi::__cxa_demangle(name, nullptr, nullptr, &status),
                                               std::free);
    return (status == 0) ? res.get() : name;
}

template <typename T> static void printType(const T&)
{
    // 为了保证程序输出整洁，不在控制台上输出
    std::string str = demangle(typeid(T).name());
}

TEST(decltype, 001)
{
    int x = 10;
    std::vector<int> y;
    decltype(x) a = 20;
    decltype(y) b;
    printType(y);
}

TEST(mapErase, 001)
{
    std::map<std::string, int> data = {
        {"apple", 1}, {"banana", 2}, {"cherry", 3}, {"date", 4}, {"elderberry", 5}};

    for (auto it = data.begin(); it != data.end();)
    {
        if (it->first.find('a') != std::string::npos)
        {
            data.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

TEST(startsWith, 001)
{
    EXPECT_TRUE(art::str::startsWith("abcdef", "a"));
    EXPECT_FALSE(art::str::startsWith(" \t\nabcdef", "a"));
}

TEST(endsWith, 001)
{
    EXPECT_TRUE(art::str::endsWith(" \t\nabcdef ", " "));
    EXPECT_TRUE(art::str::endsWith(" \t\nabcdefg", "fg"));
    EXPECT_FALSE(art::str::endsWith(" \t\nabcdef", "xa"));
}

TEST(toUpper, 001)
{
    EXPECT_EQ(art::str::toUpper("ab-dEf134-\r\t\n./"), "AB-DEF134-\r\t\n./");
}

TEST(toLower, 001)
{
    EXPECT_EQ(art::str::toLower("Ab-dEf134-\r\t\n./"), "ab-def134-\r\t\n./");
}

TEST(strtrim, 001)
{
    EXPECT_EQ(art::str::strtrim(" \t\n abcdefg \n\t\r ", "\n\t \r"), "abcdefg");
    EXPECT_EQ(art::str::strtrim(" \t\n abcdefg \n\t ", "\n\t "), "abcdefg");
    EXPECT_EQ(art::str::strtrim(" \t\n abcdefg ", "\n\t "), "abcdefg");
}

TEST(strncasecmp, 002)
{
    char szBuf[100] = "help      cluster";
    size_t startpos = 5;
    EXPECT_EQ(szBuf[startpos], ' ');
    while (isspace(szBuf[startpos]))
    {
        startpos++;
    }
    EXPECT_EQ(szBuf[startpos], 'c');

    startpos = 5;
    snprintf(szBuf, sizeof(szBuf), "%s", "help ");
    while (isspace(szBuf[startpos]))
    {
        startpos++;
    }
    EXPECT_EQ(szBuf[5], '\0');
    EXPECT_EQ(startpos, 5);
    EXPECT_EQ(szBuf[startpos], '\0');
}

TEST(strncasecmp, 001)
{
    EXPECT_EQ(strncasecmp("help xxxx", "help ", 5), 0);
    EXPECT_EQ(strncasecmp("help ", "help xxxx", 5), 0);
    EXPECT_EQ(strncasecmp("help ", "help ", 5), 0);
    EXPECT_NE(strncasecmp("help", "help ", 5), 0);
}

TEST(strsplit, 001)
{
    EXPECT_THAT(art::str::strsplit("a;b;c", ";"), ::testing::ElementsAre("a", "b", "c"));
    EXPECT_THAT(art::str::strsplit("a;b;c;", ";"), ::testing::ElementsAre("a", "b", "c", ""));
    EXPECT_THAT(art::str::strsplit("a", ";"), ::testing::ElementsAre("a"));
    EXPECT_THAT(art::str::strsplit("a", ""), ::testing::ElementsAre("a"));
    EXPECT_THAT(
        art::str::strsplit("a;b;;c;d;", ";"),
        ::testing::AllOf(::testing::SizeIs(6), ::testing::ElementsAre("a", "b", "", "c", "d", "")));
    EXPECT_THAT(art::str::strsplit("", ";"), ::testing::ElementsAre(""));
    EXPECT_THAT(art::str::strsplit("a;b;c", ";"),
                ::testing::AllOf(::testing::SizeIs(3), ::testing::ElementsAre("a", "b", "c")));
    EXPECT_THAT(art::str::strsplit("", ""),
                ::testing::AllOf(::testing::SizeIs(1), ::testing::ElementsAre("")));
}

TEST(is_pod, 001)
{
    struct NonPodType
    {
        int x;
        virtual void func()
        {
            std::cout << "haha" << std::endl;
        }
    };
    struct PodType
    {
        int x;
        double y;
    };
    EXPECT_TRUE(std::is_pod<int>::value);
    EXPECT_FALSE(std::is_pod<std::string>::value);
    EXPECT_FALSE(std::is_pod<NonPodType>::value);
    EXPECT_TRUE(::std::is_trivial_v<PodType>);
    EXPECT_TRUE(::std::is_standard_layout_v<PodType>);
}

TEST(array, 001)
{
    // array在stack上分配内存，在小尺寸上比vector有更好性能
    std::array<int, 3> arr0 = {3, 2, 7};
    std::array<int, 5> arr1 = {6, 4, 5, 9, 1};
    std::array<int, 2> arr2;
    std::array<int, 3> arr3 = {6, 4, 5};
    EXPECT_TRUE(arr0.size() == 3 && arr1.size() == 5 && arr2.size() == 2);

    arr3 = arr0;
    EXPECT_THAT(arr3, ::testing::ElementsAre(3, 2, 7));
    EXPECT_THAT(arr0, ::testing::ElementsAre(3, 2, 7));

    std::array<int, 3> arr4;
    EXPECT_THROW(arr4.at(100), std::out_of_range);

    std::array<int, 3> arr5{};
    std::array<int, 3> arr6 = {};
    std::array<int, 3> arr7 = {1};
    EXPECT_THAT(arr5, ::testing::ElementsAre(0, 0, 0));
    EXPECT_THAT(arr6, ::testing::ElementsAre(0, 0, 0));
    EXPECT_THAT(arr7, ::testing::ElementsAre(1, 0, 0));

    std::array<int, 3> arr8;
    arr8.fill(32);
    EXPECT_THAT(arr8, ::testing::ElementsAre(32, 32, 32));

    std::array<std::string, 3> arr9 = {"hello", "world"};
    EXPECT_THAT(arr9, ::testing::ElementsAre("hello", "world", ""));
}

TEST(minMaxElement, 001)
{
    std::vector<int> v0 = {2, 5, 4, 1, 6, 3};
    std::vector<int>::const_iterator minPos = std::min_element(v0.cbegin(), v0.cend());
    EXPECT_EQ(*minPos, 1);

    std::vector<int>::iterator minPos2 = std::min_element(v0.begin(), v0.end());
    EXPECT_EQ(*minPos2, 1);

    EXPECT_EQ(*std::max_element(v0.begin(), v0.end()), 6);
    EXPECT_EQ(*std::max_element(v0.cbegin(), v0.cend()), 6);

    std::sort(v0.begin(), v0.end());
    EXPECT_THAT(v0, ::testing::ElementsAre(1, 2, 3, 4, 5, 6));

    std::vector<int>::iterator pos0 = std::find(v0.begin(), v0.end(), 3);
    EXPECT_EQ(*pos0, 3);

    std::reverse(pos0, v0.end());
    EXPECT_THAT(v0, ::testing::ElementsAre(1, 2, 6, 5, 4, 3));
}

TEST(stdSet, 001)
{
    std::set<int, std::greater<int>> s0 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THAT(s0, ::testing::ElementsAre(9, 8, 7, 6, 5, 4, 3, 2, 1));

    std::deque<int> d0;
    std::transform(s0.cbegin(), s0.cend(), std::back_inserter(d0),
                   std::bind(std::multiplies<int>(), std::placeholders::_1, 10));
    EXPECT_THAT(d0, ::testing::ElementsAre(90, 80, 70, 60, 50, 40, 30, 20, 10));

    std::replace_if(d0.begin(), d0.end(),
                    std::bind(std::equal_to<int>(), std::placeholders::_1, 70), 42);
    EXPECT_THAT(d0, ::testing::ElementsAre(90, 80, 42, 60, 50, 40, 30, 20, 10));

    d0.erase(
        std::remove_if(d0.begin(), d0.end(),
                       std::bind(std::logical_and<bool>(),
                                 std::bind(std::greater_equal<int>(), std::placeholders::_1, 50),
                                 std::bind(std::less_equal<int>(), std::placeholders::_1, 80))),
        d0.end());
    EXPECT_THAT(d0, ::testing::ElementsAre(90, 42, 40, 30, 20, 10));
}

TEST(add, 001)
{
    class AddValue
    {
    private:
        int _theValue;

    public:
        AddValue(int v) : _theValue(v) {}
        void operator()(int& elem) const
        {
            elem += _theValue;
        }
    };
    std::list<int> li;
    for (int i = 1; i <= 9; ++i)
    {
        li.push_back(i);
    }
    EXPECT_THAT(li, ::testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9));

    std::for_each(li.begin(), li.end(), AddValue(10));
    EXPECT_THAT(li, ::testing::ElementsAre(11, 12, 13, 14, 15, 16, 17, 18, 19));

    std::for_each(li.begin(), li.end(), AddValue(*li.begin()));
    EXPECT_THAT(li, ::testing::ElementsAre(22, 23, 24, 25, 26, 27, 28, 29, 30));

    std::list<char> li2;
    for (char c = 'a'; c <= 'z'; ++c)
    {
        li2.push_back(c);
    }
    EXPECT_THAT(li2, ::testing::ElementsAre('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                                            'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                            'w', 'x', 'y', 'z'));
    for (auto elem : li2)
    {
    }

    // 删除第一个元素
    while (!li2.empty())
    {
        char c = li2.front();
        li2.pop_front();
        // std::cout << c << " ";
    }
}

TEST(vector, 001)
{
    std::vector<int> v0;
    for (int i = 1; i <= 6; ++i)
    {
        v0.push_back(i);
    }
    EXPECT_THAT(v0, ::testing::ElementsAre(1, 2, 3, 4, 5, 6));
    for (int i = 0; i < v0.size(); ++i)
    {
        EXPECT_EQ(v0[i], i + 1);
    }
}

static std::vector<int> cvtInitList(std::initializer_list<int> li)
{
    std::vector<int> vec;
    for (auto it = li.begin(); it != li.end(); ++it)
    {
        vec.push_back(*it);
    }
    // for (auto val : li)
    // {
    // }
    return vec;
}

TEST(initializer_list, 001)
{
    EXPECT_THAT(cvtInitList({2, 3, 4, -1}), ::testing::ElementsAre(2, 3, 4, -1));
    class MyContainer
    {
    private:
        std::vector<int> _data;

    public:
        MyContainer(std::initializer_list<int> init) : _data(init) {}
        std::vector<int> getData()
        {
            return _data;
        }
    };
    MyContainer mc = {2, 3, 4, -1};
    EXPECT_THAT(mc.getData(), ::testing::ElementsAre(2, 3, 4, -1));
}

TEST(foreach, 001)
{
    struct PrintVecInt
    {
        void operator()(int x) const
        {
            // std::cout << x << " ";
        }
    };
    std::vector<int> v0 = {1, 2, 3, 4};

    std::for_each(v0.begin(), v0.end(), PrintVecInt());
    std::for_each(v0.begin(), v0.end(), [](int x) {
        // std::cout << x << " ";
    });

    // std::vector<int> v1 = {2, 3, 4, 5};
    // tbb::parallel_for_each(v1.begin(), v1.end(), [](int& x) { x *= 2; });
    // EXPECT_THAT(v1, ::testing::ElementsAre(4, 6, 8, 10));
    std::map<std::string, int> m0{
        {"tim", 3},
        {"struppi", 7},
    };
    EXPECT_THAT(m0, ::testing::ContainerEq(std::map<std::string, int>({
                        {"struppi", 7},
                        {"tim", 3},
                    })));

    // 注意: 不关注顺序
    EXPECT_THAT(m0, ::testing::UnorderedElementsAre(::testing::Pair("struppi", 7),
                                                    ::testing::Pair("tim", 3)));
    // 注意: 关注顺序
    EXPECT_THAT(m0,
                ::testing::ElementsAre(::testing::Pair("struppi", 7), ::testing::Pair("tim", 3)));

    std::map<std::string, int> m1{
        {"tim", 3},
        {"struppi", 7},
    };
    std::for_each(m1.begin(), m1.end(), [](std::pair<const std::string, int>& elem) {
        elem.second *= elem.second;
        // std::cout << elem.first << ": " << elem.second << std::endl;
    });
    EXPECT_THAT(m1, ::testing::ContainerEq(std::map<std::string, int>({
                        {"struppi", 49},
                        {"tim", 9},
                    })));

    std::for_each(m1.begin(), m1.end(), [](const std::map<std::string, int>::value_type& elem) {
        // std::cout << elem.first << ": ---->" << elem.second << std::endl;
    });

    std::map<std::string, float> m2{
        {"BASF", 369.50},
        {"VW", 413.50},
        {"Daimler", 819.00},
        {"BMW", 834.00},
    };
    m2["Siemens"] = 842.20;

    EXPECT_THAT(m2, ::testing::ContainerEq(std::map<std::string, float>({
                        {"BASF", 369.50},
                        {"VW", 413.50},
                        {"Daimler", 819.00},
                        {"BMW", 834.00},
                        {"Siemens", 842.20},
                    })));

    for (std::map<std::string, float>::iterator pos = m2.begin(); pos != m2.end(); ++pos)
    {
        // key: pos->first val: pos->second
        // 可以修改值
        pos->second *= 2;
    }
    EXPECT_THAT(m2, ::testing::ContainerEq(std::map<std::string, float>({
                        {"BASF", 739},
                        {"VW", 827},
                        {"Daimler", 1638},
                        {"BMW", 1668},
                        {"Siemens", 1684.4},
                    })));

    m2["Volkswagen"] = m2["VW"];
    m2.erase("VW");

    EXPECT_THAT(m2, ::testing::ContainerEq(std::map<std::string, float>({
                        {"Volkswagen", 827},
                        {"BASF", 739},
                        {"Daimler", 1638},
                        {"BMW", 1668},
                        {"Siemens", 1684.4},
                    })));
}

TEST(lambda, 001)
{
    auto f1 = []() { return 42; };
    auto f2 = [](int a, int b) { return a + b; };
    auto f3 = [value = 3]() { return value; };

    int x = 10;
    auto multiply = [x](int n) {
        // 两个x地址不同
        return n * x;
    };
    EXPECT_EQ(multiply(3), 30);

    int count = 5;
    auto increment = [&count]() {
        // 两个count地址相同
        count = count + 1;
    };
    increment();
    EXPECT_EQ(count, 6);

    // 自动推导返回值类型是int
    auto square = [](int x) { return x * x; };
    EXPECT_EQ(square(3), 9);

    auto divide = [](int a, int b) -> double {
        return (b == 0) ? 0.0 : static_cast<double>(a) / b;
    };

    std::vector<int> v{3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
    EXPECT_THAT(v, ::testing::ElementsAre(1, 1, 3, 4, 5));

    int y = 10;
    auto f4 = [y]() mutable {
        y += 1;
        return y;
    };
    EXPECT_EQ(f4(), 11);
    EXPECT_EQ(y, 10);

    auto factorial = [](int n) {
        auto factImpl = [](int n, const auto& self) -> int {
            return n <= 1 ? 1 : n * self(n - 1, self);
        };
        return factImpl(n, factImpl);
    };
    EXPECT_EQ(factorial(4), 24);
    int a = 5, b = 10;
    auto f5 = [&a, &b]() {
        a++;
        b++;
    };
    f5();
    EXPECT_TRUE((a == 6) && (b == 11));
    int a1 = 5, b1 = 6;
    auto f6 = [&]() {
        a1++;
        b1++;
    };
    f6();
    EXPECT_TRUE((a1 == 6) && (b1 == 7));
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 前面: 不满足条件(要保留的数据)；后面: (后面内容不确定，可能是满足条件的数据)
    auto it = std::remove_if(nums.begin(), nums.end(), [](int n) -> bool { return n % 2 == 0; });
    nums.erase(it, nums.end());
    EXPECT_THAT(nums, ::testing::ElementsAre(1, 3, 5, 7, 9));

    auto future = std::async([](int a, int b) { return a * b; }, 6, 7);
    EXPECT_EQ(future.get(), 42);

    std::function<int(const std::string&, const std::string&)> f7 =
        [](const std::string& s1, const std::string& s2) -> int { return s1.size() + s2.size(); };
    EXPECT_EQ(f7("hello", "wo"), 7);

    int (*f9)(int) = [](int x) { return x * x; };
    EXPECT_EQ(f9(3), 9);

    int y2 = 4;
    std::function<std::string(int)> f10 = [y2](int n) mutable {
        y2++;
        return std::to_string(n);
    };

    EXPECT_TRUE(f10(3) == "3" && y2 == 4);

    auto f11 = []() -> int {
        throw std::runtime_error("lambda error");
        return 42;
    };
    EXPECT_THROW(f11(), std::runtime_error);
}

TEST(tuple, 001)
{
    std::tuple<std::string, int, int, std::complex<double>> t0;
    EXPECT_DOUBLE_EQ(std::get<3>(t0).real(), 0);
    EXPECT_DOUBLE_EQ(std::get<3>(t0).imag(), 0);
    EXPECT_TRUE((std::get<0>(t0) == "") && (std::get<1>(t0) == 0) && (std::get<2>(t0) == 0));

    std::tuple<std::string, int, std::complex<double>> t1("haha", 2,
                                                          std::complex<double>(4.0, 3.0));
    EXPECT_DOUBLE_EQ(std::get<2>(t1).real(), 4.0);
    EXPECT_DOUBLE_EQ(std::get<2>(t1).imag(), 3.0);
    EXPECT_TRUE((std::get<0>(t1) == "haha") && (std::get<1>(t1) == 2));

    auto t2 = std::make_tuple(std::string("haha"), 2, std::complex<double>(4.0, 3.0));
    EXPECT_DOUBLE_EQ(std::get<2>(t2).real(), 4.0);
    EXPECT_DOUBLE_EQ(std::get<2>(t2).imag(), 3.0);
    EXPECT_TRUE((std::get<0>(t2) == "haha") && (std::get<1>(t2) == 2));
}

TEST(shared_ptr, 002)
{
    class FileDeleter
    {
    private:
        std::string _name;

    public:
        FileDeleter(const std::string& fn) : _name(fn) {}
        void operator()(std::ofstream* fp)
        {
            delete fp;
            // std::remove(_name.c_str());
        }
    };
    std::ofstream* ptr = new std::ofstream("tmp.txt");
    std::shared_ptr<std::ostream> fp(ptr, FileDeleter("haha.txt"));
}

TEST(shared_ptr, 001)
{
    std::shared_ptr<std::string> pNico(new std::string("nico"));
    std::shared_ptr<std::string> pJutta(new std::string("jutta"));

    (*pNico)[0] = 'N';
    EXPECT_EQ(*pNico, "Nico");

    pJutta->replace(0, 1, "J");
    EXPECT_EQ(*pJutta, "Jutta");

    std::vector<std::shared_ptr<std::string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);

    EXPECT_THAT(whoMadeCoffee,
                ::testing::ElementsAre(::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Nico")),
                                       ::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Nico"))));
    *pNico = "Nicolai";
    EXPECT_THAT(whoMadeCoffee,
                ::testing::ElementsAre(::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Nicolai")),
                                       ::testing::Pointee(::testing::StrEq("Jutta")),
                                       ::testing::Pointee(::testing::StrEq("Nicolai"))));
    EXPECT_EQ(whoMadeCoffee[0].use_count(), 4);
    EXPECT_EQ(pJutta.use_count(), 4);

    EXPECT_EQ(whoMadeCoffee[2].use_count(), 3);
    EXPECT_EQ(pNico.use_count(), 3);
}

class Foo
{
public:
    Foo(std::tuple<int, float>)
    {
        // std::cout << __LINE__ << ",  " << "Foo(std::tuple<int, float>)" << std::endl;
    }
    // 注意: 局部类不能包含模版类成员
    template <typename... Args> Foo(Args... args)
    {
        // std::cout << __LINE__ << ",  " << "Foo::Foo(args...)" << std::endl;
    }
};

TEST(pair, 001)
{
    std::tuple<int, float> t(1, 2.22);
    std::pair<int, Foo> p1(42, t);
    std::pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(42), t);
}
static bool int_ptr_less(int* a, int* b)
{
    return (*a < *b);
}

TEST(valCompare, 001)
{
    int x = 17;
    int y = 42;
    int z = 33;
    int* px = &x;
    int* py = &y;
    int* pz = &z;

    int* pmax = std::max(px, py, int_ptr_less);
    EXPECT_EQ(pmax, py);

    std::pair<int*, int*> extremes = std::minmax({px, py, pz}, int_ptr_less);
    EXPECT_TRUE(extremes.first == px && extremes.second == py);
}

TEST(Limits, 001)
{
    EXPECT_TRUE((std::numeric_limits<short>::max() == 32767) &&
                (std::numeric_limits<short>::min() == -32768));

    EXPECT_FLOAT_EQ(1.1754944e-38, std::numeric_limits<float>::min());
    EXPECT_FLOAT_EQ(3.4028235e+38, std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(-3.4028235e+38, std::numeric_limits<float>::lowest());
    EXPECT_FLOAT_EQ(1.4012985e-45, std::numeric_limits<float>::denorm_min());
    EXPECT_FLOAT_EQ(1.1920929e-07, std::numeric_limits<float>::epsilon());

    EXPECT_DOUBLE_EQ(2.2250738585072014e-308, std::numeric_limits<double>::min());
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, std::numeric_limits<double>::max());
    EXPECT_DOUBLE_EQ(-1.7976931348623157e+308, std::numeric_limits<double>::lowest());
    EXPECT_DOUBLE_EQ(4.9406564584124654e-324, std::numeric_limits<double>::denorm_min());
    EXPECT_DOUBLE_EQ(2.2204460492503131e-16, std::numeric_limits<double>::epsilon());

    EXPECT_TRUE(std::numeric_limits<char>::is_signed &&
                !std::numeric_limits<unsigned char>::is_signed);
}

TEST(enable_shared_from_this, 001)
{
    class Person : public std::enable_shared_from_this<Person>
    {
    public:
        std::string _name;
        std::shared_ptr<Person> _mother;
        std::shared_ptr<Person> _father;
        std::vector<std::weak_ptr<Person>> _kids;
        Person(const std::string& n) : _name(n) {}
        ~Person()
        {
            // std::cout << "line: " << __LINE__ << ", " << std::endl;
        }
        void setParentAndKids(std::shared_ptr<Person> m = nullptr,
                              std::shared_ptr<Person> f = nullptr)
        {
            _mother = m;
            _father = f;
            if (m != nullptr)
            {
                m->_kids.push_back(shared_from_this());
            }
            if (f != nullptr)
            {
                f->_kids.push_back(shared_from_this());
            }
        }
    };

    // init nico family
    std::shared_ptr<Person> nicoMom(new Person("nico-Mom"));
    std::shared_ptr<Person> nicoDad(new Person("nico-Dad"));
    std::shared_ptr<Person> nico(new Person("nico"));
    nico->setParentAndKids(nicoMom, nicoDad);

    EXPECT_EQ(nico.use_count(), 1);
    EXPECT_EQ(nico->_mother->_kids[0].lock()->_name, "nico");
}

TEST(ratio, 001)
{
    using r1 = std::ratio<4, 6>;
    EXPECT_TRUE(r1::num == 2 && r1::den == 3);

    using r2 = std::ratio<4>;
    EXPECT_TRUE(r2::num == 4 && r2::den == 1);

    using r3 = std::ratio<4, 1>;
    EXPECT_TRUE(r3::num == 4 && r3::den == 1);

    using r4 = std::ratio<1, 3>;
    using r5 = std::ratio<1, 6>;
    using sum = std::ratio_add<r4, r5>;
    EXPECT_TRUE(sum::num == 1 && sum::den == 2);

    std::ratio<0> zero;
    EXPECT_TRUE(zero.num == 0 && zero.den == 1);

    std::ratio<0, 1> zero2;
    EXPECT_TRUE(zero2.num == 0 && zero2.den == 1);

    typedef std::ratio<25, 15> AlsoFiveThirds;
    EXPECT_TRUE(AlsoFiveThirds::num == 5 && AlsoFiveThirds::den == 3);

    std::ratio<25, 15> val1;
    EXPECT_TRUE(val1.num == 5 && val1.den == 3);

    EXPECT_TRUE((std::ratio_equal<std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>,
                                  std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_subtract<std::ratio<1, 3>, std::ratio<1, 6>>,
                                  std::ratio<1, 6>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_multiply<std::ratio<2, 3>, std::ratio<3, 4>>,
                                  std::ratio<6, 12>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_divide<std::ratio<1, 2>, std::ratio<2, 3>>,
                                  std::ratio<3, 4>>::value));
    EXPECT_TRUE((std::ratio_less<std::ratio<1, 3>, std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_greater<std::ratio<1, 2>, std::ratio<1, 3>>::value));
    EXPECT_TRUE((std::ratio_greater_equal<std::ratio<1, 2>, std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_less_equal<std::ratio<1, 2>, std::ratio<1, 2>>::value));
}

static std::string asString(const std::chrono::system_clock::time_point& tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size() - 1);
    return ts;
}

TEST(asString, 001)
{
    EXPECT_EQ(asString(std::chrono::system_clock::time_point{}), "Thu Jan  1 08:00:00 1970");
    (void)asString(std::chrono::system_clock::now());
    EXPECT_EQ(asString(std::chrono::system_clock::time_point::min()),
              "Mon Dec 22 04:04:49     -290308");
    EXPECT_EQ(asString(std::chrono::system_clock::time_point::max()),
              "Sun Jan 10 12:00:54     294247");
}
TEST(asString, 002)
{
    typedef std::chrono::duration<int, std::ratio<3600 * 24>> Days;
    std::chrono::time_point<std::chrono::system_clock> tp;
    EXPECT_EQ(asString(tp), "Thu Jan  1 08:00:00 1970");

    // 增加了的时间
    tp += Days(1) + std::chrono::hours(23) + std::chrono::minutes(55);
    EXPECT_EQ(asString(tp), "Sat Jan  3 07:55:00 1970");

    // 差异: 分钟
    auto diff = tp - std::chrono::system_clock::time_point();
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::minutes>(diff).count(), 2875);

    // 差异: 天
    Days days = std::chrono::duration_cast<Days>(diff);
    EXPECT_EQ(days.count(), 1);

    tp -= std::chrono::hours(24 * 365);
    EXPECT_EQ(asString(tp), "Fri Jan  3 07:55:00 1969");

    tp -= std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(50);
    EXPECT_EQ(asString(tp), "Thu Jan 16 07:55:00 1919");

    tp -= std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(50);
    EXPECT_EQ(asString(tp), "Wed Jan 27 08:00:43 1869");
}

#endif