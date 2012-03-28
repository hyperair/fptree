#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include <itemset.hh>
#include <transactions.hh>
#include <types.hh>
#include <parser.hh>
#include <fptree.hh>

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

    std::string dump_filename = filename + ".fptree";

    std::cout << "File: "               << filename             << std::endl
              << "Number of nodes: "    << stats.size           << std::endl
              << "Number of leaves:"    << stats.n_leaves       << std::endl
              << "Height: "             << stats.height         << std::endl
              << "Minimum fanout: "     << stats.min_fanout     << std::endl
              << "Average fanout: "     << stats.average_fanout << std::endl
              << "Maximum fanout: "     << stats.max_fanout     << std::endl
              << "FPtree dump file: "   << dump_filename        << std::endl;

    {
        std::ofstream dump (dump_filename);

        if (!dump)
            std::cerr << "Could not open file for dumping fptree" << std::endl;

        dump << tree;
    }

    return 0;
}
