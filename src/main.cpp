/*! \mainpage WebWhirr
 *
 * \section intro_sec Introduction
 *
 * WebWhirr is the beginning of an HTML rendering engine. Initial work began
 * in 2013, and several iterations of development have been conducted since 
 * then. A complete rewrite began in May of 2015, and work on the new 
 * parser is underway. 
 *
 * A large amount of work was lost to a computer crash before 
 * important commits had been pushed, which halted development for some 
 * time. Work on WebWhirr is slow and sporadic, as I am a busy college
 * student and have very little time to spend on it. It's written solely
 * as a learning project, so I wouldn't recommend waiting around for it
 * to become a usable product.
 */

/*! \file main.cpp
 * \brief The main file for WebWhirr. Pass the HTML input to the parser.
 */
#include <iostream>

#include "parser/htmlparser.h"

/*! \brief Start WebWhirr. Does nothing right now.
 *
 * Eventually, this will access the HTML input and do stuff with it. 
 */
int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
