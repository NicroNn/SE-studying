#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

namespace ArgumentParser {
class ArgParser {
  public:
    ArgParser(const std::string& description) : description(description) {}

    ArgParser& AddStringArgument(const char short_name,
                                 const std::string& long_name,
                                 const std::string& default_value = "");

    ArgParser& AddStringArgument(const std::string& long_name, const std::string& default_value = "");

    ArgParser& AddIntArgument(const char short_name, const std::string& long_name, int default_value = 0);

    ArgParser& AddIntArgument(const std::string& long_name, int default_value = 0);

    ArgParser& AddFlag(const char short_name, const std::string& long_name);

    bool Parse(const std::vector<std::string>& args);

    std::string GetStringValue(const std::string& long_name, size_t index = 0);

    int GetIntValue(const std::string& long_name, size_t index = 0);

    bool GetFlag(const std::string& long_name);

    ArgParser& StoreValue(std::string& external_var);

    ArgParser& StoreValue(bool& external_var);

    ArgParser& StoreValues(std::vector<int>& external_var);

    ArgParser& Default(const std::string& default_value);

    ArgParser& Default(const char* default_value);

    ArgParser& Default(bool default_value);

    ArgParser& Positional();

    ArgParser& MultiValue(size_t min_count = 0);

    ArgParser& AddHelp(const char short_name, const std::string& long_name, const std::string& help_message);

    ArgParser& AddFlag(const char short_name, const std::string& long_name, const std::string& help_message);

    ArgParser& AddIntArgument(const std::string& long_name, const std::string help_message);

    bool Help() const;

    std::vector<std::string> HelpDescription() const;

  private:
    struct Argument {
        enum Type { StringType, IntType, FlagType } type;
        char short_name;
        std::vector<std::string> values;
        std::string default_value;
        std::string help_message;
        bool is_multi_value = false;
        bool is_positional = false;
        size_t min_count = 0;
        std::string* external_storage = nullptr;
        bool* external_bool_storage = nullptr;
        std::vector<int>* external_multi_storage = nullptr;
    };

    std::map<std::string, Argument> arguments;
    Argument* last_added = nullptr;
    Argument* positional = nullptr;
    std::string description;

    std::string findLongNameByShortName(char short_name);

    bool processArgument(const std::string& name, const std::string& value);

    bool processArgument(Argument* positional_arg, const std::string& value);

    bool assignDefaultsAndCheck();

    void copyToExternalStorage();
};
}