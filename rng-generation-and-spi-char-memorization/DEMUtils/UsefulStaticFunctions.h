/*!
\author David "Dawn" Estes McKnight
\date 3 October 2016
Useful static functions (some of which are mainly because we're forced to work with C++ 98 due to this compiler).
*/

#include <string>
#include <sstream>

class usf
{
    public:
        static std::string to_string(float f)
        {
            std::ostringstream converterStream;
            converterStream<<f;
            return converterStream.str();
        }
};