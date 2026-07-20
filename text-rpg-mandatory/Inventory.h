#ifndef Inventory_H_
#define Inventory_H_

#include <iostream>
#include <algorithm>

using namespace std;


struct Item
{
	string name;
	int price;
	void PrintInfo() const
	{
		cout << name << " (" << price << "G)" << endl;
	}
};


template <typename T>
class Inventory
{
private:
	T* pItem;
	int capacity;
	int size;

public:
	Inventory(int capacity_ = 0, int size_ = 0) : capacity(capacity_), size(size_)
	{
		pItem = new T[capacity_];
	}

	Inventory(const Inventory& other) : capacity(other.capacity), size(other.size)
	{
		pItem = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			pItem[i] = other.pItem[i];
		}
	}

	T& operator[](int index) { return pItem[index]; }
	const T& operator[](int index) const { return pItem[index]; }
	Inventory& operator=(const Inventory& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] pItem;

		capacity = other.capacity;
		size = other.size;
		pItem = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			pItem[i] = other.pItem[i];
		}

		return *this;
	}

	~Inventory()
	{
		delete[] pItem;
	}

	int getCapacity() const { return capacity; }
	int getSize() const { return size; }

	static bool compareByPrice(const Item& a, const Item& b)
	{
		return a.price < b.price;
	}

	void SrotItems()
	{
		sort(pItem, pItem + size, compareByPrice);
	}

	void Resize(int newCapacity)
	{
		T* newInven = new T[newCapacity];
		for (int i = 0; i < size; i++)
		{
			newInven[i] = pItem[i];
		}
		delete[] pItem;

		pItem = newInven;
		capacity = newCapacity;
	}

	void AddItem(const T& item)
	{
		if (size >= capacity)
		{
			int newCapacity = capacity * 2;

			cout << endl;
			cout << "아이템 추가 시도... (현재 " << size << "/" << capacity << ")" << endl;
			cout << "-> 인벤토리 자동 확장! (" << capacity << " -> " << newCapacity << ")" << endl;
			Resize(newCapacity);
			cout << "-> 아이템 추가 완료" << endl;
		}
			pItem[size] = item;
			size++;
			SrotItems();
			cout << endl;
	}

	void RemoveLastItem()
	{
		if (size <= 0)
		{
			cout << "삭제할 아이템이 존재하지 않습니다." << endl;
			return;
		}

		size--;

		cout << endl;
	}

	void PrintAllItems()
	{
		if (size == 0)
		{
			cout << "인벤토리에 아이템이 존재하지 않습니다." << endl;
			return;
		}

		cout << "=== [ 인벤토리 ] ===" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << ". ";
			pItem[i].PrintInfo();
		}

		cout << endl;
	}

	void RemoveItem(int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "잘못된 인덱스입니다." << endl;
			return;
		}

		for (int i = index; i < size - 1; i++)
		{
			pItem[i] = pItem[i + 1];

		}
		size--;
	}
	
};

#endif