#ifndef ITEMSET_HH
#define ITEMSET_HH

#include <unordered_map>
#include <set>
#include <cstddef>
#include <cassert>
#include <types.hh>

namespace fpt
{
    struct item_with_count
    {
        item_type item;
        std::size_t count;
    };

    // Operators for use with std::set
    bool operator< (const item_with_count &, const item_with_count &);
    bool operator== (const item_with_count &, const item_with_count &);

    typedef std::multiset<item_with_count> ordered_itemset;


    // An unordered set of items. Used for counting the frequency of each item.
    class itemset : private std::unordered_map<item_type, std::size_t>
    {
        typedef std::unordered_map<item_type, std::size_t> container_type;

    public:
        void prune (std::size_t min_count);
        void insert (fpt::item_type i) {++(*this)[i];}

        ordered_itemset get_ordered () const;

        using container_type::iterator;
        using container_type::const_iterator;
        using container_type::begin;
        using container_type::end;
        using container_type::size;
    };
}



// Inline definitions
inline bool fpt::operator< (const item_with_count &a, const item_with_count &b)
{
    return a.count < b.count;
}

inline bool fpt::operator== (const item_with_count &a, const item_with_count &b)
{
    assert (a.count == b.count);
    return a.item == b.item;
}


#endif  // ITEMSET_HH
