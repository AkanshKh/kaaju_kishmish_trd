// This can be applied to all Data Structures that support (add, remove and query) and only need the operation (updateAll).

class VeniceSet
{
public:
    multiset<ll> ice;
    ll level = 0;
    void add(ll x)
    {
        ice.insert(x + level);
    }
    void remove(ll x)
    {
        ice.erase(ice.find(x + level));
    }
    void decrement_all(ll x) // update all
    {
        level += x;
    }
    ll get_min() // query
    {
        return *ice.begin() - level;
    }
    ll get_size()
    {
        return ice.size();
    }
};
