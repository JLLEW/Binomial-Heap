#include <iostream>

using namespace std;

class binomialHeap {
public:
	struct node {
		int key;
		int degree;
		node* parent;
		node* child;
		node *sibling;
	};




	node *rootListHead;
	bool isEmpty;

	binomialHeap() {
		rootListHead = nullptr;
		isEmpty = true;
	}

	void insert(int key) {
		isEmpty = false;
		node *newNode = new node;
		binomialHeap* h = new binomialHeap;
		newNode->key = key;
		newNode->child = nullptr;
		newNode->parent = nullptr;
		newNode->degree = 0;
		newNode->sibling = nullptr;
		h->rootListHead = newNode;
		unionHeaps(h);
	}


	node* getMaximum() {
		node* tempmax = rootListHead;
		node* next = rootListHead;
		while (next != nullptr) {
			if (next->key > tempmax->key)
				tempmax = next;
			next = next->sibling;
		}
		return tempmax;
	}

	node* extractElement() {
		if (rootListHead == nullptr)
			return nullptr;
		else {
			node* extractedMax;
			node* temp;
			//przestawienie wskaznikow na liscie rootow
			extractedMax = getMaximum();
			//
			temp = rootListHead;
			node*next = rootListHead->sibling;
			int keyToExtract = extractedMax->key;
			if (temp->key == keyToExtract) {
				rootListHead = next;
			}
			else {
				while (next != nullptr) {
					if (next->key == keyToExtract) {
						next = next->sibling;
						temp->sibling = next;
						next = nullptr;
					}
					else {
						temp = next;
						next = next->sibling;
					}
				}
			}
			
			binomialHeap *H = new binomialHeap;
			H->rootListHead = extractedMax->child;
			if (H->rootListHead != nullptr) {
				H->isEmpty = false;
				node* prev = H->rootListHead;
				node* tempSibling;
				temp = prev->sibling;
				prev->sibling = nullptr;
				prev->parent = nullptr;
				//odwrocenie kolejnosci listy siblingow
				while (temp != nullptr) {
					tempSibling = temp->sibling;
					temp->parent = nullptr;
					temp->sibling = prev;
					prev = temp;
					temp = tempSibling;
				}

				H->rootListHead = prev;
			}

			unionHeaps(H);
			if (rootListHead == nullptr)
				isEmpty = true;
			return extractedMax;
		}

	}


	bool increaseKey(int key, int value) {
		node* toBubble;
		if (key < value) {
			toBubble = findAndExchange(rootListHead, key, value);
			if (toBubble != nullptr) {
				bubbleUp(toBubble);
				return true;
			}
			else
				return false;
		}
		else {
			toBubble = findAndExchange(rootListHead, key, 2147483647);
			if (toBubble != nullptr) {
				bubbleUp(toBubble);
				extractElement();
				insert(value);
				return true;
			}
			else
				return false;
		}


	}

	node* findAndExchange(node* head, int key, int value){
		node* tempHead = head;
		node* found = nullptr;
		while (tempHead != nullptr && found == nullptr) {
			if (tempHead->key >= key) {
				if (tempHead->key == key) {
					tempHead->key = value;
					return tempHead;
				}
				else
					found = findAndExchange(tempHead->child, key, value);
			}
			tempHead = tempHead->sibling;
		}

		return found;
	}

	void bubbleUp(node* exchangedNode) {
		node* parent = exchangedNode->parent;
		node* temp = exchangedNode;
		bool changeHead = false;
		while (parent != nullptr && (temp->key > parent->key)) {
			
			int tempParentKey = parent->key;
			parent->key = temp->key;
			temp->key = tempParentKey;
			
			temp = parent;
			parent = temp->parent;
		}
	}


	node* linkSubHeaps(node* t1, node*t2) {
		if (t1->key > t2->key) {
			t2->parent = t1;
			t1->sibling = t2->sibling;
			t2->sibling = t1->child;
			t1->degree++;
			t1->child = t2;
			return t1;
		}
		else {
			t1->parent = t2;
			t1->sibling = t2->child;
			t2->degree++;
			t2->child = t1;
			return t2;
		}
	}

	void mergeHeaps(binomialHeap *heap) {

		node* mergerHead = heap->rootListHead;
		node* head = rootListHead;
		node* newHead = nullptr;
		
		if (heap->isEmpty == false || isEmpty == false)
			isEmpty = false;
		
		//sprawdzenie ktora glowa ma mniejszy stopien
		if (mergerHead != nullptr && head != nullptr) {
			if (head->degree > mergerHead->degree) {
				newHead = mergerHead;
			}
			else
				newHead = head;
		}
		else if(head == nullptr)
			newHead = mergerHead;
		else
			newHead = head;

		rootListHead = newHead;
		if (newHead != nullptr && newHead != head) {
			mergerHead = head;
			head = newHead;
		}
		
		node* prev = nullptr;
		// uporzadkowanie podkopców wg stopnia
		while (head != nullptr && mergerHead != nullptr) {
			if (head->degree < mergerHead->degree) {
				prev = head;
				head = head->sibling;
				if (head == nullptr)
					prev->sibling = mergerHead;
			}
			else{
				node* temp = mergerHead->sibling;
				mergerHead->sibling = head->sibling;
				head->sibling = mergerHead;
				head = head->sibling;
				mergerHead = temp;

			}
		}
		
		

	
	}


	void unionHeaps(binomialHeap *heap) {
		// uporzadkowanie podkopcow wg stopnia
		mergeHeaps(heap);
		//przestawienie kopca na pusty
		heap->rootListHead = nullptr;
		heap->isEmpty = true;

		
		node*head = rootListHead;
		node*prev = head;
		bool isHead = true;

		if (head == nullptr || head->sibling == nullptr)
			return;

		node*next = rootListHead->sibling;
		while (next != nullptr) {
			if ((head->degree != next->degree) ||( (next->sibling != nullptr) &&( next->sibling->degree == head->degree))) {
				prev = head;
				head = next;
				next = next->sibling;
				isHead = false;
			}
			else if (head->degree == next->degree) {
				head = linkSubHeaps(head, next);
				if (isHead == false)
					prev->sibling = head;
				else{
					rootListHead = head;
				}
				next = head->sibling;
			}
		}
	}

	~binomialHeap() {
		if (!isEmpty) {
			node *cleaner;
			while (rootListHead != nullptr) {
				cleaner = rootListHead;
				rootListHead = rootListHead->sibling;
				delete cleaner;
			}
		}
	}

};

class listOfHeaps {

	binomialHeap *heaps;
public:
	listOfHeaps() {
		heaps = new binomialHeap[1000];
	}

	void insert(int group, int key) {

		heaps[group].insert(key);

	}

	void print(int group) {
		binomialHeap *heap = new binomialHeap;
		binomialHeap::node* extracted;
		while (!heaps[group].isEmpty) {
			extracted = heaps[group].extractElement();
			printf("%d ", extracted->key);
			heap->insert(extracted->key);
		}
		heaps[group].rootListHead = heap->rootListHead;
		heaps[group].isEmpty = heap->isEmpty;
	}

	void extract(int group) {
		binomialHeap::node* extracted = heaps[group].extractElement();
		if (extracted != nullptr)
			printf("%d \n", extracted->key);
		else
			printf("na \n");

	}

	void increase(int group, int key, int value) {
		bool legal;
		legal = heaps[group].increaseKey(key, value);
		if (legal == false)
			printf("na \n");

	}

	void merge(int group, int mergerGroup) {

		heaps[group].unionHeaps(&heaps[mergerGroup]);

	}

	~listOfHeaps() {
		delete[] heaps;
	}



};




int main() {
	listOfHeaps meneger;
	char operation;
	int group;
	int mergerGroup;
	int key;
	int value;
	int numOfOperations;
	scanf("%d", &numOfOperations);
	int i = 0;
	while (i<numOfOperations) {
		scanf(" %c", &operation);
		switch (operation) {
		case 'a':
			scanf("%d", &group);
			scanf("%d", &key);
			meneger.insert(group, key);
			break;
		case 'e':
			scanf("%d", &group);
			meneger.extract(group);
			break;
		case 'p':
			scanf("%d", &group);
			meneger.print(group);
			break;
		case 'i':
			scanf("%d", &group);
			scanf("%d", &key);
			scanf("%d", &value);
			meneger.increase(group, key, value);
			break;
		case 'm':
			scanf("%d", &group);
			scanf("%d", &mergerGroup);
			meneger.merge(group, mergerGroup);
			break;
		default:
			break;
		}
		i++;
	}

	return 0;
}