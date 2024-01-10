#pragma once

// #define BASE_TEST
#define SHOW_DURATION_INFO

#ifndef BASE_TEST
// #define SHOW_TOTAL_PARTS_DURATION_INFO
// #define DURATION_PARTS
#endif

#define SHOW_LOG_DURATION_INFO

#ifdef BASE_TEST
#define STD_TEST1
#define STD_TEST2
#define STD_TEST3
#define STD_TEST4
#define STD_TEST5
#define MY_SIMPLE_TEST
#endif

#ifndef BASE_TEST
    // #define BIG_TEST
#define SYNCH_TEST

#endif

// #define BIG_TEST_EXTERN