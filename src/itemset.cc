#include <itemset.hh>

using fpt::itemset;

void itemset::prune (std::size_t min_count)
{
    for (auto i = begin (); i != end;)
        if (*i < min_count)
            i = erase (i);

        else
            ++i;
}
