#include <algorithm>
#include <array>
#include <chrono>
#include <complex>
#include <ctime>
#include <deque>
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
#include <utility>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ut_config.h"

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
            commandArgs_.insert(commandArgs_.end(), std::make_move_iterator(args.begin()), std::make_move_iterator(args.end()));
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

#ifdef RUN_ALL_TEST_CASE

TEST(OOP, 002)
{
    std::vector<CommandArg> userAttrArgs = {
        CommandArg::create().name("attr0").defaultValue("attr0-default").summary("attr0-summary").build(),
        CommandArg::create().name("attr1").defaultValue("attr1-default").summary("attr1-summary").build(),
    };

    Command command = Command::create()
                          .name("user.add")
                          .since("1.0")
                          .summary("add user command")
                          .arg(CommandArg::create().name("id").defaultValue("defaultId").summary("user id").build())
                          .arg(CommandArg::create().name("name").defaultValue("defaultName").summary("user name").build())
                          .args(std::move(userAttrArgs))
                          .args({
                              CommandArg::create().name("config").defaultValue("config.json").summary("Config file").build(),
                              CommandArg::create().name("log-level").defaultValue("info").summary("Log level").build(),
                          })
                          .build();

    EXPECT_EQ(command.name, "user.add");
    EXPECT_EQ(command.since, "1.0");
    EXPECT_EQ(command.summary, "add user command");

    EXPECT_TRUE(command.argsMap.contains("id"));
    EXPECT_EQ(command.argsMap["id"].name, "id");
    EXPECT_EQ(command.argsMap["id"].summary, "user id");
    EXPECT_EQ(command.argsMap["id"].defaultValue, "defaultId");

    EXPECT_TRUE(command.argsMap.contains("name"));
    EXPECT_EQ(command.argsMap["name"].name, "name");
    EXPECT_EQ(command.argsMap["name"].summary, "user name");
    EXPECT_EQ(command.argsMap["name"].defaultValue, "defaultName");

    EXPECT_TRUE(command.argsMap.contains("config"));
    EXPECT_EQ(command.argsMap["config"].name, "config");
    EXPECT_EQ(command.argsMap["config"].summary, "Config file");
    EXPECT_EQ(command.argsMap["config"].defaultValue, "config.json");

    EXPECT_TRUE(command.argsMap.contains("log-level"));
    EXPECT_EQ(command.argsMap["log-level"].name, "log-level");
    EXPECT_EQ(command.argsMap["log-level"].summary, "Log level");
    EXPECT_EQ(command.argsMap["log-level"].defaultValue, "info");

    EXPECT_TRUE(command.argsMap.contains("attr0"));
    EXPECT_EQ(command.argsMap["attr0"].name, "attr0");
    EXPECT_EQ(command.argsMap["attr0"].summary, "attr0-summary");
    EXPECT_EQ(command.argsMap["attr0"].defaultValue, "attr0-default");

    EXPECT_TRUE(command.argsMap.contains("attr1"));
    EXPECT_EQ(command.argsMap["attr1"].name, "attr1");
    EXPECT_EQ(command.argsMap["attr1"].summary, "attr1-summary");
    EXPECT_EQ(command.argsMap["attr1"].defaultValue, "attr1-default");
}

TEST(OOP, 001)
{
    auto commandArg = CommandArg::create().name("xxx").defaultValue("yyy").summary("zzz").build();
    EXPECT_EQ(commandArg.name, "xxx");
    EXPECT_EQ(commandArg.summary, "zzz");
    EXPECT_EQ(commandArg.defaultValue, "yyy");
}

#endif