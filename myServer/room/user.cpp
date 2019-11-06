#include "user.h"

User::User()
{

}

bool User::operator<(const User &rhs) const
{
    return this->username < rhs.username;
}

bool User::operator==(const User &rhs) const
{
    return this->username == rhs.username;
}
