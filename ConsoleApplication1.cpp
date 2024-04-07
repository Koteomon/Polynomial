#include<iostream>
#include<string>


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
        cout << endl;
    }
    Monomial operator - (const Monomial& B) const {
        
        }
    ~Monomial() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
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
        cout << endl;
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

class Equation : public Polynomial {
private:
    Node* head;
public:

    Equation() : Polynomial() {
        head = nullptr;
    }
    Equation(float coef, int pow) {
        head = new Node(coef, pow);
    }
    float func_x(float a, float b, float c, int x) {
        return a * x * x + b * x + c;
    }
        
    void Print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->coef << "x^" << temp->pow<<" ";
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

    
};



int main()
{
    Equation A(2,4);
    A.addNode(3, 3);
    A.addNode(2, 2);
    A.addNode(2, 0);
    A.Print();
    A.func_x(2,3,2,2);
    return 0;
}