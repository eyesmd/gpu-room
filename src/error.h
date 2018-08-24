#ifndef GRAPHICS_COMPUTING_ERROR_H
#define GRAPHICS_COMPUTING_ERROR_H

void handleGenericError(int error_code, const char * error_message);
void handleShaderCompilationError(unsigned int shader_name,  const char * shader_repr);
void handleShaderLinkageError(unsigned int program_name);

#endif //GRAPHICS_COMPUTING_ERROR_H
