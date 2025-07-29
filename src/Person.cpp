#include "Person.hpp"
#include <iostream>

Person::Person()
{
}

Person::~Person()
{
}

Person::Person(const Person& obj)
: name_(obj.name_)
, age_(obj.age_)
, catchPhrase_(obj.catchPhrase_)
{
}

Person::Person(std::string name, int age, std::string catchPhrase)
: name_(name)
, age_(age)
, catchPhrase_(catchPhrase)
{
}

void Person::emote(void) const
{
    std::cout << catchPhrase_<< std::endl;
}   