#include "ArgParser.h"
namespace ArgumentParser {
ArgParser& ArgParser::AddStringArgument(const char short_name,
                                        const std::string& long_name,
                                        const std::string& default_value) {
    arguments[long_name] =
        Argument{.type = Argument::StringType, .short_name = short_name, .default_value = default_value};
    last_added = &arguments[long_name];
    return *this;
}
ArgParser& ArgParser::AddStringArgument(const std::string& long_name, const std::string& default_value) {
    arguments[long_name] = Argument{.type = Argument::StringType, .default_value = default_value};
    last_added = &arguments[long_name];
    return *this;
}
ArgParser& ArgParser::AddIntArgument(const char short_name, const std::string& long_name, int default_value) {
    arguments[long_name] =
        Argument{.type = Argument::IntType, .short_name = short_name, .default_value = std::to_string(default_value)};
    last_added = &arguments[long_name];
    return *this;
}
ArgParser& ArgParser::AddIntArgument(const std::string& long_name, int default_value) {
    arguments[long_name] = Argument{.type = Argument::IntType, .default_value = std::to_string(default_value)};
    last_added = &arguments[long_name];
    return *this;
}
ArgParser& ArgParser::AddFlag(const char short_name, const std::string& long_name) {
    arguments[long_name] = Argument{.type = Argument::FlagType, .short_name = short_name};
    last_added = &arguments[long_name];
    return *this;
}
bool ArgParser::Parse(const std::vector<std::string>& args) {
    // Clear previous values
    for (auto& arg : arguments) {
        arg.second.values.clear();
    }

    for (const auto& arg : args) {
        if (arg == "--help" || arg == "-h") {
            return true;
        }

        bool is_long_arg = arg.find("--") == 0;
        bool is_short_arg = arg.find('-') == 0 && !is_long_arg;
        bool is_positional = !(is_long_arg || is_short_arg) && arg != args[0];

        if (is_long_arg) {
            auto pos = arg.find('=');
            std::string name = arg.substr(2, pos - 2);
            std::string
                value = (pos != std::string::npos) ? arg.substr(pos + 1) : "true"; // Default value for flags

            if (!processArgument(name, value)) {
                return false;
            }
        } else if (is_short_arg) {
            if (arg.size() > 2 && arg[2] != '=') {
                // Iterate over each character as a separate flag
                for (size_t i = 1; i < arg.size(); ++i) {
                    std::string name = findLongNameByShortName(arg[i]);
                    if (name.empty()) {
                        return false;
                    }

                    // Set the flag value to true
                    if (!processArgument(name, "true")) {
                        return false;
                    }
                }
            } else {
                // Argument in form -x=value
                std::string name;
                std::string value;

                auto pos = arg.find('=');
                if (pos != std::string::npos) {
                    char short_name = arg[1];
                    name = findLongNameByShortName(short_name);
                    if (name.empty()) {
                        return false;
                    }

                    value = arg.substr(pos + 1);
                } else {
                    name = findLongNameByShortName(arg[1]);
                    if (name.empty()) {
                        return false;
                    }

                    value = "true";
                }

                if (!processArgument(name, value)) {
                    return false;
                }
            }
        } else if (is_positional) {
            processArgument(positional, arg);
        }

    }
    if (!assignDefaultsAndCheck()) {
        return false;
    }

    copyToExternalStorage();

    return true;
}
std::string ArgParser::GetStringValue(const std::string& long_name, size_t index) {
    const auto& values = arguments.at(long_name).values;
    if (index < values.size()) {
        return values[index];
    }
    throw std::out_of_range("Index out of range");
}
int ArgParser::GetIntValue(const std::string& long_name, size_t index) {
    if (index < arguments[long_name].values.size()) {
        return std::stoi(arguments[long_name].values[index]);
    }
    throw std::out_of_range("Index out of range");
}
bool ArgParser::GetFlag(const std::string& long_name) {
    return arguments[long_name].values[0] == "true";
}
ArgParser& ArgParser::StoreValue(std::string& external_var) {
    if (last_added != nullptr) {
        last_added->external_storage = &external_var;
    }
    return *this;
}
ArgParser& ArgParser::StoreValue(bool& external_var) {
    if (last_added != nullptr) {
        last_added->external_bool_storage = &external_var;
    }
    return *this;
}
ArgParser& ArgParser::StoreValues(std::vector<int>& external_var) {
    if (last_added != nullptr && last_added->is_multi_value) {
        last_added->external_multi_storage = &external_var;
    }
    return *this;
}
ArgParser& ArgParser::Default(const std::string& default_value) {
    if (last_added != nullptr) {
        last_added->default_value = default_value;
    }
    return *this;
}
ArgParser& ArgParser::Default(const char* default_value) {
    return Default(std::string{default_value});
}
ArgParser& ArgParser::Default(bool default_value) {
    if (last_added != nullptr && last_added->type == Argument::FlagType) {
        last_added->default_value = default_value ? "true" : "false";
    }
    return *this;
}
ArgParser& ArgParser::Positional() {
    if (last_added != nullptr) {
        last_added->is_positional = true;
        positional = last_added;
    }
    return *this;
}
ArgParser& ArgParser::MultiValue(size_t min_count) {
    if (last_added != nullptr) {
        last_added->is_multi_value = true;
        last_added->min_count = min_count;
    }
    return *this;
}
ArgParser& ArgParser::AddHelp(const char short_name, const std::string& long_name, const std::string& help_message) {
    // Add help argument as a special flag
    AddFlag(short_name, long_name);
    last_added->help_message = help_message;
    return *this;
}
ArgParser& ArgParser::AddFlag(const char short_name, const std::string& long_name, const std::string& help_message) {
    return AddHelp(short_name, long_name, help_message);
}
ArgParser& ArgParser::AddIntArgument(const std::string& long_name, const std::string help_message) {
    return AddHelp('n', long_name, help_message);
}
bool ArgParser::Help() const {
    std::cout << description << "\n";
    for (const auto& arg : arguments) {
        std::cout << "-" << arg.second.short_name << ", --" << arg.first << ": " << arg.second.help_message << "\n";
    }
    return true;
}
std::vector<std::string> ArgParser::HelpDescription() const {
    std::vector<std::string> result;
    result.push_back(description + "\n");
    for (const auto& arg : arguments) {
        std::string new_line = &"-"[arg.second.short_name];
        new_line += ", --" + arg.first + ": " + arg.second.help_message + "\n";
        result.push_back(new_line);
    }
    return result;
}
std::string ArgParser::findLongNameByShortName(char short_name) {
    auto it = std::find_if(arguments.begin(), arguments.end(),
                           [short_name](const auto& pair) { return pair.second.short_name == short_name; });
    if (it == arguments.end()) {
        std::cout << "Argument not found for short name: " << short_name << "\n";
        return "";
    }
    return it->first;
}
bool ArgParser::processArgument(const std::string& name, const std::string& value) {
    auto it = arguments.find(name);
    if (it == arguments.end()) {
        std::cout << "Argument not found: " << name << "\n";
        return false;
    }

    if (it->second.is_multi_value) {
        it->second.values.push_back(value);
    } else {
        it->second.values = {value};
    }
    return true;
}
bool ArgParser::processArgument(ArgParser::Argument* positional_arg, const std::string& value) {
    if (positional_arg->is_multi_value) {
        positional_arg->values.push_back(value);
    } else {
        positional_arg->values = {value};
    }
    return true;
}
bool ArgParser::assignDefaultsAndCheck() {
    for (auto& arg : arguments) {
        if (arg.second.values.empty()) {
            if (arg.second.default_value.empty() && !arg.second.is_multi_value) {
                std::cout << "Missing required argument: " << arg.first << "\n";
                return false;
            } else if (!arg.second.default_value.empty()) {
                arg.second.values.push_back(arg.second.default_value);
            }
        }
    }

    for (auto& arg_pair : arguments) {
        Argument& arg = arg_pair.second;
        if (arg.is_multi_value && arg.min_count > 0 && arg.values.size() < arg.min_count) {
            std::cout << "Not enough values for argument: " << arg_pair.first << ". Expected at least "
                      << arg.min_count << " values.\n";
            return false;
        }
    }
    return true;
}
void ArgParser::copyToExternalStorage() {
    for (auto& arg_pair : arguments) {
        Argument& arg = arg_pair.second;
        if (arg.external_storage != nullptr) {
            *(arg.external_storage) = arg.values.empty() ? "" : arg.values.front();
        }
        if (arg.external_multi_storage != nullptr && arg.is_multi_value) {
            arg.external_multi_storage->clear();
            for (const auto& val : arg.values) {
                arg.external_multi_storage->push_back(std::stoi(val));
            }
        }
        if (arg.external_bool_storage != nullptr && arg.type == Argument::FlagType) {
            *(arg.external_bool_storage) = (arg.values.front() == "true");
        }
    }
}
}