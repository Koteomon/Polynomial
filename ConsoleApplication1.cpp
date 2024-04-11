#include<iostream>

using namespace std;

class Node {
public:
    float coef;
    int pow;
    Node* next;

    Node(float coef, int pow) {
        this->coef = coef;
        this->pow = pow;
        next = nullptr;
    }
};

class Monomial {
private:
    Node* head;
public:
    Monomial() {
        head = nullptr;
    }
    Monomial(float coef, int pow) {
        head = new Node(coef, pow);
    }
    void Print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->coef << "x^" << temp->pow;
            temp = temp->next;
        }
        cout << "\n";
    }
    ~Monomial() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    Monomial operator + (const Monomial& A) {
        Monomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        if (temp->pow == temp1->pow) {
            float resCoef = temp->coef + temp1->coef;
            while (temp != nullptr) {
                cout << resCoef << "x^" << temp->pow;
                temp = temp->next;
            }
        }
        else {
            while (temp != nullptr && temp1 != nullptr) {
                if (temp1->pow > temp->pow) {
                    if (temp->coef < 0)
                        cout << temp1->coef << "x^" << temp->pow << " " << temp->coef << "x^" << temp1->pow;
                    else
                        cout << temp1->coef << "x^" << temp->pow << " + " << temp->coef << "x^" << temp1->pow;
                }
                else {
                    if (temp1->coef < 0)
                        cout << temp->coef << "x^" << temp->pow << " " << temp1->coef << "x^" << temp1->pow;
                    else
                        cout << temp->coef << "x^" << temp->pow << " + " << temp1->coef << "x^" << temp1->pow;
                }
                temp = temp->next;
                temp1 = temp1->next;
            }
        }
        return result;
    }
    Monomial operator * (const Monomial& A) {
        Monomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        float resCoef;
        float resPow;
        while (temp != nullptr && temp1 != nullptr) {
            resCoef = temp->coef * temp1->coef;
            resPow = temp->pow + temp1->pow;
            cout << resCoef << "x^" << resPow;
            temp = temp->next;
            temp1 = temp1->next;
        }
        return result;
    }
};

class Polynomial {
private:
    Node* head;
public:
    Polynomial() {
        head = nullptr;
    }
    Polynomial(float coef, int pow) {
        head = new Node(coef, pow);
    }
    void addNode(float coef, int pow) {
        Node* newNode = new Node(coef, pow);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void Print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->coef << "x^" << temp->pow << " ";
            if (temp->next != nullptr) {
                if (temp->next->coef > 0)
                    cout << "+ ";
            }
            else
                cout << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    ~Polynomial() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Equation {
private:
    Node* head;
public:

    Equation() {
        head = nullptr;
    }
    Equation(float coef, int pow) {
        head = new Node(coef, pow);
    }
    void Print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->coef << "x^" << temp->pow << " ";
            if (temp->next != nullptr) {
                if (temp->next->coef > 0)
                    cout << "+ ";
            }
            else
                cout << " ";
            temp = temp->next;
        }
    }
    void addNode(float coef, int pow) {
        Node* newNode = new Node(coef, pow);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void convertFunc() {
        Node* temp = head;
        cout << "Equation: ";
        while (temp != nullptr) {
            cout << temp->coef;
            if (temp->pow != 0) {
                cout << "x";
                if (temp->pow != 1) {
                    cout << "^" << temp->pow;
                }
            }
            if (temp->next != nullptr) {
                if (temp->next->coef > 0) {
                    cout << " + ";
                }
                else {
                    cout << " ";
                }
            }
            temp = temp->next;
        }
        cout << " = 0" << endl;
    }
};

int main() {
    Equation A;
    A.addNode(2, 2);
    A.addNode(-3, 1);
    A.addNode(-4, 0);
    A.convertFunc();
    return 0;
}
