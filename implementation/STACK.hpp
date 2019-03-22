#ifndef  _TEMPLATE_STACK
#define  _TEMPLATE_STACK

#include <deque>
#include <exception>

class EmptyStack : public std::exception
{
	const char* reason;
public:

	EmptyStack(const char* res) : reason(res) {}

	virtual const char* what() const override
	{
		return reason;
	}
};

template<typename T,
	template<typename Elem, typename = std::allocator<Elem>>
		class Cont = std::deque>
class Stack
{
private:
	Cont<T> elems;

public:

	using iterator = typename Cont<T>::iterator;
	using const_iterator = typename Cont<T>::const_iterator;

	Stack() = default;

	explicit Stack(T&&);

	iterator begin()
	{
		return elems.begin();
	}

	iterator end()
	{
		return elems.end();
	}
	
	const_iterator begin() const
	{
		return elems.begin();
	}

	const_iterator end() const
	{
		return elems.end();
	}

	void push(T&&);

	void pop();

	T const& top();

	size_t size() const;

	bool empty() const
	{
		return elems.empty();
	}


	template<typename T2,
		template<typename Elem2, typename = std::allocator<Elem2>> class Cont2,
			typename = typename std::enable_if<std::is_convertible<T2, T>::value>::type>
	Stack<T, Cont>& operator= (Stack<T2, Cont2> const&);

	template<typename, template<typename, typename> class>
		friend class Stack;

};

template<typename T, template<typename, typename> class Cont>
Stack<T, Cont>::Stack(T&& value)
{
	elems.push_back(std::forward<T>(value));
}

template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::push(T&& val)
{
	elems.push_back(std::forward<T>(val));
}

template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::pop()
{
	if (!elems.empty())
		elems.pop_back();
}

template<typename T, template<typename, typename> class Cont>
T const& Stack<T, Cont>::top()
{
	if (elems.empty())
		throw EmptyStack("Error : using Stack::top() for an empty stack");

	return elems.back();
}

template<typename T, template<typename, typename> class Cont>
size_t Stack<T, Cont>::size() const
{
	return elems.size();
}

template<typename T, template<typename, typename> class Cont>
template<typename T2, template<typename, typename> class Cont2, typename>
Stack<T, Cont>& Stack<T, Cont>::operator= (Stack<T2, Cont2> const& op2)
{
	elems.clear();
	elems.insert(elems.begin(),
		op2.elems.begin(),
		op2.elems.end());
	return *this;
}

#endif // ! _TEMPLATE_STACK
