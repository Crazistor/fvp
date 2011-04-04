#ifndef ACCESS_H
#define ACCESS_H


struct _Access;
typedef struct _Access Access;
typedef block*(*access_read)(Access *thiz);
typedef void (*access_destroy)(Access *thiz);

struct _Access
{
    access_read read;
    access_destroy destroy;
    char priv[0];
};


void access_seek()
{

    return thiz->seek();
}

void access_control()
{

    return thiz->control();
}

Block *access_read(Access *thiz)
{

    return thiz->read(Access *thiz);
}


void access_destroy(Access *thiz)
{
    if(thiz)
    {
        thiz->destroy(thiz);
    }
}




#endif /*ACCESS_H*/
