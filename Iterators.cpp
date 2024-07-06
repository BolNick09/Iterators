#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray 
{
private:
	T* data;
	size_t capacity;
	size_t size;
	void resize(size_t newCapacity) 
	{
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < size; ++i) 
			newData[i] = data[i];
		
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}
public:
	DynamicArray() : data(nullptr), capacity(0), size(0) {}
	~DynamicArray() 
	{
		delete[] data;
	}

	void push_back(const T& value) 
	{
		if (size == capacity) 		
			resize(capacity == 0 ? 1 : capacity * 2);
		
		data[size++] = value;
	}
	void pop_back() 
	{
		if (size == 0) 
			throw std::out_of_range("Array is empty");
		
		--size;
	}
	T& operator[](size_t index) 
	{
		if (index >= size) 
			throw std::out_of_range("Index out of range");
		
		return data[index];
	}
	const T& operator[](size_t index) const 
	{
		if (index >= size) 
			throw std::out_of_range("Index out of range");
		
		return data[index];
	}
	size_t getSize() const 
	{
		return size;
	}

	class Iterator 
	{
	private:
		DynamicArray& array;
		size_t index;

	public:
		Iterator(DynamicArray& array, size_t index) : array(array), index(index) {}


		T& operator*() 
		{
			return array[index];
		}

		Iterator& operator++() 
		{
			++index;
			return *this;
		}

		bool operator!=(const Iterator& other) const 
		{
			return index != other.index;
		}


	};
	Iterator begin() 
	{
		return Iterator(*this, 0);
	}

	Iterator end() 
	{
		return Iterator(*this, size);
	}

};

int main() 
{
	DynamicArray<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	std::cout << "Print by foreach" << std::endl;
	for (auto& element : arr) 	
		std::cout << element << " ";
	
	std::cout << std::endl;
	std::cout << "Print by iterator" << std::endl;

	for (DynamicArray<int>::Iterator it = arr.begin(); it != arr.end(); ++it)
	
		std::cout << *it << " ";
	
	std::cout << std::endl;

	return 0;
}