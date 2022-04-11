#ifndef MYURL_H
#define MYURL_H

#include <qstring.h>



class MyUrl
{
public:
    MyUrl();
    QString getBaseUrl() const;

private:
    QString baseUrl;
};

#endif // MYURL_H
