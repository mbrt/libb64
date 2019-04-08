// :mode=c++:
/*
encode.h - c++ wrapper for a base64 encoding algorithm

This is part of the libb64 project, and has been placed in the public domain.
For details, see http://sourceforge.net/projects/libb64
*/
#ifndef BASE64_ENCODE_H
#define BASE64_ENCODE_H

#include <algorithm>
#include <iostream>

namespace base64
{
    extern "C"
    {
        #include "cencode.h"
    }

    class encoder
    {
    public:
        encoder(std::size_t buffersize_in)
            : _buffersize(buffersize_in), _code(0), _plaintext(0)
        { }

        ~encoder()
        {
            if (_code) delete[] _code;
            if (_plaintext) delete[] _plaintext;
        }

        encoder(const encoder& ) = delete;
        encoder& operator= (const encoder& ) = delete;

        int encode(char value_in)
        {
            return base64_encode_value(value_in);
        }

        int encode(const char* code_in, const int length_in, char* plaintext_out)
        {
            return base64_encode_block(code_in, length_in, plaintext_out, &_state);
        }

        int encode_end(char* plaintext_out)
        {
            return base64_encode_blockend(plaintext_out, &_state);
        }

        void encode(std::istream& istream_in, std::ostream& ostream_in)
        {
            base64_init_encodestate(&_state);
            //
            if (!_plaintext)
                _plaintext = new char[_buffersize];
            if (!_code)
                _code = new char[2 * _buffersize];
            int plainlength;
            int codelength;

            do
            {
                istream_in.read(_plaintext, _buffersize);
                plainlength = istream_in.gcount();
                //
                codelength = encode(_plaintext, plainlength, _code);
                ostream_in.write(_code, codelength);
            }
            while (istream_in.good() && plainlength > 0);

            codelength = encode_end(_code);
            ostream_in.write(_code, codelength);
            //
            base64_init_encodestate(&_state);
        }

        void encode(const char* in, std::size_t len, std::ostream& ostream_in)
        {
            base64_init_encodestate(&_state);
            //
            if (!_code)
                _code = new char[2 * _buffersize];
            int plainlength;
            int codelength;

            do
            {
                plainlength = std::min(len, _buffersize);
                //
                codelength = encode(in, plainlength, _code);
                ostream_in.write(_code, codelength);
                in += plainlength;
                len -= plainlength;
            }
            while (plainlength > 0);

            codelength = encode_end(_code);
            ostream_in.write(_code, codelength);
            //
            base64_init_encodestate(&_state);
        }

    private:
        base64_encodestate _state;
        std::size_t _buffersize;
        char* _code;
        char* _plaintext;
    };

} // namespace base64

#endif // BASE64_ENCODE_H

