#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using object_holder = std::map<std::string, std::map<int, std::string>>;
using place_holder = std::map<std::string,
        std::map<int, std::vector<std::string>>>;

#define elif else if

auto find_location(const std::string& uuid, int timestamp,
                   object_holder& objects_to_places) {
    auto& locations = objects_to_places[uuid];
    auto desired_iterator = locations.upper_bound(timestamp);
    if (desired_iterator == locations.begin()) {
        return std::string("no data");
    } else {
        return std::prev(desired_iterator)->second;
    }
}

int main() {
    object_holder objects_to_places;
    place_holder places_to_objects;

    int N, timestamp;
    std::cin >> N;
    std::string uuid, location;
    for(auto i = 0; i < N; i++) {
        std::cin >> uuid >> location >> timestamp;
        objects_to_places[uuid][timestamp] = location;
        places_to_objects[location][timestamp].push_back(uuid);
    }

    int M;
    std::cin >> M;
    std::string type;
    for (auto i = 0; i < M; i++) {
        std::cin >> type;
        if (type == "object") {
            std::cin >> uuid >> timestamp;
            std::cout << find_location(uuid, timestamp, objects_to_places) << std::endl;
        } elif (type == "location") {
            std::cin >> location >> timestamp;
            auto& places = places_to_objects[location];
            std::set<std::string> all_objects;
            for(auto iter = places.begin();
                iter != places.upper_bound(timestamp);
                iter = std::next(iter)) {
                auto& vector_with_objets = iter->second;
                std::copy(vector_with_objets.begin(), vector_with_objets.end(),
                          std::inserter(all_objects, all_objects.begin()));
            }
            for(const auto& object: all_objects) {
                if (find_location(object, timestamp, objects_to_places) == location) {
                    std::cout << object << ' ';
                }
            }
            std::cout << std::endl;
        }
    }
}
