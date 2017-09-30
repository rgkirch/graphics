    #include <benchmark/reporter.h>

    static void BM_red_noWork(benchmark::State& state) {
        double open = (double)rand() / RAND_MAX;
        double close = (double)rand() / RAND_MAX;
        while (state.KeepRunning()) {
        }
    }
    BENCHMARK(BM_red_noWork);

    static void BM_red_fast_work(benchmark::State& state) {
        double open = (double)rand() / RAND_MAX;
        double close = (double)rand() / RAND_MAX;
        while (state.KeepRunning()) {
            int red = ((int)open - (int)close) >> sizeof(int) - 1;
        }
    }
    BENCHMARK(BM_red_fast_work);

    static void BM_red_slow_work(benchmark::State& state) {
        double open = (double)rand() / RAND_MAX;
        double close = (double)rand() / RAND_MAX;
        while (state.KeepRunning()) {
            int red = open > close ? 0 : 1;
        }
    }
    BENCHMARK(BM_red_slow_work);

//static void BM_red_noWork(benchmark::State& state) {
//    std::vector<double> prices;
//    prices.reserve(100);
//    for (int i = 0; i < prices.size(); ++i) {
//        prices.push_back(rand());
//    }
//    volatile double open = rand() * 1000;
//    volatile double close = rand() * 1000;
//    while (state.KeepRunning()) {
//    }
//}
//BENCHMARK(BM_red_noWork);
//
//static void BM_red_fast_work(benchmark::State& state) {
//    std::vector<double> prices;
//    prices.reserve(100);
//    for (int i = 0; i < prices.size(); ++i) {
//        prices.push_back(rand());
//    }
//    int red;
//    while (state.KeepRunning()) {
//        for (int a = 0; a < 1000; ++a) {
//            for (int i = 0; i < prices.size() - 1; ++i) {
//                red = ((int) prices[i] - (int) prices[i+1]) >> sizeof(int) - 1;
//            }
//        }
//    }
//}
//BENCHMARK(BM_red_fast_work);
//
//static void BM_red_slow_work(benchmark::State& state) {
//    std::vector<double> prices;
//    prices.reserve(100);
//    for (int i = 0; i < prices.size(); ++i) {
//        prices.push_back(rand());
//    }
//    int red;
//    while (state.KeepRunning()) {
//        for (int a = 0; a < 1000; ++a) {
//            for (int i = 0; i < prices.size() - 1; ++i) {
//                red = prices[i] > prices[i+1] ? 1 : 0;
//            }
//        }
//    }
//}
//BENCHMARK(BM_red_slow_work);

BENCHMARK_MAIN();
