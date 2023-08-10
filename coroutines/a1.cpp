#include <iostream>
#include<coroutine>
template<typename T> 
struct Generator 
{
    struct promise_type ;
    using handle_type = std::coroutine_hanlde<promise_type> ;

    struct promise_type
    {
        T value_;
        std::exception_ptr exception_;
        Generator get_return_object()
        {
            return Generator(handle_type::from_promise(*this));

        }
        std::suspend_always initial_suspend(){return {};}
        std::suspend_always final_suspend()noexcept{return {};}
    void unhandled_exception(){exception_ = std::current_exception();}
    
    template<std::convertible_to<T>From>
    std::suspend_always yield_value (From &&from)
    {
        value_ = std::forward<From>(from);
        return {};
    }
    void return_void(){}

    };

    handle_type h_;

    Generator(handle_type h):h_(h){}
    Generator(const Generator&) = delete;
    ~Generator (){h_.destory();}

    explicit operator bool()
    {
        fill();
        return !h_.done(); 
    }

    T operator()()
    {
        fill(); 
        full_ = false;
        return std::move(h_.promise().value());
    }


private :
    bool full_ = false;
    void full()
    {
        if(!full_)
        {
            h_();
            if(h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            full_ = true;
        }
    }


};


Generator<unsigned> counter6()
{
    for (unsigned i = 0; i<3;)
    {
        co_yield i++;
    }
}

void main()
{
    auto gen = counter6();
    while(gen)
    {
        std::cout<<"counter6: "<<gen()<<std::endl;
    }
}
