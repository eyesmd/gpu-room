#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>

#include "room.h"
#include "error.h"

void handleGenericError(int error_code, const char * error_message) {
    std::cout << "Error code: " << error_code << "\n";
    std::cout << "Error message: " << error_message << "\n";
}
