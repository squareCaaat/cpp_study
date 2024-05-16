#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

class OrderedVecInt {
private:
	// capacity = 동적 배열 길이
	// size = 정수 개수
	// *arr = 동적 배열 시작 주소, 처음 길이 = 0
	int capacity = 0, size = 0; 
	int* arr = nullptr;
	// 첫 번째 원소 삽입 시 길이 1
	// 이후 필요시 길이를 2배로
public:
	void insert(int a) {
		if (capacity == 0) {
			capacity = 1;
			int* tmp = new int[capacity];
			tmp[size] = a;
			arr = tmp;
			size++;
			return;
		}
		if (size == capacity) {
			capacity *= 2;
			int* tmp = new int[capacity];
			int idx = 0;
			for (int i = 0; i < capacity; i++) {
				tmp[idx] = arr[i];
				idx++;
			}
			delete[] arr;
			arr = tmp;
		}
		arr[size++] = a;
		for (int i = size - 1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
			}
		}
	}

	bool remove_by_val(int a) {
		int idx = -1;
		for (int i = 0; i < size; i++) {
			if (arr[i] == a) {
				idx = i;
				break;
			}
		}
		if (idx != -1) {
			return remove_by_index(idx);
		}
		return false;
	}

	bool remove_by_index(int idx) {
		if (idx < 0 || idx >= size)
			return false;
		for (int i = idx; i < size - 1; i++) {
			arr[i] = arr[i + 1];
		}
		size--;
		return true;
	}

	int _size() const { return size; }

	int &operator[](int idx) {
		return arr[idx];
	}

	const int& operator[] (int idx) const {
		return arr[idx];
	}
};

int main() {
	srand((unsigned int)time(NULL));
	int n, k;
	OrderedVecInt vec;
	cin >> n;
	for (int i = 0; i < n; i++) {
		k = rand() % 1000;
		vec.insert(k);
		// 정수 k 삽입, 정렬되어 저장
	}

	// indexing [] 제공
	for (int i = 0; i < vec._size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	// 매개변수로 주어진 정수를 찾아 삭제
	// 유효한 인덱스 true 아니면 false
	if (vec.remove_by_val(vec[2]))
		cout << "Remove Done" << endl;
	else
		cout << "Remove Failed" << endl;

	// 매개변수로 주어진 인덱스 위치의 정수 삭제
	// 유효한 인덱스 true 아니면 false
	if (vec.remove_by_index(4))
		cout << "Remove Done" << endl;
	else
		cout << "Remove Failed" << endl;

	// size() -> 저장된 정수 개수
	// 저장된 정수를 수정, 이때 정렬이 흐트러질 수 있다.
	for (int i = 0; i < vec._size(); i++)
		vec[i] -= 10;

	for (int i = 0; i < vec._size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	return 0;
}