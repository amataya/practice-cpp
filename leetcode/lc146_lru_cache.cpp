// Design and implement a data structure for Least Recently Used (LRU) cache.
// It should support the following operations: get and put.
//
// get(key) - Get the value (will always be positive) of the key if the key
// exists in the cache, otherwise return -1.
// put(key, value) - Set or insert the value if the key is not already present.
// When the cache reached its capacity, it should invalidate the least recently
// used item before inserting a new item.
//
// Follow up:
// Could you do both operations in O(1) time complexity?
//
// Example:
//
// LRUCache cache = new LRUCache( 2 /* capacity */ );
//
// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // returns 1
// cache.put(3, 3);    // evicts key 2
// cache.get(2);       // returns -1 (not found)
// cache.put(4, 4);    // evicts key 1
// cache.get(1);       // returns -1 (not found)
// cache.get(3);       // returns 3
// cache.get(4);       // returns 4
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <list>
#include <utility>
#include <unordered_map>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// A linked list + hashtable of pointers to the linked list nodes is the usual
// way to implement LRU caches. This gives O(1) operations
// (assuming a decent hash). Advantage of this (being O(1)): you can do a
// multithreaded version by just locking the whole structure.
// This is how it works:
// - On an access of a value, you move the corresponding node in the linked
// list to the head.
// - When you need to remove a value from the cache, you remove from the tail
// end.
// - When you add a value to cache, you just place it at the head of the
// linked list.
class LRUCache
{
    typedef int key_t; // Useful when we want to convert it to template
    typedef int val_t;
    typedef list<pair<int, int>> cache_t;
    typedef unordered_map<key_t, cache_t::iterator> index_t;

    index_t _index;
    cache_t _cache;
    size_t _capacity;
public:
    LRUCache(const int& capacity) : _capacity(capacity)
    {
        _index.reserve(_capacity);
    }
    ~LRUCache() = default;
    LRUCache(const LRUCache&) = delete;
    LRUCache operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&) = default;
    LRUCache& operator=(LRUCache&&) = default;

    int get(const key_t key)
    {
        const auto& it = _index.find(key);
        if (it == _index.end())
            return -1;

        // Move accessed element to front. splice has added benefit that
        // iterators in the _index will not be invalidated.
        if (it->second != _cache.begin())
            _cache.splice(_cache.begin(), _cache, it->second);

        return it->second->second;
    }

    void put(const key_t key, const val_t value)
    {
        const auto& it = _index.find(key);
        if (it != _index.end()) // Update value. Move accessed key to front.
        {
            it->second->second = value;
            _cache.splice(_cache.begin(), _cache, it->second);
        }
        else
        {
            if (_index.size() >= _capacity)
            {
                const auto& last = --_cache.end();
                _index.erase(last->first);
                _cache.pop_back();
            }
            _cache.emplace_front(make_pair(key, value));
            _index.emplace(key, _cache.begin());
        }
    }
};

// Standard trick to make code run fast
static const int _= []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("LRU Cache 1", "[leetcode]")
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    REQUIRE(cache.get(1) == 1);
    cache.put(3, 3);
    REQUIRE(cache.get(2) == -1);
    cache.put(4, 4);
    REQUIRE(cache.get(1) == -1);
    REQUIRE(cache.get(3) == 3);
    REQUIRE(cache.get(4) == 4);
}

TEST_CASE("LRU Cache 2", "[leetcode]")
{
    LRUCache cache(2);
    cache.put(2, 1);
    cache.put(2, 2);
    REQUIRE(cache.get(2) == 2);
    cache.put(1, 1);
    cache.put(4, 1);
    REQUIRE(cache.get(2) == -1);
}

TEST_CASE("LRU Cache 3", "[leetcode]")
{
    LRUCache cache(2);
    cache.put(2, 1);
    cache.put(1, 1);
    cache.put(2, 3);
    cache.put(4, 1);
    REQUIRE(cache.get(1) == -1);
    REQUIRE(cache.get(2) == 3);
}
