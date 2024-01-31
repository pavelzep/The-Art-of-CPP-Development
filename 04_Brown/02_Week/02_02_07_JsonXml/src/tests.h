#pragma once

#include "solution.h"
#include "test_runner.h"

void TestAll();

void TestAll(){
    TestRunner tr;
    RUN_TEST(tr, TestXmlToJson);
    RUN_TEST(tr, TestJsonToXml);
}

