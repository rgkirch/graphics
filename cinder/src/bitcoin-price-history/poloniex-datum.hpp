#ifndef MYPROJECT_POLONIEX_DATA_H
#define MYPROJECT_POLONIEX_DATA_H

#include <vector>
#include <string>
#include <json.hpp>
#include "bitcoin.hpp"

using std::vector;
using std::string;
using std::to_string;
using json = nlohmann::json;

namespace Poloniex {
    struct Request {
    public:
        operator string() {
            return "https://poloniex.com/public"
                           "?command=returnChartData"
                           "&currencyPair=" + currencyPair +
                   "&start=" + to_string(start) +
                   "&end=" + to_string(end) +
                   "&period=" + to_string(period);
        }

    private:
        string currencyPair;
        long start;
        long end;
        long period;

    public:
        string getCurrencyPair() const {
            return currencyPair;
        }

        Request& setCurrencyPair(string currencyPair) {
            Request::currencyPair = currencyPair;
            return *this;
        }

        long getStart() const {
            return start;
        }

        Request& setStart(long start) {
            Request::start = start;
            return *this;
        }

        long getEnd() const {
            return end;
        }

        Request& setEnd(long end) {
            Request::end = end;
            return *this;
        }

        long getPeriod() const {
            return period;
        }

        Request& setPeriod(long period) {
            Request::period = period;
            return *this;
        }
    };

    struct Datum {

        Datum(json j) {
            date = j["date"];
            high = j["high"];
            low = j["low"];
            open = j["open"];
            close = j["close"];
            volume = j["volume"];
            quoteVolume = j["quoteVolume"];
            weightedAverage = j["weightedAverage"];
        }

        double date;
        double high;
        double low;
        double open;
        double close;
        double volume;
        double quoteVolume;
        double weightedAverage;
    };

    struct History {
        History() {};

        History(int r) {
            date.reserve(r);
            high.reserve(r);
            low.reserve(r);
            open.reserve(r);
            close.reserve(r);
            volume.reserve(r);
            quoteVolume.reserve(r);
            weightedAverage.reserve(r);
        }

        void push_back(Datum d) {
            date.push_back(d.date);
            high.push_back(d.high);
            low.push_back(d.low);
            open.push_back(d.open);
            close.push_back(d.close);
            volume.push_back(d.volume);
            quoteVolume.push_back(d.quoteVolume);
            weightedAverage.push_back(d.weightedAverage);
        }

        vector<double> date;
        vector<double> high;
        vector<double> low;
        vector<double> open;
        vector<double> close;
        vector<double> volume;
        vector<double> quoteVolume;
        vector<double> weightedAverage;
    };

    History downloadData(Request request) {
        HTTPDownloader downloader;
        auto content = downloader.download(request);
        auto j = json::parse(content);
        History history(j.size());
        for (auto r : j) {
            history.push_back(r);
        }
        return history;
    }

}

#endif //MYPROJECT_POLONIEX_DATA_H
