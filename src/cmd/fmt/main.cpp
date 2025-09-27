#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>
#include <fmt/ranges.h>
#include <map>
#include <vector>

int main()
{
    std::string message = fmt::format("Hello {}! The answer is {:.2f}", "world", 3.14159);
    fmt::print("{}\n", message);
    fmt::print(fg(fmt::color::steel_blue), "This is colored text!\n");
    auto str = fmt::format("Int: {}, Hex: {:#x}", 42, 42);
    fmt::print("{}\n", str);

    std::vector<int> vec = {1, 2, 3, 4, 5};
    fmt::print("Vector: {}\n", vec);

    std::map<std::string, int> dict = {{"key1", 1}, {"key2", 2}};
    fmt::print("Map: {}\n", dict);

    fmt::print("Positional: {1} {0} {1}\n", "A", "B");
    fmt::memory_buffer buf;
    fmt::format_to(std::back_inserter(buf), "Buffer data: {}", 789);
    fmt::print("{}\n", fmt::to_string(buf));

    return 0;
}