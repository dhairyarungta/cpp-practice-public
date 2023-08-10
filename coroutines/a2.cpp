#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>



struct ReturnObject 
{
    struct promise_type 
    {
        ReturnObject get_return_object(){return {};}

        std::suspend_never initial_suspend(){return{};}
        std::suspend_never final_suspend()noexcept{return{};}
        void unhandled_exception(){}
    };
};
struct Awaiter
{
    std::coroutine_handle<>*hp_;

    constexpr bool await_ready()const noexcept{return false};
    void await_suspend(std::coroutine_handle<>h){*hp_ = h;}
    constexpr void await_resume()const noexcept{}
    
};


ReturnObject counter(std::coroutine_handle<>*continuation_out)
{
    Awaiter a{continuation_out};
    for (int i=0;;++i )
    {
        co_await a;
        std::cout<<"counter: "<<i <<std::endl;
    }

}
void main()
{
    std::coroutine_handle<>h;
    counter(&h);
    for (int i =0 ;i<3;++i)
    {
        std::cout <<"inside main:\n";
        h();
    }
    h.destroy();
}


/*void Awaiter::await_suspend(std::coroutine_handle<>h)
// {
    if(hp_)
    {
        *hp_ = h;
        hp_ = nullptr;
    }
// }

*/


struct ReturnObject 
{
    struct promise_type
    {
        std::suspend_never initial_suspend(){return {};}
        std::suspend_never final_suspend(){return {};}
        ReturnObject get_return_value ()
        {
            return {};
        }

        void unhandled_exception(){}
    };
};

struct Awaiter
{
    std::coroutine_handle<>*hp_;
    constexpr bool await_ready()const noexcept{return false;}
    void await_suspend(std::coroutine_handle<>h){
        if(hp_)
        {
            *hp = h;
            hp = nullptr;
        }
    }
    constexpr void await_resume(){}
};


ReturnObject counter(std::coroutine_handle<>*handle_ptr)
{   
    Awaiter a{handle_ptr};

    for (unsigned i =0;;++i)
    {
        co_await a;
        cout<<i<<endl;
    }
}


void main()
{   
    std::coroutine_handle<>h;
    counter(&h);
    for (int i= 0;i< 3;++i)
    {
        cout<<"in main\n";
        h();
    }
    h.destroy();
}