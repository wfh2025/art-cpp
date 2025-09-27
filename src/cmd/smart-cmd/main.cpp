// clang-format off
#include <string>
#include <vector>
#include <map>
#include "linenoise.h"
// clang-format on

static char* stringToHeapChars(const std::string& str)
{
    char* pTmp = static_cast<char*>(malloc(str.size() + 1));
    if (NULL != pTmp)
    {
        snprintf(pTmp, str.size() + 1, "%s", str.c_str());
    }
    return pTmp;
}

static bool startsWith(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}
static bool endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static std::string strtrim(const std::string& str, const std::string& trimChars)
{
    if (trimChars.empty())
    {
        return str;
    }
    size_t start = str.find_first_not_of(trimChars);
    if (start == std::string::npos)
    {
        return "";
    }
    size_t end = str.find_last_not_of(trimChars);
    return str.substr(start, end - start + 1);
}

static std::vector<std::string> strsplit(const std::string& s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    if (s.empty() || delimiter.empty())
    {
        tokens.push_back(s);
        return tokens;
    }

    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

static std::string toLower(const std::string& str)
{
    std::string result = str;
    for (auto& c : result)
    {
        c = std::tolower(c);
    }
    return result;
}

enum class CommandArgType
{
    ARG_TYPE_STRING = 0,
    ARG_TYPE_INTEGER = 1,
    ARG_TYPE_DOUBLE = 2,
    ARG_TYPE_UNIX_TIME = 3,
    ARG_TYPE_BOOL = 4,
};

struct CommandArg
{
    std::string name;         // 参数名称
    std::string summary;      // 概要
    std::string defaultValue; // 默认值
    class Builder
    {
    private:
        std::string name_;
        std::string summary_;
        std::string defaultValue_;

    public:
        Builder& name(std::string name)
        {
            name_ = std::move(name);
            return *this;
        }
        Builder& summary(std::string summary)
        {
            summary_ = std::move(summary);
            return *this;
        }
        Builder& defaultValue(std::string defaultValue)
        {
            defaultValue_ = std::move(defaultValue);
            return *this;
        }
        CommandArg build()
        {
            CommandArg cmdArg;
            cmdArg.name = std::move(name_);
            cmdArg.summary = std::move(summary_);
            cmdArg.defaultValue = std::move(defaultValue_);
            return cmdArg;
        }
    };
    static Builder create()
    {
        return Builder{};
    }
};

struct Command
{
    std::string name;                          // 命令名称
    std::string summary;                       // 概要
    std::string since;                         // 支持的起始版本
    std::map<std::string, CommandArg> argsMap; // 命令参数, key: 参数名称

    class Builder
    {
    private:
        std::string name_;
        std::string summary_;
        std::string since_;
        std::vector<CommandArg> commandArgs_;

    public:
        Builder& name(std::string name)
        {
            name_ = std::move(name);
            return *this;
        }
        Builder& summary(std::string summary)
        {
            summary_ = std::move(summary);
            return *this;
        }
        Builder& since(std::string since)
        {
            since_ = std::move(since);
            return *this;
        }
        Builder& arg(CommandArg arg)
        {
            commandArgs_.push_back(std::move(arg));
            return *this;
        }
        Builder& args(std::vector<CommandArg> args)
        {
            commandArgs_.reserve(commandArgs_.size() + args.size());
            commandArgs_.insert(commandArgs_.end(), std::make_move_iterator(args.begin()),
                                std::make_move_iterator(args.end()));
            return *this;
        }
        Builder& args(std::initializer_list<CommandArg> args)
        {
            commandArgs_.insert(commandArgs_.end(), args.begin(), args.end());
            return *this;
        }
        Command build()
        {
            Command command;
            command.name = std::move(name_);
            command.since = std::move(since_);
            command.summary = std::move(summary_);
            for (auto& arg : commandArgs_)
            {
                std::string key = arg.name;
                command.argsMap.emplace(std::move(key), std::move(arg));
            }
            return command;
        }
    };
    static Builder create()
    {
        return Builder{};
    }
};

struct InputCommandBuf
{
private:
    std::string _buf;

public:
    explicit InputCommandBuf(std::string buf) : _buf(std::move(buf)) {}
    std::vector<std::pair<std::string, std::string>> parse()
    {
        std::vector<std::pair<std::string, std::string>> args;
        for (const auto& elem : strsplit(_buf, " "))
        {
            std::string kvData = strtrim(elem, " \t\n");
            if (kvData.empty())
            {
                continue;
            }
            std::vector<std::string> kv = strsplit(kvData, "=");

            if (kv.size() == 1)
            {
                args.push_back({kv[0], ""});
            }
            else if (kv.size() == 2)
            {
                args.push_back({kv[0], kv[1]});
            }
        }
        return args;
    }
    std::string pretty()
    {
        std::vector<std::string> args;
        for (const auto& elem : strsplit(_buf, " "))
        {
            if (strtrim(elem, " \t\n").empty())
            {
                continue;
            }
            args.push_back(strtrim(elem, " \t\n"));
        }
        std::string str = "";
        for (const auto& elem : args)
        {
            str.append(" ").append(elem);
        }
        if (endsWith(_buf, " "))
        {
            str.append(" ");
        }
        return str;
    }
};

struct CommandsManager
{
    std::string prompt;
    int historyMaxLen;
    bool enableMultiLine;
    std::string historyFileName;
    std::map<std::string, Command> commandMap;
    std::vector<std::string> commandNames;
};

static CommandsManager initializeCommandsManager();
static CommandsManager g_commandsManager = initializeCommandsManager();

// user.add id=000 name=xxx age=yy height=zzz sex=F deleted=0
// user.delete name=xxx
// user.search name=x sex=f isLocal
// user.update id=kkk

static std::tuple<bool, std::string, std::string> parseArg(const std::string& str)
{
    std::vector<std::string> vec = strsplit(strtrim(str, " \t\n\r"), "=");
    if (vec.size() != 2)
    {
        return std::make_tuple(false, "", "");
    }
    return std::make_tuple(true, strtrim(vec[0], " \t\n\r"), strtrim(vec[1], " \t\n\r"));
}

static void completionCallback(const char* buf, linenoiseCompletions* lc)
{
    std::string rawBuf = buf;
    if (rawBuf.empty())
    {
        for (const auto& pair : g_commandsManager.commandMap)
        {
            linenoiseAddCompletion(lc, pair.second.name.c_str());
        }
    }
    else
    {
    }
}

static char* hintsCallback(const char* buf, int* color, int* bold)
{
    std::string rawBuf = buf;
    if (endsWith(rawBuf, " ") || rawBuf.empty())
    {
        return NULL;
    }

    std::vector<std::string> cmdWithOpts;
    for (auto& elem : strsplit(rawBuf, " "))
    {
        if (elem.empty())
        {
            continue;
        }
        cmdWithOpts.push_back(elem);
    }
    if (cmdWithOpts.size() == 0)
    {
        return NULL;
    }

    *color = 90;
    *bold = 0;

    if (cmdWithOpts.size() >= 1)
    {
        // 命令，hints
        auto cmdIt = g_commandsManager.commandMap.find(toLower(cmdWithOpts[0]));
        if (cmdIt != g_commandsManager.commandMap.end())
        {
            return stringToHeapChars("  ==> " + cmdIt->second.summary);
        }
        else
        {
            return NULL;
        }

        // options hints
        auto optIt = cmdIt->second.argsMap.find(toLower(cmdWithOpts[cmdWithOpts.size() - 1]));
    }
    else
    {
        return NULL;
    }
    return NULL;
}

static void freeHintsCallback(void* ptr)
{
    if (NULL != ptr)
    {
        free(ptr);
    }
}

static CommandsManager initializeCommandsManager()
{
    auto mgr = CommandsManager{};
    mgr.prompt = "demo> ";
    mgr.historyMaxLen = 200;
    mgr.enableMultiLine = true;
    mgr.historyFileName = "history.txt";

    linenoiseSetMultiLine(mgr.enableMultiLine ? 1 : 0);
    linenoiseHistorySetMaxLen(mgr.historyMaxLen);
    linenoiseHistoryLoad(mgr.historyFileName.c_str());
    linenoiseSetHintsCallback(hintsCallback);
    linenoiseSetFreeHintsCallback(freeHintsCallback);
    linenoiseSetCompletionCallback(completionCallback);

    std::vector<Command> commands;
    commands.emplace_back(Command::create()
                              .name("user.add")
                              .since("1.0")
                              .summary("add user")
                              .arg(CommandArg::create()
                                       .name("name")
                                       .defaultValue("defaultValue")
                                       .summary("user name")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("age")
                                       .defaultValue("defaultValue")
                                       .summary("user age")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("gender")
                                       .defaultValue("man or woman")
                                       .summary("user gender: man/woman")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("height")
                                       .defaultValue("175")
                                       .summary("user height, centimeters")
                                       .build())
                              .build());

    commands.emplace_back(Command::create()
                              .name("user.delete")
                              .since("1.0")
                              .summary("delete user by name")
                              .arg(CommandArg::create()
                                       .name("name")
                                       .defaultValue("defaultValue")
                                       .summary("user name")
                                       .build())
                              .build());

    commands.emplace_back(Command::create()
                              .name("user.search")
                              .since("1.0")
                              .summary("search")
                              .arg(CommandArg::create()
                                       .name("name")
                                       .defaultValue("defaultValue")
                                       .summary("user name")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("gender")
                                       .defaultValue("man or woman")
                                       .summary("user gender: man/woman")
                                       .build())
                              .build());
    commands.emplace_back(Command::create()
                              .name("user.update")
                              .since("1.0")
                              .summary("update")
                              .arg(CommandArg::create()
                                       .name("name")
                                       .defaultValue("defaultValue")
                                       .summary("user name")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("gender")
                                       .defaultValue("man or woman")
                                       .summary("user gender: man/woman")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("age")
                                       .defaultValue("defaultValue")
                                       .summary("user age")
                                       .build())
                              .arg(CommandArg::create()
                                       .name("height")
                                       .defaultValue("175")
                                       .summary("user height, centimeters")
                                       .build())
                              .build());
    commands.emplace_back(
        Command::create().name("quit").since("1.0").summary("quit program").build());
    commands.emplace_back(
        Command::create().name("exit").since("1.0").summary("exit program").build());
    commands.emplace_back(
        Command::create().name("clear").since("1.0").summary("clear screen").build());
    for (const auto& elem : commands)
    {
        mgr.commandMap[elem.name] = elem;
        mgr.commandNames.emplace_back(elem.name);
    }

    return mgr;
}

int main(int argc, char** argv)
{
    char* rawLine = NULL;
    initializeCommandsManager();
    while ((rawLine = linenoise(g_commandsManager.prompt.c_str())) != NULL)
    {
        // 转换C++字符串，避免遗漏释放内存
        std::string line = rawLine;
        linenoiseFree(rawLine);
        if (line.empty())
        {
            continue;
        }

        if (line == "exit" || line == "quit")
        {
            linenoiseHistorySave(g_commandsManager.historyFileName.c_str());
            break;
        }
        else if (line == "clear")
        {
            linenoiseClearScreen();
        }
        else
        {
            // 正常业务处理
            fprintf(stdout, "|result => %s\n", line.c_str());
            fflush(stdout);
        }
    }
    return 0;
}