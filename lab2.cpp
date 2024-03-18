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

int main() {
	int a, d, c;
	int g = -1; //Метка ошибки
	int res = 0;
	cout << "Enter a: ";
	a = input_correct_number();
	cout << "Enter c: ";
	c = input_correct_number();
	cout << "Enter d: ";
	d = input_correct_number();
	cout << "(2 * c + d * 51) / (d - a - 1)" << endl;
		//(2 * c + d * 51) / (d - a - 1)
	__asm {
		; Первая скобка
		mov	eax, c;  eax = c
		cdq;
		mov ebx, 2;  ebx = 2
		imul ebx; eax = 2 * c
		jo numerator_error_of;
		mov ecx, eax; ecx = 2 * c
			mov eax, d; eax = d
			mov ebx, 51;  ebx = 51
			imul ebx; eax = d * 51
			jo numerator_error_of
		add eax, ecx; eax = 2 * c + d * 51
		jo numerator_error_of;
		push eax;

			; Вторая скобка;
		mov eax, d; eax = d
			mov ebx, a; ebx = a
			sub eax, ebx; eax = d - a
			jo numerator_error_of;
		mov ebx, 1;
		sub eax, ebx; eax = d - a - 1
		mov ebx, eax;  ebx = d - a - 1

			; итоговые рассчеты
			pop eax; eax = 2 * c + d * 51
			cdq;
		cmp ebx, 0
			je denominator_error_zf
		idiv ebx; eax = (2 * c + d * 51) / (d - a - 1)

			mov res, eax;
		jmp end_of_program;


	denominator_error_zf:
		mov g, 1
		jmp end_of_program


	numerator_error_of:
		mov g, 0
		jmp end_of_program


			end_of_program:
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
		cout << "Result C++: " << (2 * c + d * 51) / (d - a - 1) << '\n';
	}
	return 0;
}
