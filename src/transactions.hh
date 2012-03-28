#ifndef TRANSACTIONS_HH
#define TRANSACTIONS_HH

#include <unordered_set>
#include <vector>
#include <unordered_set>
#include <types.hh>
#include <itemset.hh>

namespace fpt
{
    typedef std::unordered_set<item_type> transaction;

    // Database of transactions, parsed from file
    class transaction_database : private std::vector<transaction>
    {
    public:
        void insert (transaction transaction);
        itemset extract_itemset () const;

        // Expose underlying functions for iterating
        using std::vector<transaction>::begin;
        using std::vector<transaction>::end;
        using std::vector<transaction>::iterator;
        using std::vector<transaction>::const_iterator;

        using std::vector<transaction>::size;
    };
}

#endif  // TRANSACTIONS_HH
