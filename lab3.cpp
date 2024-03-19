#include <iostream>
using namespace std;


int input_correct_number() {
	int n;
	while (!(cin >> n) || cin.peek() != '\n') {
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Error, enter an int: ";
	}
	return n;
}

void showTask() {
	cout << "Вариант 10." << endl;
	cout << "a > b: a^2 / b - 1" << endl;
	cout << "a = b: -2" << endl;
	cout << "a < b: (b - 7) / (1 - a^2)" << endl;
}

int cppResult(int a, int b) {
	if (a > b) {
		return (a * a )/ b - 1;
	}
	else if (a == b) {
		return -2;
	}
	else {
		return (b - 7) / (1 - (a * a));
	}
}



int main() {
	int a, b;
	int g = -1; //Метка ошибки
	int res = 0;
	showTask();

	cout << "Enter a: ";
	a = input_correct_number();
	cout << "Enter b: ";
	b = input_correct_number();
	__asm {
		; Первая скобка
		mov	eax, a;  eax = a
		mov ebx, b;  ebx = b
		cmp eax, ebx
		je abequal;
		jg abgreater;
		jl abless;

	abequal:
		mov eax, -2; eax = -2
		mov res, eax;
		jmp end_of_program;

	abgreater:
		cmp ebx, 0;
		jz denominator_error_zf;
		imul eax, eax; eax = a ^ 2
		jo numerator_error_of;
		cdq;
		idiv ebx; eax = a ^ 2 / b
		jo numerator_error_of; Ловим переполнение
		sub eax, 1; eax = a ^ 2 / b - 1
		mov res, eax;
		jmp end_of_program;

	abless:
		imul eax; eax = a ^ 2;
		jo numerator_error_of; Ловим переполнение
		mov ecx, 1; ecx = 1
		sub ecx, eax; ecx = 1 - a ^ 2

		cmp ecx, 0; Сравниваем на ноль
		jz denominator_error_zf; Ловим деление на 0

		sub ebx, 7; ebx = b - 7

		;Меняем регистры, чтоб поделить нормально
		mov eax, ebx; eax = b - 7
		mov edx, ecx; edx = 1 - a ^ 2


		cdq; eax = > edx:eax;
		idiv ecx; eax = (b - 7) / (1 - a ^ 2)
		jo numerator_error_of; Ловим переполнение
		mov res, eax
		jmp end_of_program


	denominator_error_zf:
		mov g, 1
		jmp end_of_program


	numerator_error_of :
		mov g, 0
		jmp end_of_program


	end_of_program :
	}

	if (g == 1) {
		cout << "Division by zero!\n";
		return 0;
	}
	else if (g == 0) {
		cout << "Out of size!\n";
		return 0;
	}
	else {
		cout << "Result ASM: " << res << '\n';
		cout << "Result C++: " << cppResult(a,b) << endl;
	}
	return 0;
}
