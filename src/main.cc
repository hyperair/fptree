#include <cstdlib>
#include <string>
#include <iostream>

#include <itemset.hh>
#include <transactions.hh>
#include <types.hh>
#include <parser.hh>

int main (int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <min_support>"
                  << std::endl;

        return 1;
    }

    std::string filename = argv[1];
    double min_support = std::atof (argv[2]);

    fpt::transaction_database db = fpt::parse_file (filename);
    fpt::itemset items = db.extract_itemset ();

    items.prune (db.size () * min_support);

    fpt::fptree tree (items.get_ordered (), db);
    fpt::fptree::stats stats = tree.get_stats ();

    std::cout << "File: "               << filename             << std::endl
              << "Number of nodes: "    << stats.size           << std::endl
              << "Number of leaves:"    << stats.n_leaves       << std::endl
              << "Height: "             << stats.height         << std::endl
              << "Minimum fanout: "     << stats.min_fanout     << std::endl
              << "Average fanout: "     << stats.average_fanout << std::endl
              << "Maximum fanout: "     << stats.max_fanout     << std::endl;

    return 0;
}
