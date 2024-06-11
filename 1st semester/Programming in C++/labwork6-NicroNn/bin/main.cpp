#include "lib/parser/Parser.h"
#include "lib/archiver/Archiver.h"
#include <sstream>
#include <iterator>


int main(int argc, char** argv) {
    ArgumentParser::ArgParser parser("Archiver argument parser");
    std::vector<std::string> filenames;
    parser.AddStringArgument('f', "file");
    parser.AddStringArgument("files").MultiValue().Positional().StoreValues(filenames);
    parser.AddFlag('c', "create").Default(false);
    parser.AddFlag('l', "list").Default(false);
    parser.AddFlag('x', "extract").Default(false);
    parser.AddFlag('a', "append").Default(false);
    parser.AddFlag('d', "delete").Default(false);
    parser.AddFlag('A', "concatenate").Default(false);

    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    parser.Parse(args);

    if (parser.GetFlag("create")){
        Archiver::createArchive(parser.GetStringValue("file"));
        for (const std::string& file : filenames){
            Archiver::appendFile(parser.GetStringValue("file"), file);
        }
    }
    if (parser.GetFlag("list")){
        Archiver::listFiles(parser.GetStringValue("file"));
    }
    if (parser.GetFlag("extract")){
        for (const std::string& file : filenames) {
            Archiver::extractFile(parser.GetStringValue("file"), file);
        }
    }
    if (parser.GetFlag("append")){
        for (const std::string& file : filenames){
            Archiver::appendFile(parser.GetStringValue("file"), file);
        }
    }
    if (parser.GetFlag("delete")){
        for (const std::string& file : filenames){
            Archiver::deleteFile(parser.GetStringValue("file"), file);
        }
    }
    if (parser.GetFlag("concatenate")){
        for (const std::string& file : filenames){
            Archiver::concatenateArchives(filenames[0], filenames[1], parser.GetStringValue("file"));
        }
    }
}
