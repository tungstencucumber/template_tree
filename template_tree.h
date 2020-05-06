#ifndef TEMPLATE_TREE_H
#define TEMPLATE_TREE_H
#include "container.h"
#include <iostream>

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
	Vessel(T i);
	~Vessel();

	T getID();
	Vessel<T>* attach_to_fleet(Vessel<T>* ship);
  bool find_vessel(T i);
	Vessel<T>* detach_from_fleet(T target_id);
	void report();
	void dismiss_fleet();
};

template<typename T>
class Fleet: public Container<T>
{
private:
	Vessel<T>* root;
protected:

	void attach_to_fleet(Vessel<T>* ship);
	bool find_vessel(T i);
	void detach_from_fleet(T target_id);
	void dismiss_fleet();

public:

	Fleet();
	~Fleet();
	void insert(const T& value);
  bool exists(const T& value) const;
  void remove(const T& value);
  void print();

};

#endif
