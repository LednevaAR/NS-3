#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	int n = 0; // number of UE
	double start, end, bytes, d;
	double *throughput_UL, *throughput_DL;
	string st;
	ifstream file("UlRlcStats.txt");
	getline(file, st);
	int k = 1;
	while (file >> d) {
		if (k % 18 == 1) start = d;
		else if (k % 18 == 2) end = d;
		else if (k % 18 == 10) { 
			bytes = d;
			if (start == 0.0) {
				n += 1;
				throughput_UL = new double [n];
			}
			throughput_UL[(k / 18) % n] = max(bytes / (end - start), throughput_UL[(k / 18) % n]);
		}
		k++;
	}
	file.close();
	file.open("DlRlcStats.txt");
	getline(file, st);
	k = 1;
	n = 0;
	while (file >> d) {
		if (k % 18 == 1) start = d;
		else if (k % 18 == 2) end = d;
		else if (k % 18 == 10) {
			bytes = d;
			if (start == 0.0) {
				n += 1;
				throughput_DL = new double [n];
			}
			throughput_DL[(k / 18) % n] = max(bytes / (end - start), throughput_DL[(k / 18) % n]);
		}
		k++;
	}
	file.close();
	cout << "UL throughput" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ") " << throughput_UL[i] << " bytes per second = " << 8 * throughput_UL[i] << " bits per second = " << 8 * throughput_UL[i] / (1024 * 1024) << " megabits per second" << endl;
	}
	cout << "DL throughput" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ") " << throughput_DL[i] << " bytes per second = " << 8 * throughput_DL[i] << " bits per second = " << 8 * throughput_DL[i] / (1024 * 1024) << " megabits per second" << endl;
	}
}