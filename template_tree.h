#ifndef TEMPLATE_TREE_H
#define TEMPLATE_TREE_H
#include "container.h"
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Vessel
{
private:
	T id;
	int level;
	Vessel* parent;
	Vessel* left;
	Vessel* right;
public:
	Vessel();
	Vessel(const T& i);
	~Vessel();

	T getID() const;
	Vessel<T>* attach_to_fleet(Vessel<T>* ship);
  bool find_vessel(const T& i) const;
	Vessel<T>* detach_from_fleet(const T& target_id);
	void report() const;
	void dismiss_fleet();
	Vessel<T>* left_rotation();
};

template<typename T>
class Fleet: public Container<T>
{
private:
	Vessel<T>* root;
	unsigned int size;
protected:

	void attach_to_fleet(Vessel<T>* ship);
	bool find_vessel(const T& i) const;
	void detach_from_fleet(const T& target_id);
	void dismiss_fleet();

public:

	Fleet();
	~Fleet();
	void insert(const T& value);
  bool exists(const T& value) const;
  void remove(const T& value);
  void print() const;

};

#endif
