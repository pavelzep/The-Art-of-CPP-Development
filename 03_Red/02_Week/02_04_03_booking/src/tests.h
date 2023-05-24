#pragma once

#include "test_runner.h"
#include "boking_manager.h"

void Test_All();
void Test0() {
    BookingManager manager;
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);

    ASSERT_EQUAL(manager.Clients("FourSeasons"),1);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 4);

    manager.Book(86410,"FourSeasons", 1, 1); 

    ASSERT_EQUAL(manager.Clients("FourSeasons"),1);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
}

void Test1() {
    BookingManager manager;
    ASSERT_EQUAL(manager.Clients("Marriot"), 0);
    ASSERT_EQUAL(manager.Rooms("Marriot"), 0);
    manager.Book(10, "FourSeasons", 1, 2);
    manager.Book(10, "Marriot", 1, 1);
    manager.Book(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.Clients("Marriot"), 1);
    manager.Book(86410, "Marriot", 2, 10);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("Marriot"), 10);

}

void Test_All() {
    TestRunner tr;
    RUN_TEST(tr, Test0);
    RUN_TEST(tr, Test1);
    
}
