// list::pop_back
#include <iostream>
#include "../../../include/list.hpp"

int main ()
{
 ft::list<int> mylist;
 int sum (0);
 mylist.push_back (100);
 mylist.push_back (200);
 mylist.push_back (300);

 while (!mylist.empty())
 {
 sum+=mylist.back();
 mylist.pop_back();
 }

 std::cout << "The elements of mylist summed " << sum << '\n';

 return 0;
}