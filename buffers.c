#include "buffers.h"

/******************************
 * INITILIZE GLOBAL VARIABLES *
 * ***************************/
char buffer_1[50][1000] = {0};
int count_1 = 0;
int insert_index_1 = 0;
int read_index_1 = 0;

char buffer_2[50][1000] = {0};
int count_2 = 0;
int insert_index_2 = 0;
int read_index_2 = 0;

char buffer_3[50][1000] = {0};
int count_3 = 0;
int insert_index_3 = 0;
int read_index_3 = 0;

bool done_processing = false;