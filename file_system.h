#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <list>
#include <stdbool.h>

#include "date.h"

using namespace std;

template<typename T, typename U>
class Iterator
{
public:
	typedef typename list<T*>::iterator iterator_t;

	Iterator(U& children);

	void	first();
	void	previous();
	void	next();
	bool	is_done();
	T*		current();

private:
	U& children_;
	iterator_t it_;
};

class FileSystem
{
public:
	friend class Iterator<FileSystem, list<FileSystem>>;

	void set_creation_date();
	void set_modification_date();
	void set_name(string name);
	void set_parent(FileSystem* parent);
	void set_size(size_t size);
	void set_nesting(int nesting);

	string			get_creation_date();
	string			get_modification_date();
	FileSystem*		get_root();
	string			get_name() const;
	string			get_date(Date* date) const;
	FileSystem*		get_parent() const;
	int				get_nesting() const;
	size_t			get_size() const;
	string			get_path();
	virtual string	get_path_by_name(string name);
	virtual int		get_children_amount() const;
	virtual int		get_all_children_amount() const;
	void			get_attributes() const;

	virtual	list<FileSystem*>&	get_list();
	virtual FileSystem*			get_from_folder(FileSystem* folder, string component_name);

	virtual void		add(FileSystem* component);
	virtual FileSystem* add_folder(FileSystem* folder, string folder_name);
	virtual FileSystem* add_file(FileSystem* folder, string folder_name, size_t size);

	virtual FileSystem* clone() const = 0;
	void				copy_parameters(FileSystem* recipient);
	virtual FileSystem* copy(FileSystem* to_folder, FileSystem* component, string name) = 0;

	void modify(FileSystem* component, size_t new_size);
	void rename(FileSystem* component, string name);
	void move(FileSystem* to_folder, FileSystem* component);
	void remove(FileSystem* component);


	virtual FileSystem*			search_by_name(string name) = 0;
	virtual list<FileSystem*>	search_by_size(FileSystem* folder, size_t min_size, size_t max_size);
	void						delete_all_dates();
	void						invalidate_parameters();
	void						calculate_nesting();
	virtual void				recalculate_nesting() = 0;
	virtual bool				is_folder() const = 0;

	virtual void system_visualization() = 0;

	virtual Iterator<FileSystem, list<FileSystem*>>* create_iterator()
	{
		return nullptr;
	}

protected:
	string		name_{ "NoName" };
	Date*		creation_date_{};
	Date*		modification_date_{};
	size_t		size_{ 0 };
	FileSystem* parent_{ nullptr };
	int			nesting_{ 0 };
};


class Folder : public FileSystem
{
public:
	Folder();
	Folder(string name);
	~Folder();

	string	get_path_by_name(string name) override;
	int		get_children_amount() const override;
	int		get_all_children_amount() const override;

	list<FileSystem*>&	get_list() override;
	FileSystem*			get_from_folder(FileSystem* folder, string component_name);

	void		add(FileSystem* component) override;
	FileSystem* add_folder(FileSystem* folder, string folder_name) override;
	FileSystem* add_file(FileSystem* folder, string folder_name, size_t size) override;

	FileSystem* clone() const override;
	FileSystem* copy(FileSystem* to_folder, FileSystem* component, string name) override;

	FileSystem*			search_by_name(string name) override;
	list<FileSystem*>	search_by_size(FileSystem* folder, size_t min_size, size_t max_size) override;
	void				recalculate_nesting() override;
	bool				is_folder() const override;

	void system_visualization() override;

	Iterator<FileSystem, list<FileSystem*>>* create_iterator() override
	{
		return new Iterator<FileSystem, list<FileSystem*>>(this->components);
	}

private:
	int children_amount_{ 0 };
	int all_children_amount_{ 0 };
	list<FileSystem*> components;
};


class File : public FileSystem
{
public:
	File();
	File(string name);
	File(string name, size_t size);

	FileSystem* clone() const override;
	FileSystem* copy(FileSystem* to_folder, FileSystem* component, string name) override;

	FileSystem* search_by_name(string name) override;
	void		recalculate_nesting() override;
	bool		is_folder() const override;

	void system_visualization() override;
};

#endif //FILE_SYSTEM_H
