#ifndef LABWORK6_LIB_ARCHIVER_ARCHIVER_H_
#define LABWORK6_LIB_ARCHIVER_ARCHIVER_H_
#include "../hamming/Hamming.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Archiver {
  public:
    static void createArchive(const std::string& archiveName);
    static void appendFile(const std::string& archiveName, const std::string& fileName);
    static void extractFile(const std::string& archiveName, const std::string& fileName);
    static void listFiles(const std::string& archiveName);
    static void deleteFile(const std::string& archiveName, const std::string& fileName);
    static void concatenateArchives(const std::string& archiveName1, const std::string& archiveName2, const std::string& resultArchiveName);
};


#endif //LABWORK6_LIB_ARCHIVER_ARCHIVER_H_
