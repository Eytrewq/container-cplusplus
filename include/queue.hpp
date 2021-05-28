/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:58:50 by ebiscara          #+#    #+#             */
/*   Updated: 2021/05/28 13:58:50 by ebiscara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <memory>
# include <limits>
# include <cstdlib>
# include <deque>
# include "list.hpp"

namespace ft
{
    template <class T, class Container = list<T> >
	class queue
	{
        private:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;
        protected:
            container_type ct;
        public:
            explicit queue (const container_type& ctnr = container_type()): ct(ctnr) {};
            queue (const queue &x) { *this = x; };
            ~queue() {};
            queue::operator=(const queue &x) { this->ct = x.ct; return (*this); };

            bool empty() const {
                return (this->ct.empty());
            };
            size_type size() const {
                return (this->ct.size());
            };
            void push (const value_type& val) {
                this->ct.push_back(val);
            };
            void pop() {
                this->ct.pop_back();
            };
            value_type& front() {
                return (this->ct.front());
            };
            const value_type& front() const {
                return (this->ct.front());
            };
            value_type& back() {
                return (this->ct.back());
            };
            const value_type& back() const {
                return (this->ct.back());
            };
    };
    template <class T, class Container>
    bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return (lhs.ct == rhs.ct);
    };
    template <class T, class Container>
    bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return (lhs.ct != rhs.ct);
    };
    template <class T, class Container>
    bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs){
        return (lhs.ct < rhs.ct);
    };
    template <class T, class Container>
    bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return (lhs.ct <= rhs.ct);
    };
    template <class T, class Container>
    bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return (lhs.ct > rhs.ct);
    };
    template <class T, class Container>
    bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return (lhs.ct >= rhs.ct);
    };
}

#endif
