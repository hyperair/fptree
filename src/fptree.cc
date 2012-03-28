#include <unordered_set>
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

private:
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

fptree::stats fptree::get_stats () const
{
    fptree::stats stats;

    // TODO: Implement

    return stats;
}
