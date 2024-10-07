#include <iostream>

using namespace std;

class ContiguousSequence {
    public:


        ContiguousSequence(int x) { //Constructor with an integer parameter
            _end = 3;
            elements[3] = x;
        }

        ContiguousSequence(ContiguousSequence &c) { //Copy Constructor
            int counter = 0;
            this->_start = c._start;
            this->_end = c._end;
            while (counter < this->basicSize()) {
                elements[counter] = c.elements[counter];
            }

        }

        ~ContiguousSequence() { //Destructs the array
            delete[] elements;
        }

        int basicSize(){ //returns the total size of the allocated array
            return (sizeof(elements)/sizeof(int));
        }

        int size(){ //returns only the number of elements stored in the array
            return (_end - _start + 1);
        }

        int operator[](int i){
            int ithElement = _start + i; //adds _start to i so that integers would correspond to _start despite what they are
            if (ithElement > _end) {
                printf("out of bounds");
                return -1; //returns a default value when out of bounds is caught
            }
            return elements[ithElement];
        }

        int* insertAt(int i, int x){ //insert integer x and position i
            int counter = 0;
            if (this->size() == this->basicSize()) {
                grow(); // Implement later
            }
            else
            {
                if (_start > 0) { // Shifts values to the left by changing the _start
                    _start = _start - 1;
                    counter = _start;
                    while(counter < i) { //Shifts all values before the index to insert at back one
                        elements[counter] = elements[counter + 1];
                        counter++;
                    }
                    elements[_start + i] = x; //takes into account what _start is and sets the logical position to the physical one
                }
                else if(_end < this->basicSize()) {
                    _end = _end + 1;
                    counter = _end;
                    while(counter >= i+1) { // Shifts values up to and including i to the right || 1 is added to account for the physical value being one higher that the logical
                        elements[counter] = elements[counter - 1];
                        counter--;
                    }
                    elements[_start + 1] = x; //takes into account what _start is and sets the logical position to the physical one
                }
                return this->elements;

            }
        }

        int find(int i) { //find the index of the specified 'i' element
            for (int k = _start; k < _end; ++k) {
                if (elements[k] == i) { //If the element is found within the receiver it returns the index position
                    return k - _start; //Index position is (k - _start) in order to go from physical memory to logical for the user
                }
            }
            return -1; //If the for loop above can't find the looked for value 'i', it will return -1
        }

        int* removeAt(int i) { //remove the element at index i
            int deleteIth = _start + i;
            if(i > _end || i < _start) { //If i is out of bounds, it would do nothing to the receiver and return it
                return elements;
            }

            elements[i] = NULL;
            for (int count = i; count < _end; ++count) { //starts at the deleted position and increments to the right, shifting all values already within the array to the left
                elements[count] = elements[count + 1];
            }
            return elements;

        }

        int* iterate(int *fn (int)) {
            for (int i = this->_start; i <= this->_end; ++i) { //begins at the start of the receiver and iterate through to the end of it apply fn to all stored values
                elements[i] = *fn(elements[i]);
            }
            return elements;
        }

        void operator=(const ContiguousSequence &c) { //Assignment operator
            int counter = 0;
            this->_start = c._start;
            this->_end = c._end;
            while (counter < this->basicSize()) {
                elements[counter] = c.elements[counter];
            }
        }

    private:

        int *elements = new int[8];
        int _start = 3;
        int _end = 2;

       int* grow() {
            int newSize = this->basicSize() * 2;
            int *newArray = new int[newSize];
            for (int i = 0; i < this->basicSize(); ++i) {
                newArray[i] = elements[i];
            }

            elements = newArray;
            return elements;
        }

};


int main() {
    return 0;
}
