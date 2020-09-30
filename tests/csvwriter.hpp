#ifndef CSVWRITER_H
#define CSVWRITER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;
class CSVWriter
{
public:
    CSVWriter(const std::string &filename)
    {
        this->filename = filename;
    }

    ~CSVWriter()
    {
        flush(false);
    }

    CSVWriter &add(std::string &str)
    {
        //if " character was found, escape it
        size_t position = str.find("\"", 0);
        bool foundQuotationMarks = position != string::npos;
        while (position != string::npos)
        {
            str.insert(position, "\"");
            position = str.find("\"", position + 2);
        }
        if (foundQuotationMarks)
        {
            str = "\"" + str + "\"";
        }
        else if (str.find(this->separator) != string::npos)
        {
            //if separator was found and string was not escapted before, surround string with "
            str = "\"" + str + "\"";
        }
        return this->add<string>(str);
    }

    template <typename T>
    CSVWriter &add(T str)
    {
        if (valueCount > 0)
            this->ss << this->separator;
        this->ss << str;
        this->valueCount++;

        return *this;
    }

    template <typename T>
    CSVWriter &operator<<(const T &t)
    {
        return this->add(t);
    }

    void operator+=(CSVWriter &csv)
    {
        this->ss << endl
                 << csv;
    }

    string toString()
    {
        return ss.str();
    }

    friend ostream &operator<<(std::ostream &os, CSVWriter &csv)
    {
        return os << csv.toString();
    }

    CSVWriter &newRow()
    {
        if (this->firstRow)
        {
            //if the row is the first row, do not insert a new line
            this->firstRow = false;
        }
        else
        {
            ss << endl;
        }
        valueCount = 0;
        return *this;
    }

    bool flush(bool append = false)
    {
        ofstream file;
        if (append)
            file.open(filename.c_str(), ios::out | ios::app);
        else
            file.open(filename.c_str(), ios::out | ios::trunc);

        if (!file.is_open())
            return false;
        if (append)
            file << endl;
        file << ss.rdbuf();
        file.close();
        if (file.good())
        {
            ss.clear();
            return true;
        }
        return false;
    }

protected:
    bool firstRow = false;
    string separator = ";";
    int valueCount = 0;
    stringstream ss;
    std::string filename;
};

#endif // CSVWRITER_H
