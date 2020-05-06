#ifndef TEMPLATE_TREE_H
#define TEMPLATE_TREE_H
#include <container.h>

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
	Vessel(T i);
	~Vessel();

	T getID();
	Vessel* attach_to_fleet(Vessel* ship);
  bool find_vessel(T i);
	Vessel* detach_from_fleet(T target_id);
	void report();
	void dismiss_fleet()
};

class Fleet: public Container
{
private:
	Vessel* root;
protected:

	void attach_to_fleet(Vessel* ship);
	bool find_vessel(T i);
	void detach_from_fleet(T target_id);
	void dismiss_fleet();

public:

	Fleet();
	~Fleet();
	void insert(T value);
  bool exists(T value);
  void remove(T value);
  void print();

};

#endif
