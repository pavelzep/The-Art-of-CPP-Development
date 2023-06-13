template<typename T>
class MyList {
    struct Node {
        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    ~MyList();


private:
    Node* head = nullptr;

};



int main() {



    return 0;
}

