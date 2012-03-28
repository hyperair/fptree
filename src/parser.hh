#ifndef PARSER_HH
#define PARSER_HH

#include <exception>
#include <string>

#include <transactions.hh>

namespace fpt
{
    transaction_database parse_file (const std::string &filename);

    class file_open_exception : public std::exception
    {
    public:
        file_open_exception (const std::string &filename) :
            msg (std::string ("Could not open file: ") + filename) {}

        virtual ~file_open_exception () throw () {}

        virtual const char *what () const throw () {return msg.c_str ();}

    private:
        const std::string msg;
    };
}

#endif  // PARSER_HH
