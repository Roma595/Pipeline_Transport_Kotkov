#include "Log.h"

Teebuf::Teebuf(std::istream& input, std::ostream& peek)
    : m_input_stream{ input }
    , m_input_buf{ input.rdbuf() }
    , m_output_buf{ peek.rdbuf() }
    , m_char{} {
    input.rdbuf(this);
}

Teebuf::~Teebuf() {
    m_input_stream.rdbuf(m_input_buf);
}


Teebuf::int_type Teebuf::underflow(){
    int_type c = m_input_buf->sbumpc();
    if (traits_type::eq_int_type(c, traits_type::eof())) {
        return traits_type::eof();
    }
    m_char = traits_type::to_char_type(c);
    setg(&m_char, &m_char, &m_char + 1);
    int_type r = m_output_buf->sputc(m_char);
    if (traits_type::eq_int_type(r, traits_type::eof())) {
        return traits_type::eof();
    }
    return c;
}
