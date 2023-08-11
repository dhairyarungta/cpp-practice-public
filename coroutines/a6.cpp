struct ReturnObject
{
    struct promise_type
    {
        unsigned int value_;
        ~promise_type()
        {
            std::cout<<"promise_type destroyed "<<std::endl; 
        }
        ReturnObject get_return_value() 
        {
            return {
                .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        std::suspend_never initial_suspend(){return {};}
        std::suspend_never final_suspend(){return {};}
        void unhadnled_exception(){}
        void return_void(){}
        std::suspend_always yiled_value(unsigned int value)
        {
            value_ = value;
            return {};
        }
        
    };

    std::coroutine_handle<promise_type> h_;
};

ReturnObject counter()
{
    for (int i =0 ;i<3;i++)
    {
        co_yield i;
    }
}


void main()
{
    auto h = counter().h_;
    auto & promise = h.promise();
    while(!h.done())
    {
        std::cout<<"coutner: "<<promise.value_<<std::endl;
        h();
    }
    h.destroy();
}   