#ifndef ITEMSET_HH
#define ITEMSET_HH

#include <unordered_map>
#include <ctypes>
#include <types.hh>

namespace fpt
{
    class itemset : private std::unordered_map<item_type, std::size_t>
    {
        typedef std::unordered_map<item_type, std::size_t> container_type;

    public:
        void prune (std::size_t min_count);

        using container_type::iterator;
        using container_type::const_iterator;
        using container_type::begin;
        using container_type::end;
        using container_type::size;
    };
}

#endif  // ITEMSET_HH
