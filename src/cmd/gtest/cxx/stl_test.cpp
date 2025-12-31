#include <algorithm>
#include <array>
#include <chrono>
#include <complex>
#include <ctime>
#include <deque>
#include <exception>
#include <filesystem>
#include <fstream>
#include <future>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

#include "base/art_str.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(STD_ASYNC, 004)
{
    std::future<std::string> fut;
    try
    {
        fut = std::async(
            std::launch::async,
            [&](const std::string& str) -> std::string {
                if (str.size() < 2)
                {
                    throw std::runtime_error("invalid param, too small");
                }
                if (str.size() > 10)
                {
                    throw std::runtime_error("invalid param, too large");
                }

                std::this_thread::sleep_for(std::chrono::seconds(5));
                return str;
            },
            std::string(""));
    }
    catch (std::exception& e)
    {
        SPDLOG_INFO("exception, {}", e.what());
        return;
    }
    catch (...)
    {
        SPDLOG_INFO("unknow");
        return;
    }

    try
    {
        std::string ret = fut.get();
    }
    catch (std::exception& e)
    {
        SPDLOG_INFO("exception, {}, func: {}", e.what(), __FUNCTION__);
    }
    catch (...)
    {
        SPDLOG_INFO("unknow");
    }
    auto x = std::make_error_code(std::errc::timed_out).value();
}

TEST(STD_ASYNC, 003)
{
    SPDLOG_INFO("before, async");
    std::future<std::string> fut;
    try
    {
        fut = std::async(
            std::launch::deferred,
            [&](const std::string& str) -> std::string {
                std::this_thread::sleep_for(std::chrono::seconds(15));
                return str;
            },
            "Hello");
    }
    catch (std::system_error& e)
    {
        SPDLOG_ERROR("Failed to create thread, {}", e.what());
    }
    SPDLOG_INFO("after, async");
    std::this_thread::sleep_for(std::chrono::seconds(7));
    SPDLOG_INFO("after, sleep");
    std::string ret = fut.get();
    SPDLOG_INFO("after, get, value: {}", ret);
}

TEST(STD_ASYNC, 002)
{
    /**
     * 1. std::future<std::string> fut = std::async(std::launch::async, fn):
     *      fn在新的线程立即开始执行
     * 2. std::future对象必须被保存, 否则其析构函数会阻塞直到异步操作完成
     * 3. 如果抛出异常,异常会在std::future中,调用get()重新抛出
     */
    SPDLOG_INFO("before, async");
    std::future<std::string> fut;
    try
    {
        fut = std::async(
            std::launch::async,
            [&](const std::string& str) -> std::string {
                std::this_thread::sleep_for(std::chrono::seconds(15));
                return str;
            },
            "Hello");
    }
    catch (std::system_error& e)
    {
        SPDLOG_ERROR("Failed to create thread, {}", e.what());
    }
    SPDLOG_INFO("after, async");
    std::this_thread::sleep_for(std::chrono::seconds(7));
    SPDLOG_INFO("after, sleep");
    std::string ret = fut.get();
    SPDLOG_INFO("after, get, value: {}", ret);
}

TEST(STD_ASYNC, 001)
{
    /**
     * 1. std::async(std::launch::async, fn1):
     * 1. std::launch::any: 非C++标准,禁止使用std::async(std::launch::any, fn)
     * 2. std::async(std::launch::any, fn): 非标准，行为不确定
     * 3. std::async(std::launch::async, fn): fn将会在新的线程中异步执行
     * 4. std::async(std::launch::deferred, fn): 执行会被延迟,
     * 直到在返回的future上执行get()或者wait才会执行,fn将会在执行get()或wait的线程中执行
     */

    /**
     * 1. std::async(fn)尝试启动fn于后台，并将结果赋值给std::future对象
     * 2. std::async尝试将所获得函数立刻异步启动于一个分离线程内
     *      fn在这里被启动，不会造成当前执行用例线程阻塞
     * 3. 返回std::future对象是必须的:
     *      a) 允许启动函数的结果: 返回值/异常
     *      b) 无返回值: std::future<void>
     *      c) 必须存在，确保"目标函数"或快/慢被调用:
     *          async只是尝试启动目标函数，如果没有发生，稍后必须通过该该对象强制启动(需要结果或确保该函数被执行)
     *      d) 无论对async函数的返回敢不敢兴趣，都必须有，而且后面必须得有get()调用
     * 4. std::future的get()调用，三种场景:
     *      a) 任务被async启动一个分离线程并结束，立刻获得结果
     *      b) 任务被async启动，但是未结束，get()会阻塞并等任务结束后返回结果
     *      c) 任务没有启动,会被强迫启动如同一个同步调用，get()会阻塞并直至产生结果
     * 5. std::future的get()确保在单线程环境，或async无法启动新线程，程序仍能有效运作
     */
    std::future<std::string> fut;
    try
    {
        SPDLOG_INFO("before, async");
        fut = std::async(
            [&](const std::string& str) -> std::string {
                std::this_thread::sleep_for(std::chrono::seconds(15));
                return str;
            },
            "Hello");
        SPDLOG_INFO("after async");
    }
    catch (std::system_error& e)
    {
        SPDLOG_ERROR("Failed to create thread, {}", e.what());
    }

    std::string ret = fut.get();
    SPDLOG_INFO("after get, value: {}", ret);
}

std::tuple<std::vector<std::string>, std::vector<std::string>> listFsPrefix(const std::string& prefix)
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
        std::tuple<std::vector<std::string>, std::vector<std::string>> entries = listFsPrefix(curPath);

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
    std::string prefix = "/usr/bin";
    listFsBFS(prefix);
    listFsDFS(prefix);
}

static std::string joinThreeIntValues(int a, int b, int c)
{
    std::string tmp = std::to_string(a) + "-" + std::to_string(b) + "-" + std::to_string(c);
    return tmp;
}

TEST(bind, 001)
{
    std::function<std::string(int, int)> f2 = std::bind(joinThreeIntValues, 10, std::placeholders::_1, std::placeholders::_2);
    EXPECT_EQ(f2(20, 30), "10-20-30");

    std::function<std::string(int, int)> f3 = std::bind(joinThreeIntValues, 10, std::placeholders::_2, std::placeholders::_1);
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
        std::bind(&Calculator::join, &calc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    EXPECT_EQ(f4(3, 3.14, "world"), "haha-3-3.140000-world");

    std::function<std::string(int, double, const std::string&)> f5 =
        std::bind(&Calculator::join, std::make_shared<Calculator>("hi"), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    EXPECT_EQ(f5(3, 3.14, "world"), "hi-3-3.140000-world");
}

static std::string demangle(const char* name)
{
    int status = -1;
    std::unique_ptr<char, void (*)(void*)> res(abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free);
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
    std::map<std::string, int> data = {{"apple", 1}, {"banana", 2}, {"cherry", 3}, {"date", 4}, {"elderberry", 5}};

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
    EXPECT_THAT(art::str::strsplit("a;b;;c;d;", ";"), ::testing::AllOf(::testing::SizeIs(6), ::testing::ElementsAre("a", "b", "", "c", "d", "")));
    EXPECT_THAT(art::str::strsplit("", ";"), ::testing::ElementsAre(""));
    EXPECT_THAT(art::str::strsplit("a;b;c", ";"), ::testing::AllOf(::testing::SizeIs(3), ::testing::ElementsAre("a", "b", "c")));
    EXPECT_THAT(art::str::strsplit("", ""), ::testing::AllOf(::testing::SizeIs(1), ::testing::ElementsAre("")));
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
    std::transform(s0.cbegin(), s0.cend(), std::back_inserter(d0), std::bind(std::multiplies<int>(), std::placeholders::_1, 10));
    EXPECT_THAT(d0, ::testing::ElementsAre(90, 80, 70, 60, 50, 40, 30, 20, 10));

    std::replace_if(d0.begin(), d0.end(), std::bind(std::equal_to<int>(), std::placeholders::_1, 70), 42);
    EXPECT_THAT(d0, ::testing::ElementsAre(90, 80, 42, 60, 50, 40, 30, 20, 10));

    d0.erase(std::remove_if(d0.begin(), d0.end(),
                            std::bind(std::logical_and<bool>(), std::bind(std::greater_equal<int>(), std::placeholders::_1, 50),
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
    EXPECT_THAT(li2, ::testing::ElementsAre('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
                                            'v', 'w', 'x', 'y', 'z'));
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
    EXPECT_THAT(m0, ::testing::UnorderedElementsAre(::testing::Pair("struppi", 7), ::testing::Pair("tim", 3)));
    // 注意: 关注顺序
    EXPECT_THAT(m0, ::testing::ElementsAre(::testing::Pair("struppi", 7), ::testing::Pair("tim", 3)));

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

    EXPECT_THAT(whoMadeCoffee, ::testing::ElementsAre(::testing::Pointee(::testing::StrEq("Jutta")), ::testing::Pointee(::testing::StrEq("Jutta")),
                                                      ::testing::Pointee(::testing::StrEq("Nico")), ::testing::Pointee(::testing::StrEq("Jutta")),
                                                      ::testing::Pointee(::testing::StrEq("Nico"))));
    *pNico = "Nicolai";
    EXPECT_THAT(whoMadeCoffee, ::testing::ElementsAre(::testing::Pointee(::testing::StrEq("Jutta")), ::testing::Pointee(::testing::StrEq("Jutta")),
                                                      ::testing::Pointee(::testing::StrEq("Nicolai")), ::testing::Pointee(::testing::StrEq("Jutta")),
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
        void setParentAndKids(std::shared_ptr<Person> m = nullptr, std::shared_ptr<Person> f = nullptr)
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

#endif
