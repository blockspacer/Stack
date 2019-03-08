#ifndef  _TEMPLATE_STACK
#define  _TEMPLATE_STACK

#include <deque>

template<typename T, 
			template<typename Elem, typename = std::allocator<Elem>>
		class Cont = std::deque>
class Stack
{
private: 
	Cont<T> elems;

public:
	void push(T const&);
	void pop()
	T const& top();
	bool empty() const
	{
		return elems.empty();
	}
	
	template<typename T2, 
			template<typename Elem2, typename = std::allocator<Elem2>>
	class Cont2>
	Stack<T, Cont>& operator= (Stack<T2, Cont2> const&);

	template<typename, typename<typename, typename> class>
	friend class Stack;

};


template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::push(T&& elem)
{
	elem.push_back(std::forward<T>(elem));
}

template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::pop()
{
	if (!elems.empty())
		elems.pop_back();
	else
		cout << "Stack is empty" << endl;
}

template<typename T, template<typename, typename> class Cont>
T const& Stack<T, Cont>::top()
{
	if (!elems.empty())
		return elems.back();
	else
		throw std::string("top(): unable to extract element from an empty stack")
	return static_cast<Stack<T, Cont>>(0);
}

template<typename T, template<typename, typename> class Cont>
template<typename T2, template<typename, typename> class Cont2>
Stack<T, Cont>& Stack<T, Cont>::operator= (Stack<T2, Cont2> const& op2)
{
	elems.clear();
	elems.insert(elems.begin(),
		op2.elems.begin(),
		op2.elems.end());
	return *this;
}

#endif // ! _TEMPLATE_STACK
