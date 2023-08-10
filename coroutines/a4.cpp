//awaiter type
template <typename PromiseType> 
struct GetPromise
{
    PromiseType *p_;
    bool await_ready(){return false;}
    bool await_suspend(std::coroutine_handle<PromiseType>h)
    {
        p_ = &(h.promise());
        return false; // doesn't suspend actually at the end
    }
    PromiseType* await_resume(){return p_;}
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
    std::coroutine_handle<promise_type>h_;
    operator std::coroutine_handle<promise_type>()const {return h_;}
};


ReturnObject3 coutner()
{
    auto pp = co_await GetPromise<ReturnObject3::promise_type>{};

    for (unsigned i =0;;i++)
    {
        pp->value_ = i;
        co_await std::suspend_always{};
    }
    //two different awaiter objects being used in the same coroutine
}


void main()
{
    std::coroutine_handle<ReturnObject3::promise_type>h = counter3();
    ReturnObject3::promise_type &promise = h.promise();
    for (int i =0;i<3;i++)
    {
        std::cout<<"coutner: "<<promise.value_<<std::endl;
        h();
    }
    h.destroy();
}