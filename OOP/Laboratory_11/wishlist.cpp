#include "wishlist.h"
#include "service.h"
#include "errors.h"
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
using std::vector;
using std::string;
using std::iota;
using std::multimap;

Wishlist::Wishlist() {
    favorites = new Inventory<Travel_Package>;
}

void Wishlist::add_to_wishlist(Travel_Package* travel_package) {

    auto it = std::find_if(favorites->begin_ascendent(), favorites->end_ascendent(), [travel_package](const Travel_Package* pkg) {return pkg->get_id() == travel_package->get_id(); });
    if (it != favorites->end_ascendent()) {
        throw ExceptionWishlist("Travel package already exists in your wishlist");
    }
    favorites->add(travel_package);

    // Add the travel package to the wishlist map

    wishlist_map.insert({ travel_package->get_type(), travel_package });


}

void Wishlist::delete_from_wishlist(int id) {

    auto it = std::find_if(favorites->begin_ascendent(), favorites->end_ascendent(), [id](const Travel_Package* pkg) {return pkg->get_id() == id; });

    if (it == favorites->end_ascendent())
    {
        throw ExceptionWishlist("Travel package not found in your wishlist");
    }

    for (auto i = wishlist_map.begin(); i != wishlist_map.end(); ++i) {
        if (i->second->get_id() == id) {
            wishlist_map.erase(i);
            break;
        }
    }
    favorites->remove(it.get_index());


}

const Inventory<Travel_Package>* Wishlist::get_wishlist() const {
    return favorites;
}

void Wishlist::generate_wishlist(int number, const Inventory<Travel_Package>* travel_packages) {

    wishlist_map.clear();
    vector<int>* indexi = new vector<int>(travel_packages->size());
    iota(indexi->begin(), indexi->end(), 0);

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(indexi->begin(), indexi->end(), gen);

    favorites->clear();
    for (auto index : *indexi) {
        Travel_Package* travel_package = new Travel_Package(*(*travel_packages)[index]);
        favorites->add(travel_package);
        wishlist_map.insert({ travel_package->get_type(), travel_package });
        if (--number == 0) {
            break;
        }
    }

    delete indexi;
}

void Wishlist::export_wishlist(const string& file_name) {

    std::ofstream file(file_name + ".html");
    if (!file.is_open()) { throw ExceptionWishlist("Could not open file"); }

    file << "<html><head><title>---->WISHLIST<----</title></head><body>";
    file << "<h1>Travel Packages</h1>";
    file << "<table border='1'><tr><th>ID</th><th>Name</th><th>Destination</th><th>Type</th><th>Price</th></tr>";

    std::for_each(favorites->begin_ascendent(), favorites->end_ascendent(), [&file](Travel_Package* travel_package) {file << travel_package->to_html(); });

    file << "</table></body></html>";
    file.close();
}

const multimap<string, Travel_Package*>* Wishlist::get_wishlist_map() const {

    return &wishlist_map;

}

Wishlist::~Wishlist() {
    delete favorites;
}
