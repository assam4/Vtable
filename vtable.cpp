#include <iostream>
#include <map>
#include <functional>

//  Base  class declaration
  class Base
{
 public:
        Base()  :  type('B') 
        {
          if( vtable.find(type) == vtable.end() )
          vtable[type] = [this]() { f_declaration(); };
        }
        virtual ~Base() noexcept = default ;
        Base(const Base& oth) : type('B')  
        { }
        Base& operator= (const Base& other) noexcept
        {  
            if(this != &other )
                type = 'B' ; 
            return *this ;
        }
        void f_get() const 
        {
          vtable[type]() ;
        }
 protected:
        char type ;
        static std::map< char , std::function< void() >> vtable;
 private:
        void f_declaration() const noexcept
        { 
          std::cout << "Calling Base::f()" << std::endl ;
        }  
};

// static member global definition ( c++ rule for static)
std::map< char , std::function< void() >> Base::vtable ;

// Derived class declaration
class Derived:public Base
{
  public:
       Derived(): Base() 
        {
          type = 'D' ;
          if(vtable.find(type)==vtable.end())
          vtable[type] = [this]() { f_declaration();};
        }
        Derived(const Derived& oth): Base(oth)
        {
          type= 'D' ;  
        }
        Derived(const Base& oth)
         {
            type = 'D' ;
            if(vtable.find(type) == vtable.end())
            vtable[type] = [this]() { f_declaration(); };
          }
        Derived& operator= (const Base& other) noexcept
          {  
            if(this != &other )
                type = 'D' ; 
            return *this ;
          }
  private:
   void f_declaration() const noexcept
    { 
      std::cout << "Calling Derived::f() " << std::endl;
    }
};

int main()
{ 
  try
    {
    Base obj1;
    obj1.f_get();
    Derived obj2;
    obj2.f_get();
    Base* ptr = &obj2;
    ptr->f_get();
    obj2 = obj1;
    obj2.f_get();
    Derived obj3(obj2);
    obj3.f_get();
    return 0;
    }
    catch (...) { return 1 ; }
}

