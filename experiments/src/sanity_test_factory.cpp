#include <homomorphism/forget_handler.h>
#include <homomorphism/helper_functions.h>
#include "experiments/sanity_test_factory.h"

#include "experiments/graph_generator.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/iterator_remapper.h"
#include "homomorphism/main.h"

#define BEGIN_TEST(name, type) logger.NotifyTestStart(name);type exp;

#define END_TEST //logger.NotifyTestEnd(duration);

#define ASSERT_START(expected) exp = expected;

#define ASSERT_END(note, result) logger.NotifyTestAssert(note,exp == result);

#define BEGIN_LOOP_TEST(name, type) BEGIN_TEST(name, type) bool allPassed;

#define LOOP_START allPassed = true;

#define LOOP_ASSERT_START(expected) ASSERT_START(expected)

#define LOOP_ASSERT_END(note, result) if(exp != result) { logger.NotifyTestAssert(note,exp == result); allPassed = false; break; }

#define LOOP_END(note) logger.NotifyTestAssert(note, allPassed)

std::function<void(TestSettings&, TestLogger&)> SanityTestFactory::getTest(TestCase t) {
    switch (t) {
        case SQUARE_PATTERN:
            return squarePatternTest;
        case REMAPPER_CALCULATION:
            return calculationRemapperTest;
        case REMAPPER_ITERATOR:
            return iteratorRemapperTest;
        default:
            return nullptr;
    }
}

std::vector<std::function<void(TestSettings&, TestLogger&)>> SanityTestFactory::allTests() {
    //TODO: Needs to add manually currently
    return std::vector<std::function<void(TestSettings&, TestLogger&)>> {squarePatternTest, calculationRemapperTest};
}

void SanityTestFactory::squarePatternTest(TestSettings& settings, TestLogger& logger) {
    BEGIN_TEST("SquareSanity", long);
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();

    GraphGenerator::CompleteGrid(h, 2, 2);
    GraphGenerator::CompleteGrid(g, 2, 2);
    ASSERT_START(1);
    long result = Main::subgraphsGraph(h, g);
    ASSERT_END("InSquare", result)

    GraphGenerator::CompleteGrid(g, 3, 3);
    ASSERT_START(4);
    result = Main::subgraphsGraph(h, g);
    ASSERT_END("In3x3", result)

    GraphGenerator::CompleteGrid(g, 4, 3);
    ASSERT_START(6);
    result = Main::subgraphsGraph(h, g);
    ASSERT_END("In4x3", result)
    END_TEST;
}

void SanityTestFactory::calculationRemapperTest(TestSettings& settings, TestLogger& logger) {
    CalculationRemapper mapper;
    remapperTest(settings, logger, mapper);
}

void SanityTestFactory::iteratorRemapperTest(TestSettings& settings, TestLogger& logger) {
    IteratorRemapper mapper;
    remapperTest(settings, logger, mapper);
}

void SanityTestFactory::remapperTest(TestSettings& settings, TestLogger& logger, Remapper& mapper) {
    BEGIN_TEST("CalculationRemapperSanity", std::vector<size_t>);
    std::vector<size_t> input(8), result(8), expected;

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    mapper.SetSizes(2, 3);

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 1);
    ASSERT_END("ExtractMiddle", result)

    expected = std::vector<size_t> {0, 4, 1, 5, 2, 6, 3, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 0);
    ASSERT_END("ExtractFirst", result)

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 1);
    ASSERT_END("InsertMiddle", result)

    expected = std::vector<size_t> {0, 2, 4, 6, 1, 3, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 0);
    ASSERT_END("insertFirst", result)

    END_TEST;
}

void SanityTestFactory::forgetLastTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("ForgetHandlerSanity", std::vector<size_t>);

    std::vector<size_t> input, expected, result;

    ForgetHandler handler;

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b);
            LOOP_ASSERT_START(expected)
            result = handler.forgetLast(input, result, n);
            std::stringstream str;
            str << "ForgetHandlerN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetHandler");

    END_TEST;
}

void SanityTestFactory::prepareForgetTest(std::vector<size_t>& input, std::vector<size_t>& expected, std::vector<size_t>& result, size_t n, size_t b) {
    size_t size = HelperFunctions::pow(n, b);

    input.resize(size);
    expected.resize(size / n);
    result.resize(size / n);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    size_t sum = n * (n - 1) / 2;
    size_t offset = n * n;
    for (size_t i = 0; i < expected.size(); ++i) {
        expected[i] = sum + i * offset;
    }
}
