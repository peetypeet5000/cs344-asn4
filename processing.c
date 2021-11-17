#include "processing.h"

// Actual input function
void do_input() {
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
}



void do_line_seperator() {
    char private_buffer[1000];

    for(int i = 0; i < count_1; i++) {
        // Copy the current location in the buffer to a private buffer
        strcpy(private_buffer, buffer_1[read_index_1++]);

        char* newline_location = strchr(private_buffer, '\n');

        // If a newline was found, replace it with a space
        if(newline_location != NULL) {
            *newline_location = 32;
        }

        // Copy into next buffer
        strcpy(buffer_2[insert_index_2++], private_buffer);
        count_2++;
    }

}


void do_plus_sign() {
    char private_buffer[1000] = {0};

    for(int i = 0; i < count_2; i++) {
        char result_buffer[1000] = {0};
        char* private_buffer_location = &private_buffer;    // ptr to working location in buffer

        // Initially copy the working string into the buffer & get first substr 
        strcpy(private_buffer, buffer_2[read_index_2++]);
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
        strcpy(buffer_3[insert_index_3++], result_buffer);
        count_3++;
    }

}



void do_output() {
    char private_buffer[1000] = {0};
    char result_buffer[82] = {0};
    int result_length = 0;

    for(int i = 0; i < count_3; i++) {
        strcpy(private_buffer, buffer_3[read_index_3++]);

        for(int j = 0; j < strlen(private_buffer); j++) {
            result_buffer[result_length++] = private_buffer[j];

            if(result_length == 80) {
                result_buffer[80] = '\n';
                write(STDOUT_FILENO, result_buffer, 81);

                memset(result_buffer, '\0', 82);
                result_length = 0;
            }
        }
    }
}
