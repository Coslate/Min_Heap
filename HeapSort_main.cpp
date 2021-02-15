#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <math.h>
#include <MinHeap.h>

void PrintArray(const int size, const int* arr, const std::string arr_name){
    std::cout<<arr_name<<" = [";
    for(int i=0;i<size;++i){
        if(i == 0){
            std::cout<<arr[i];
        }else if(i == size - 1){
            std::cout<<", "<<arr[i]<<"]"<<std::endl; 
        }else{
            std::cout<<", "<<arr[i];
        }
    }
}

void MoveArray(const int* from_arr, int* to_arr, const int to_size, const int to_begin_index, const int from_begin_index){
    int index = to_begin_index;
    for(int i=from_begin_index; i<from_begin_index+to_size; ++i){
        to_arr[index] = from_arr[i];
        ++index;
    }
}

int main(){
    const int n = 10;
    int *test_arr = new int[n]();
    int *ans_arr  = new int[n]();
    MinHeap<int> heap_a;
    MinHeap<int>::is_debug = false;
    const bool max_to_min = false;

    std::cout<<"---test_arr initialize---"<<std::endl;
    //initialize random seed
    srand(time(NULL));

    std::cout<<"---before HeapSort---"<<std::endl;
    for(int i=0;i<n;++i){
        test_arr[i] = rand()%10000+1;
        if(max_to_min){
            heap_a.Insert(-1*test_arr[i]);
        }else{
            heap_a.Insert(test_arr[i]);
        }
    }

    PrintArray(n, test_arr, "test_arr");
    if(MinHeap<int>::is_debug){
        heap_a.PrintContent();
    }

    for(int i=0;i<n;++i){
        if(max_to_min){
            ans_arr[i] = -1*heap_a.ExtractMin();
        }else{
            ans_arr[i] = heap_a.ExtractMin();
        }
    }

    std::cout<<"---after HeapSort---"<<std::endl;
    PrintArray(n, ans_arr, "ans_arr");

    return EXIT_SUCCESS;
}
