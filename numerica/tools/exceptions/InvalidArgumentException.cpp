//
// Created by Miguel Angel Carvajal on 1/17/17.
//

#include "InvalidArgumentException.h"


namespace numerica {

    namespace tools {
        namespace except {
            InvalidArgumentException::InvalidArgumentException(const char *errorMessage) : _message(errorMessage) {}

            const char *InvalidArgumentException::what() const throw() {
                return _message.c_str();
            }
        }
    }


}