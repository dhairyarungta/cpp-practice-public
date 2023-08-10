

struct ReturnObject2
{
    struct promise_type 
    {

        ReturnObject2 get_return_object()
        {
            return{.h_ =std::coroutine_handle<promise_type>::from_promise(*this) };
        }


        std::suspend_never inital_suspend(){return{};}
        std::suspend_never final_suspend(){return{};}
        void unhandled_exception(){}
    };


    std::coroutine_handle<promise_type> h_;
    operator std::coroutine_handle<promise_type>()const {return h_;}
    operator std::coroutine_handle<> ()const {return h_;}
    
};


ReturnObject2 counter2 ()
{

    for (unsigned i =0 ;;++i)
    {
        co_await std::suspend_always{};
        std::cout<<"counter2: "<<i<<std::endl;
    }

}

void main()
{
    std::coroutine_handle<> h = counter2();
    for (int i =0 ;i<3;i++)
    {
        std::cout<<"in main function\n";
        h();
    }
    h.destroy();
}