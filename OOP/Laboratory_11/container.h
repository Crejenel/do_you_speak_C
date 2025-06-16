#ifndef CONTAINER_H
#define CONTAINER_H
#define DEFAULT_SIZE 5
#include "errors.h"
#include <iostream>
#include <iterator> 
#include <cstddef>

template <typename unknow_type>
class InteratorInventory;

// container
template <typename unknow_type>
class Inventory {

private:

	unknow_type** items;
	int number_of_items;
	int dimension;

public:

	// default constructor
	Inventory() {

		items = new unknow_type * [DEFAULT_SIZE];
		dimension = DEFAULT_SIZE;
		number_of_items = 0;
	}

	// constructor with size
	Inventory(int size) {

		if (size < 0) {
			size = DEFAULT_SIZE;
		}

		items = new unknow_type * [size];
		dimension = size;
		number_of_items = 0;
	}

	// copy constructor
	Inventory(const Inventory& other) {

		if (other.dimension < other.number_of_items) { throw ExceptionContainer("Buffer overrun detected while copying items"); }

		number_of_items = other.number_of_items;
		dimension = other.dimension;

		items = new unknow_type * [dimension];
		for (int i = 0; i < number_of_items; i++) {
			items[i] = new unknow_type(*other.items[i]);
		}
	}

	// assignment operator
	Inventory& operator=(const Inventory& other) {

		if (this != &other) {

			if (other.dimension < other.number_of_items) { throw ExceptionContainer("Buffer overrun detected while copying items"); }

			for (int i = 0; i < number_of_items; i++) {
				delete items[i];
			}
			delete[] items;

			number_of_items = other.number_of_items;
			dimension = other.dimension;

			items = new unknow_type * [dimension];

			for (int i = 0; i < number_of_items; i++) {

				items[i] = new unknow_type(*other.items[i]);
			}
		}
		return *this;
	}

	// subscript operator
	unknow_type* operator[](int index) const {

		if (index < 0 || index >= number_of_items) {
			throw ExceptionContainer("Index out of range");
		}
		return items[index];
	}

	// move constructor
	Inventory(Inventory&& other) noexcept {

		std::cout << number_of_items << std::endl;
		number_of_items = other.number_of_items;
		dimension = other.dimension;
		items = other.items;

		other.items = nullptr;
		other.number_of_items = 0;
		other.dimension = 0;
	}

	// move assignment operator
	Inventory& operator=(Inventory&& other) noexcept {

		if (this != &other) {

			for (int i = 0; i < number_of_items; i++) { delete items[i]; }
			delete[] items;

			number_of_items = other.number_of_items;
			dimension = other.dimension;
			items = other.items;

			other.items = nullptr;
			other.number_of_items = 0;
			other.dimension = 0;
		}
		return *this;
	}

	// add item
	void add(unknow_type* item) {

		if (item == nullptr) {

			throw ExceptionContainer("connot add a null pointer in container");
		}

		if (number_of_items == dimension) {

			resize();
		}

		items[number_of_items++] = item;
	}

	// get item
	unknow_type* get(int index) const {

		if (index < 0 || index >= number_of_items) {
			throw ExceptionContainer("Index out of range");
		}
		return items[index];
	}

	// insert item
	void insert(int index, unknow_type* item) {

		if (index < 0 || index > number_of_items) {

			delete item;
			throw ExceptionContainer("Index out of range");
		}

		if (item == nullptr) {
			throw ExceptionContainer("connot add a null pointer in container");
		}

		if (number_of_items == dimension) {

			resize();
		}

		for (int i = number_of_items; i > index; i--) {
			items[i] = items[i - 1];
		}

		items[index] = item;
		number_of_items++;
	}

	// set item
	void set(int index, unknow_type* item) {

		if (index < 0 || index >= number_of_items) { throw ExceptionContainer("Index out of range"); }

		if (item == nullptr) {
			throw ExceptionContainer("connot add a null pointer in container");
		}

		delete items[index];
		items[index] = item;
	}

	// remove item
	void remove(int index) {

		if (index < 0 || index >= number_of_items) {

			throw ExceptionContainer("Index out of range");
		}

		delete items[index];

		for (int i = index; i < number_of_items - 1; i++) {
			items[i] = items[i + 1];
		}

		number_of_items--;
	}

	// get size
	int size() const {
		return number_of_items;
	}

	// clear container
	void clear() {

		for (int i = 0; i < number_of_items; i++) { delete items[i]; }
		number_of_items = 0;
	}

	// destructor
	~Inventory() {
		for (int i = 0; i < number_of_items; i++) {
			delete items[i];
		}
		delete[] items;
	}

	// interator
	friend class InteratorInventory<unknow_type>;

	InteratorInventory<unknow_type> begin_ascendent() const {
		return InteratorInventory<unknow_type>(*this, 0, false);
	}
	InteratorInventory<unknow_type> end_ascendent() const {
		return InteratorInventory<unknow_type>(*this, size(), true);
	}

	InteratorInventory<unknow_type> begin_descendent() const {
		return InteratorInventory<unknow_type>(*this, size() - 1, true);
	}
	InteratorInventory<unknow_type> end_descendent() const {
		return InteratorInventory<unknow_type>(*this, -1, false);
	}

private:

	void resize() {

		unknow_type** temp = new unknow_type * [dimension * 2];

		for (int i = 0; i < number_of_items; i++) {
			temp[i] = items[i];
		}

		delete[] items;
		items = temp;
		dimension *= 2;
	}

};

// iterator
template <typename unknow_type>
class InteratorInventory {

private:

	const Inventory<unknow_type>& inventory;
	int index;
	bool reverse;

public:

	using difference_type = std::ptrdiff_t;


	// constructor 
	InteratorInventory(const Inventory<unknow_type>& inventory, int index, bool reverse) : inventory(inventory), index(index), reverse(reverse) {}

	// operator *
	unknow_type* operator*() const {
		return inventory.get(index);
	}

	// operator ++
	InteratorInventory& operator++() {

		if (reverse) {
			index--;
		}

		else {
			index++;
		}

		return *this;
	}

	// operator !=
	bool operator!=(const InteratorInventory& other) const {
		return index != other.index;
	}

	// operator ==
	bool operator==(const InteratorInventory& other) const {
		return index == other.index;
	}

	// Constructor de copiere
	InteratorInventory(const InteratorInventory& other)
		: inventory(other.inventory), index(other.index), reverse(other.reverse) {
	}

	int get_index() const {
		return index;
	}

	difference_type operator-(const InteratorInventory& other) const {
		return this->index - other.index;
	}


	// Operator de copiere
	InteratorInventory& operator=(const InteratorInventory& other) {
		if (this != &other) {
			index = other.index;
			reverse = other.reverse;
		}
		return *this;
	}

};

#endif