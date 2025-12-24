#include <system_error>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE

TEST(std_errc, 001)
{
    std::errc::address_family_not_supported;
    std::errc::address_in_use;
    std::errc::address_not_available;
    std::errc::already_connected;
    std::errc::argument_list_too_long;
    std::errc::argument_out_of_domain;
    std::errc::bad_address;
    std::errc::bad_file_descriptor;
    std::errc::bad_message;
    std::errc::broken_pipe;
    std::errc::connection_aborted;
    std::errc::connection_already_in_progress;
    std::errc::connection_refused;
    std::errc::connection_reset;
    std::errc::cross_device_link;
    std::errc::destination_address_required;
    std::errc::device_or_resource_busy;
    std::errc::directory_not_empty;
    std::errc::executable_format_error;
    std::errc::file_exists;
    std::errc::file_too_large;
    std::errc::filename_too_long;
    std::errc::function_not_supported;
    std::errc::host_unreachable;
    std::errc::identifier_removed;
    std::errc::illegal_byte_sequence;
    std::errc::inappropriate_io_control_operation;
    std::errc::interrupted;
    std::errc::invalid_argument;
    std::errc::invalid_seek;
    std::errc::io_error;
    std::errc::is_a_directory;
    std::errc::message_size;
    std::errc::network_down;
    std::errc::network_reset;
    std::errc::network_unreachable;
    std::errc::no_buffer_space;
    std::errc::no_child_process;
    std::errc::no_link;
    std::errc::no_lock_available;
    std::errc::no_message;
    std::errc::no_protocol_option;
    std::errc::no_space_on_device;
    std::errc::no_such_device_or_address;
    std::errc::no_such_device;
    std::errc::no_such_file_or_directory;
    std::errc::no_such_process;
    std::errc::not_a_directory;
    std::errc::not_a_socket;
    std::errc::not_connected;
    std::errc::not_enough_memory;
    std::errc::not_supported;
    std::errc::operation_canceled;
    std::errc::operation_in_progress;
    std::errc::operation_not_permitted;
    std::errc::operation_not_supported;
    std::errc::operation_would_block;
    std::errc::owner_dead;
    std::errc::permission_denied;
    std::errc::protocol_error;
    std::errc::protocol_not_supported;
    std::errc::read_only_file_system;
    std::errc::resource_deadlock_would_occur;
    std::errc::resource_unavailable_try_again;
    std::errc::result_out_of_range;
    std::errc::state_not_recoverable;
    std::errc::text_file_busy;
    std::errc::timed_out;
    std::errc::too_many_files_open_in_system;
    std::errc::too_many_files_open;
    std::errc::too_many_links;
    std::errc::too_many_symbolic_link_levels;
    std::errc::value_too_large;
    std::errc::wrong_protocol_type;
    std::system_error(std::make_error_code(std::errc::value_too_large), "invalid value");
    std::error_code ec = std::make_error_code(std::errc::value_too_large);
    SPDLOG_INFO("errc: {}, value: {}, message: {}, category name: {}, category message: {}", static_cast<int>(std::errc::value_too_large), ec.value(),
                ec.message(), ec.category().name(), ec.category().message(2));

    auto fn = [](bool x) -> std::error_code {
        if (x)
        {
            return std::error_code{};
        }
        else
        {
            return std::make_error_code(std::errc::invalid_argument);
        }
    };
    if (!fn(true))
    {
        SPDLOG_INFO("no exception");
    }
    else
    {
        SPDLOG_INFO("have exception");
    }
}
#endif