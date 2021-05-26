/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:47:49 by ebiscara          #+#    #+#             */
/*   Updated: 2021/05/22 11:02:46 by ebiscara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <limits>
# include <cstdlib>

# include <iostream>

namespace ft
{
	template < class T >
	struct node
	{
		T data;
		node *prev;
		node *next;
	};

	template < class T >
	void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	};

	template < class T >
	class ListIterator: public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef T value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef node<value_type>* _node;
      		typedef std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t difference_type;
		protected:
			_node n;
		public:
			ListIterator() {};
			explicit ListIterator(_node _n): n(_n) {};
			ListIterator(const ListIterator &other) { *this = other; };
			virtual ~ListIterator() {};

			ListIterator &operator=(const ListIterator &other) { this->n = other.n; return (*this); };

			bool operator==(const ListIterator &other) const { return (this->n == other.n); };
			bool operator!=(const ListIterator &other) const { return (this->n != other.n); };

			reference operator*() { return (this->n->data); };
			const_reference operator*() const { return (this->n->data); };

			pointer operator->() { return (this->n->data); };
			const_pointer operator->() const { return (this->n->data); };

			ListIterator operator++(int) { ListIterator tmp(*this); this->n = this->n->next; return (tmp); };
			ListIterator &operator++() { this->n = this->n->next; return (*this); };
			ListIterator operator--(int) { ListIterator tmp(*this); this->n = this->n->prev; return (tmp); };
			ListIterator &operator--() { this->n = this->n->prev; return (*this); };

			ListIterator operator+(int __n) { ListIterator tmp(*this); tmp += __n; return (tmp); };
			ListIterator &operator+=(int __n) { 
				while (__n < 0) {
					(*this)--;
					__n++;
				}
				while (__n > 0) {
					(*this)++;
					__n--;
				}
				return (*this);
			};

			_node getNode() { return (n); };
	};

	template<class _Iterator>
	class list_reverse_iterator: public _Iterator
	{
		public:
			typedef typename _Iterator::value_type value_type;
			typedef typename _Iterator::difference_type difference_type;
			typedef typename _Iterator::pointer pointer;
			typedef typename _Iterator::const_pointer const_pointer;
			typedef typename _Iterator::reference reference;
			typedef typename _Iterator::const_reference const_reference;
			typedef typename _Iterator::_node _node;
		protected:
			_node n;
		public:
			list_reverse_iterator() {};
			explicit list_reverse_iterator(_node _n): n(_n) {};
			list_reverse_iterator(const list_reverse_iterator &other) { *this = other; };
			virtual ~list_reverse_iterator() {};

			list_reverse_iterator &operator=(const list_reverse_iterator &other) { this->n = other.n; return (*this); };

			bool operator==(const list_reverse_iterator &other) const { return (this->n == other.n); };
			bool operator!=(const list_reverse_iterator &other) const { return (this->n != other.n); };

			reference operator*() { return (this->n->data); };
			const_reference operator*() const { return (this->n->data); };

			pointer operator->() { return (this->n->data); };
			const_pointer operator->() const { return (this->n->data); };

			list_reverse_iterator operator++(int) { list_reverse_iterator tmp(*this); this->n = this->n->prev; return (tmp); };
			list_reverse_iterator &operator++() { this->n = this->n->prev; return (*this); };
			list_reverse_iterator operator--(int) { list_reverse_iterator tmp(*this); this->n = this->n->next; return (tmp); };
			list_reverse_iterator &operator--() { this->n = this->n->next; return (*this); };

			_node getNode() { return (n); };
	};

	template < class T >
	bool less(const T& a, const T& b) { return (a < b); };

	template < class T >
	bool equal(const T& a, const T& b) { return (a == b); };

	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef T value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::ListIterator<value_type> iterator;
			typedef ft::ListIterator<const value_type> const_iterator;
			typedef ft::list_reverse_iterator<iterator> reverse_iterator;
			typedef ft::list_reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
			typedef Alloc allocator_type;
		private:
			typedef node<value_type>* _node;
			typedef node<const value_type>* const_node;
			_node n_begin;
			_node n_end;
			size_type list_size;
			allocator_type alloc;

			_node create_node(value_type v, _node prev, _node next) {
				_node n = new node<value_type>();
				n->data = v;
				n->prev = prev;
				n->next = next;
				return (n);
			};

			_node _create_node(_node prev, _node next) {
				_node n = new node<value_type>();
				n->prev = prev;
				n->next = next;
				return (n);
			};

			void reinit_list(void) {
				this->n_begin->prev = 0;
				this->n_begin->next = 0;
				this->n_end->prev = this->n_begin;
				this->n_end->next = 0;
				this->n_begin->next = this->n_end;
			}

			void init_list()
			{
				this->n_begin = _create_node(0, 0);
				this->n_end = _create_node(n_begin, 0);
				this->n_begin->next = this->n_end;
			}

		public:
			explicit list (const allocator_type& alloc = allocator_type()):
			n_begin(0), n_end(0), list_size(0), alloc(alloc) { this->init_list(); };

			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
			n_begin(0), n_end(0), list_size(0), alloc(alloc) {
				this->init_list();
				this->assign(n, val);
			};

			template <class InputIterator>
  			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
			n_begin(0), n_end(0), list_size(0), alloc(alloc) {
				this->init_list();
				this->assign(first, last);
			};

			list (const list& x): n_begin(0), n_end(0), list_size(0), alloc(x.alloc) { this->init_list(); *this = x; };

			~list() { this->clear(); delete n_begin; delete n_end; };

			list& operator= (const list& x) {
				this->alloc = x.alloc;
				this->list_size = 0;
				this->assign(x.begin(), x.end());
				return (*this);
			};

			// ITERATOR

			iterator begin() { return (iterator(this->n_begin->next)); };
			const_iterator begin() const { return (const_iterator(reinterpret_cast<const_node>(this->n_begin->next))); };

			iterator end() { return (iterator(this->n_end)); };
			const_iterator end() const { return (const_iterator(reinterpret_cast<const_node>(this->n_end))); };

			reverse_iterator rbegin() { return (reverse_iterator(this->n_end->prev));};
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(reinterpret_cast<const_node>(this->n_end->prev))); };

			reverse_iterator rend() { return (reverse_iterator(this->n_begin));};
			const_reverse_iterator rend() const { return (const_reverse_iterator(reinterpret_cast<const_node>(this->n_begin))); };

			// CAPACITY

			size_type size() const { return (this->list_size); };
			size_type max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(list<value_type>)); };

			bool empty() const {
				if (this->list_size == 0)
					return (1);
				return (0);
			};

			// ELEMENT 

			reference front() { return (this->n_begin->next->data); };
			const_reference front() const { return (this->n_begin->next->data); };

			reference back() { return (this->n_end->prev->data); };
			const_reference back() const { return (this->n_end->prev->data); };

			// MODIFIERS

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				this->clear();
				this->insert(this->begin(), first, last);
			};
			void assign (size_type n, const value_type& val) {
				this->clear();
				this->insert(this->begin(), n, val);
			};

			void push_front (const value_type& val) {
				_node nod = this->create_node(val, this->n_begin, this->n_begin->next);
				this->n_begin->next->prev = nod;
				this->n_begin->next = nod;
				this->list_size++;
			};

			void pop_front() {
				if (this->list_size)
				{
					_node p = this->n_begin->next->next;
					this->n_begin->next->next->prev = this->n_begin;
					delete this->n_begin->next;
					this->n_begin->next = p;
					this->list_size--;
				}
			};

			void push_back (const value_type& val) {
				_node nod = this->create_node(val, this->n_end->prev, this->n_end);
				this->n_end->prev->next = nod;
				this->n_end->prev = nod;
				this->list_size++;
			};

			void pop_back() {
				if (this->list_size)
				{
					_node p = this->n_end->prev->prev;
					delete this->n_end->prev;
					p->next = this->n_end;
					this->n_end->prev = p;
					this->list_size--;
				}
			};

			iterator insert (iterator position, const value_type& val) {
				_node p = position.getNode();
				_node nod = this->create_node(val, p->prev, p);
				p->prev->next = nod;
				p->prev = nod;
				this->list_size++;
				return (iterator(nod));
			};
    		void insert (iterator position, size_type n, const value_type& val) {
				while (n--)
					position = this->insert(position, val);
			};
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {
				while (first != last)
				{
					position = this->insert(position, *first);
					first++;
					if (position != this->end())
						position++;
				}
			};

			iterator erase (iterator position) {
				_node tmp_next = position.getNode()->next;
				_node tmp_prev = position.getNode()->prev;
				delete position.getNode();
				tmp_prev->next = tmp_next;
				tmp_next->prev = tmp_prev;
				if (this->list_size > 0)
					this->list_size--;
				return (iterator(tmp_next));
			};
			iterator erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
				return (iterator(first));
			};

			void swap (list& x) {
				std::swap(this->list_size, x.list_size);
				std::swap(this->n_begin, x.n_begin);
				std::swap(this->n_end, x.n_end);
			};

			void resize (size_type n, value_type val = value_type()) {
				while (n < this->list_size)
					this->pop_back();
				while (n > this->list_size)
					this->push_back(val);
			};

			void clear() {
				this->erase(this->begin(), this->end());
				this->reinit_list();
			};

			// OPERATIONS
			
			void splice (iterator position, list& x) { this->splice(position, x, x.begin(), x.end()); };
			void splice (iterator position, list& x, iterator i) { this->insert(position, *i); x.erase(i); };
			void splice (iterator position, list& x, iterator first, iterator last) { this->insert(position, first, last); x.erase(first, last); };

			void remove (const value_type& val) {
				iterator it = this->begin();
				while (it != this->end()) {
					if (*it == val)
						it = this->erase(it);
					else
						it++;
				}
			};

			template <class Predicate>
  			void remove_if (Predicate pred) {
				iterator it = this->begin();
				while (it != this->end()) {
					if (pred(*it))
						it = this->erase(it);
					else
						it++;
				}
			};

			void unique() {
				this->unique(&equal<value_type>);
			};
			template <class BinaryPredicate>
  			void unique (BinaryPredicate binary_pred) {
				iterator it = this->begin();
				iterator next = this->begin();
				while (++next != this->end()) {
					if (binary_pred(*it, *next))
					{
						this->erase(next);
						next = it;
					}
					else
						it++;
				}
			};

			void merge (list& x) {
				this->merge(x, &less<value_type>);
			};
			template <class Compare>
  			void merge (list& x, Compare comp) {
				if (&x == this)
					return ;
				this->insert(this->end(), x.begin(), x.end());
				x.clear();
				this->sort(comp);
			};

			void sort() {
				this->sort(&less<value_type>);
			};
			template <class Compare>
 			void sort (Compare comp) { // ??
				iterator it = this->begin();
				iterator next;
				while (it + 1 != this->end()) {
					next = it + 1;
					while (next != this->end()) {
						if (comp(*next, *it))
							ft::swap(*next, *it);
						next++;
					}
					it++;
				}
			};

			void reverse() {
				iterator it = this->begin();
				list<value_type> l;
				while (it != this->end())
				{
					l.push_front(*it);
					it++;
				}
				*this = l;
			};
	};

	template <class T, class Alloc>
	void swap(list<T, Alloc> &x, list<T, Alloc> &y)
	{
		x.swap(y);
	};

	template <>
	template <>
	void ft::list<int>::insert(iterator position, int s, int v)
	{
		this->insert(position, (size_type)s, v);
	};

	template <class T, class Alloc>
  	bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		typename list<T, Alloc>::const_iterator it = lhs.begin();
		typename list<T, Alloc>::const_iterator itt = rhs.begin();
		while (it != lhs.end()) {
			if (*it != *itt)
				return (0);
			it++;
			itt++;
		}
		return (1);
	};

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	};

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs > rhs));
	};

	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	};

	template < class T >
	void swap(list<T> &x, list<T> &y) { x.swap(y); };
}

#endif
