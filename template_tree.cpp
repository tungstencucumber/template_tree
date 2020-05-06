#include "template_tree.h"

template<typename T>
Vessel<T>::Vessel() {}

template<typename T>
Vessel<T>::Vessel(T i)
{
	this->id = i;
	this->level = 0;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

template<typename T>
Vessel<T>::~Vessel() {}

template<typename T>
T Vessel<T>::getID()
{
	return this->id;
}

template<typename T>
Vessel<T>* Vessel<T>::attach_to_fleet(Vessel* ship)
{
	if(this->id > ship->id)
	{
		if (this->left == NULL) {
			this->left = ship;
			ship->parent = this;
			return this;
		}
		else this->left->attach_to_fleet(ship);
	}
	else
	{
		if (this->right == NULL) {
			this->right = ship;
			ship->parent = this;
			return this;
		}
		else this->right->attach_to_fleet(ship);
	}
	return this;
}

template<typename T>
bool Vessel<T>::find_vessel(T i)
{
	if (this->id == i)
		return true;
	else if (this->id > i && this->left != NULL)
		return this->left->find_vessel(i);
	else if (this->id < i && this->right != NULL)
		return this->right->find_vessel(i);
	return false;
}

template<typename T>
Vessel<T>* Vessel<T>::detach_from_fleet(T target_id) {
	if (target_id < this->id)
		this->left->detach_from_fleet(target_id);
	else if (target_id > this->id)
		this->right->detach_from_fleet(target_id);
	else {
		if (this->left == NULL) {
			if (this->parent != NULL) {
				this->parent->right = this->right;
				if (this->right != NULL)
					this->right->parent = this->parent;
			}
			delete this;
		} else {
			Vessel* replaced = this->left;
			while (replaced->right != NULL)
				replaced = replaced->right;
			this->id = replaced->id;
			replaced->parent->right = NULL;
			delete replaced;
		}
	}
	return this;
}

template<typename T>
void Vessel<T>::report()
{
	if (this->left != NULL)
		this->left->report();
	std::cout << this->getID() << std::endl;
	if(this->right != NULL)
		this->right->report();
}

template<typename T>
void Vessel<T>::dismiss_fleet()
{
	while (this->left != NULL)
		this->left->detach_from_fleet(this->left->id);
	while (this->right != NULL)
		this->right->detach_from_fleet(this->right->id);
}




template<typename T>
void Fleet<T>::attach_to_fleet(Vessel<T>* ship)
{
	if (root == NULL) {
		root = ship;
		return;
	}
	this->root = root->attach_to_fleet(ship);
}

template<typename T>
bool Fleet<T>::find_vessel(T i)
{
	return this->root->find_vessel(i);
}

template<typename T>
void Fleet<T>::detach_from_fleet(T target_id)
{
	if (this->find_vessel(target_id) == true)
		this->root = root->detach_from_fleet(target_id);
}

template<typename T>
void Fleet<T>::dismiss_fleet()
{
	root->dismiss_fleet();
	delete root;
}

template<typename T>
Fleet<T>::Fleet()
{
	this->root = NULL;
}

template<typename T>
Fleet<T>::~Fleet()
{
	dismiss_fleet();
}

template<typename T>
void Fleet<T>::insert(const T& value)
{
	Vessel<T>* t = new Vessel<T>(value);
	this->attach_to_fleet(t);
}

template<typename T>
bool Fleet<T>::exists(const T& value) const
{
  return this->find_vessel(value);
}

template<typename T>
void Fleet<T>::remove(const T& value)
{
  this->root->detach_from_fleet(value);
}

template<typename T>
void Fleet<T>::print()
{
	this->root->report();
}
