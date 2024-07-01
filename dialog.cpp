#include "dialog.h"
#include "ui_dialog.h"
#include <fstream>
#include <iostream>
#include <vector>
//###########################################################################
bool writeVectorToFile(const std::vector<long long> &vec, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open the file for writing: " << filename << std::endl;
        return false;
    }

    size_t size = vec.size();
    outFile.write(reinterpret_cast<const char *>(&size), sizeof(size));
    outFile.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(long long));

    outFile.close();
    return true;
}

bool readVectorFromFile(std::vector<long long> &vec, const std::string &filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Cannot open the file for reading: " << filename << std::endl;
        return false;
    }

    size_t size;
    inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
    vec.resize(size);
    inFile.read(reinterpret_cast<char *>(vec.data()), size * sizeof(long long));

    inFile.close();
    return true;
}

bool compareVectors(const std::vector<long long> &vec1, const std::vector<long long> &vec2)
{
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}
//###########################################################################
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //###########################################################################
    std::vector<long long> originalVec = {1, 2, 3, 4, 5};
    std::string filename = "vector_data.bin";

    if (!writeVectorToFile(originalVec, filename)) {
    }

    std::vector<long long> readVec;
    if (!readVectorFromFile(readVec, filename)) {
    }

    if (compareVectors(originalVec, readVec)) {
        std::cout << "The vector was written and read correctly." << std::endl;
    } else {
        std::cout << "The vector was not written and read correctly." << std::endl;
    }
    //###########################################################################
}

Dialog::~Dialog()
{
    delete ui;
}
