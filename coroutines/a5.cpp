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