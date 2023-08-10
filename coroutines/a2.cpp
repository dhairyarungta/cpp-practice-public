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

    constexpr bool await_read()const noexcept{return false};
    
}

ReturnObject counter(std::coroutine_handle<>*continuation_out)
{
    Awaiter a{continuation_out};

}
void main()
{
    std::coroutine_handle<>h;
    counter(&h);
    for (int i =0 ;i<3;++i)

}