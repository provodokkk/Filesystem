#include <stdbool.h>

#include "file_system.h"
#include <iostream>


// class Iterator

template<typename T, typename U>
Iterator<T, U>::Iterator(U& children) : children_(children)
{
	it_ = children_.begin();
}

template<typename T, typename U>
void Iterator<T, U>::first()
{
	it_ = children_.begin();
}

template<typename T, typename U>
void Iterator<T, U>::previous()
{
	--it_;
}
template<typename T, typename U>
void Iterator<T, U>::next()
{
	++it_;
}

template<typename T, typename U>
bool Iterator<T, U>::is_done()
{
	return (it_ == children_.end());
}

template<typename T, typename U>
T* Iterator<T, U>::current()
{
	return *it_;
}


// class FileSystem

void FileSystem::set_creation_date()
{
	if (creation_date_) {
		delete creation_date_;
	}
	creation_date_ = new Date();
}

void FileSystem::set_modification_date()
{
	if (modification_date_) {
		delete modification_date_;
	}
	modification_date_ = new Date();
}

void FileSystem::set_name(string name)
{
	name_ = name;
	set_modification_date();
}

void FileSystem::set_parent(FileSystem* parent)
{
	parent_ = parent;
	set_modification_date();
}
void FileSystem::set_size(size_t size)
{
	size_ = size;
	set_modification_date();
}

void FileSystem::set_nesting(int nesting)
{
	nesting_ = nesting;
	set_modification_date();
}


string FileSystem::get_creation_date()
{
	return creation_date_->get_date();
}

string FileSystem::get_modification_date()
{
	return modification_date_->get_date();
}

FileSystem* FileSystem::get_root()
{
	FileSystem* current = this;
	while (current->get_parent()) {
		current = current->get_parent();
	}
	return current;
}

string FileSystem::get_name() const
{
	return name_;
}

string FileSystem::get_date(Date* date) const
{
	return date->get_date();
}

FileSystem* FileSystem::get_parent() const
{
	return parent_;
}

int FileSystem::get_nesting() const
{
	return nesting_;
}

size_t FileSystem::get_size() const
{
	return size_;
}

string FileSystem::get_path()
{
	if (creation_date_->get_year() == 0) {
		return "ERROR: File not found";
	}
	FileSystem* current = this;
	string path;
	while (current) {
		path = "/" + current->get_name() + path;
		current = current->get_parent();
	}
	return path;
}

void FileSystem::get_attributes() const
{
	cout << endl << get_name() << " attributes:" << endl;
	cout << "Name -	" << name_ << endl;
	cout << "Creation date -     " << creation_date_->get_date() << endl;
	if (modification_date_->get_year() != 0) {
		cout << "Modification date - " << modification_date_->get_date() << endl;
	}
	cout << "Size - " << size_ << endl;
	if (parent_) {
		cout << "Parent - " << parent_->get_name() << endl;
	}
	cout << "Nesting - " << nesting_ << endl << endl;
}

string FileSystem::get_path_by_name(string name)
{
	return string();
}

int FileSystem::get_children_amount() const
{
	return 0;
}

int FileSystem::get_all_children_amount() const
{
	return 0;
}


list<FileSystem*>& FileSystem::get_list()
{
	list<FileSystem*> empty_list;
	return empty_list;
}

FileSystem* FileSystem::get_from_folder(FileSystem* folder, string component_name)
{
	return nullptr;
}


void FileSystem::add(FileSystem* component)
{

}

FileSystem* FileSystem::add_folder(FileSystem* folder, string folder_name)
{
	return nullptr;
}

FileSystem* FileSystem::add_file(FileSystem* folder, string folder_name, size_t size)
{
	return nullptr;
}


void FileSystem::copy_parameters(FileSystem* recipient)
{
	recipient->set_parent(parent_);
	recipient->set_creation_date();
	recipient->set_size(size_);
	recipient->calculate_nesting();
}


void FileSystem::modify(FileSystem* component, size_t size)
{
	component->set_size(size);
	FileSystem* current = component;
	while (current) {
		current->set_modification_date();
		current = current->get_parent();
	}
}

void FileSystem::rename(FileSystem* component, string name)
{
	component->set_name(name);
	component->set_modification_date();
}

void FileSystem::move(FileSystem* to_folder, FileSystem* component)
{
	component->get_parent()->get_list().remove(component);
	component->set_parent(to_folder);
	to_folder->add(component);
}

void FileSystem::remove(FileSystem* component)
{
	component->get_parent()->get_list().remove(component);
	component->invalidate_parameters();
}

list<FileSystem*> search_by_size(FileSystem* folder, size_t min_size, size_t max_size)
{
	return list<FileSystem*>();
}

void FileSystem::delete_all_dates()
{
	creation_date_->delete_date();
	modification_date_->delete_date();
}

void FileSystem::invalidate_parameters()
{
	set_parent(nullptr);
	delete_all_dates();
	set_size(0);
	set_nesting(0);
}

list<FileSystem*> FileSystem::search_by_size(FileSystem* folder, size_t min_size, size_t max_size)
{
	return list<FileSystem*>();
}

void FileSystem::calculate_nesting()
{
	FileSystem* current = this;
	while (current->get_parent()) {
		++nesting_;
		current = current->get_parent();
	}
}


// class Folder

Folder::Folder()
{
	set_name("Folder");
	set_creation_date();
	size_ = sizeof(this);
}

Folder::Folder(string name)
{
	set_name(name);
	set_creation_date();
	size_ = sizeof(this);
}

Folder::~Folder()
{
	delete creation_date_;
	if (modification_date_) {
		delete modification_date_;
	}
}

string Folder::get_path_by_name(string name)
{
	FileSystem* root = get_root();
	FileSystem* component = root->search_by_name(name);
	if (component) {
		return component->get_path();
	}
	return "ERROR: File not found";
}

int Folder::get_children_amount() const
{
	return children_amount_;
}

int Folder::get_all_children_amount() const
{
	return all_children_amount_ + children_amount_;
}


list<FileSystem*>& Folder::get_list()
{
	return components;
}

FileSystem* Folder::get_from_folder(FileSystem* folder, string component_name)
{
	for (auto& component : folder->get_list()) {
		if (component->get_name() == component_name) {
			return component;
		}
	}
	return nullptr;
}

void Folder::add(FileSystem* component)
{
	component->set_parent(this);
	components.push_back(component);
	component->recalculate_nesting();
	component->set_modification_date();
	set_modification_date();
	size_ += component->get_size();
	++children_amount_;
	all_children_amount_ += component->get_all_children_amount();
}

FileSystem* Folder::add_folder(FileSystem* folder, string folder_name)
{
	FileSystem* new_folder = new Folder(folder_name);
	folder->add(new_folder);
	return new_folder;
}

FileSystem* Folder::add_file(FileSystem* folder, string folder_name, size_t size)
{
	FileSystem* new_file = new File(folder_name, size);
	folder->add(new_file);
	return new_file;
}


FileSystem* Folder::clone() const
{
	return new Folder();
}

FileSystem* Folder::copy(FileSystem* to_folder, FileSystem* component, string name)
{
	FileSystem* new_component = component->clone();
	component->copy_parameters(new_component);
	new_component->set_name(name);
	Iterator<FileSystem, list<FileSystem*>>* i = component->create_iterator();
	for (i->first(); !i->is_done(); i->next()) {
		i->current()->copy(new_component, i->current(), i->current()->get_name() + "_copy");
	}
	to_folder->add(new_component);
	return new_component;
}


FileSystem* Folder::search_by_name(string name)
{
	FileSystem* component = nullptr;
	Iterator<FileSystem, list<FileSystem*>>* i = create_iterator();
	for (i->first(); !i->is_done(); i->next()) {
		if (i->current()->get_name() == name) {
			return i->current();
		}
		component = i->current()->search_by_name(name);
		if (component) {
			return component;
		}
	}
	return component;
}

list<FileSystem*> Folder::search_by_size(FileSystem* folder, size_t min_size, size_t max_size)
{
	list<FileSystem*> collection;
	size_t component_size{ 0 };
	Iterator<FileSystem, list<FileSystem*>>* i = folder->create_iterator();
	for (i->first(); !i->is_done(); i->next()) {
		component_size = i->current()->get_size();
		if (component_size >= min_size && component_size <= max_size) {
			collection.push_back(i->current());
		}
	}
	return collection;
}
void Folder::recalculate_nesting()
{
	nesting_ = 0;
	calculate_nesting();
	Iterator<FileSystem, list<FileSystem*>>* i = create_iterator();
	for (i->first(); !i->is_done(); i->next()) {
		i->current()->recalculate_nesting();
	}
	set_modification_date();
}

bool Folder::is_folder() const
{
	return true;
}


void Folder::system_visualization()
{
	for (int i = 0; i < nesting_; ++i) {
		cout << " ";
	}
	cout << "-" << get_name() << endl;
	Iterator<FileSystem, list<FileSystem*>>* i = create_iterator();
	for (i->first(); !i->is_done(); i->next()) {
		i->current()->system_visualization();
	}
}


// class File

File::File()
{
	set_name("File");
	set_creation_date();
	size_ = sizeof(this);
}

File::File(string name)
{
	set_name(name);
	set_creation_date();
	size_ = sizeof(this);
}

File::File(string name, size_t size)
{
	set_name(name);
	set_creation_date();
	size_ = size;
}

FileSystem* File::clone() const
{
	return new File();
}

FileSystem* File::copy(FileSystem* to_folder, FileSystem* component, string name)
{
	FileSystem* new_component = component->clone();
	component->copy_parameters(new_component);
	new_component->set_name(name);
	to_folder->add(new_component);
	return new_component;
}


FileSystem* File::search_by_name(string name)
{
	if (get_name() == name) {
		return this;
	}
	return nullptr;
}

void File::recalculate_nesting()
{
	nesting_ = 0;
	calculate_nesting();
	set_modification_date();
}

bool File::is_folder() const
{
	return false;
}


void File::system_visualization()
{
	for (int i = 0; i < nesting_; ++i) {
		cout << " ";
	}
	cout << "-" << get_name() << endl;
}