#include <iostream>
#include <map>
#include <functional>

using namespace std;

//Base  class declaration

class Base
{

 public:
        Base():type('B') 
                        {
                           if(vtable.find(type)==vtable.end())
                          vtable[type] = [this]() { f_declaration() ; } ;
                        }

        void f_get() 
                        {
                          vtable[type]();
                        }
 protected:

     char type ;
     static map< char , std::function<void()>> vtable;

 private:

    void f_declaration() { cout<<"Base::f"<<endl;}  
};

// static member definition
map<char, std::function<void()>> Base::vtable;

//Derived class declaration

class Derived:public Base
{
public:
         Derived():Base() 
                        {
                          type = 'D' ;
                            if(vtable.find(type)==vtable.end())
                          vtable[type] = [this]() { f_declaration();};
                        }

private:

 void f_declaration()
                      { 
                        cout<<"Derived::f"<<endl;
                      }
};

int main()
{
    
    Base obj1;
    obj1.f_get();
    Derived obj2;
    obj2.f_get();
    Base* ptr = &obj2;
    ptr->f_get();

    
    

    return 0;
}


