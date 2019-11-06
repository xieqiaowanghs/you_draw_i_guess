#include "sqluser.h"

SqlUser::SqlUser()
    : online(false)
{

}

SqlUser::SqlUser(const QString &username, const QString &password, bool online)
    : username(username), password(password), online(online)
{

}
