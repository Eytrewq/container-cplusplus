/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:10:15 by ebiscara          #+#    #+#             */
/*   Updated: 2021/04/26 18:42:36 by ebiscara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <cstdlib>

namespace ft
{

	template < class T >
	class VectorIterator: public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef std::ptrdiff_t difference_type;
		protected:
			pointer p;
		public:
			VectorIterator(): p(NULL) {};
			explicit VectorIterator(pointer _p): p(_p) {};
			VectorIterator(const VectorIterator &other) { *this = other; };
			virtual ~VectorIterator() {};

			VectorIterator &operator=(const VectorIterator &other) { this->p = other.p; return (*this); };

			bool operator==(const VectorIterator &other) const { return (this->p == other.p); };
			bool operator!=(const VectorIterator &other) const { return (this->p != other.p); };

			reference operator*() { return (*this->p); };
			const_reference operator*() const { return (*this->p); };

			pointer operator->() { return (this->p); };
			const_pointer operator->() const { return (this->p); };

			VectorIterator operator++(int) { this->p++; return (VectorIterator(this->p - 1)); };
			VectorIterator &operator++() { this->p++; return (*this); };
			VectorIterator operator--(int) { this->p--; return (VectorIterator(this->p + 1)); };
			VectorIterator &operator--() { this->p--; return (*this); };

			VectorIterator operator+(difference_type n) const { return (VectorIterator(this->p + n)); };
			VectorIterator operator-(difference_type n) const { return (VectorIterator(this->p - n)); };
			difference_type operator-(const VectorIterator &other) { return (this->p - other.p); };

			bool operator<(const VectorIterator &other) const { return (this->p < other.p); };
			bool operator>(const VectorIterator &other) const { return (this->p > other.p); };
			bool operator<=(const VectorIterator &other) const { return (this->p <= other.p); };
			bool operator>=(const VectorIterator &other) const { return (this->p >= other.p); };

			VectorIterator &operator+=(difference_type n) { this->p += n; return (*this); };
			VectorIterator &operator-=(difference_type n) { this->p -= n; return (*this); };

			reference operator[](difference_type n) { return (*(this->p + n)); };
			const_reference operator[](difference_type n) const { return (*(this->p + n)); };
	};

	template<class _Iterator>
	class reverse_iterator: public _Iterator
	{
		public:
			typedef typename _Iterator::value_type value_type;
			typedef typename _Iterator::difference_type difference_type;
			typedef typename _Iterator::pointer pointer;
			typedef typename _Iterator::const_pointer const_pointer;
			typedef typename _Iterator::reference reference;
			typedef typename _Iterator::const_reference const_reference;
		public:
			reverse_iterator() {};
			explicit reverse_iterator(pointer _p) { this->p = _p; };
			reverse_iterator(const reverse_iterator &other) { *this = other; };
			virtual ~reverse_iterator() {};

			reverse_iterator &operator=(const reverse_iterator &other) { this->p = other.p; return (*this); };

			reference operator*() { _Iterator tmp(this->p); return (*--tmp); };
			const_reference operator*() const { _Iterator tmp(this->p); return (*--tmp); };

			pointer operator->() { _Iterator tmp(this->p); return (*--tmp); };
			const_pointer operator->() const { _Iterator tmp(this->p); return (*--tmp); };

			reverse_iterator operator++(int) { this->p--; return (reverse_iterator(this->p + 1)); };
			reverse_iterator &operator++() { this->p--; return (*this); };
			reverse_iterator operator--(int) { this->p++; return (reverse_iterator(this->p - 1)); };
			reverse_iterator &operator--() { this->p++; return (*this); };

			reverse_iterator operator+(difference_type n) const { return (reverse_iterator(this->p - n)); };
			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(this->p + n)); };

			reverse_iterator &operator+=(difference_type n) { this->p -= n; return (*this); };
			reverse_iterator &operator-=(difference_type n) { this->p += n; return (*this); };

			reference operator[](difference_type n) { return (*(*this + n)); };
			const_reference operator[](difference_type n) const { return (*(*this + n)); };
	};

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::VectorIterator<value_type> iterator;
			typedef ft::VectorIterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
			typedef Alloc allocator_type;
		private:
			pointer container;
			size_type container_size;
			size_type _capacity;
			allocator_type alloc;
		public:
			explicit vector (const allocator_type& alloc = allocator_type()): container(NULL), container_size(0), _capacity(0), alloc(alloc) {
				this->container = this->alloc.allocate(0);
			};

			explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()):
			container(NULL), container_size(0), _capacity(0), alloc(alloc) {
				this->container = this->alloc.allocate(0);
				this->assign(n, val);
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
			container(NULL), container_size(0), _capacity(0), alloc(alloc) {
				this->container = this->alloc.allocate(0);
				this->assign(first, last);
			};
			
			vector (const vector& x): container(NULL), container_size(0), _capacity(0), alloc(x.alloc)  { *this = x; };

			~vector() {
				if (this->container)
					this->alloc.deallocate(this->container, this->container_size);
			};

			vector &operator=(const vector& x) {
				if (this->container)
					this->alloc.deallocate(this->container, this->container_size);
				this->alloc = x.alloc;
				this->container_size = 0;
				this->_capacity = 0;
				this->container = this->alloc.allocate(0);
				this->assign(x.begin(), x.end());
				return (*this);
			};

			// ITERATOR

			iterator begin() { return (iterator(this->container)); };
			const_iterator begin() const {return (const_iterator(this->container)); };

			iterator end() { return (iterator(this->container + this->container_size)); };
			const_iterator end() const { return (const_iterator(this->container + this->container_size)); };

			reverse_iterator rbegin() { return (reverse_iterator(this->container + this->container_size)); };
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->container + this->container_size)); };

			reverse_iterator rend() { return (reverse_iterator(this->container)); };
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->container)); };

			// CAPACITY

			size_type size() const { return (this->container_size); };
			size_type max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); };

			void resize (size_type n, value_type val = value_type()) {
				while (n > this->container_size)
					this->push_back(val);
				while (n < this->container_size)
					this->pop_back();

			};

			size_type capacity() const { return (this->_capacity); };
			bool empty() const {
				if (!this->container_size)
					return (1);
				return (0);
			};

			void reserve (size_type n) {
				if (n > this->_capacity)
				{
					pointer tmp;
					tmp = this->alloc.allocate(n);
					for (size_type i = 0; i < this->container_size; i++)
						tmp[i] = this->container[i];
					if (this->container)
						this->alloc.deallocate(this->container, this->_capacity);
					this->container = tmp;
					this->_capacity = n;
				}
			};

			// ELEMENT 
			
			reference operator[] (size_type n) { return (*(this->container + n)); };
			const_reference operator[] (size_type n) const { return (*(this->container + n)); };

			reference at (size_type n) {
				if (n >= this->container_size)
					throw "Erreur Out-of-Range";
				return (this->container[n]);
			};
			const_reference at (size_type n) const {
				if (n >= this->container_size)
					throw "Erreur Out-of-Range";
				return (this->container[n]);
			};

			reference front() { return (this->container[0]); };
			const_reference front() const { return (this->container[0]); };

			reference back() { return (this->container[this->container_size - 1]); };
			const_reference back() const { return (this->container[this->container_size - 1]); };

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

			void push_back (const value_type& val) {
				if (this->container_size + 1 > this->_capacity)
					this->reserve(this->_capacity ? this->_capacity * 2 : 1);
				this->container[this->container_size++] = val;
			};

			void pop_back() {
				if (this->container_size)
					this->container_size--;
			}

			iterator insert (iterator position, const value_type& val) {
				size_type i = 0;
				iterator it = begin();
				while (it + i != position && i < this->container_size)
					i++;
				if (this->container_size + 1 > this->_capacity)
					this->reserve(this->_capacity ? this->_capacity * 2 : 1);
				this->container_size++;
				size_type j = this->container_size - 1;
				while (j > i)
				{
					this->container[j] = this->container[j - 1];
					j--;
				}
				this->container[i] = val;
				return (iterator(&this->container[i]));
			};
    		void insert (iterator position, size_type n, const value_type& val) {
				while (n--)
					position = this->insert(position, val);
			};
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {
				while (first != last)
				{
					position = this->insert(position, *first) + 1;
					first++;
				}
			};

			iterator erase (iterator position) {
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
	};
}

#endif
