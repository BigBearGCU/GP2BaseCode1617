#ifndef _NON_COPYABLE_H
#define _NON_COPYABLE_H

//inherit from this structure if you don't want your object to be copied
struct NonCopyable {
  NonCopyable() = default;
  //this is the C++0x11 way  of disabling the copy constuctor and copy assignment
  //these are generated for you by the compiler, if you don't want copying
  //then do the following!
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
