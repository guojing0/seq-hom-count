#ifndef EXPERIMENTS_TEST_SETTINGS_H
#define EXPERIMENTS_TEST_SETTINGS_H

#include "homomorphism/tree_width_solver.h"

class TestSettings {
public:
    void SetRandomSeed(int seed) {
        randomSeed_ = seed;
    };
    int GetRandomSeed() {
        return randomSeed_;
    }
    void SetTWS(TreeWidthSolver *tws) {
        tws_ = tws;
    };
    void SetRunAll(bool run) {
        runAll_ = run;
    }
    bool GetRunAll() {
        return runAll_;
    }
    void SetSingleTest(int test) {
        singleTest_ = test;
        runSingleTest_ = true;
    };
    int GetSingleTest() {
        return singleTest_;
    };
    bool ShouldRunSingleTest(){
        return runSingleTest_;
    };
    void SetPrTestTime(float time) {
        prTestTime_ = time;
    };
    void SetGroup(bool runSanity, bool runPerformance) {
        runSanity_ = runSanity;
        runPerformance_ = runPerformance;
    }
    void SetRunSpasmCreation(bool val) {
        runCreateSpasm_ = val;
    }
    void SetRunConvertGr(bool val) {
        runConvertGr_ = val;
    }
    void SetRunCountSub(bool val) {
        runCountSub_ = val;
    }
    bool GetRunCountSub() {
        return runCountSub_;
    }
    void SetRunCountHom(bool val) {
        runCountHom_ = val;
    }
    bool GetRunCountHom() {
        return runCountHom_;
    }
    bool GetRunSanity() {
        return runSanity_;
    }
    bool GetRunPerformance() {
        return runPerformance_;
    }
    bool GetRunCreateSpasm() {
        return runCreateSpasm_;
    }
    bool GetRunConvertGr() {
        return runConvertGr_;
    }
    void SetIn(std::string& filename) {
        in_ = &filename;
    }
    void SetOut(std::string& filename) {
        out_ = &filename;
    }
    std::string GetIn() {
        return in_ ? *in_ : "";
    }
    std::string GetOut() {
        return out_ ? *out_ : "";
    }
    int GetPrTestTime() {
        return prTestTime_;
    }
    int GetRepetitions() {
        return repetitions_;
    }
    void SetRepetitions(int repetitions) {
        repetitions_ = repetitions;
    }
    int GetCreateGraphSize() {
        return createGraphSize_;
    }
    void SetCreateGraphSize(int size) {
        createGraphSize_ = size;
    }
    float GetEdgeProbability() {
        return edgeProb_;
    }
    void SetEdgeProbability(float p) {
        edgeProb_ = p;
    }
    void SetCreateSpasm(bool val) {
        createSpasm_ = val;
    }
    bool GetCreateSpasm() {
        return createSpasm_;
    }
    void SetCreateSpasmDecomp(bool val) {
        createSpasmDecomp_ = val;
    }
    bool GetCreateSpasmDecmop() {
        return createSpasmDecomp_;
    }
    void SetRunTimed(bool val) {
        runTimed_ = val;
    }
    bool GetRunTimed() {
        return runTimed_;
    }
    void SetTimedDegree(bool val) {
        timedDegree_ = val;
    }
    bool GetTimedDegree() {
        return timedDegree_;
    }
private:
    int randomSeed_;
    int singleTest_ = 0;
    bool runSingleTest_ = false;
    bool runAll_ = false;
    bool runSanity_;
    bool runPerformance_;
    bool runCreateSpasm_;
    bool runConvertGr_;
    bool runCountSub_;
    bool runCountHom_;
    bool createSpasm_;
    bool createSpasmDecomp_;
    bool runTimed_;
    bool timedDegree_ = false;
    std::string *in_ = nullptr, *out_ = nullptr;
    int prTestTime_;
    int createGraphSize_ = 0;
    float edgeProb_ = 0.0;
    int repetitions_;
    TreeWidthSolver *tws_;
};


#endif /* test_settings_h */
