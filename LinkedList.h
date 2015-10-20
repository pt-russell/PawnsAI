#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T> class LinkedList;
template<class T> class Link;

// LIST CLASS

template<class T>
class LinkedList
{
private :

	Link<T>* head;
	Link<T>* tail;

	// Copy constructor / operator= not currently in use

	LinkedList<T>(const LinkedList<T>&);
	const LinkedList<T>& operator= (const LinkedList<T>&);

public :

	// Constructors + destructor
	LinkedList<T>(const Link<T>&, const Link<T>&);
	LinkedList<T>();
	~LinkedList<T>();

	// Getters
	Link<T>* GetHead() const;
	Link<T>* GetTail() const;

	// Methods
	void AppendLink(Link<T>&);
	void Reset();
};

// CONSTRUCTORS

template<class T> LinkedList<T>::LinkedList(const Link<T>& start, const Link<T>& end)
{
	head = &start;
	tail = &end;
}

template<class T> LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template <class T> LinkedList<T>::~LinkedList()
{

}

// GETTERS

template<class T> Link<T>* LinkedList<T>::GetHead() const
{
	return head;
}

template<class T> Link<T>* LinkedList<T>::GetTail() const
{
	return tail;
}

// METHODS

template<class T> void LinkedList<T>::AppendLink(Link<T>& link)
{
	if (head == NULL)
	{
		head = &link;
	}

	else
	{
		tail->SetNext(link);
	}

	tail = &link;
}

template <class T> void LinkedList<T>::Reset()
{
	head = tail = NULL;
}

// LINK CLASS

template<class T>
class Link
{
private :

	T data;
	Link<T>* next;

	// Copy constructor / operator= not currently in use
	
	Link<T>(const Link<T>&);
	const Link<T>& operator= (const Link<T>&);

public :

	// Constructors + destructor
	Link<T>(const T&);
	Link<T>();
	~Link<T>();

	// Getters
	T GetData() const;
	Link<T>* GetNext() const;

	// Setters
	void SetData(const T&);
	void SetNext(Link<T>&);
};

// CONSTRUCTORS

template <class T> Link<T>::Link(const T& x)
{
	data = x;
	next = NULL;
}

template <class T> Link<T>::Link()
{
	data = NULL;
	next = NULL;
}

template <class T> Link<T>::~Link()
{

}

// GETTERS

template <class T> T Link<T>::GetData() const
{
	return data;
}

template <class T> Link<T>* Link<T>::GetNext() const
{
	return next;
}

// SETTERS

template <class T> void Link<T>::SetData(const T& x)
{
	data = x;
}

template <class T> void Link<T>::SetNext(Link<T>& link)
{
	next = &link;
}

#endif
