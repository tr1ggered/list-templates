#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace rut::miit
{
	template <typename T>
	class SingleList
	{
	public:
		/**
		*@brief �������������� ����� SingleList.
		*/
		SingleList();

		/**
		*@brief ���������� ������ SingleList.
		*/
		~SingleList();

		/**
		*@brief �������� ������ ������ SingleList.
		*@param ������ ����, ������� ����� ����������.
		*/
		//����������� �����������
		SingleList(const SingleList& second);

		/**
		*@brief ���������� ������ ������ SingleList � ������ �����.
		*@param ������ ����, ������� ����� ���������.
		*/
		//����������� �����������
		SingleList(SingleList&& second) noexcept;

		/**
		@brief �������, ������� ������� Node(��������� �� ���� ��-�) ����� �������.
		*/
		void popFront();

		/**
		*@brief ������� ��� Node.
		*/
		void clear();

		/**
		*@brief ������� ������� ��������� Node � ����� ������.
		*@param ������ ������� ����� ���������.
		*/
		void pushBack(T data);

		/**
		*@brief ������� ������� ��������� Node ����� �������.
		*@param ������ ������� ����� ���������.
		*/
		void pushFront(T data);

		/**
		*@brief ������� ������� ���������� ������ �����.
		*@return ������ ������.
		*/
		size_t getSize() const noexcept;

		/**
		*@brief �������, ������������� �������� [].
		*@param ����������� ����� ��������.
		*@return �������� � �������� ��������.
		*/
		T& operator[](int index);

		/**
		*@brief �������, ������� ��������� ������ ���������.
		*@return �������� true, ���� ��������� �������, �������� false, ���� ��������� �� �������.
		*/
		bool isEmpty() const noexcept;

		/**
		*@brief �������, ������� ����������� ��������� � ������.
		*@return ������, ��������� �� Nodes.
		*/
		std::string toString();

		/**
		*@brief �������, ������������� �������� ==.
		*@param ������ ������, ������� ����� ����������.
		*@return ����� ������������� ������.
		*/
		//�������� ����������
		SingleList<T>& operator=(const SingleList<T>& second);

		/**
		*@brief �������, ������������� �������� ==.
		*@param ������ ������, ������� ����� ���������.
		*@return ������������ ������.
		*/
		//�����������
		SingleList<T>& operator=(SingleList<T>&& second) noexcept;

		/**
		*@brief �������, ������������� �������� ���������.
		*@param ���������� ������ ������.
		*@return ���� ���������� ������ ����� ������� ������ �� �������� true � � ��������� ������ �������� false.
		*/
		//�������� ���������
		bool operator==(SingleList<T>& second);

	private:
		template<typename T>
		struct Node
		{
			Node(T& data, Node<T>* pNext = nullptr)
				: data(data), pNext(pNext)
			{}

			Node<T>* pNext;
			T data;
		};
		size_t size;
		Node<T>* h;
	};
	//����������� �� ���������
	template <typename T>
	SingleList<T>::SingleList()
		:h(nullptr), size(0)
	{
	}

	template <typename T>
	void SingleList<T>::pushBack(T data)
	{
		if (h == nullptr)
		{
			h = new Node(data);
		}
		else
		{
			Node<T>* current = h;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = new Node(data);
		}
		this->size++;
	}

	template <typename T>
	void SingleList<T>::pushFront(T data)
	{
		h = new Node<T>(data, h);
		this->size++;
	}

	template <typename T>
	size_t SingleList<T>::getSize() const noexcept
	{
		return this->size;
	}

	template <typename T>
	T& SingleList<T>::operator[](int index)
	{
		int counter = 0;
		Node<T>* current = this->h;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}

	template <typename T>
	bool SingleList<T>::isEmpty() const noexcept
	{
		return this->size == 0;
	}

	template <typename T>
	std::string SingleList<T>::toString()
	{
		std::stringstream buffer;
		if (h != nullptr)
		{
			Node<T>* current = h;
			for (size_t i = 0; i < size; i++)
			{
				buffer << current->data << ' ';
				current = current->pNext;
			}
		}
		return buffer.str();
	}

	template <typename T>
	void SingleList<T>::popFront()
	{
		if (h != nullptr)
		{
			Node<T>* temp = h;
			h = h->pNext;
			this->size--;
			delete temp;
		}
	}

	template <typename T>
	void SingleList<T>::clear()
	{
		while (size)
		{
			popFront();
		}
	}

	template <typename T>
	SingleList<T>::~SingleList()
	{
		clear();
	}

	template <typename T>
	SingleList<T>::SingleList(SingleList&& second) noexcept
	{
		std::swap(this->h, second.h);
	}

	template <typename T>
	bool SingleList<T>::operator==(SingleList<T>& second)
	{
		return(this->toString() == second.toString());
	}
	//����������
	template <typename T>
	SingleList<T>& SingleList<T>::operator=(const SingleList<T>& second)
	{
		if (this->h == nullptr)
		{
			for (Node<T>* node = second.h; node != nullptr; node = node->pNext)
			{
				this->pushBack(node->data);
			}
		}
		return *this;
	}
	//���������
	template <typename T>
	SingleList<T>& SingleList<T>::operator=(SingleList<T>&& second) noexcept
	{
		std::swap(this->h, second.h);
		return *this;
	}
	//�����������
	template <typename T>
	SingleList<T>::SingleList(const SingleList<T>& second)
		:SingleList<T>()
	{
		if (this->h == nullptr)
		{
			for (Node<T>* node = second.h; node != nullptr; node = node->pNext)
			{
				this->pushBack(node->data);
			}
		}
	}
}