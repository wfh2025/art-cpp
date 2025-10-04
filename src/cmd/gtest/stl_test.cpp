#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <chrono>
#include <complex>
#include <ctime>
#include <fstream>
#include <future>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifdef RUN_ALL_TEST_CASE
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
        std::cout << __LINE__ << ",  " << "Foo(std::tuple<int, float>)" << std::endl;
    }
    // 注意: 局部类不能包含模版类成员
    template <typename... Args> Foo(Args... args)
    {
        std::cout << __LINE__ << ",  " << "Foo::Foo(args...)" << std::endl;
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