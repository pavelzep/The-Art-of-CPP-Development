#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        throw logic_error("Unimplemented");
    }

protected:
    void PassOn(unique_ptr<Email> email) const {
        nextWorker->Process(move(email));
    };

    unique_ptr<Worker> nextWorker;

public:
    void SetNext(unique_ptr<Worker> next) {
        nextWorker = move(next);
    };
};

class Reader : public Worker {
public:
    Reader(istream& in) {

    }
    void Process(unique_ptr<Email> email) override {

    }
    void Run() override {
        // Process ();
    }
};

class Filter : public Worker {
    void Process(unique_ptr<Email> email) override {

    }

public:
    using Function = function<bool(const Email&)>;
    Filter(Filter::Function func) {

    }
};

class Copier : public Worker {
    void Process(unique_ptr<Email> email) override {

    }
    void Run() override {

    }
public:
    Copier(string recipient) {

    }
};


class Sender : public Worker {
    void Process(unique_ptr<Email> email) override {

    }
    void Run() override {

    }
public:
    Sender(ostream& out) {
    }
};

class PipelineBuilder {
public:
    explicit PipelineBuilder(istream& in) {
        pipeline_store.push_back(make_unique<Reader>(in));


    };

    PipelineBuilder& FilterBy(Filter::Function filter) {
        pipeline_store.push_back(make_unique<Filter>(filter));
        return *this;
    }

    PipelineBuilder& CopyTo(string recipient) {
        pipeline_store.push_back(make_unique<Copier>(recipient));
        return *this;
    }

    PipelineBuilder& Send(ostream& out) {
        pipeline_store.push_back(make_unique<Sender>(out));
        return *this;
    }

    unique_ptr<Worker> Build() {
        for (size_t i = pipeline_store.size()-1; i > 0 ; --i) {
            pipeline_store[i-1].get()->SetNext(move(pipeline_store[i]));
        }
        return move(pipeline_store.at(0));
    };

private:
    vector<unique_ptr<Worker>> pipeline_store;


};


void TestSanity() {
    string input = (
        "erich@example.com\n"
        "richard@example.com\n"
        "Hello there\n"

        "erich@example.com\n"
        "ralph@example.com\n"
        "Are you sure you pressed the right button?\n"

        "ralph@example.com\n"
        "erich@example.com\n"
        "I do not make mistakes of that kind\n"
        );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) {
        return email.from == "erich@example.com";
        });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
        "erich@example.com\n"
        "richard@example.com\n"
        "Hello there\n"

        "erich@example.com\n"
        "ralph@example.com\n"
        "Are you sure you pressed the right button?\n"

        "erich@example.com\n"
        "richard@example.com\n"
        "Are you sure you pressed the right button?\n"
        );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
