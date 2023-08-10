//awaiter type
template <typename PromiseType> 
struct GetPromise
{
    PromiseType *p_;
    bool await_ready(){return false;}
    bool await_suspend(std::coroutine_handle<PromiseType>)
};

struct ReturnObject3
{
    struct promise_type 
    {
        unsigned value_;

        ReturnObject3 get_return_object() 
        {
            return ReturnObject3
            {
                .h_= std::coroutine_hanlde<promise_type>::from_promise(*this);
            };
        }
        std::suspend_never inital_suspend(){return{};}
        std::suspend_never final_suspend(){return{};}
        void unhandled_exception(){}
    };
};


ReturnObject3 coutner()
{

}


void main()
{
    std::coroutine_handle<ReturnObject3::promise_type>h = counter3();

    for (int i =0;i<3;i++)
    {

    }
}