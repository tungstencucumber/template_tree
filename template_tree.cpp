#include <template_tree.h>


Vessel::Vessel(T i)
{
	this->id = i;
	this->level = 0;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

T Vessel::getID()
{
	return this->id;
}

Vessel* Vessel::attach_to_fleet(Vessel* ship)
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

bool Vessel::find_vessel(T i)
{
	if (this->id == i)
		return true;
	else if (this->id > i && this->left != NULL)
		return this->left->find_vessel(i);
	else if (this->id < i && this->right != NULL)
		return this->right->find_vessel(i);
	return false;
}

Vessel* Vessel::detach_from_fleet(T target_id) {
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

void Vessel::report()
{
	if (this->left != NULL)
		this->left->report();
	cout << this->getID() << endl;
	if(this->right != NULL)
		this->right->report();
}

void Vessel::dismiss_fleet()
{
	while (this->left != NULL)
		this->left->detach_from_fleet(this->left->id);
	while (this->right != NULL)
		this->right->detach_from_fleet(this->right->id);
}


void Fleet::attach_to_fleet(Vessel* ship)
{
	if (root == NULL) {
		root = ship;
		return;
	}
	this->root = root->attach_to_fleet(ship);
}

bool Fleet::find_vessel(T i)
{
	return this->root->find_vessel(i);
}

void Fleet::detach_from_fleet(T target_id)
{
	if (this->find_vessel(target_id) == true)
		this->root = root->detach_from_fleet(target_id);
}

void Fleet::dismiss_fleet() {
	root->dismiss_fleet();
	delete root;
}

Fleet::Fleet()
{
	this->root = NULL;
}

~Fleet::Fleet()
{
	dismiss_fleet();
}

void Fleet::insert(T value)
{
	Vessel* t = new Vessel(value);
	this->attach_to_fleet(t);
}

bool exists(T value)
{
  return this->find_vessel(value);
}

void Fleet::remove(T value)
{
  this->root->detach_from_fleet(value);
}

void Fleet::print()
{
	this->root->report();
}

};
