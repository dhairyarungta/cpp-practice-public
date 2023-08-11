struct ReturnObject
{
    struct promise_type
    {
        unsigned int value_;
        
    };
};



void main()
{
    auto h = counter().h_;
    auto & promise = h.promise();
    while(!h.done())
    {

    }

}