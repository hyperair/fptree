#include <itemset.hh>

using fpt::itemset;

void itemset::prune (std::size_t min_count)
{
    for (auto i = begin (); i != end ();)
        if (i->second < min_count)
            i = erase (i);

        else
            ++i;
}

fpt::ordered_itemset itemset::get_ordered () const
{
    ordered_itemset ordered_items;

    for (const auto &i : *this)
        ordered_items.insert ({i.first, i.second});

    return ordered_items;
}
