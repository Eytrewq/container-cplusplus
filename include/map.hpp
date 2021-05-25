/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:04:43 by ebiscara          #+#    #+#             */
/*   Updated: 2021/05/23 18:13:54 by ebiscara         ###   ########.fr       */
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
		std::pair<const Key, T> data;
		BSTNode *left;
		BSTNode *right;
		BSTNode *parent;
		bool end;
	};

	template < class Key, class T >
	class MapIterator: public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef std::pair<const Key, T> value_type;
			typedef std::pair<const Key, T>& reference;
			typedef const std::pair<const Key, T>& const_reference;
			typedef std::pair<const Key, T>* pointer;
			typedef const std::pair<const Key, T>* const_pointer;
			typedef BSTNode<const Key, T>* m_node;
		protected:
			m_node n;
		public:
			MapIterator() {};
			explicit MapIterator(m_node _n): n(_n) {};
			MapIterator(const MapIterator &other) { *this = other; };
			virtual ~MapIterator() {};

			MapIterator &operator=(const MapIterator &other) { this->n = other.n; return (*this); };

			bool operator==(const MapIterator &other) const { return (this->n == other.n); };
			bool operator!=(const MapIterator &other) const { return (this->n != other.n); };

			reference operator*() { return (this->n->data); };
			const_reference operator*() const { return (this->n->data); };

			pointer operator->() { return (this->n->data); };
			const_pointer operator->() const { return (this->n->data); };

			MapIterator operator++(int) { MapIterator tmp(*this); this->operator++(); return (tmp); };
			MapIterator &operator++() {
				m_node tmp = n;
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
			MapIterator operator--(int) { MapIterator tmp(*this); this->operator--(); return (tmp); };
			MapIterator &operator--() {
				m_node tmp = n;
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

			m_node getNode() { return (n); };
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
			typedef typename MapIterator::m_node m_node;
		protected:
			m_node n;
		public:
			map_reverse_iterator() {};
			explicit map_reverse_iterator(m_node _n): n(_n) {};
			map_reverse_iterator(const map_reverse_iterator &other) { *this = other; };
			virtual ~map_reverse_iterator() {};

			map_reverse_iterator &operator=(const map_reverse_iterator &other) { this->n = other.n; return (*this); };

			bool operator==(const map_reverse_iterator &other) const { return (this->n == other.n); };
			bool operator!=(const map_reverse_iterator &other) const { return (this->n != other.n); };

			reference operator*() { return (this->n->data); };
			const_reference operator*() const { return (this->n->data); };

			pointer operator->() { return (this->n->data); };
			const_pointer operator->() const { return (this->n->data); };

			map_reverse_iterator operator++(int) { map_reverse_iterator tmp(*this); this->operator++(); return (tmp); }; // ?
			map_reverse_iterator &operator++() {
				m_node tmp = n;
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
			map_reverse_iterator operator--(int) { map_reverse_iterator tmp(*this); this->operator--(); return (tmp); };
			map_reverse_iterator &operator--() {
				m_node tmp = n;
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

			m_node getNode() { return (n); };
	};

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type,mapped_type> value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::MapIterator<Key, T> iterator;
			typedef ft::MapIterator<const Key, const T> const_iterator; //??
			typedef ft::map_reverse_iterator<iterator> reverse_iterator;
			typedef ft::map_reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
			typedef Alloc allocator_type;
			typedef Compare key_compare;
			//typedef value_compare; ??
		private:
			typedef BSTNode<key_type, mapped_type>* _node;
			typedef BSTNode<const key_type, const mapped_type>* const_node;

			_node root;
			size_type map_size;
			allocator_type alloc;
			key_compare comp;

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

			_node _insert_node(_node n, key_type key, mapped_type val, bool end = false)
			{
				while (n->end || (key < n->data.first && !end))
				{
					if (!n->left)
					{
						n->left = create_node(key, val, n, end);
						return (n->left);
					}
					n = n->left;
				}
				while (key >= n->data.first || end)
				{
					if (!n->right)
					{
						n->right = create_node(key, val, n, end);
						return (n->right);
					}
					n = n->right;
				}
			};

			// ATT
			_node _find(_node n, key_type key) const
			{
				_node tmp = n;
				if (!n->end && n->data.first == key && n->parent)
					return (n);
				while (tmp->right)
				{
					if (!tmp->end && tmp->data.first == key && tmp->parent)
						return (tmp);
					n = n->right;
				}
				while (n->left)
				{
					if (!n->end && n->data.first == key && n->parent)
						return (n);
					n = n->left;
				}
				return (0);
			};

			void free_tree(_node n)
			{
				if (n->right)
					free_tree(n->right)
				if (n->left)
					free_tree(n->left)
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
			{ this->init_tree(); this->insert(comp, first, last); };

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

			/*template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				this->clear();
				this->insert(this->begin(), first, last);
			};
			void assign (size_type n, const value_type& val) {
				this->clear();
				this->insert(this->begin(), n, val);
			};

			void push_back (const value_type& val) {
				if (this->container_size + 1 > this->_capacity)
					this->reserve(this->_capacity ? this->_capacity * 2 : 1);
				this->container[this->container_size++] = val;
			};

			void pop_back() {
				if (this->container_size)
					this->container_size--;
			}*/

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
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			};

			// ATT
			iterator find(const key_type &val)
			{
				if (this->empty())
					return (this->end());
				_node tmp = this->_find(root, val);
				if (tmp)
					return (iterator(tmp));
				return (this->end());
			};
			const_iterator find(const key_type &val) const
			{
				if (this->empty())
					return (this->end());
				_node tmp = this->_find(root, val);
				if (tmp)
					return (const_iterator(tmp));
				return (this->end());
			};

			/*iterator erase (iterator position) {
				iterator p = position;
				while (p + 1 != this->end())
				{
					*p = *(p + 1);
					p++;
				}
				this->container_size--;
				return (iterator(position));
			};
			iterator erase (iterator first, iterator last) {
				while (first != last)
					erase(--last);
				return (iterator(first));
			};

			void swap (vector& x) {
				std::swap(this->container, x.container);
				std::swap(this->container_size, x.container_size);
				std::swap(this->_capacity, x._capacity);
			};

			void clear() { this->erase(this->begin(), this->end()); };
	};

	template <>
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
	};
}

#endif
