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
public:
    Node* head;
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
    void addNode(float coef, int pow) {
        Node* newNode = new Node(coef, pow);
        if (head == nullptr)
            head = newNode;
        else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }
    }
    friend ostream& operator<< (ostream& out, const Monomial& A) {
        Node* temp = A.head;
        while (temp != nullptr) {
            if (temp->coef == 0) {
                out << 0;
                temp = temp->next;
            }
            else if (temp->coef == 1) {
                out << "x^" << temp->pow;
                temp = temp->next;
            }
            else {
                out << temp->coef << "x^" << temp->pow;
                temp = temp->next;
            }
            if (temp != nullptr) {
                if (temp->coef < 0)
                    out << " ";
                else
                    out << " + ";
            }
        }
        cout << endl;
        return out;
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
        int resPow;
        while (temp != nullptr && temp1 != nullptr) {
            resCoef = temp->coef * temp1->coef;
            resPow = temp->pow + temp1->pow;
            cout << resCoef << "x^" << resPow;
            temp = temp->next;
            temp1 = temp1->next;
        }
        return result;
    }
    Monomial operator - (const Monomial& A) {
        Monomial res;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                res.addNode(temp->coef - temp1->coef, temp->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                res.addNode(-temp1->coef, temp1->pow);
                temp1 = temp1->next;
            }
            else {
                res.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
        }
        while (temp != nullptr) {
            res.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            res.addNode(-temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        cout << res;
        return res;
    }
    Monomial operator / (const Monomial& A) {
        Monomial res;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->coef+temp1->coef == 1)
            {
                temp = temp->next;
                temp1 = temp1->next;
                cout << "\n";
            }
            if (temp->pow == 1)
            {

            }
            res.addNode(temp->coef / temp1->coef, temp->pow - temp1->pow);
            temp = temp->next;
            temp1 = temp1->next;
        }
        cout << res;
        return res;
    }
    
};

class Polynomial {
public:
    Node* head;
    Monomial D;
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
    Polynomial operator + (const Monomial& A) {
        Polynomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef + temp1->coef, temp1->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                result.addNode(temp1->coef, temp1->pow);
                temp1 = temp1->next;
            }
            else {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        cout << result;
        return result;
    }
    Polynomial operator - (const Monomial& A) {
        Polynomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef - temp1->coef, temp->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                result.addNode(temp1->coef, temp1->pow);
                temp = temp->next;
            }
            else {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        cout << result;
        return result;
    }
    friend ostream& operator<< (ostream& out, const Polynomial& A) {
        Node* temp = A.head;
        while (temp != nullptr) {
            if (temp->coef == 0) {
                out << 0;
                temp = temp->next;
            }
            else if (temp->coef == 1) {
                out << "x^" << temp->pow;
                temp = temp->next;
            }
            else {
                out << temp->coef << "x^" << temp->pow;
                temp = temp->next;
            }
            if (temp != nullptr) {
                if (temp->coef < 0)
                    out << " ";
                else
                    out << " + ";
            }
        }
        cout << endl;
        return out;
    }
    Polynomial operator + (const Polynomial& A) {
        Polynomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef + temp1->coef, temp->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if(temp->pow < temp1->pow) {
                result.addNode(temp1->coef, temp1->pow);
                temp1 = temp1->next;
            }
            else {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            } 
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(-temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        cout << result;
        return result;
    }
    Polynomial operator - (const Polynomial& A) {
        Polynomial result;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef - temp1->coef, temp->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
            else {
                result.addNode(-temp1->coef, temp1->pow);
                temp1 = temp1->next;
            }
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(-temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        cout << result;
        return result;
    }
    Polynomial operator [] (const int& A){
        Polynomial res;
        Node* temp=head;
        while(temp!=nullptr){
            if(A!=temp->pow){
                temp=temp->next;
            }
            else{
                res.addNode(temp->coef, temp->pow);
                cout<<res<<endl;
                return res;
        }
    }
    return res;
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
    friend ostream& operator<< (ostream& out, const Equation& A) {
        Node* temp = A.head;
        while (temp != nullptr) {
            if (temp->coef == 0) {
                out << 0;
                temp = temp->next;
            }
            else if (temp->coef == 1) {
                out << "x^" << temp->pow;
                temp = temp->next;
            }
            else {
                out << temp->coef << "x^" << temp->pow;
                temp = temp->next;
            }
            if (temp != nullptr) {
                if (temp->coef < 0)
                    out << " ";
                else
                    out << " + ";
            }
        }
        cout << endl;
        return out;
    }
    Equation operator + (const Monomial& A){
        Equation result;
        Node* temp=head;
        Node* temp1=A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef + temp1->coef, temp1->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                result.addNode(temp1->coef, temp1->pow);
                temp1 = temp1->next;
            }
            else {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        result.convertFunc();
        return result;
    }
    Equation operator - (const Monomial& A){
        Equation result;
        Node* temp = head;
        Node* temp1 = A.head;
        while (temp != nullptr && temp1 != nullptr) {
            if (temp->pow == temp1->pow) {
                result.addNode(temp->coef - temp1->coef, temp->pow);
                temp = temp->next;
                temp1 = temp1->next;
            }
            else if (temp->pow < temp1->pow) {
                result.addNode(temp1->coef, temp1->pow);
                temp = temp->next;
            }
            else {
                result.addNode(temp->coef, temp->pow);
                temp = temp->next;
            }
        }
        while (temp != nullptr) {
            result.addNode(temp->coef, temp->pow);
            temp = temp->next;
        }
        while (temp1 != nullptr) {
            result.addNode(temp1->coef, temp1->pow);
            temp1 = temp1->next;
        }
        result.convertFunc();
        return result;
    }
};

int main() {
    Monomial a(2,2);
    Equation d(5,2);
    d.addNode(4,1);
    d.addNode(7,0);
    cout<<a;
    cout<<d;
    d+a;
    d-a;
    return 0;
}
