#include <fstream>
#include <sstream>
#include <parser.hh>

fpt::transaction_database fpt::parse_file (const std::string &filename)
{
    std::ifstream file (filename);

    if (!file)
        throw file_open_exception (filename);

    fpt::transaction_database db;

    std::string line;

    while (std::getline (file, line)) {
        std::stringstream ss (line);
        transaction transaction;

        item_type item;

        while (ss >> item)
            transaction.insert (item);

        db.insert (std::move (transaction));
    }

    return db;
}
