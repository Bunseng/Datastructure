// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet() //completed
{
   used = 0; //initialize used to 0
}

int IntSet::size() const //completed
{
   return used; //return the size of current set
}


bool IntSet::isEmpty() const //completed
{
   if(used == 0) //return true if set = empty, false otherwise
        return true;
    else
        return false;
}

bool IntSet::contains(int anInt) const //completed
{
   int counter;

   if(used == 0)
        return false;

   counter = 0;
   while(counter < used){
        if(data[counter] == anInt)
            return true;
        counter++; //update counter
   }
   return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const  //complete
{
   int counter;

   for(counter = 0; counter < used; counter++){
        if(otherIntSet.contains(data[counter]) == 0){
            return false;
        }
   }
   return true;
}

void IntSet::DumpData(ostream& out) const //given
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int counter = 1; counter < used; ++counter)
         out << "  " << data[counter];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const //completed
{
    int setSize; //set size for the set
    int counter;
    IntSet newOtherIntSet;
    newOtherIntSet = otherIntSet; //set otherIntSet to a new one

    assert(size() + (newOtherIntSet.subtract(*this)).size() <= MAX_SIZE);
    setSize = size() + (newOtherIntSet.subtract(*this)).size();

    for(counter = 0; counter < setSize; counter++)
    {
        if(!newOtherIntSet.contains(data[counter]) && this->contains(data[counter]))
           newOtherIntSet.add(data[counter]);
    }
    return newOtherIntSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet newOtherIntSet;
   int setSize, counter = 0;

   if(this->size() > newOtherIntSet.size())
       setSize  = this->size();
   else
       setSize = otherIntSet.size();

   while(counter < setSize)
   {
        if(otherIntSet.contains(data[counter]) && this->contains(data[counter]))
	      newOtherIntSet.add(data[counter]);
	      counter++;
   }
   return newOtherIntSet;

  /* int min_size, counter;
   IntSet one, two;
   min_size = (MAX_SIZE <= otherIntSet.MAX_SIZE) ? MAX_SIZE : otherIntSet.MAX_SIZE;

   for (counter = 0; counter < min_size; counter++)
   {
       if(data[counter] && otherIntSet.data[counter])
            return two;
   }
   return one; */
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const //completed
{
   IntSet sub;
   int counter;


   counter = 0;
   while(counter < this->size()){
        if(!otherIntSet.contains(data[counter]))
            sub.add(data[counter]);
        counter++;//update the counter
   }
   return sub;
}

void IntSet::reset() //completed
{
   int counter;

   counter = 0;
   while(counter < used){
        data[counter] = 0;
        counter++; //update counter
   }
   used = 0;
}

bool IntSet::add(int anInt)//completed
{
    assert(contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE);

    if(contains(anInt) == 0) //if the element isn't in the set
    {
        data[used] = anInt; //add the element to current set
        used++; //increased used by 1
        return true;
    }
    return false;
}

bool IntSet::remove(int anInt)//need work
{
  /* int counter0 = 0, counter1 = 0;


   if(contains(anInt)){
        while(counter0 < used){
            //counter0++;
                if(data[counter1] == anInt){
                    while(counter1 < used){
                        data[counter1] = data[counter1 + 1];
                        counter1++;
                    }
                      counter0++;
                }
        }
        used--;
        return true;
   }
   else
        return false;  */

    bool flag = false; //set flag to false

    if(contains(anInt)== 0) //if the element is not in the set
        return false;

    for(int counter = 0; counter < used; counter++)
    {
        if(data[counter] == anInt) //if that element = passed element
            flag = true; //flag it true

        if(flag == true && counter != used-1) //if found and not at end-set
            data[counter] = data[counter+1]; //copy the next element to prev. positon
    }
    used--; //decrement used by 1
    return true;
}

bool equal(const IntSet& is1, const IntSet& is2)
{
   if(is1.isSubsetOf(is2) && is2.isSubsetOf(is1)) //if first set is subset of second, and vice versa
        return true;
   else
        return false;
}
