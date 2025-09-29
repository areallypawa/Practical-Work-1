#include <iostream>
#include <vector>
using namespace std;


const int BITS = sizeof(int) * 8;
union MyFuncUnion {
	int tool;
	float num_float;
	int tools[2];
	double num_double;
};
MyFuncUnion myFuncUnion;

void clear() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void pause() {
	cout << '\n';
	system("Pause");
}

void Print_int_bits() {
	cout << "\nBIN: ";
	unsigned int mask = 1U << (BITS - 1);

	for (int i = 0; i < BITS; i++) {
		if (((i == 1) || (i % 4 == 0)) && i != 0) {
			cout << ' ';
		}
		if (i == 0) { cout << "\033[31m"; }
		else { cout << "\033[36m"; }
		cout << ((myFuncUnion.tool & mask) ? '1' : '0');
		mask >>= 1;
	}
	cout << "\033[0m" << endl;
}

void Print_double_bits() {
	cout << "\nBIN: ";
	for (int j = 1; j >= 0; j--) {
		unsigned int mask = 1 << (BITS - 1);
		for (int i = 0; i < BITS; i++) {
			int global_bit_index = (1 - j) * 32 + i;
			if (global_bit_index == 1 || global_bit_index == 12) { cout << "\033[0m|"; }
			else if (i % 4 == 0 && !(global_bit_index == 1 || global_bit_index == 12)) { cout << ' '; }
			// Цвета по зонам
			if (global_bit_index == 0) { cout << "\033[31m"; } else if (global_bit_index >= 1 && global_bit_index <= 11) { cout << "\033[33m"; } else { cout << "\033[36m"; }
			cout << ((myFuncUnion.tools[j] & mask) ? '1' : '0');
			mask >>= 1;
		}
	}
	cout << "\033[0m" << endl;
}

int Zero_one_quest(int number, int idx, bool is_double) {
	if (!is_double) {
		unsigned int mask = 1 << (BITS - 1);
		for (int i(0); i < BITS; i++) {
			if (i == (BITS - idx - 1)) {
				return (number & mask ? 1 : 0);
			}
			mask >>= 1;
		}
	}
	else {
		if (idx > 31) { number = myFuncUnion.tools[1]; idx -= 32; }
		else { number = myFuncUnion.tools[0]; }

		unsigned int mask = 1 << (BITS - 1);
		for (int i(0); i < BITS; i++) {
			if (i == (BITS - idx - 1)) {
				return (number & mask ? 1 : 0);
			}
			mask >>= 1;
		}
	}
	return -1;
}

void Create_mask(int idx, int flag) {
	int modify_num; int number(myFuncUnion.tool);

	if (flag != 3) {
		if (Zero_one_quest(number, idx, 0)) {
			// IDX is 1, create mask as 1110111 and use &, because need 1 -> 0
			unsigned int mask = (1U << BITS) - 1 - (1 << idx);
			modify_num = number & mask;
		}
		else {
			// IDX is 0, create mask as 000100 and use |, because need 0 -> 1
			unsigned int mask = (1 << idx);
			modify_num = number | mask;
		}
		myFuncUnion.tool = modify_num;
	}
	else {
		//cout << idx << " бит это" << Zero_one_quest(number, idx, 1) << '\n';
		if (Zero_one_quest(number, idx, 1)) {
			if (idx > 31) {
				unsigned int mask = (1 << BITS) - 1 - (1 << idx - 32);
				modify_num = myFuncUnion.tools[1] & mask;
				myFuncUnion.tools[1] = modify_num;
			}
			else {
				unsigned int mask = (1 << BITS) - 1 - (1 << idx);
				modify_num = myFuncUnion.tools[0] & mask;
				myFuncUnion.tools[0] = modify_num;
			}
		}
		else {
			if (idx > 31) {
				unsigned int mask = (1 << (idx - 32));
				modify_num = myFuncUnion.tools[1] | mask;
				myFuncUnion.tools[1] = modify_num;
			}
			else {
				unsigned int mask = (1 << (idx));
				modify_num = myFuncUnion.tools[0] | mask;
				myFuncUnion.tools[0] = modify_num;
			}
		}

	}
}

void Inversion_bit(int flag) {
	short N, idx;

	cout << "\nВведи количество, сколько хочешь битов поменять? : ";
	cin >> N;
	vector<int> arr_idx(N);
	cout << "Введи " << N << " индексов через Enter\n";

	// flag is type data. 
	switch (flag) {
	case 1:
		for (int i(0); i < N; i++) { cin >> idx; Create_mask(idx, flag); }
		cout << "Стало число " << myFuncUnion.tool;
		Print_int_bits();
		break;
	case 2:
		for (int i(0); i < N; i++) { cin >> idx; Create_mask(idx, flag); }
		cout << "Стало число " << myFuncUnion.num_float;
		Print_int_bits();
		break;
	case 3:
		for (int i(0); i < N; i++) { cin >> idx; Create_mask(idx, flag); }
		cout << "Стало число " << myFuncUnion.num_double;
		Print_double_bits();
		break;
	}
	pause();
}

int Algorithm_IDZ() {
	short flag;
	cout << "Выбер типа данных:\n1 - int\n2 - float\n3 - double\n0 - Назад\n";
	cin >> flag;
	switch (flag) {
	case 0: return 0;
	case 1:
		clear();
		cout << "Введи целое число: ";
		cin >> myFuncUnion.tool;
		cout << "Было число: " << myFuncUnion.tool;
		Print_int_bits();
		Inversion_bit(flag);
		break;
	case 2:
		clear();
		cout << "Введи число float: ";
		cin >> myFuncUnion.num_float;
		cout << "Было число: " << myFuncUnion.num_float;
		Print_int_bits();
		Inversion_bit(flag);
		break;
	case 3:
		clear();
		cout << "Введи число double: ";
		cin >> myFuncUnion.num_double;
		cout << "Было число: " << myFuncUnion.num_double;
		Print_double_bits();
		Inversion_bit(flag);
		break;
	}
	return -1;
}

int main() {
	setlocale(0, "RU");
	while (1) {
		clear();
		short N, choice;
		cout << "Выбор действия:\n1 - проверить ИДЗ\n0 - Выход\n";
		cin >> choice;
		switch (choice) {
		case 1:
			clear();
			Algorithm_IDZ();
			break;
		case 0:
			return 0;
		}
	}
}
