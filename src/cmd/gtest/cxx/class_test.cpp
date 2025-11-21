#include "base/art_str.h"
#include "ut_config.h"
#include "utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

TEST(ClassBasic, 015)
{
    class Base
    {
    public:
        Base()
        {
            printf("line: %d, func: Base()\n", __LINE__);
        }
        void show()
        {
            printf("line: %d, func: show()\n", __LINE__);
        }

    protected:
        std::string _name;
    };

    class Derive : public Base
    {
    public:
        Derive()
        {
            printf("line: %d, func: Derive()\n", __LINE__);
        }
        void display()
        {
            printf("line: %d, func: display() \n", __LINE__);
        }
    };

    auto fn = [](Base* pstBase) { pstBase->show(); };
    {
        Derive derive;
        Base base = derive;
        Base& refBase = derive;
        Base* pstBase = &derive;
        base.show();
        refBase.show();
        pstBase->show();
        fn(&derive);
    }
}
#ifdef RUN_ALL_TEST_CASE
TEST(ClassBasic, 014)
{
    class Student
    {
    public:
        void setGrade(std::string grade)
        {
            _grade = grade;
        }
        std::string getGrade()
        {
            return _grade;
        }
        void setName(std::string name)
        {
            _name = name;
        }
        std::string getName()
        {
            return _name;
        }

    protected:
        std::string _grade; // 年级

    private:
        std::string _name; // 名字
    };
    class Undergraduate : public Student
    {
    public:
        Undergraduate(std::string major) : _major(major) {}
        void display()
        {
            printf("line: %d, name: %s, grade: %s, major: %s \n", __LINE__, getName().c_str(),
                   getGrade().c_str(), _major.c_str());
        }

    private:
        std::string _major; // 专业
    };

    {
        Undergraduate stu("Computer");
        stu.setName("ZhangSan");
        stu.setGrade("DaSan");
        stu.display();
    }
}

TEST(ClassBasic, 013)
{
    // 1. 基类构造函数与析构函数不能被继承
    // 2. 派生类对基类成员的继承没有选择权,不能选择继承或不继承某些成员
    // 3. 派生类可以增加新成员
    // 4. 一个基类可以派生多个派生类

    class Animal
    {
    public:
        Animal()
        {
            printf("line: %d, Animal() \n", __LINE__);
        }
        void move()
        {
            printf("line: %d, void Animal::move() \n", __LINE__);
        }
        ~Animal()
        {
            printf("line: %d, ~Animal() \n", __LINE__);
        }
    };

    class Cat : public Animal
    {
    public:
        Cat(std::string name) : _name(name)
        {
            printf("line: %d, Cat(std::string name), name: %s \n", __LINE__, name.c_str());
        }
        void walk()
        {
            printf("line: %d, void walk(), name: %s \n", __LINE__, _name.c_str());
        }

        ~Cat()
        {
            printf("line: %d, ~Cat(), name: %s \n", __LINE__, _name.c_str());
        }

    private:
        std::string _name;
    };

    {
        // 1. 派生类继承基类，构造函数: 基类 => 派生类构造
        Cat cat("猫");
        cat.move();
        cat.walk();
    }
}

class GPoint
{
public:
    friend void updateGPointAttrs(GPoint& pt, double x, double y);
    GPoint(double x, double y);
    ~GPoint();
    static double getLen(GPoint& p1, GPoint& p2);
    static double _sLen;

private:
    double _x;
    double _y;
};

double GPoint::_sLen = 0;
GPoint::GPoint(double x, double y) : _x(x), _y(y)
{
    printf("line: %d, GPoint(double x, double y), x: %.2f, y: %.2f, len: %2.f \n", __LINE__, _x, _y,
           GPoint::_sLen);
}

GPoint::~GPoint()
{
    printf("line: %d, ~GPoint(), x: %.2f, y: %.2f, len: %2.f \n", __LINE__, _x, _y, GPoint::_sLen);
}

double GPoint::getLen(GPoint& p1, GPoint& p2)
{
    double x = std::abs(p1._x - p2._x);
    double y = std::abs(p1._y - p2._y);
    _sLen = std::sqrt(x * x + y * y);
    printf("line: %d, getLen(GPoint& p1, GPoint& p2), slen: %.2f \n", __LINE__, GPoint::_sLen);
    return _sLen;
}

void updateGPointAttrs(GPoint& pt, double x, double y)
{
    pt._x = x;
    pt._y = y;
    printf("line: %d, updateGPointAttrs(GPoint& pt, double x, double y), x: %.2f, y: %.2f \n",
           __LINE__, pt._x, pt._y);
}

TEST(ClassBasic, 012)
{
    GPoint p1 = {3, 5};
    GPoint p2 = {4, 6};
    (void)GPoint::getLen(p1, p2);

    updateGPointAttrs(p2, 10.0, 11.0);
}

TEST(ClassBasic, 011)
{
    class Person
    {
    public:
        Person(std::string name, int age, std::string addr, std::string fruit)
            : _name(name), _age(age), _addr(addr), _favoriteFruit(fruit)
        {
            printf("line: %d, Person(std::string name, int age, std::string addr, std::string "
                   "fruit), name: %s, age: %d, addr: %s, fruit: %s \n",
                   __LINE__, _name.c_str(), _age, _addr.c_str(), _favoriteFruit.c_str());
        }
        Person(const Person& other)
            : _name(other._name), _age(other._age), _addr(other._addr),
              _favoriteFruit(other._favoriteFruit)
        {
            printf(
                "line: %d, Person(const Person& other), name: %s, age: %d, addr: %s, fruit: %s \n",
                __LINE__, _name.c_str(), _age, _addr.c_str(), _favoriteFruit.c_str());
        }
        Person& operator=(const Person&) = delete;
        void printAttrs() const
        {
            // _favoriteFruit = "apple"; // 常成员函数不能修改类成员函数
            // printAddr();              // 常成员函数只能调用常成员函数
            printf("line: %d, void printAttrs() const, name: %s, age: %d, addr: %s, fruit: %s \n",
                   __LINE__, _name.c_str(), _age, _addr.c_str(), _favoriteFruit.c_str());
        }

        void printAttrs()
        {
            // 成员函数与常成员函数构成重载,常成员函数只能由const修饰的对象访问
            printAddr();
            printf("line: %d, void printAttrs(), name: %s, age: %d, addr: %s, fruit: %s \n",
                   __LINE__, _name.c_str(), _age, _addr.c_str(), _favoriteFruit.c_str());
        }

        void printAddr()
        {
            printf("line: %d, void printAddr(), addr: %s\n", __LINE__, _addr.c_str());
        }

        ~Person()
        {
            printf("line: %d, ~Person() \n", __LINE__);
        }
        const std::string _addr;

    private:
        const std::string _name;
        const int _age;
        std::string _favoriteFruit;
    };

    {
        Person p("wfh2025", 10, "Shanghai", "peach");
        p.printAttrs();
    }
    {
        const Person p("wfh2025", 10, "Shanghai", "peach");
        p.printAttrs();
    }

    {
        Person p1("wfh2025", 10, "Shanghai", "peach");
        Person p2 = p1;
    }
}

TEST(ClassBasic, 010)
{
    class Sheep
    {
    public:
        Sheep(int id) : _id(id)
        {
            printf("line: %d, Sheep(int id), id: %d \n", __LINE__, id);
        }
        Sheep(const Sheep& another)
        {
            this->_id = another._id + 1;
            printf("line: %d,  Sheep(const Sheep& another), input id: %d, output id: %d \n",
                   __LINE__, another._id, this->_id);
        }
        ~Sheep()
        {
            printf("line: %d, ~Sheep(), id: %d \n", __LINE__, this->_id);
        }

    public:
        int _id;
    };

    {
        Sheep s1(5);
        Sheep s2(25);

        // 没有调用拷贝构造函数
        s2 = s1;
    }
}

TEST(ClassBasic, 009)
{
    class Sheep
    {
    public:
        Sheep(std::string name) : _name(std::move(name)) {}

    public:
        std::string _name;
    };

    // 没有定义拷贝函数,编译器提供默认构造函数,仅能做到简单的赋值
    Sheep s1("haha");
    Sheep s2 = s1;
    EXPECT_EQ(s2._name, s1._name);
    EXPECT_NE(s2._name.data(), s1._name.data());
}

TEST(ClassBasic, 008)
{
    class Sheep
    {
    public:
        Sheep(int id) : _id(id)
        {
            // printf("line: %d, Sheep(int id), id: %d \n", __LINE__, id);
        }
        Sheep(const Sheep& another)
        {
            this->_id = another._id + 1;
            // printf("line: %d,  Sheep(const Sheep& another), input id: %d, output id: %d \n",
            //        __LINE__, another._id, this->_id);
        }
        ~Sheep()
        {
            // printf("line: %d, ~Sheep(), id: %d \n", __LINE__, this->_id);
        }

    public:
        int _id;
    };

    {
        // 使用一个对象初始化另外一个对象
        Sheep s1(2);
        Sheep s2(s1);
        EXPECT_NE(&s1._id, &s2._id);
    }

    {
        // 使用一个对象初始化另外一个对象
        Sheep s1(3);
        Sheep s2 = s1;
    }

    {
        // 对象作为参数传递给函数
        Sheep s(4);
        auto fn0 = [](Sheep s) {};
        fn0(s);
    }

    {
        // 函数返回值为对象
        auto fn = []() -> Sheep {
            // RVO
            return Sheep(5);
        };
        Sheep sh0 = fn();
        // printf("line: %d \n", __LINE__);
    }

    {
        // 函数返回值为对象
        auto fn = []() -> Sheep {
            // NRVO
            auto tmp = Sheep(6);
            return tmp;
        };
        Sheep sh = fn();
        // printf("line: %d \n", __LINE__);
    }
}

TEST(ClassBasic, 007)
{
    class Birth
    {
    public:
        Birth(int year, int month, int day) : _year(year), _month(month), _day(day) {}

    public:
        int _year;
        int _month;
        int _day;
    };
    class Student
    {
    public:
        Student(std::string name, int year, int month, int day)
            : _name(name), _birth(year, month, day)
        {}

    public:
        std::string _name;
        Birth _birth;
    };

    // 成员对象构造函数有参数，需从类成员构造函数传递
    Student stu("Li", 2000, 10, 14);
    EXPECT_TRUE(stu._name == "Li" && stu._birth._year == 2000 && stu._birth._month == 10 &&
                stu._birth._day == 14);
}

TEST(ClassBasic, 006)
{
    class ClassA
    {
    public:
        ClassA()
        {
            // printf("line: %d, ClassA() \n", __LINE__);
        }
    };
    class ClassB
    {
    public:
        ClassB()
        {
            // printf("line: %d, ClassB() \n", __LINE__);
        }

    private:
        ClassA _objA;
    };

    // 顺序:
    // 1. 调用成员对象构造函数
    // 2. 调用类构造函数
    ClassB objB;
}

TEST(ClassBasic, 005)
{
    class Clock
    {
    public:
        // 构造函数有默认值时,请注意二义性
        Clock(int hour) : _hour(hour), _min(0), _sec(0) {}
        Clock(int hour, int min) : _hour(hour), _min(min), _sec(0) {}
        Clock(int hour, int min, int sec) : _hour(hour), _min(min), _sec(sec) {}
        std::string getKey()
        {
            return std::to_string(this->_hour) + std::string("-") + std::to_string(this->_min) +
                   "-" + std::to_string(this->_sec);
        }

    private:
        int _hour;
        int _min;
        int _sec;
    };

    EXPECT_EQ(Clock(5).getKey(), "5-0-0");
    EXPECT_EQ(Clock(6, 2).getKey(), "6-2-0");
    EXPECT_EQ(Clock(7, 4, 3).getKey(), "7-4-3");

    Clock c0 = {9, 5, 2};
    EXPECT_EQ(c0.getKey(), "9-5-2");
}

TEST(ClassBasic, 004)
{
    class Clock
    {
    public:
        Clock(int hour, int min, int sec) : _hour(hour), _min(min), _sec(sec) {}
        std::string getKey()
        {
            return std::to_string(this->_hour) + std::string("-") + std::to_string(this->_min) +
                   "-" + std::to_string(this->_sec);
        }

    private:
        int _hour;
        int _min;
        int _sec;
    };
    Clock clock(10, 20, 30);
    EXPECT_EQ(clock.getKey(), "10-20-30");
}

TEST(ClassBasic, 003)
{
    class Student
    {
    public:
        std::string study()
        {
            return std::to_string(__LINE__) + std::string("-") + "study";
        }
        std::string exam()
        {
            return std::to_string(__LINE__) + std::string("-") + std::string("exam");
        }
        void setName(std::string name)
        {
            this->_name = std::move(name);
        }
        std::string getName()
        {
            return this->_name;
        }

    private:
        std::string _name;
        int _age;
    };

    // 1. 类中没有定义构造函数,编译器提供默认无参数构造函数
    // 2. 默认无参构造函数体为空
    Student stu;
    stu.exam();

    // 构造函数
    // 1. 构造函数名与类名相同
    // 2. 构造函数名前面没有返回值类型
    // 3. 构造函数无返回值,不能使用return返回
    // 4. 构造函数权限一般是public
}

TEST(ClassBasic, 002)
{
    class Student
    {
    public:
        std::string study()
        {
            return std::to_string(__LINE__) + std::string("-") + "study";
        }
        std::string exam()
        {
            return std::to_string(__LINE__) + std::string("-") + std::string("exam");
        }

    private:
        std::string _name;
        int _age;
    };

    Student stu;
    stu.exam();

    Student* pstStu = new Student();
    pstStu->exam();
    delete pstStu;
}

TEST(ClassBasic, 001)
{
    class Student
    {
    public:
        std::string study()
        {
            return std::to_string(__LINE__) + std::string("-") + "study";
        }
        std::string exam()
        {
            return std::to_string(__LINE__) + std::string("-") + std::string("exam");
        }

    private:
        std::string _name;
        int _age;
    };

    Student stu;
    stu.exam();
}

#endif