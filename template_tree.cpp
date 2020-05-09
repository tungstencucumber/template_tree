#include "template_tree.h"

template<typename T>
Vessel<T>::Vessel() {}

template<typename T>
Vessel<T>::Vessel(const T& i)
{
	this->id = i;
	this->level = 0;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

template<typename T>
Vessel<T>::~Vessel() {}

template<typename T>
T Vessel<T>::getID() const
{
	return this->id;
}

template<typename T>
Vessel<T>* Vessel<T>::attach_to_fleet(Vessel* ship)
{
	if(this->id > ship->id)
	{
		if (this->left == nullptr) {
			this->left = ship;
			ship->parent = this;
			return this;
		}
		else this->left->attach_to_fleet(ship);
	}
	else
	{
		if (this->right == nullptr) {
			this->right = ship;
			ship->parent = this;
			return this;
		}
		else this->right->attach_to_fleet(ship);
	}
	return this;
}

template<typename T>
bool Vessel<T>::find_vessel(const T& i) const
{
	if (this->id == i)
		return true;
	else if (this->id > i && this->left != nullptr)
		return this->left->find_vessel(i);
	else if (this->id < i && this->right != nullptr)
		return this->right->find_vessel(i);
	return false;
}

template<typename T>
Vessel<T>* Vessel<T>::detach_from_fleet(const T& target_id) {
	if (target_id < this->id)
		this->left->detach_from_fleet(target_id);
	else if (target_id > this->id)
		this->right->detach_from_fleet(target_id);
	else {
		if (this->left == nullptr) {
			if (this->parent != nullptr)
			{
				if(this == this->parent->right)
				{
					this->parent->right = this->right;
					if (this->right != nullptr)
					{
						this->right->parent = this->parent;
					}
				}
				else
				{
					this->parent->left = this->right;
					if (this->right != nullptr)
					{
						this->right->parent = this->parent;
					}
				}
			}
			Vessel<T>* replaced = this->right;
			delete this;
			return replaced;
		} else {
			Vessel<T>* replaced = this->left;
			while (replaced->right != nullptr)
				replaced = replaced->right;
			this->id = replaced->id;
			if(replaced == replaced->parent->right)
				replaced->parent->right = nullptr;
			else replaced->parent->left = nullptr;
			delete replaced;
		}
	}
	return this;
}

template<typename T>
void Vessel<T>::report() const
{
	if (this->left != nullptr)
		this->left->report();
	std::cout << this->getID() << std::endl;
	if(this->right != nullptr)
		this->right->report();
}

template<typename T>
void Vessel<T>::dismiss_fleet()
{
	while (this->left != nullptr)
		this->left->detach_from_fleet(this->left->id);
	while (this->right != nullptr)
		this->right->detach_from_fleet(this->right->id);
}

template<typename T>
Vessel<T>* Vessel<T>::left_rotation()
{
	if(this->right != nullptr)
	{
		Vessel<T>* t = this->right;
		right = t->left;
		if(right != nullptr)
			right->parent = this;
		t->left = this;
		t->parent = this->parent;
		this->parent = t;
		return t;
	}
	return this;
}




template<typename T>
void Fleet<T>::attach_to_fleet(Vessel<T>* ship)
{
	if (root == nullptr) {
		root = ship;
		return;
	}
	this->root = root->attach_to_fleet(ship);
}

template<typename T>
bool Fleet<T>::find_vessel(const T& i) const
{
	return this->root->find_vessel(i);
}

template<typename T>
void Fleet<T>::detach_from_fleet(const T& target_id)
{
	if (this->find_vessel(target_id) == true) {
		this->root = root->detach_from_fleet(target_id);
	}
}

template<typename T>
void Fleet<T>::dismiss_fleet()
{
	root->dismiss_fleet();
	root = nullptr;
	size = 0;
}

template<typename T>
Fleet<T>::Fleet()
{
	this->root = nullptr;
	size = 0;
}

template<typename T>
Fleet<T>::~Fleet()
{
	if(size != 0)
		dismiss_fleet();
}

template<typename T>
void Fleet<T>::insert(const T& value)
{
	Vessel<T>* t = new Vessel<T>(value);
	this->attach_to_fleet(t);
	size++;
}

template<typename T>
bool Fleet<T>::exists(const T& value) const
{
	if(this->size == 0)
	{
		return false;
	}
  return this->find_vessel(value);
}

template<typename T>
void Fleet<T>::remove(const T& value)
{
	if(this->exists(value) == true)
	{
		size--;
		if(value == root->getID())
		{
			if(this->size == 0)
			{
				delete root;
				root = nullptr;
				return;
			}
			else root = root->left_rotation();
		}
	  this->root->detach_from_fleet(value);
	}
}

template<typename T>
void Fleet<T>::print() const
{
	this->root->report();
}

template class Vessel<int>;
template class Vessel<string>;
template class Fleet<int>;
template class Fleet<string>;
