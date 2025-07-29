#pragma once
#include <string>

class Person 
{
    private:
        std::string name_;
        int age_;
        std::string catchPhrase_;

    public: 
        Person();
        ~Person();

        Person(const Person& obj);
        Person(std::string name, int age, std::string catchPhrase);

        void emote(void) const;

        // Getters
        std::string getName(void)   const { return name_; }
        int         getAge(void)    const { return age_; }
 };  