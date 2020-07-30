#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
	/// Constructs an m-ary heap for any m >= 2
	Heap(int m, PComparator c = PComparator());

	/// Destructor as needed
	~Heap();

	/// Adds an item
	void push(const T& item);

	/// returns the element at the top of the heap 
	///  max (if max-heap) or min (if min-heap)
	T const & top() const;

	/// Removes the top element
	void pop();

	/// returns true if the heap is empty
	bool empty() const;

private:
	/// Add whatever helper functions and data members you need below

	std::vector<T> nodes;
	int m_num;
	PComparator comp;
	void swap(int index1, int index2);
	void trickle_up(int index);
	void trickle_down(int index);


};

// Add implementation of member functions here

//Constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
	this -> m_num = m;
	if(m_num < 2){
		throw std::invalid_argument("m < 2");
	}
	this -> comp = c;
}

//Destructor
//Nothing is dynamically allocated so nothing
//is needed in destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}

//Push Function
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
	nodes.push_back(item);
	trickle_up(nodes.size()-1);
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const{
	// Here we use exceptions to handle the case of trying
	// to access the top element of an empty heap
	if(empty()){
		throw std::logic_error("can't top an empty heap");
	}
	// If we get here we know the heap has at least 1 item
	// Add code to return the top element
	return nodes[0];
}


// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop(){
	if(empty()){
		throw std::logic_error("can't pop an empty heap");
	}
	nodes[0]=nodes[nodes.size()-1];
	nodes.pop_back();
	trickle_down(0);
}

//Empty Function
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
	return nodes.empty();
}

//Swap Function
template <typename T, typename PComparator>
void Heap<T,PComparator>::swap(int index1, int index2){
	T temp = nodes[index1];
	nodes[index1] = nodes[index2];
	nodes[index2] = temp;

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickle_up(int index){

	if(index == 0){
		return;
	}
	int temp_index = index;
	int parent = (temp_index-1)/m_num;
	if(parent >= 0 && comp(nodes[temp_index],nodes[parent])){
		swap(temp_index,parent);
		trickle_up(parent);
	}
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::trickle_down(int index){

	//if vector is size 0 or 1
	if(nodes.size() == 0 || nodes.size() == 1){
		return;
	}

	//find all valid child nodes
	std::vector<int> child_nodes;
	for(int i = 0; i < m_num; i++){
		int temp = m_num*index + (i+1);
		if(temp < int(nodes.size())){
			child_nodes.push_back(temp);
		}
		else{
			break;
		}
	}

	//if index is a leaf node
	if(child_nodes.empty() == true){
		return;
	}

	//find smallest child nodes
	int smallest_index;
	if(child_nodes.size()==1){
		smallest_index = child_nodes[0];
	}
	else{
		smallest_index = child_nodes[0];
		for(size_t i = 1; i < child_nodes.size(); i++){
			if(comp(nodes[child_nodes[i]],nodes[smallest_index])){
				smallest_index = child_nodes[i];
			}
		}
	}

	//now smallest_index should have the index of the
	//smallest_index of the current node

	//if the smallest index is not node
 	if(comp(nodes[smallest_index],nodes[index])){
 		swap(smallest_index, index);
 		trickle_down(smallest_index);
 	}
}

#endif