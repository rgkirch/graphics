#include <unordered_map>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../src/bitcoin-price-history/bitcoin.hpp"
#include "json.hpp"

using json = nlohmann::json;

TEST(download, test) {
    HTTPDownloader downloader;
    std::string content = downloader.download("https://poloniex.com/public?command=returnChartData&currencyPair=USDT_BTC&start=1496970103&end=9999999999&period=86400");
    std::cout << std::endl << content << std::endl;
}

TEST(parse, test) {
    auto data = R"thing([{"date":1497052800,"high":0.0199,"low":0.01815003,"open":0.01982997,"close":0.01820007,"volume":1807.11377643,"quoteVolume":94953.88597358,"weightedAverage":0.01903148},{"date":1497139200,"high":0.01991685,"low":0.01810004,"open":0.01820007,"close":0.0199011,"volume":1967.00917103,"quoteVolume":103144.87843504,"weightedAverage":0.01907035},{"date":1497225600,"high":0.02022638,"low":0.01832007,"open":0.0199011,"close":0.01900155,"volume":3154.3689201,"quoteVolume":163799.95257181,"weightedAverage":0.01925744},{"date":1497312000,"high":0.01947649,"low":0.01871471,"open":0.01909999,"close":0.019225,"volume":1842.83306803,"quoteVolume":96333.59331047,"weightedAverage":0.0191297},{"date":1497398400,"high":0.01944444,"low":0.01880026,"open":0.01922501,"close":0.01890393,"volume":1424.58272619,"quoteVolume":74602.17912358,"weightedAverage":0.01909572},{"date":1497484800,"high":0.01923647,"low":0.01820001,"open":0.0188705,"close":0.01902,"volume":1938.87107813,"quoteVolume":103345.02251164,"weightedAverage":0.01876114},{"date":1497571200,"high":0.01949506,"low":0.01886104,"open":0.01902003,"close":0.01934,"volume":1172.07245459,"quoteVolume":61149.01588335,"weightedAverage":0.01916747},{"date":1497657600,"high":0.02059998,"low":0.01931268,"open":0.01934001,"close":0.01999303,"volume":2843.61043108,"quoteVolume":143168.9839295,"weightedAverage":0.01986191},{"date":1497744000,"high":0.02049999,"low":0.01962019,"open":0.01999303,"close":0.01986847,"volume":1590.53880736,"quoteVolume":79048.67626897,"weightedAverage":0.020121},{"date":1497830400,"high":0.0202226,"low":0.01916869,"open":0.01986847,"close":0.019489,"volume":2411.04315694,"quoteVolume":122632.01627505,"weightedAverage":0.01966079},{"date":1497916800,"high":0.02022785,"low":0.0187,"open":0.019489,"close":0.01900002,"volume":3034.9064921,"quoteVolume":155443.90783793,"weightedAverage":0.01952412},{"date":1498003200,"high":0.01931343,"low":0.01780012,"open":0.01900004,"close":0.01840004,"volume":2172.03939871,"quoteVolume":116331.27812104,"weightedAverage":0.01867115},{"date":1498089600,"high":0.01884001,"low":0.01819463,"open":0.01840004,"close":0.01863593,"volume":992.93391619,"quoteVolume":53363.18310446,"weightedAverage":0.01860709},{"date":1498176000,"high":0.01924972,"low":0.01844016,"open":0.01863593,"close":0.01902731,"volume":1218.59171694,"quoteVolume":64616.64401146,"weightedAverage":0.01885878},{"date":1498262400,"high":0.0191711,"low":0.01840468,"open":0.01902731,"close":0.0186,"volume":1020.4648047,"quoteVolume":54515.8021522,"weightedAverage":0.01871869},{"date":1498348800,"high":0.01869752,"low":0.01795446,"open":0.0185995,"close":0.01802001,"volume":1054.19969402,"quoteVolume":57430.74241201,"weightedAverage":0.01835601},{"date":1498435200,"high":0.01883515,"low":0.01688,"open":0.01802002,"close":0.01794074,"volume":2481.18528024,"quoteVolume":140078.2537591,"weightedAverage":0.01771285},{"date":1498521600,"high":0.01810872,"low":0.01665001,"open":0.01794075,"close":0.01720007,"volume":1663.60390259,"quoteVolume":96690.90653399,"weightedAverage":0.01720538},{"date":1498608000,"high":0.01851962,"low":0.017019,"open":0.01720008,"close":0.01845487,"volume":1401.6527248,"quoteVolume":78919.82631182,"weightedAverage":0.01776046},{"date":1498694400,"high":0.01887881,"low":0.01770122,"open":0.01846581,"close":0.01781817,"volume":1317.08572325,"quoteVolume":72165.64523311,"weightedAverage":0.01825086},{"date":1498780800,"high":0.01829508,"low":0.01762,"open":0.01781817,"close":0.0178585,"volume":771.57470305,"quoteVolume":43166.84322943,"weightedAverage":0.01787424},{"date":1498867200,"high":0.01788691,"low":0.01671154,"open":0.01779631,"close":0.017101,"volume":1056.8112835,"quoteVolume":61178.44925719,"weightedAverage":0.01727424},{"date":1498953600,"high":0.0174005,"low":0.01686,"open":0.017101,"close":0.01710011,"volume":965.55954781,"quoteVolume":56447.56940962,"weightedAverage":0.01710542},{"date":1499040000,"high":0.01743657,"low":0.01689201,"open":0.017135,"close":0.01710297,"volume":992.6099637,"quoteVolume":57961.48925861,"weightedAverage":0.01712533},{"date":1499126400,"high":0.01723463,"low":0.01701245,"open":0.01710304,"close":0.01719,"volume":95.45607339,"quoteVolume":5571.40800322,"weightedAverage":0.0171332},{"date":1499212800,"high":0.01845,"low":0.01746813,"open":0.0174904,"close":0.017715,"volume":2075.96597926,"quoteVolume":115965.73817863,"weightedAverage":0.01790154},{"date":1499299200,"high":0.0194143,"low":0.01761543,"open":0.017715,"close":0.01930002,"volume":3010.12506885,"quoteVolume":161069.30253216,"weightedAverage":0.01868838},{"date":1499385600,"high":0.01966669,"low":0.01761002,"open":0.01930003,"close":0.01776744,"volume":2845.76685156,"quoteVolume":153060.31199112,"weightedAverage":0.01859245},{"date":1499472000,"high":0.01819149,"low":0.01685,"open":0.01776744,"close":0.01808448,"volume":1466.72644613,"quoteVolume":83993.88362443,"weightedAverage":0.0174623},{"date":1499558400,"high":0.0184,"low":0.01754091,"open":0.01808451,"close":0.01828069,"volume":757.08648713,"quoteVolume":42045.64298373,"weightedAverage":0.0180063}])thing";
    auto j = json::parse(data);
    for(auto i : j) {
        std::cout << i["close"] << " " << i["date"] << " " << i["high"] << " " << i["low"] << " " << i["open"] << " " << i["quoteVolume"] << " " << i["volume"] << " " << i["weightedAverage"] << std::endl;
    }
}

TEST(downloadParse, test) {
    HTTPDownloader downloader;
    std::string content = downloader.download("https://poloniex.com/public?command=returnChartData&currencyPair=USDT_BTC&start=1496970103&end=9999999999&period=86400");
    auto j = json::parse(content);
    for(auto i : j) {
        std::cout << i["close"] << " " << i["date"] << " " << i["high"] << " " << i["low"] << " " << i["open"] << " " << i["quoteVolume"] << " " << i["volume"] << " " << i["weightedAverage"] << std::endl;
    }
}

TEST(umm, mapTest) {
    std::unordered_map<std::string, std::vector<float>> data
    {
        {"close", {}},
        {"date", {}},
        {"high", {}},
        {"low", {}},
        {"open", {}},
        {"quoteVolume", {}},
        {"volume", {}},
        {"weightedAverage", {}}
    };
    data["close"].push_back(3.9);
    std::cout << std::endl << data["close"].front() << std::endl;
    ASSERT_FLOAT_EQ(3.9f, data["close"].front());
}