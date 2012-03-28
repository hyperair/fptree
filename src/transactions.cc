#include <utility>
#include <transactions.hh>

using fpt::transaction_database;

void transaction_database::insert (transaction transaction)
{
    push_back (std::move (transaction));
}

fpt::itemset transaction_database::extract_itemset () const
{
    fpt::itemset items;

    for (const transaction &i : *this)
        for (const item_type &j : i)
            items.insert (j);

    return items;
}
