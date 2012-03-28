#include <unordered_set>
#include <limits>
#include <cassert>
#include <fptree.hh>
#include <memory>

using fpt::fptree;

class fptree::node : public std::enable_shared_from_this<node>
{
public:
    node (item_type item, nodeptr parent = nodeptr ()) :
        item (item),
        counter (0),
        parent (parent) {}

    nodeptr operator[] (item_type);
    void increment_count ()         {++counter;}

    item_type                               item;
    std::size_t                             counter;

    std::weak_ptr<node>                     parent;
    std::unordered_map<item_type, nodeptr>  children;

    nodeptr                                 next_sibling;
};

fptree::nodeptr fptree::node::operator[] (item_type item)
{
    nodeptr &retval = children[item];

    if (!retval)
        retval = nodeptr (new node (item, shared_from_this ()));

    return retval;
}


fptree::fptree (const ordered_itemset &item_order,
                transaction_database &db) :
    item_order (item_order)
{
    for (const transaction &trans : db) {
        nodeptr current;

        // Find first item to look for root
        auto i = item_order.begin ();
        for (; i != item_order.end (); ++i)
            if (trans.find (i->item) != trans.end ())
                break;

        assert (i != item_order.end ());

        {
            // construct root if non-existent
            nodeptr &root = roots[i->item];

            if (!root)
                root = nodeptr (new node (i->item));

            current = root;
        }

        current->increment_count ();

        // Loop through the rest of the elements
        for (; i != item_order.end (); ++i) {
            if (trans.find (i->item) == trans.end ())
                continue;

            current = (*current)[i->item];
            current->increment_count ();
        }

    }
}

namespace {
    void traverse (const fptree::nodeptr &current_node, std::size_t height,
                   fptree::stats &stats, std::size_t &total_fanout)
    {
        ++stats.size;

        if (current_node->children.empty ()) { // leaf
            ++stats.n_leaves;
            stats.height = std::max (stats.height, height);
        } else {
            std::size_t fanout = current_node->children.size ();

            stats.min_fanout = std::min (stats.min_fanout, fanout);
            stats.max_fanout = std::max (stats.max_fanout, fanout);
            total_fanout += fanout;

            for (const auto &i : current_node->children)
                traverse (i.second, height + 1, stats, total_fanout);
        }
    }
}

fptree::stats fptree::get_stats () const
{
    fptree::stats stats;
    std::size_t total_fanout = 0;

    for (const auto &i : roots)
        traverse (i.second, 1, stats, total_fanout);

    stats.average_fanout = double (total_fanout) / stats.size;

    return stats;
}


fptree::stats::stats () :
    size (0),
    n_leaves (0),
    height (0),
    min_fanout (std::numeric_limits<decltype (min_fanout)>::max ()),
    average_fanout (0),
    max_fanout (0)
{}
