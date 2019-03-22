// STACK.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "STACK.hpp"


int main()
{
	Stack<int, std::vector> St(7);
	Stack<int, std::vector> dSt;
	St.push(4);
	St.push(7);
	dSt = St;


	dSt.pop();
	for (auto val : dSt)
		std::cout << val << std::endl;

	system("pause");
}

