/********************************************

	Radix Sort
	Running time: O(n * k)

********************************************/

#include <iostream>
#include <string>

using namespace std;

const int CAP = 20;

void print(const int *a, int numOfElements);

int main()
{
	int digits = 3;
	int numOfElements = 15;
	
	int *a1 = new int[CAP] {789, 456, 123, 741, 852, 963, 321, 654, 987, 147, 258, 369, 159, 753, 111};
	int *a2 = new int[CAP];

	cout << "Start:  ";
	print(a1,numOfElements);
	cout << endl;

	/**********************************************************************************************************
		Insert your implementation of radix sort in here.
		Use the print function to print the array. 
		Your output should be as shown below:
		
			Start:  789 456 123 741 852 963 321 654 987 147 258 369 159 753 111

			Pass 1: 741 321 111 852 123 963 753 654 456 987 147 258 789 369 159
			Pass 2: 111 321 123 741 147 852 753 654 456 258 159 963 369 987 789
			Pass 3: 111 123 147 159 258 321 369 456 654 741 753 789 852 963 987

		Requirements:
			1) A total of 4 loops.
			2) For EACH loop clearly show the O-notation and explain WHY, not simply "this
				is O(k))".
			3) Assume ALL values have the same number of digits.
			4) Do NOT use any additional functions, including pow or other. Use mod and division only.
			5) Do NOT create addition arrays.
			6) The whole algorithm should go in this section.
			7) You need to check from 0 to 9. If the array is full and you have just checked, for example, 
				the digit 4, do NOT keep on traversing the array, but end the loop instead and CLEARLY 
				show how you are making this step more efficient by adding a comment.			

		PRINT this section (NOT the whole program). It should fit in 1 page (or a little more); if not, then
		you need to review your code, because it is too long. 
			
	***********************************************************************************************************/
	// Your code ONLY in here...

	/*
		Tran, Hoang

		CS A200
		Sep 27, 2017

		Lab 3
	*/
	int j = 0;
	int exp = 1;
	int check = 0;

	for (int n = 1; n <= digits; ++n)
		//This is O(n) because the loop will check each digit of a number and stop until
		//it reaches the last digit.
	{
		while ((check <= 9) && (j < numOfElements))
			//This is O(1) because the loop only checks from 0 to 9.
			//By checking if j is less than number of elements, the loop will end if the array is full
		{
			for (int k = 0; k < numOfElements; ++k) 
			//This is O(k) because the loop will traverse the array and check each elements
			//and stop until it reach the last element.
			 
			{
				if ((a1[k] / exp) % 10 == check)
				{
					a2[j] = a1[k];
					++j;
				}
			}
			++check;
		}
		//So, the loop has the running time of O(n*k)
		check = 0;
		j = 0;
		exp *= 10;

		//swap those 2 arrays
		int *temp = a2;
		a2 = a1;
		a1 = temp;

		//Print sorted array after each iteration
		cout << "Pass " << n << ": ";
		print(a1, numOfElements);
		cout << endl;
	}

	delete[]a2;
	
	/***********************************************************************************************************/

	cout << endl << endl;
	system("Pause");
	return 0;
}

void print(const int *a, int numOfElements)
{
	for (int i = 0; i < numOfElements; ++i)
		cout << a[i] << " ";
}