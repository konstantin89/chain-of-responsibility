add_executable (email-processing-example "email_processing_example.cpp")

target_include_directories(email-processing-example PRIVATE ${CHAIN_OF_RESPONSIBILITY_INCLUDE_PATH})