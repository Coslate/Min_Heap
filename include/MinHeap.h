#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unordered_map>

template <typename T>
class MinHeap{
    private:
        T*    heap_arr_;
        int   size_of_heap_;
        int   cap_of_heap_;

        void SiftDown(const int &pos);
        void SiftUp(const int &pos);
        bool IsLess(const T &x, const T &y){ return (x<y); }
        bool IsLess(const std::string &x, const std::string &y){ return (x.compare(y) < 0); }
        void Resize(const T &new_cap_size);

    public:
        MinHeap() : heap_arr_(nullptr), size_of_heap_(0), cap_of_heap_(0) {}
        MinHeap(const int &num_size) : cap_of_heap_(num_size), size_of_heap_(0) {
            heap_arr_ = new T [num_size]();
        }
        ~MinHeap(){
            while(size_of_heap_ > 0){
                ExtractMin();
            }
        }

        static bool is_debug;
        int   GetSize()    {return size_of_heap_;}

        // Returns a reference to the actual top data item in the list.
        // This can be used to directly change the data in that node.
        // You must make sure that the list is not empty before you call this.
        T& top(){
            if (size_of_heap_ == 0) {
            throw std::runtime_error("top() called on empty MinHeap");
            } else {
                return heap_arr_[0];
            }
        }

        // This version of top() is overloaded to be compatible with
        // const instances of this LinkedList type.
        // For example, when you pass a LinkedList<int> by reference to a function
        // that takes an argument of type const LinkedList<int>&, then within that
        // function, the list is treated as const, and this version of top() must
        // exist or top() cannot be called on the object.
        // Please also see the note below in this file about "const correctness".
        const T& top() const {
            if (size_of_heap_ == 0) {
                throw std::runtime_error("top() called on empty MinHeap");
            } else {
                return heap_arr_[0];
            }
        }

        void Insert(const T &data);
        const T ExtractMin();

        //For debug
        void PrintContent(){
            for(int i=0;i<size_of_heap_;++i){
                if((i == 0) && (size_of_heap_ == 1)){
                    std::cout<<"In Heap, heap_arr_ = ["<<heap_arr_[i]<<"]"<<std::endl;
                }else if(i==0){
                    std::cout<<"In Heap, heap_arr_ = ["<<heap_arr_[i]<<", ";
                }else if(i == size_of_heap_ - 1){
                    std::cout<<heap_arr_[i]<<"]"<<std::endl;
                }else{
                    std::cout<<heap_arr_[i]<<", ";
                }
            }
        }
};

template <typename T>
bool MinHeap<T>::is_debug = false;

#include <MinHeap.impl.h>
#endif
