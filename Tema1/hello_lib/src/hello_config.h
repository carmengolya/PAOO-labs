#ifndef HELLO_CONFIG_H
#define HELLO_CONFIG_H

// Header PRIVAT: folosit doar la compilarea bibliotecii, nu se exporta.

#ifndef HELLO_LIB_VERSION
#define HELLO_LIB_VERSION "0.0"
#endif

#ifndef COPYRIGHT_INFO
#define COPYRIGHT_INFO "Copyright 03"
#endif

namespace hello {

///\brief Text to get displayed
const auto str_hello   = "Hello, ";
const auto str_timeis  = "Current time is: ";
const auto str_goodbye = "Good bye, ";

} // namespace hello

#endif // HELLO_CONFIG_H
