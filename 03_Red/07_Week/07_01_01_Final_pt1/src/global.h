#pragma once

// #define BASE_TEST

#ifndef BASE_TEST
#define SHOW_TOTAL_DURATION_INFO
#endif
#define SHOW_LOG_DURATION_INFO

// #define ORIGIN

// #define USE_STRING_VIEW
#ifdef BASE_TEST
#define STD_TEST1
#define STD_TEST2
#define STD_TEST3
#define STD_TEST4
#define STD_TEST5
#endif
// #define BIG_TEST
// #define BIG_TEST2
#ifndef BASE_TEST
#define BIG_TEST3
#endif
// #define MY_TEST
// #define EMPTY_TEST