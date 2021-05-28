/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebiscara <ebiscara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:36:21 by ebiscara          #+#    #+#             */
/*   Updated: 2021/05/28 13:36:21 by ebiscara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include <limits>
# include <cstdlib>
# include <deque>
# include "vector.hpp"

namespace ft
{
    template <class T, class Container = vactor<T> >
	class stack
	{
        private:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;
        protected:
            container_type ct;
        public:
            explicit stack (const container_type& ctnr = container_type()): ct(ctnr) {};
            stack (const stack &x) { *this = x; };
            ~stack() {};
            stack::operator=(const stack &x) { this->ct = x.ct; return (*this); };

            bool empty() const {
                return (this->ct.empty());
            };
            size_type size() const {
                return (this->ct.size());
            };
            value_type& top() {
                return (this->ct.back());
            };
            const value_type& top() const {
                return (this->ct.back());
            };
            void push (const value_type& val) {
                this->ct.push_back(val);
            };
            void pop() {
                this->ct.pop_back();
            };
    };
    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.ct == rhs.ct);
    };
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.ct != rhs.ct);
    };
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.ct < rhs.ct);
    };
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.ct <= rhs.ct);
    };
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.ct > rhs.ct);
    };
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.ct >= rhs.ct);
    };
}

#endif
