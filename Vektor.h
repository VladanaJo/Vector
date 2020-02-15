#include<iostream>
#include<stdexcept>
#include<initializer_list>

using namespace std;

const size_t initial_size=4;   // initial vector size



class Vector{
  size_t sz;       //current size of array
  size_t max_sz;   // capacity of array
  double* values;  // dynamic value that gets saved into the array

  public:
     Vector():Vector(initial_size){};  // Constructor that takes no values, gets defaulted to size 4

     Vector(size_t newsz):sz{0}{    //Constructor for given value
      if(newsz < initial_size)      //to prevent the initial
        newsz = initial_size;
       values= new double[newsz];    // makes an array oftype double that can fit newsz amount of elements
       max_sz=newsz;                 // sets the max capacity to the new size
}
//-----------------------------------------------------
Vector(initializer_list<double> li):Vector(li.size()){  // Constructor if given an initializer list
      for(auto& elem : li)                              //adds or copies the elements from the initializer list to the new array
        push_back(elem);
}

//------------------------------------------------------

Vector(const Vector& copy):Vector(copy.size()){  // Constructor to copy an array
      for(size_t i=0; i < copy.size(); i++)      // goes trough all elements of the parameter array and adds them
         push_back(copy[i]);                     // to the new one
}

//------------------------------------------------------

~Vector(){
    delete[] values;    //
    }

//---------------------------------------------------------


void push_back(double value){
     if(sz==max_sz)
       reserve(sz*2);
     values[sz++]=value;
}

//----------------------------------------------------------
 void shrink_to_fit() {
     double* neu=new double[sz];
     for(size_t i=0; i<sz; i++)
        neu[i] = values[i];
     delete [] values;
     values = neu;
 }
//----------------------------------------------------------
void reserve(size_t newsz){                // copies the values into a temp array that has a new size
     double* zwischen = new double[newsz];
     for(size_t i=0; i < sz; ++i)          // loop that saves the values of old array into temp array
        zwischen[i]=values[i];

delete[] values;     // deletes the old array
values = zwischen;   // sets value equal to the temp array
max_sz = newsz;      // the new capacity size gets set to the given size
}

//----------------------------------------------------------

double& operator[](size_t index){
        if( index < 0 || index >= sz)
          throw runtime_error("Out of bounds");
        return values[index];
}


Vector& operator= (Vector src) {
        swap(max_sz, src.max_sz);
        swap(sz, src.sz);
        swap(values, src.values);
        return *this;
    }

//-----------------------------------------------------

const double& operator[](size_t index)const{
        if( index < 0 || index >= sz)
          throw runtime_error("Out of bounds");
        return values[index];
}
//------------------------------------------------------

size_t size() const{
    return sz;
    }

//-------------------------------------------------------

bool empty() const{
    return sz == 0;
    }

//-------------------------------------------------------

void clear() {
    sz = 0;
    }

//--------------------------------------------------------

void pop_back(){
     if(sz==0)
       return;
     --sz;
}

};
