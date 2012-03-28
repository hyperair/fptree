#ifndef FPTREE_HH
#define FPTREE_HH

#include <iostream>
#include <memory>

#include <itemset.hh>
#include <transactions.hh>

namespace fpt
{
    class fptree
    {
    public:
        fptree (const ordered_itemset &items,
                transaction_database &db);
        fptree (const fptree &) = delete;

        struct stats
        {
            stats ();

            std::size_t size;
            std::size_t n_leaves;
            std::size_t height;

            std::size_t min_fanout;
            double      average_fanout;
            std::size_t max_fanout;
        };

        stats get_stats () const;

        class node;
        typedef std::shared_ptr<node> nodeptr;

    private:
        const ordered_itemset                  &item_order;
        std::unordered_map<item_type, nodeptr>  roots;

        struct header
        {
            nodeptr head;
            nodeptr tail;
        };
        std::unordered_map<item_type, header>   headers;
    };
}

#endif
