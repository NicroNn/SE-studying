#include "lib/scheduler.h"

int main() {
    double a = 1;
    double b = -2;
    double c = 0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](double a, double c){return -4 * a * c;}, a, c);

    auto id2 = scheduler.add([](double b, double v){return b * b + v;}, b, scheduler.getFutureResult<double>(id1));

    auto id3 = scheduler.add([](double b, double d){return -b + std::sqrt(d);}, b, scheduler.getFutureResult<double>(id2));

    auto id4 = scheduler.add([](double b, double d){return -b - std::sqrt(d);}, b, scheduler.getFutureResult<double>(id2));

    auto id5 = scheduler.add([](double a, double v){return v/(2 * a);}, a, scheduler.getResult<double>(id3));

    auto id6 = scheduler.add([](double a, double v){return v/(2 * a);},a, scheduler.getResult<double>(id4));

    scheduler.executeAll();

    std::cout << "x1 = " << scheduler.getResult<double>(id5) << std::endl;
    std::cout << "x2 = " << scheduler.getResult<double>(id6) << std::endl;



    return 0;
}
