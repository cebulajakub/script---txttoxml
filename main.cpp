#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

void txtToXml(const std::string &txtContent, const std::string &xmlFilePath)
{
    std::ofstream outputFile(xmlFilePath);
    outputFile << "<root>" << std::endl;
    outputFile << txtContent << std::endl;
    outputFile << "</root>" << std::endl;
    std::cout << "Utworzono plik XML: " << xmlFilePath << std::endl;
}

void convertTxtToXmlInFolder(const std::string &folderPath)
{
    std::stringstream buffer;

    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            std::ifstream inputFile(entry.path().string());
            if (inputFile.is_open())
            {
                buffer.str("");
                buffer << inputFile.rdbuf();
                std::string txtContent = buffer.str();
                inputFile.close();

                std::string xmlFilePath = entry.path().string();
                size_t lastDot = xmlFilePath.find_last_of(".");
                xmlFilePath = xmlFilePath.substr(0, lastDot) + ".xml";
                txtToXml(txtContent, xmlFilePath);
            }
            else
            {
                std::cerr << "Blad otwierania pliku " << entry.path() << std::endl;
            }
        }
    }
}

int main()
{
    std::string folderPath = "C:\\Users\\Jakub\\Desktop\\txttoxml";

    convertTxtToXmlInFolder(folderPath);

    return 0;
}
