#pragma once

#include <streambuf>
#include <iostream>

class Teebuf : public std::streambuf {
public:
    Teebuf(std::istream& input, std::ostream& peek);

    ~Teebuf();
 
protected:
    int_type underflow() override;

private:
    std::istream& m_input_stream;
    std::streambuf* m_input_buf;
    std::streambuf* m_output_buf;
    char_type m_char;
};

