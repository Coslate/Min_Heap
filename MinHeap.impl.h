#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <MinHeap.h>
#include <queue> 
#include <utility>
#include <math.h>

template <typename T>
void MinHeap<T>::SiftUp(const int &pos){
    int current_pos = pos;
    while(1){
        int parent_pos = floor((current_pos-1)/2.f);

        if((parent_pos >= 0) && (heap_arr_[parent_pos] > heap_arr_[current_pos])){
            SetMapPos(heap_arr_[parent_pos], current_pos);
            SetMapPos(heap_arr_[current_pos], parent_pos);
            CustSwap(heap_arr_[parent_pos], heap_arr_[current_pos]);
        }else{
            break;
        }

        current_pos = parent_pos;
    }
}

template <typename T>
void MinHeap<T>::SiftDown(const int &pos){
    int current_pos = pos;
    while(1){
//        std::cout<<"current_pos = "<<current_pos<<std::endl;
//        char c = getchar();

        int left_child  = current_pos*2 + 1;
        int right_child = current_pos*2 + 2;
        int smaller_child = -1;

        if((left_child <= (size_of_heap_ - 1)) && (right_child <= (size_of_heap_ - 1))){
            smaller_child = (heap_arr_[left_child] > heap_arr_[right_child]) ? right_child : left_child;
        }else if((left_child > (size_of_heap_ - 1)) && (right_child <= (size_of_heap_ - 1))){
            smaller_child = right_child;
        }else if((left_child <= (size_of_heap_ - 1)) && (right_child > (size_of_heap_ - 1))){
            smaller_child = left_child;
        }else{//no children
            break;
        }

        if(heap_arr_[current_pos] > heap_arr_[smaller_child]){
            SetMapPos(heap_arr_[smaller_child], current_pos);
            SetMapPos(heap_arr_[current_pos], smaller_child);
            CustSwap(heap_arr_[smaller_child], heap_arr_[current_pos]);
            current_pos = smaller_child;
        }else{
            break;
        }
    }
}

template <typename T>
void MinHeap<T>::Resize(const int &new_cap_size){
    T* new_heap_arr_ = new T [new_cap_size]();

    for(int i=0;i<size_of_heap_;++i){
        new_heap_arr_[i] = heap_arr_[i];
    }

    delete [] heap_arr_;
    heap_arr_ = new_heap_arr_;
    cap_of_heap_ = new_cap_size;

    if(is_debug){
        std::cout<<"Resize new_cap_size = "<<new_cap_size<<std::endl;
        PrintContent();
        std::cout<<"---------"<<std::endl;
    }
}

template <typename T>
void MinHeap<T>::Insert(const T &data){
    int size_of_heap_tmp = size_of_heap_ + 1;
    if(size_of_heap_tmp > cap_of_heap_){
        if(cap_of_heap_ == 0){
            Resize(1);
        }else{
            Resize(2*cap_of_heap_);
        }
    }

    heap_arr_[size_of_heap_] = data;
    SetMapPos(heap_arr_[size_of_heap_], size_of_heap_);
    size_of_heap_ = size_of_heap_tmp;
    SiftUp(size_of_heap_-1);
}

template <typename T>
T MinHeap<T>::ExtractMin(){
    if(size_of_heap_ <= 0){
        throw std::runtime_error(std::string("Error in ExtractMin(): size_of_heap_ <= 0."));
        exit(0);
    }

    T ret_data = heap_arr_[0];
    DeletePosFromMap(heap_arr_[0]);
    heap_arr_[0] = heap_arr_[size_of_heap_-1];
    SetMapPos(heap_arr_[0], 0);
    --size_of_heap_;
    SiftDown(0);

    if(size_of_heap_ == 0){
        delete [] heap_arr_;
        heap_arr_ = nullptr;
        cap_of_heap_ = 0;
    }

    if(is_debug){
        std::cout<<"ExtractMin size_of_heap_ = "<<size_of_heap_<<", ret_data = "<<ret_data<<std::endl;
        PrintContent();
        std::cout<<"---------"<<std::endl;
    }

    return ret_data;
}

template <typename T>
void MinHeap<T>::DecreaseKey(const std::string &key_name, const int &key_val){
    if(size_of_heap_ <= 0){
        std::cout<<"----->Warning: DecreaseKey(): size_of_heap_ <= 0."<<std::endl;
        return;
    }

    if(map_str2pos_.find(key_name) == map_str2pos_.end()){//not found
        std::cout<<"----->Warning: DecreaseKey(): key_name not found in map_str2pos_."<<std::endl;
        return;
    }

    int pos = map_str2pos_[key_name];
    if(heap_arr_[pos] < key_val){
        std::cout<<"----->Warning: DecreaseKey(): key_val is larger than the original value in heap."<<std::endl;
        return;
    }else if(heap_arr_[pos] == key_val){
        //no need to do anything
        return;
    }

    heap_arr_[pos] = key_val;
    SiftUp(pos);

    if(is_debug){
        std::cout<<"DecreaseKey(), size_of_heap_ = "<<size_of_heap_<<std::endl;
        PrintContent();
        std::cout<<"---------"<<std::endl;
    }
}
