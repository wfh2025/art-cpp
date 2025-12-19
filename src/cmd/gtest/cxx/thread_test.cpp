#include <algorithm>
#include <array>
#include <chrono>
#include <complex>
#include <condition_variable>
#include <ctime>
#include <deque>
#include <fstream>
#include <future>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ut_config.h"

static void hello()
{
    std::cout << "line: " << __LINE__ << ", hello" << std::endl;
}

static void printValue(int value)
{
    std::cout << "line: " << __LINE__ << ", value: " << value << std::endl;
}

static std::mutex g_mutex;
static std::condition_variable g_condVar;
static int64_t g_count = 0;
static bool g_ready = false;

static void incrementCount()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    for (int i = 0; i < 100000; ++i)
    {
        g_count++;
    }
}

static void printId(int id)
{
    std::unique_lock<std::mutex> lock(g_mutex);
    while (!g_ready)
    {
        g_condVar.wait(lock);
        std::cout << "line: " << __LINE__ << " " << (g_ready == true ? "true" : "false")
                  << std::endl;
    }
    std::cout << "line: " << __LINE__ << " " << (g_ready == true ? "true" : "false") << std::endl;
}
#ifdef RUN_ALL_TEST_CASE
TEST(thread, 004)
{
    g_ready = false;
    const int thread_num = 10;
    std::thread threads[thread_num];
    for (int i = 0; i < thread_num; i++)
    {
        threads[i] = std::thread(printId, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::unique_lock lock(g_mutex);
        g_ready = true;
        std::cout << "line: " << __LINE__ << " " << (g_ready == true ? "true" : "false")
                  << std::endl;
        g_condVar.notify_all();
        std::cout << "line: " << __LINE__ << " " << (g_ready == true ? "true" : "false")
                  << std::endl;
    }
    for (auto& th : threads)
    {
        th.join();
    }
    std::cout << "line: " << __LINE__ << " " << (g_ready == true ? "true" : "false") << std::endl;
}

TEST(thread, 001)
{
    std::thread t(hello);
    t.join();
}

TEST(thread, 002)
{
    int num = 43;
    std::thread t(printValue, num);
    t.join();
}

TEST(thread, 003)
{
    g_count = 0;
    std::thread t1(incrementCount);
    std::thread t2(incrementCount);
    t1.join();
    t2.join();
    EXPECT_EQ(g_count, 200000);
}
#endif