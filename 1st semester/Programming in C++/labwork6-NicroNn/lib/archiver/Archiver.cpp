#include "Archiver.h"


void Archiver::createArchive(const std::string& archiveName) {
    std::ofstream archive(archiveName, std::ios::binary);
    if (!archive.is_open()) {
        std::cerr << "Failed to create archive: " << archiveName << std::endl;
        return;
    }
    archive.close();
}

void Archiver::appendFile(const std::string& archiveName, const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::ofstream archive(archiveName, std::ios::binary | std::ios::app);
    if (!archive.is_open()) {
        std::cerr << "Failed to open archive: " << archiveName << std::endl;
        return;
    }

    std::string name = "[file:" + fileName + "]";
    archive << name << '\n';
    char ch = 0;
    char temp = 0;
    int count = 0;
    while (file.get(ch)) {
        std::bitset<8> data(ch);
        std::bitset<12> encoded = Hamming::encode(data);
        if (count % 2 == 0) {
            for (int i = 0; i < 8; i++){
                ch <<= 1;
                ch |= encoded[i];
            }
            for (int i = 8; i < 12; i++) {
                temp <<= 1;
                temp |= encoded[i];
            }
            temp <<= 4;
            archive << ch;
        } else {
            temp >>= 4;
            for (int i = 0; i < 4; i++) {
                temp <<= 1;
                temp |= encoded[i];
            }
            for (int i = 4; i < 12; i++) {
                ch <<= 1;
                ch |= encoded[i];
            }
            archive << temp;
            archive << ch;
        }
        count++;
    }
    if (count % 2 == 1) {
        archive << temp;
    }
    file.close();
    archive << '\n';
    archive.close();
}

void Archiver::extractFile(const std::string& archiveName, const std::string& fileName) {
    std::ifstream archive(archiveName, std::ios::binary);
    if (!archive.is_open()) {
        std::cerr << "Failed to open archive: " << archiveName << std::endl;
        return;
    }

    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to create file: " << fileName << std::endl;
        return;
    }
    std::string line;
    std::getline(archive, line);
    if (line.substr(0, 6) != "[file:") {
        std::cerr << "No metadata." << std::endl;
        return;
    }

    char ch;
    char temp = 0;
    int count = 0;
    while (archive.get(ch) && ch != '\n') {
        std::bitset<12> bits;
        if (count % 2 == 0) {
            for (int i = 0; i < 8; i++) {
                bits[i] = ch & (1 << (7 - i));
            }
            archive.get(temp);
            for (int i = 8; i < 12; i++) {
                bits[i] = temp & (1 << (7 - (i - 8)));
            }
        } else {
            for (int i = 0; i < 4; i++) {
                bits[i] = temp & (1 << (3 - i));
            }
            for (int i = 4; i < 12; i++) {
                bits[i] = ch & (1 << (7 - (i - 4)));
            }
        }
        char decoded_char = static_cast<char>(Hamming::decode(bits).to_ulong());
        file.put(decoded_char);
        count++;
    }

    file.close();
    archive.close();
}


void Archiver::listFiles(const std::string& archiveName) {
    if (archiveName.length() == 0) {
        std::cerr << "Failed to open archive: " << archiveName << std::endl;
        return;
    }
    std::ifstream archive(archiveName, std::ios::binary);
    std::string line;
    std::getline(archive, line);
    if (line.substr(0, 6) != "[file:") {
        std::cerr << "No metadata." << std::endl;
        return;
    }
    std::string filename = line.substr(6, line.size() - 7);
    std::cout << "Files in archive: " << std::endl;
    std::cout << " - file : " << filename << std::endl;
    char ch;
    while (archive.get(ch)) {
        if (ch == '['){
            if (line.substr(0, 6) != "[file:") {
                std::cerr << "No metadata." << std::endl;
                return;
            }
            std::getline(archive, line);
            std::cout << " - file : " << line.substr(5, line.size() - 6) << std::endl;
        }
    }
}

void Archiver::deleteFile(const std::string& archiveName, const std::string& fileName) {
    std::ifstream archive(archiveName, std::ios::binary);
    if (!archive.is_open()) {
        std::cerr << "Failed to open archive: " << archiveName << std::endl;
        return;
    }

    std::ofstream tempArchive("temp_archive", std::ios::binary);
    std::string line;
    bool skip = false;

    while (std::getline(archive, line)) {
        if (line.substr(0, 6) == "[file:") {
            if (line.substr(6, line.find(']') - 6) == fileName) {
                skip = true;
                continue;
            }
            else {
                skip = false;
            }
            tempArchive << line << '\n';
        }
        else {
            if (!skip) {
                tempArchive << line << '\n';
            }
        }
    }

    archive.close();
    tempArchive.close();

    remove(archiveName.c_str());
    rename("temp_archive", archiveName.c_str());
}


void Archiver::concatenateArchives(const std::string& archiveName1, const std::string& archiveName2, const std::string& resultArchiveName) {
    std::ifstream archive1(archiveName1, std::ios::binary);
    std::ifstream archive2(archiveName2, std::ios::binary);
    std::ofstream resultArchive(resultArchiveName, std::ios::binary);

    if (!archive1.is_open() || !archive2.is_open() || !resultArchive.is_open()) {
        std::cerr << "Error opening archives." << std::endl;
        return;
    }

    resultArchive << archive1.rdbuf();
    archive1.close();

    resultArchive << archive2.rdbuf();
    archive2.close();
    resultArchive.close();
}



