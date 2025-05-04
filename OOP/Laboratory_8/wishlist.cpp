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

Wishlist::Wishlist() {
    favorites = new Inventory<Travel_Package>;
}

/*
* The function adds a travel package to the wishlist, ensuring no duplicates are added.
* >> Input:
*    - travel_package (Travel_Package*): The travel package to be added to the wishlist.
* >> Output:
*    - Adds the travel package to the wishlist if it doesn't already exist.
*    - Throws an exception if the travel package is already in the wishlist.
* >> Behavior:
*    1. The function checks if the provided `travel_package` is already in the wishlist using the `std::find_if` method.
*    2. If the travel package is found in the wishlist, an `ExceptionWishlist` is thrown with the message "Travel package already exists in your wishlist".
*    3. If the travel package is not found, it is added to the wishlist using the `add` method of the `favorites` container.
*/
void Wishlist::add_to_wishlist(Travel_Package* travel_package) {

    auto it = std::find_if(favorites->begin_ascendent(), favorites->end_ascendent(), [travel_package](const Travel_Package* pkg) {return pkg->get_id() == travel_package->get_id(); });
    if (it != favorites->end_ascendent()) {
        throw ExceptionWishlist("Travel package already exists in your wishlist");
    }
    favorites->add(travel_package);

	// Add the travel package to the wishlist map

	wishlist_map.insert({ travel_package->get_type(), travel_package });
        
    
}

/*
* The function removes a travel package from the wishlist based on the provided ID.
* >> Input:
*    - id (int): The ID of the travel package to be removed from the wishlist.
* >> Output:
*    - Removes the travel package from the wishlist if found.
*    - Throws an exception if the travel package is not found in the wishlist.
* >> Behavior:
*    1. The function searches for the travel package with the given `id` using the `std::find_if` method.
*    2. If the travel package is not found in the wishlist (i.e., the iterator reaches `end_ascendent()`), an `ExceptionWishlist` is thrown with the message "Travel package not found in your wishlist".
*    3. If the travel package is found, it is removed from the wishlist using the `remove` method, passing the index of the package obtained from `it.get_index()`.
*/
void Wishlist::delete_from_wishlist(int id){

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

/*
* The function retrieves the current list of favorite travel packages (the wishlist).
* >> Input:
*    - None
* >> Output:
*    - Returns a constant pointer to the `Inventory<Travel_Package>` that contains the travel packages in the wishlist.
* >> Behavior:
*    1. The function simply returns the `favorites` inventory, which is a list of travel packages marked as favorites (the wishlist).
*    2. The returned inventory is constant, meaning the caller cannot modify the contents of the wishlist directly.
*/
const Inventory<Travel_Package>* Wishlist::get_wishlist() const {
    return favorites;
}

/*
* The function generates a wishlist of a specified number of random travel packages from a given inventory.
* >> Input:
*    - number (int): The number of random travel packages to add to the wishlist.
*    - travel_packages (const Inventory<Travel_Package>*): A constant pointer to the inventory containing all travel packages.
* >> Output:
*    - The function populates the `favorites` inventory with the specified number of random travel packages.
* >> Behavior:
*    1. The function first creates a list of indices corresponding to the travel packages in the provided `travel_packages` inventory.
*    2. It then shuffles the indices randomly using the `std::shuffle` algorithm and a random number generator.
*    3. The `favorites` list is cleared to ensure that only the newly generated wishlist will be retained.
*    4. The function then iterates over the shuffled indices and adds the corresponding `Travel_Package` objects to the `favorites` wishlist, stopping when the desired number of packages (`number`) is reached.
*    5. The memory allocated for the index list (`indexi`) is freed after use.
*/
void Wishlist::generate_wishlist(int number, const Inventory<Travel_Package>* travel_packages){

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

/*
* The function exports the wishlist of travel packages to an HTML file.
* >> Input:
*    - file_name (const string&): The name of the file (without extension) where the wishlist will be saved.
* >> Output:
*    - The function generates an HTML file containing a table representation of the wishlist travel packages.
* >> Behavior:
*    1. The function attempts to open a file with the given `file_name` and a `.html` extension. If the file cannot be opened, it throws an `ExceptionWishlist` with the message "Could not open file".
*    2. The HTML structure is written into the file, including a title and an initial table structure with column headers for `ID`, `Name`, `Destination`, `Type`, and `Price`.
*    3. For each travel package in the `favorites` list, the function calls the `to_html()` method of `Travel_Package` to generate the HTML representation of the package and writes it to the file.
*    4. Once all travel packages are written, the table is closed, and the HTML document is finalized.
*    5. The file is closed after the content is written.
*/
void Wishlist::export_wishlist(const string& file_name) {

    std::ofstream file(file_name + ".html");
    if (!file.is_open()) {throw ExceptionWishlist("Could not open file");}

    file << "<html><head><title>---->WISHLIST<----</title></head><body>";
    file << "<h1>Travel Packages</h1>";
    file << "<table border='1'><tr><th>ID</th><th>Name</th><th>Destination</th><th>Type</th><th>Price</th></tr>";

    std::for_each(favorites->begin_ascendent(), favorites->end_ascendent(), [&file](Travel_Package* travel_package) {file << travel_package->to_html(); });

    file << "</table></body></html>";
    file.close();
}

/*
* The function retrieves the wishlist map, which contains the travel packages categorized by their type
*/
void Wishlist::get_wishlist_map() const {
	
	for (auto it = wishlist_map.begin(); it != wishlist_map.end(); ++it) {
        if (it == wishlist_map.begin() || it->first != std::prev(it)->first) {
            std::cout << "Type: " << it->first << " | Number: " << wishlist_map.count(it->first) << std::endl;
        }
	}
}

Wishlist::~Wishlist() {
    delete favorites;
}
