// ArgumentDescriptor.hpp
// Gaétan "Aarnold Gad" Jalin
// 24 Nov 2022
#ifndef SCA_ARGUMENTDESCRIPTOR_HPP
#define SCA_ARGUMENTDESCRIPTOR_HPP

#include <string>

class ArgumentDescriptor
{
public:
   std::string getName() const noexcept;
   char getShortName() const noexcept;
   std::string getDescription() const noexcept;

   ArgumentDescriptor() = default;
   ArgumentDescriptor(std::string const& name, char shortName, std::string const& description);

private:
   std::string m_name;
   char m_shortName;
   std::string m_description;
};

#include "ArgumentDescriptor.inl"

#endif // SCA_ARGUMENTDESCRIPTOR_HPP
//Don't Be a Jerk: The Open Source Software License.
//Last Update: March 19, 2015
//
//This software is free and open source.
//
//- *I* am the software author. *I* might be a *we*, but that's OK.
//- *You* are the user of this software. *You* might also be a *we*, and that's also OK!
//
//> This is free software.  I will never charge you to use, license, or obtain this software.  Doing so would make me a jerk.
//
//> I will never take down or start charging for what is available today.  Doing so would make me a jerk.
//
//> You may use this code (and by "code" I mean *anything* contained within in this project) for whatever you want.  Personal use, Educational use, Corporate use, Military use, and all other uses are OK!  Limiting how you can use something free would make me a jerk.
//
//> I offer no warranty on anything, ever.  I've tried to ensure that there are no gaping security holes where using this software might automatically send your credit card information to aliens or erase your entire hard drive, but it might happen.  I'm sorry.  However, I warned you, so you can't sue me.  Suing people over free software would make you a jerk.
//
//> If you find bugs, it would be nice if you let me know so I can fix them.  You don't have to, but not doing so would make you a jerk.
//
//> Speaking of bugs, I am not obligated to fix anything nor am I obligated to add a feature for you.  Feeling entitled about free software would make you a jerk.
//
//> If you add a new feature or fix a bug, it would be nice if you contributed it back to the project.  You don't have to, but not doing so would make you a jerk.   The repository/site you obtained this software from should contain a way for you to contact me.  Contributing to open source makes you awesome!
//
//> If you use this software, you don't have to give me any credit, but it would be nice.
//
//Don't be a jerk.
//Enjoy your free software!