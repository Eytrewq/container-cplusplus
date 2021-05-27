/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:04:43 by ebiscara          #+#    #+#             */
/*   Updated: 2021/05/26 10:47:01 by ebiscara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <limits>
# include <cstdlib>

namespace ft
{
	template < class Key, class T >
	struct BSTNode
	{
		std::pair<Key, T> data;
		BSTNode *left;
		BSTNode *right;
		BSTNode *parent;
		bool end;
	};

	template < class T > // ??
	void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	};

	template < class Key, class T >
	class MapIterator: public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef std::pair<Key, T> value_type;
			typedef std::pair<Key, T>& reference;
			typedef const std::pair<const Key, T>& const_reference;
			typedef BSTNode<Key, T>* pointer;
			typedef const BSTNode<Key, T>* const_pointer;
		protected:
			pointer n;
		private:
			pointer n_next(pointer n)
			{
				pointer tmp = n;
				if (tmp->right == 0)
				{
					while (tmp->parent && tmp->parent->right == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
				else
				{
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
				}
				return (tmp);
			};
			pointer n_pred(pointer n)
			{
				pointer tmp = n;
				if (tmp->left == 0)
				{
					while (tmp->parent && tmp->parent->left == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
				else
				{
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
				}
				return (tmp);
			};
		public:
			MapIterator() {};
			explicit MapIterator(pointer _n): n(_n) {};
			MapIterator(const MapIterator &other) { *this = other; };
			virtual ~MapIterator() {};

			MapIterator &operator=(const MapIterator &other) { this->n = other.n; return (*this); };

			bool operator==(const MapIterator &other) const { return (this->n == other.n); };
			bool operator!=(const MapIterator &other) const { return (this->n != other.n); };

			value_type &operator*() { return (this->n->data); };
			value_type *operator->() { return (&this->n->data); };

			//value_type &operator*() const { return (this->n->data); }; // Const
			//value_type *operator->() const { return (&this->n->data); };

			MapIterator operator++(int) { MapIterator tmp(*this); this->operator++(); return (tmp); };
			MapIterator &operator++() {
				this->n = this->n_next(this->n);
				return (*this);
			};
			MapIterator operator--(int) { MapIterator tmp(*this); this->operator--(); return (tmp); };
			MapIterator &operator--() {
				this->n = this->n_pred(this->n);
				return (*this);
			};

			pointer getNode() { return (n); };
	};

	template<class MapIterator>
	class map_reverse_iterator: public MapIterator
	{
		public:
			typedef typename MapIterator::value_type value_type;
			typedef typename MapIterator::pointer pointer;
			typedef typename MapIterator::const_pointer const_pointer;
			typedef typename MapIterator::reference reference;
			typedef typename MapIterator::const_reference const_reference;
		protected:
			pointer n;
		private:
			pointer n_next(pointer n)
			{
				pointer tmp = n;
				if (tmp->right == 0)
				{
					while (tmp->parent && tmp->parent->right == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
				else
				{
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
				}
				return (tmp);
			};
			pointer n_pred(pointer n)
			{
				pointer tmp = n;
				if (tmp->left == 0)
				{
					while (tmp->parent && tmp->parent->left == tmp)
						tmp = tmp->parent;
					tmp = tmp->parent;
				}
				else
				{
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
				}
				return (tmp);
			};
		public:
			map_reverse_iterator() {};
			explicit map_reverse_iterator(pointer _n): n(_n) {};
			map_reverse_iterator(const map_reverse_iterator &other) { *this = other; };
			virtual ~map_reverse_iterator() {};

			map_reverse_iterator &operator=(const map_reverse_iterator &other) { this->n = other.n; return (*this); };

			bool operator==(const map_reverse_iterator &other) const { return (this->n == other.n); };
			bool operator!=(const map_reverse_iterator &other) const { return (this->n != other.n); };

			value_type &operator*() { return (this->n->data); };
			value_type *operator->() { return (&this->n->data); };

			map_reverse_iterator operator++(int) { map_reverse_iterator tmp(*this); this->operator++(); return (tmp); }; // ?
			map_reverse_iterator &operator++() {
				this->n = this->n_next(this->n);
				return (*this);
			};
			map_reverse_iterator operator--(int) { map_reverse_iterator tmp(*this); this->operator--(); return (tmp); };
			map_reverse_iterator &operator--() {
				this->n = this->n_pred(this->n);
				return (*this);
			};

			pointer getNode() { return (n); };
	};

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type,mapped_type> value_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef ft::MapIterator<Key, T> iterator;
			typedef ft::MapIterator<Key, T> const_iterator; //??
			typedef ft::map_reverse_iterator<iterator> reverse_iterator;
			typedef ft::map_reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
			typedef Alloc allocator_type;
			typedef Compare key_compare;
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
			};
		private:
			typedef BSTNode<key_type, mapped_type>* _node;
			typedef BSTNode<key_type, mapped_type>* const_node;

			_node root;
			size_type map_size;
			allocator_type alloc;
			key_compare k_comp;

			_node create_node(key_type key, mapped_type val, _node parent, bool end) {
				_node n = new BSTNode<key_type, mapped_type>();
				n->data = std::make_pair(key, val);
				n->left = 0;
				n->right = 0;
				n->parent = parent;
				n->end = end;
				return (n);
			};

			_node create_node(_node parent, bool end) {
				_node n = new BSTNode<key_type, mapped_type>();
				n->left = 0;
				n->right = 0;
				n->parent = parent;
				n->end = end;
				return (n);
			};

			// ??
			_node _insert_node(_node n, key_type key, mapped_type value, bool end = false)
			{
				if (n->end)
				{
					if (!n->left)
					{
						n->left = create_node(key, value, n, end);
						return (n->left);
					}
					return (_insert_node(n->left, key, value));
				}
				if (key < n->data.first && !end)
				{
					if (!n->left)
					{
						n->left = create_node(key, value, n, end);
						return (n->left);
					}
					else
						return (_insert_node(n->left, key, value));
				}
				else
				{
					if (!n->right)
					{
						n->right = create_node(key, value, n, end);
						return (n->right);
					}
					else
						return(_insert_node(n->right, key, value));
				}
			};

			_node _find(_node n, key_type key) const
			{
				_node tmp;
				if (!n->end && n->data.first == key && n->parent)
					return (n);
				if (n->right)
				{
					if ((tmp = _find(n->right, key)))
						return (tmp);
				}
				if (n->left)
				{
					if ((tmp = _find(n->left, key)))
						return (tmp);
				}
				return (0);
			};

			_node erase_node(_node n)
			{
				node parent = n->parent;
				if (!n->left && !n->right)
				{
					if (parent->right == n)
						parent->right = 0;
					else
						parent->left = 0;
					delete n;
					return ;
				}
				if (n->right && !n->left)
				{
					if (parent->right == n)
						parent->right = n->right;
					else
						parent->left = n->right;
					n->right->parent = parent;
					delete n;
					return ;
				}
				if (n->left && !n->right)
				{
					if (parent->right == n)
						parent->right = n->left;
					else
						parent->left = n->left;
					n->left->parent = parent;
					delete n;
					return ;
				}
				node next = (++iterator(n)).node();
				if (!next)
					next = (--iterator(n)).node();
				ft::swap(next->pair, n->pair);
				_delete_node(next);
			};

			void print_tree(node n)
			{
				if (!n)
					return;
				print_tree(n->left);
				if (n->parent && !n->end)
					std::cout << n->pair.first << "->" << n->pair.second << std::endl;
				print_tree(n->right);
			};

			void free_tree(_node n)
			{
				if (n->right)
					free_tree(n->right);
				if (n->left)
					free_tree(n->left);
				delete n;
			};

			void init_tree()
			{
				this->root = create_node(0, false);
				this->root->right = create_node(root, true); //??
				this->map_size = 0;
			};
		public:
			explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()): alloc(alloc), comp(comp) { this->init_tree(); };

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): alloc(alloc), comp(comp)
			{ this->init_tree(); this->insert(first, last); };

			map (const map& x) { this->init_tree(); *this = x; };
			~map() {
				free_tree(root);
			};

			map &operator=(const map& x) {
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			};

			// ITERATOR

			iterator begin() {
				_node n = this->root;
				if (n->left == 0 && n->right == 0)
					return (iterator(n->right));
				if (n->left == 0 && n->right)
					n = n->right;
				while (n->left)
					n = n->left;
				return (iterator(n));
			};
			const_iterator begin() const {
				const_node n = this->root;
				if (n->left == 0 && n->right == 0)
					return (const_iterator(n->right));
				if (n->left == 0 && n->right)
					n = n->right;
				while (n->left)
					n = n->left;
				return (const_iterator(n));
			};

			iterator end() {
				_node n = this->root;
				while (n->right)
					n = n->right;
				return (iterator(n));
			};
			const_iterator end() const {
				_node n = this->root;
				while (n->right)
					n = n->right;
				return (const_iterator(n));
			};

			reverse_iterator rbegin() {
				iterator t = this->end();
				t--;
				return (reverse_iterator(t.getNode()));
			};
			const_reverse_iterator rbegin() const {
				iterator t = this->end();
				t--;
				return (const_reverse_iterator(t.getNode()));
			};

			reverse_iterator rend() { return (reverse_iterator(this->root)); };
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->root)); };

			// CAPACITY

			size_type size() const { return (this->map_size); };
			size_type max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(map<key_type, mapped_type>)); }; // ??

			bool empty() const {
				if (!this->map_size)
					return (1);
				return (0);
			};

			// ELEMENT
			mapped_type& operator[] (const key_type& k) {
				iterator tmp = find(k);
				if (tmp != this->end())
					return (tmp->second);
				return (this->insert(std::make_pair(k,mapped_type())).first->second);
			};

			// MODIFIERS

			std::pair<iterator,bool> insert (const value_type& val)
			{
				iterator tmp;
				if ((tmp = this->find(val.first)) != this->end())
					return (std::make_pair(tmp, false));
				this->map_size++;
				return (std::make_pair(iterator(_insert_node(root, val.first, val.second)), true));
			};
			iterator insert (iterator position, const value_type& val)
			{
				iterator tmp;
				if ((tmp = this->find(val.first)) != this->end())
					return (tmp);
				this->map_size++;
				return (iterator(_insert_node(position.getNode(), val.first, val.second)));
			};
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			};

			void erase (iterator position)
			{
				erase_node(position.getNode());
				map_size--;
			};
			size_type erase (const key_type& k)
			{
				iterator it = this->begin();
				size_type count = 0;
				while (it != this->end()) {
					if (it->first == k) {
						count++;
						erase(it);
					}
					it++;
				}
				return (count);
			};
     		void erase (iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
				return (iterator(first));
			};

			void swap (map& x)
			{
				ft::swap(root, x.root);
				ft::swap(map_size, x.map_size);
			}

			void clear()
			{
				erase(this->begin(), this->end());
			};

			// OBSERVERS
			key_compare key_comp() const
			{
				return (this->k_comp);
			};

			value_compare value_comp() const
			{
				return (this->value_compare);
			};

			// OPERATIONS
			iterator find (const key_type& k)
			{
				if (this->empty())
					return (this->end());
				_node tmp = this->_find(this->root, k);
				if (tmp)
					return (iterator(tmp));
				return (this->end());
			};

			const_iterator find (const key_type& k) const
			{
				if (this->empty())
					return (this->end());
				_node tmp = this->_find(this->root, k);
				if (tmp)
					return (const_iterator(tmp));
				return (this->end());
			};

			size_type count (const key_type& k) const
			{
				const_iterator it = this->begin();
				size_type count = 0;
				while (it != this->end()) {
					if (it->first == k)
						count++;
					it++;
				}
				return (count);
			};

			iterator lower_bound (const key_type& k)
			{
				iterator it = this->begin();
				while (it != this->end()) {
					if (this->k_comp(it->first, k) <= 0)
						return (it);
					it++;
				}
				return (this->end());
			};

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				while (it != this->end()) {
					if (this->k_comp(it->first, k) <= 0)
						return (it);
					it++;
				}
				return (this->end());
			};

			iterator upper_bound (const key_type& k)
			{
				iterator it = this->begin();
				while (it != this->end()) {
					if (this->k_comp(it->first, k) <= 0 && it->first != k)
						return (it);
					it++;
				}
				return (this->end());
			};

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				while (it != this->end()) {
					if (this->k_comp(it->first, k) <= 0 && it->first != k)
						return (it);
					it++;
				}
				return (this->end());
			};

			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (std::pair<const_iterator,const_iterator>(this->lower_bound(k), this->upper_bound(k)));
			};
			std::pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (std::pair<iterator,iterator>(this->lower_bound(k), this->upper_bound(k)));
			};
	};

	/*template <>
	template <>
	void ft::vector<int>::insert(iterator position, int s, int v)
	{
		this->insert(position, (size_type)s, v);
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator it = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator itt = rhs.begin();
		if (lhs.size() != rhs.size())
			return (0);
		while (it != lhs.end())
		{
			if (*it != *itt)
				return (0);
			it++;
			itt++;
		}
		return (1);
	};
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!operator==(lhs, rhs));
	};
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!operator<(rhs, lhs));
	};
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!operator<(lhs, rhs));
	};
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!operator<(lhs, rhs));
	};*/
}

#endif
