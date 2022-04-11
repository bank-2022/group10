#include "myurl.h"

MyUrl::MyUrl()
{
    baseUrl="http://localhost:3000";
}

QString MyUrl::getBaseUrl() const
{
    return baseUrl;
}
