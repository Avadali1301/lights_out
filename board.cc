#include <iostream>
#include <cstdlib>
#include <vector>
#include "board.h"
using namespace std;
void board::init(size_t s) {
	size = s;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			grid[i][j] = 0;
		}
	}
}
board::board(size_t s) {
	init(s);
}
board::board(const board & orig, size_t s) {
	init(s);
	copy(orig);
}
bool board::get(int x, int y) const {
	return grid[x][y];
}
void board::set(int x, int y, bool value) {
	grid[x][y] = value;
}
// pressing a given button 
// account for sides
// abuse square grid
void board::press(int x, int y) {
	// presses button at (x, y)
	set(x, y, !get(x, y));
	// set left
	if(x > 0) {
		set(x - 1, y, !get(x - 1, y));
	}
	// set right
	if(x < size - 1) {
		set(x + 1, y, !get(x + 1, y));
	}
	// set down
	if(y > 0) {
		set(x, y - 1, !get(x, y - 1));
	}
	// set up
	if(y < size - 1) {
		set(x, y + 1, !get(x, y + 1));
	}
}
void board::seed(int coords[][2], int xl) {
	for(int i = 0; i < xl; i++) {
		press(coords[i][0], coords[i][1]);
	}
}
void board::print() const {
	for(int i = size - 1; i >= 0; i--) {
		for(int j = 0; j < size; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void board::copy(const board & orig) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			set(i, j, orig.get(i, j));
		}
	}
}
// 1 iteration of the algorithm
// this is phi(pi(x)) + x
void board::iteration(board & backup) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(!backup.get(i, j)) {
				press(i, j);
			}
		}
	}
}
// regular equality
bool board::equals(board & rhs) const {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(rhs.get(i, j) != get(i, j)) {
				return false;
			}
		}
	}
	return true;
}
// 1st row conjecture
bool board::equalTo(board & rhs) const {
	for(int i = 0; i < size; i++) {
		if(rhs.get(0, i) != get(0, i)) {
			return false;
		}
	}
	return true;
}
// 1st column conjecture
bool board::isEqual(board & rhs) const {
	for(int i = 0; i < size; i++) {
		if(rhs.get(i, 0) != get(i, 0)) {
			return false;
		}
	}
	return true;
}
void board::pressingSequence() const {
	cout << "[";
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout << !get(i, j);
		}
		if(i != size - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
}
bool board::isIdentity() const {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(get(i, j) == 1) {
				return false;
			}
		}
	}
	return true;
}
void cycleSize(vector<board> backups, int size) {
	//backups.at(0).print();
	int i = 1;
	bool condition = true;
	while(condition) {
		board temp(backups.at(i - 1), size);
		board b1(temp, size);
		b1.iteration(temp);
		backups.push_back(b1);
		// if(backups.at(i - 1).isIdentity()) {
		// 		cout << "Identity Found at position: " << i - 1 << endl;
		// }
		for(int j = 0; j < i; j++) {
			if(backups.at(i).equals(backups.at(j))) {
				cout << "cycle size: " << i - j << endl;
				cout << "iterations to cycle: " << j << endl;
				// backups.at(i).pressingSequence();
				condition = false;
				break;
			}
		}
		// backups.at(i - 1).pressingSequence();
		//cout << "test" << endl;
		// backups.at(i - 1).print();
		i += 1;
	}
	cout << "cycle end configuration: " << endl;
	// backups.at(i - 1).print();
	// for(int j = 0; j < i; j++) {
	// 	backups.at(j).pressingSequence();
	// }
}
int main() {
	int inits[13][2];
	inits[0][0] = 0;
	inits[0][1] = 0;

	inits[1][0] = 0;
	inits[1][1] = 5;

	inits[2][0] = 0;
	inits[2][1] = 2;

	inits[3][0] = 1;
	inits[3][1] = 1;

	inits[4][0] = 1;
	inits[4][1] = 2;

	inits[5][0] = 1;
	inits[5][1] = 0;

	inits[6][0] = 3;
	inits[6][1] = 0;

	inits[7][0] = 3;
	inits[7][1] = 1;

	inits[8][0] = 3;
	inits[8][1] = 2;

	inits[9][0] = 3;
	inits[9][1] = 3;

	inits[10][0] = 3;
	inits[10][1] = 0;

	inits[11][0] = 1;
	inits[11][1] = 3;

	// inits[12][0] = 10;
	// inits[12][1] = 19;

	int size = 178;
	board b(size);
	b.seed(inits, 2);
	vector<board> backups;
	backups.push_back(b);
	cycleSize(backups, size);
	vector<board> backups1;
	// board c(size);
	// c.seed(inits, 2);
	// backups1.push_back(c);
	// cycleSize(backups1, size);
	// bool cond = true;
	// int i = 0;
	// while(cond) {

	// }
}
// https://oeis.org/A268754
// conjecture: if initial seed is an identity, cycle_length cut in half
// conjecture: if dim. = 2^k, then cycle length = 2^(k+1) - 2
// conjecture: mersenne primes have cycle length 1
// (a, b) where a is dimensions of board, and b is cycle length
// (1, 1) M
// (2, 1)
// (3, 1) M
// (4, 1)
// n x 1 rectangular oscillator starts here at n = 5
// (5, 4)
// (6, 14)
// (7, 1) M
// (8, 14)
// (9, 12)
// (10, 62)
// (11, 8)
// (12, 126)
// (13, 28)
// (14, 30)
// (15, 1) M
// (16, 30)
// (17, 28)
// (18, 1022)
// (19, 24)
// (20, 126)
// (21, 124)
// (22, 4094)
// (23, 16)
// (24, 2046)
// (25, 252)
// (26, 1022)
// (27, 56)
// (28, 32766)
// (29, 60)
// (30, 62)
// (31, 1) M
// (32, 62)
// (33, 60)
// (34, 8190)
// (35, 56)
// (36, 174762)
// (62, 126)
// (63, 1) M
// (64, 126)
// (81, 4092)
// (127, 1) M
// (128, 254)
// (199 16368)
// (255, 1)
// (256, 510)
// (510, 1022)
// (511, 1) M
// (512, 1022)
// (1023, 1) M

