struct ReturnObject4
{
    struct promise_type 
    {
        unsigned value_;

        ReturnObject4 get_return_value()
        {
            return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};

        }
        std::suspend_never inital_suspend(){return {};}
        std::suspend_never final_suspend()noexcept{return {};}
        vodi unhandled_exception(){}
        std::suspend_always yield_value(unsigned value)
        {
            value_ = value;
            return{};
        }
    };
    std::coroutine_handle<promise_type>h_;


};

ReturnObject4 counter4()
{
    for (unsigned i = 0;;++i)
    {
        co_yield i;
    }
}

void main()
{
    auto h = counter4().h_;
    auto &promise = h.promise();
    for (int i = 0;i<3;i++)
    {
        std:cout<<"counter4: "<<promise.value_<<std::endl;
        h();
    }
    h.destroy();
}



//the coyield essentially repalces the code below for the need of the GetPromise class
//both the codes have the same functionality 



template<typename PromiseType>
struct GetPromise
{   
    PromiseType* p_;
    bool await_ready(){return false;}
    bool await_suspend(std::coroutine_handle<PromiseType>h)
    {
        p_ = &(h.promise());
        return false;
    }
    PromiseType* await_resume (){return p_;}
    
};


struct ReturnObject
{
    struct promise_type 
    {
        unsigned value_;
        std::suspend_never initial_suspend(){return{};}
        std::suspend_never final_suspend(){return{};}
        void unhandled_exception(){}
        ReturnObject get_return_value()
        {
            return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
        }



    };

    std::coroutine_handle<promise_type> h_;
    operator std::coroutine_handle<promise_type>()const {return h_;}

};


ReturnObject counter ()
{
    auto pp = co_await GetPromise<ReturnObject::proimse_type> {}; 
    for (int i = 0;;i++)
    {
        pp->value_ = i;
        co_await std::suspend_always{};
        
    }

}

void main()
{
    std::coroutine_handle<ReturnObject3::promise_type>h = counter3();
    ReturnObject3::promise_type &promise =h.promise();
    for (int i =0 ;i<3;i++)
    {
        std::cout<<"counter: "<<promsie.value_<<std::endl;
        h();
    }

    h.destroy();
}
