#include <ruby.h>

class Hello{
    public:
    Hello(){};
    ~Hello(){};
};

static Hello 
*getHello(VALUE self)
{
    Hello *p;
    Data_Get_Struct(self, Hello, p);
    return p;
}

static VALUE
wrap_free_Hello(Hello *p)
{
    p->~Hello();
    ruby_xfree(p);
}

static VALUE 
wrap_init_Hello(VALUE self)
{
    Hello *p = getHello(self);
    p = new Hello;

    return Qnil;
}

static VALUE
wrap_alloc_Hello(VALUE self)
{
    void *p = ruby_xmalloc(sizeof(Hello));
    p = new Hello;
    return Data_Wrap_Struct(self, NULL, wrap_free_Hello, p);
}

extern "C" {

    void Init_hello() {
        VALUE cHello = rb_define_class("Hello", rb_cObject);

        rb_define_alloc_func(cHello, wrap_alloc_Hello);
        rb_define_private_method(cHello, "initialize", RUBY_METHOD_FUNC(wrap_init_Hello), 0);
    }
}