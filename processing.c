#include "processing.h"

// Actual input function
void* do_input(void* args) {
    char* input_buffer = NULL;
    size_t input_len;

    // Get input from the user
    // Note: Allowing getline to malloc input_buffer, make sure to free
    while(done_processing == false) {
        getline(&input_buffer, &input_len, stdin);

        // Check if it's STOP and at max there are 5 characters (+1 for \n)
        if(strncmp(input_buffer, "STOP", 4) == 0 && strlen(input_buffer) == 5) {
            done_processing = true;
        // Only place result in buffer if it is not STOP
        } else {
            put_buff_1(input_buffer);
        }

        // Free memory associated with input and set it back to null
        free(input_buffer);
        input_buffer = NULL;
    }

    return EXIT_SUCCESS;
}



void* do_line_seperator(void* args) {
    char* private_buffer;

    // Keep processing while more user input is possible or while buffer is still full
    while(done_processing == false || count_1 > 0) {
        // Copy the current location in the buffer to a private buffer
        private_buffer = get_buff_1();

        char* newline_location = strchr(private_buffer, '\n');

        // If a newline was found, replace it with a space
        if(newline_location != NULL) {
            *newline_location = 32;
        }

        // Copy into next buffer
        put_buff_2(private_buffer);

        // Free stack memory from private buffer
        free(private_buffer);
    }

    return EXIT_SUCCESS;
}


void* do_plus_sign(void* args) {
    char* private_buffer;

    // Keep processing until no more data is possible
    while(done_processing == false || count_1 > 0 || count_2 > 0) {
        char result_buffer[1000] = {0};
        char* private_buffer_location = private_buffer;    // ptr to working location in buffer

        // Initially copy the working string into the buffer & get first substr 
        private_buffer = get_buff_2();
        char* plus_location = strstr(private_buffer, "++");

        // If there are no occuraces, just copy string
        if(plus_location == NULL) {
            strcpy(result_buffer, private_buffer);
        } else {
            // Else, loop and insert ^
            while(plus_location != NULL) {
                // If a ++ was found, copy the first part of the stiring to result
                strncat(result_buffer, private_buffer_location, strlen(private_buffer_location) - strlen(plus_location));

                // Concatinate a ^
                strcat(result_buffer, "^");

                // Find next occurance
                char* temp = plus_location;
                plus_location = strstr(plus_location + 2, "++");

                // If this is the last occurance, copy the rest of the string in
                if(plus_location == NULL) {
                    strcat(result_buffer, temp + 2);
                }

                // Otherwise, adjust pointer for working buffer to ignore processed part
                private_buffer_location = temp + 2;
            }
        }

        // Copy result to next buffer
        put_buff_3(result_buffer);

        // Free memory from private buffer
        free(private_buffer);
    }

    return EXIT_SUCCESS;
}



void* do_output(void* args) {
    char* private_buffer;
    char result_buffer[82] = {0};
    int result_length = 0;

    while(done_processing == false || count_1 > 0 || count_2 > 0 || count_3 > 0) {
        // Place current buffer location in private buffer
        private_buffer = get_buff_3();

        // Loop through each char in the buffer, appending to result
        for(int j = 0; j < strlen(private_buffer); j++) {
            result_buffer[result_length++] = private_buffer[j];

            // Whenever the result reaches 80 chars, print to stdout
            if(result_length == 80) {
                result_buffer[80] = '\n';
                write(STDOUT_FILENO, result_buffer, 81);

                memset(result_buffer, '\0', 82);
                result_length = 0;
            }
        }

        // Free memory associated with private buffer
        free(private_buffer);
    }

    return EXIT_SUCCESS;
}
