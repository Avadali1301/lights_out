#include <iostream>
#include <cstdlib>
using namespace std;
class board {
	private:
		size_t size;
		// just change the size here
		bool grid[178][178];
	public:
		void copy(const board & orig);
		void init(size_t s);
		board(size_t s);
		board(const board & orig, size_t s);
		// access the value at coordinates
		bool get(int x, int y) const;
		// set the value at coordinates
		void set(int x, int y, bool value);
		// press the lights at the coordinates
		void press(int x, int y);
		// output matrix
		void print() const;
		void seed(int coords[][2], int xl);
		void pressingSequence() const;
		bool equals(board & rhs) const;
		// this will use 1st row conjecture to check 4 equality
		bool equalTo(board & rhs) const;
		// use 1st column conjecture to check 4 equality
		bool isEqual(board & rhs) const;
		// perform 1 iteration of the algorithm
		// going to need a backup
		void iteration(board & backup);

		bool isIdentity() const;
};