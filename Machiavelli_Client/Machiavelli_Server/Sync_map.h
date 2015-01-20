//
//  Sync_map.h 
//  adapted from an example from Bjarne Stroustrup by Bas and Gijs!
//

#ifndef __Sync_map__
#define __Sync_map__

#include <mutex>
#include <condition_variable>
#include <map>
#include <future>
#include <thread>

template<typename K, typename V>
class Sync_map {
public:
	void put(const K& key, const V& value);
	V get(K& key);

private:
	std::mutex mtx;
	std::condition_variable cond;
	std::map<K, V> map;
};

template<typename K, typename V>
void Sync_map<K, V>::put(const K& key, const V& value)
{
	std::lock_guard<std::mutex> lck{ mtx };
	map.insert[key] = value;
	cond.notify_one();
}

template<typename K, typename V>
V Sync_map<K, V>::get(K& key)
{
	std::unique_lock<std::mutex> lck{ mtx };
	cond.wait(lck, [this]{ return !map.empty(); });
	if (m.find("f") == m.end()) {
		printf("Sync_map key didn't exist!");
		return nullptr;
	}
	else{
		return map[key];
	}
}

#endif /* defined(__Sync_map__) */
