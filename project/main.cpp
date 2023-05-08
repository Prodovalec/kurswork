#include "CPanel.h"
// ���������� ����� ����������� �������� 2
long nearestPowerOf2(long N)
{
	long a = log2(N);

	if (pow(2, a) == N)
		return N;

	return pow(2, a + 1);
}

// RSA

void RSAKeyGen(long size) {
	long key_size = nearestPowerOf2(size);
	string prompt("openssl genrsa -out key.private ");
	prompt += to_string(key_size);
	system(prompt.c_str());
	prompt = "openssl rsa -in key.private -pubout -out key.public";
	system(prompt.c_str());
}

void RSAEncrypt(long size) {
	RSAKeyGen(size);
	string prompt("openssl pkeyutl -encrypt -pubin -inkey key.public -in file.bin -out file-enc.bin");

	system(prompt.c_str());
	system("del /f file.bin");
}

void RSADecrypt() {
	ifstream f("file.bin", ios_base::binary);
	if (f.good()) {
		f.close();
		return;
	}
	string prompt("openssl pkeyutl -decrypt -inkey key.private -in file-enc.bin -out file.bin");

	system(prompt.c_str());
	system("del /f file-enc.bin");
	system("del /f key.public");
	system("del /f key.private");
}

// AES-256-CBC

string AESKey() {
	cout << "������� ����: ";
	return InputString();
}

void AESEncrypt() {
	string prompt("openssl aes-256-cbc -salt -a -e -in file.bin -out file-enc.bin -pass pass:");
	prompt += AESKey();

	system(prompt.c_str());
	system("del /f file.bin");
}

void AESDecrypt() {
	// �������� - ���� ���� ���������� �� ����������, �� ����������� �� ���������
	ifstream f("file.bin", ios_base::binary);
	if (f) {
		f.close();
		return;
	}
	cout << "������������...\n";
	string prompt("openssl aes-256-cbc -salt -a -d -in file-enc.bin -out file.bin -pass pass:");
	prompt += AESKey();
	system(prompt.c_str());
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	AESDecrypt();
	ifstream fin("file.bin", ios_base::binary);
	if (!fin) 
	{
		cout << "���� �� ��� ������!";
	}
	else {
		ptrNODE head;
		import(fin, head);
		Menu(head);
		fin.close();
		ofstream fout("file.bin", ios_base::binary);
		fexport(fout, head);
		/* ���� ������������ RSA ����������, �� ����� ��������� ���� ������, ����� ������ ������ �����.
		��� ����� ��� ������������ �������� ����� �������� �� ����� ������� �����*/
		// long size = fout.tellp(); // �������� size � ������� RSAEncrypt(size)
		fout.close();
		clear(head);
		cout << "����������...\n";
		AESEncrypt();
		cout << "���� ��� ������� ����������!";
	}

	return 0;
}