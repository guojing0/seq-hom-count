#ifndef TEST_TEST_LOGGER_h
#define TEST_TEST_LOGGER_h

#include <string>

enum SubStep {CREATE_SPASM, DECOMPOSE_SPASM, RUN_ALG};
enum TestingKeyword {TAMAKI};

class TestLogger {
public:
    TestLogger(std::ostream& stream) : stream_(stream) {};
    void NotifyTestStart(std::string name);
    void NotifyTestEnd(float duration);
    void NotifyTestSubstep(SubStep step, std::string note, float duration);
private:
    std::ostream& stream_;
    std::string currentTestName_;
    std::string subStepToString(SubStep step);
};

#endif /* test_logger_h */
