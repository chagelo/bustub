class A {

};

class  B{
    public:
    template <typename T>
    T* fun();
};

template <typename T>
T* B::fun() {
    T t;
    return &t;
}

int main() {
   
}