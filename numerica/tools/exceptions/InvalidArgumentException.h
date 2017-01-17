//
// Created by Miguel Angel Carvajal on 1/17/17.
//

#ifndef PROJECT_INVALIDARGUMENTEXCEPTION_H
#define PROJECT_INVALIDARGUMENTEXCEPTION_H

#include <stdexcept>
#include <string>

namespace numerica {
    namespace tools {
        namespace except {

            class InvalidArgumentException : public std::exception {

            private:
                std::string _message;
            public:
                //constructor
                InvalidArgumentException(const char *errorMessage);

                virtual const char *what() const throw();
                /** Destructor.
                  * Virtual to allow for subclassing.
                */
                virtual ~InvalidArgumentException() throw (){}


            };

        }

    }

}


#endif //PROJECT_INVALIDARGUMENTEXCEPTION_H
