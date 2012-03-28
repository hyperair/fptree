#include <cstdlib>
#include <string>
#include <iostream>

#include <itemset.hh>
#include <transactions.hh>
#include <types.hh>

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

    fpt::ordered_itemset ordered_items (items);

    fpt::fptree tree (ordered_items, db);

    std::cout << "File: " << filename << std::endl
              << "Number of nodes: " << tree.size () << std::endl
              << "Number of leaves:" << tree.n_leaves () << std::endl
              << "Height: " << tree.height () << std::endl;

    fpt::fptree::fanout_stats stats = tree.fanout_stats ();

    std::cout << "Minimum fanout: " << stats.min << std::endl
              << "Average fanout: " << stats.average << std::endl
              << "Maximum fanout: " << stats.max << std::endl

    return 0;
}
