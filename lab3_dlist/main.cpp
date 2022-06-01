#include <iostream>
#include <exception>

template<typename T>
struct Node {
    T data;
    Node *next, *prev;
};

template<typename T>
class List {
public:
    List() {
        Head = nullptr;
        Tail = nullptr;
        count = 0;
    }

    ~List() {
        while (Head) {
            Tail = Head->next;
            delete[] Head;
            Head = Tail;
        }
    }

    void add(T data) {
        auto *temp = new Node<T>;
        temp->next = temp->prev = nullptr;
        temp->data = data;
        if (Head != nullptr) {
            temp->prev = Tail;
            Tail->next = temp;
            Tail = temp;
        } else {
            temp->prev = nullptr;
            Head = Tail = temp;
        }
        count++;
    }

    void addHead(T data) {
        auto *temp = new Node<T>;

        temp->prev = nullptr;
        temp->data = data;
        temp->next = Head;

        if (Head != nullptr)
            Head->prev = temp;

        if (count == 0)
            Head = Tail = temp;
        else
            Head = temp;

        count++;
    }

    void insert(int pos, T data) {
        if (pos < 0 or pos > count) {
            throw std::exception();
        }
        if (pos == 0) {
            addHead(data);
            return;
        } else if (pos == count) {
            add(data);
            return;
        }

        auto *ins_el = Head;

        if (count / 2 >= pos) {
            std::cout << "Head\n";
            ins_el = Head;
            int c = 0;
            while (c < pos) {
                ins_el = ins_el->next;
                c++;
            }
        } else {
            std::cout << "Tail\n";
            ins_el = Tail;
            int c = count - 1;
            while (c > pos) {
                ins_el = ins_el->prev;
                c--;
            }
        }

        auto *prev_temp = ins_el->prev;
        auto *temp = new Node<T>;

        temp->data = data;

        if (count != 1)
            prev_temp->next = temp;

        temp->next = ins_el;
        temp->prev = prev_temp;
        ins_el->prev = temp;

        count++;
    }

    void pop(int pos) {
        if (pos < 0 or pos > count) {
            throw std::exception();
        }

        auto *del_el = Head;

        if (count / 2 >= pos) {
            std::cout << "Head\n";
            del_el = Head;
            int c = 0;
            while (c < pos) {
                del_el = del_el->next;
                c++;
            }
        } else {
            std::cout << "Tail\n";
            del_el = Tail;
            int c = count - 1;
            while (c > pos) {
                del_el = del_el->prev;
                c--;
            }
        }

        auto *prev_del = del_el->prev;
        auto *after_del = del_el->next;

        // Если удаляем не голову
        if (prev_del != nullptr and count != 1)
            prev_del->next = after_del;
        // Если удаляем не хвост
        if (after_del != nullptr and count != 1)
            after_del->prev = prev_del;

        if (pos == 0)
            Head = after_del;
        if (pos == count - 1)
            Tail = prev_del;

        count--;
    }

    T get(int pos){
        if (pos < 0 or pos > count) {
            throw std::exception();
        }

        auto *get_el = Head;

        if (count / 2 >= pos) {
            std::cout << "Head\n";
            get_el = Head;
            int c = 0;
            while (c < pos) {
                get_el = get_el->next;
                c++;
            }
        } else {
            std::cout << "Tail\n";
            get_el = Tail;
            int c = count - 1;
            while (c > pos) {
                get_el = get_el->prev;
                c--;
            }
        }

        return get_el->data;
    }

    void print() {
        auto *temp = Head;
        while (temp != nullptr) {
            std::cout << temp->data << '\n';
            temp = temp->next;
        }
    }

    void invPrint() {
        auto *temp = Tail;
        while (temp != nullptr) {
            std::cout << temp->data << '\n';
            temp = temp->prev;
        }
    }

private:
    Node<T> *Head, *Tail;
    int count;
};


int main() {
    List<int> t;

    t.add(10);
    t.add(11);
    t.add(13);

    t.print();
    std::cout << '\n';

    t.insert(2, 12);

    t.print();
    std::cout << '\n';
    t.invPrint();
    std::cout << '\n';

    std::cout << t.get(3) << " \n";
    std::cout << '\n';

    t.pop(2);
    t.print();
    std::cout << '\n';


    return 0;
}
