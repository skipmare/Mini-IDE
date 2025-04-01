//
// Created by Jappe on 24/06/2024.
//

#include "htmlConverter.h"

HTMLWriter::HTMLWriter(const std::string &filename): filename("../" + filename) {
        htmlContent = "<html><body>";
}

HTMLWriter::~HTMLWriter()
{
    if (file.is_open()) {
        file.close();
    }
}

void HTMLWriter::writePlainText(const std::string &text)
{
    htmlContent += text;
}

void HTMLWriter::writeStyledText(const std::string &text, const std::string &hexColorCode, int fontWeight)
{
    htmlContent += "<span style=\"color:" + hexColorCode + "; font-weight:" + std::to_string(fontWeight) + ";\">" + text + "</span>";
}

void HTMLWriter::addNewline()
{
    htmlContent += "<br>";
}

void HTMLWriter::saveFile()
{
    htmlContent += "</body></html>";
    file.open(filename);
    if (file.is_open()) {
        file << htmlContent;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}