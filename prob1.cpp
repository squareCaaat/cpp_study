#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

class OrderedVecInt {
private:
	// capacity = ���� �迭 ����
	// size = ���� ����
	// *arr = ���� �迭 ���� �ּ�, ó�� ���� = 0
	int capacity = 0, size = 0; 
	int* arr = nullptr;
	// ù ��° ���� ���� �� ���� 1
	// ���� �ʿ�� ���̸� 2���
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
		// ���� k ����, ���ĵǾ� ����
	}

	// indexing [] ����
	for (int i = 0; i < vec._size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	// �Ű������� �־��� ������ ã�� ����
	// ��ȿ�� �ε��� true �ƴϸ� false
	if (vec.remove_by_val(vec[2]))
		cout << "Remove Done" << endl;
	else
		cout << "Remove Failed" << endl;

	// �Ű������� �־��� �ε��� ��ġ�� ���� ����
	// ��ȿ�� �ε��� true �ƴϸ� false
	if (vec.remove_by_index(4))
		cout << "Remove Done" << endl;
	else
		cout << "Remove Failed" << endl;

	// size() -> ����� ���� ����
	// ����� ������ ����, �̶� ������ ��Ʈ���� �� �ִ�.
	for (int i = 0; i < vec._size(); i++)
		vec[i] -= 10;

	for (int i = 0; i < vec._size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	return 0;
}