#ifndef LABWORK10_NICRONN_LIB_SCHEDULER_H_
#define LABWORK10_NICRONN_LIB_SCHEDULER_H_
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <thread>

class SubTask {
  public:
    virtual void execute() = 0;
    virtual void* getResult() = 0;
};

template<typename function>
class EmptySubTask : public SubTask {
  private:
    bool is_done = false;
    function func_;
    using return_type = decltype(func_());
    return_type answer_;
    return_type* answer_pointer_ = &answer_;

  public:
    explicit EmptySubTask(function func)
        : func_(func) {};

    void execute() override {
        is_done = true;
        answer_ = func_();
    }

    void* getResult() override {
        if (!is_done) {
            execute();
        }
        return static_cast<void*>(answer_pointer_);
    }

};

template<typename function, typename argument>
class UnarySubTask : public SubTask {
  private:
    bool is_done = false;
    function func_;
    argument arg_;
    using return_type = decltype(func_(arg_));
    return_type answer_;
    return_type* answer_pointer_ = &answer_;

  public:
    UnarySubTask(function func, argument arg)
        : func_(func), arg_(arg) {};

    void execute() override {
        is_done = true;
        answer_ = func_(arg_);
    }

    void* getResult() override {
        if (!is_done) {
            execute();
        }
        return static_cast<void*>(answer_pointer_);
    }
};

template<typename function, typename argument1, typename argument2>
class BinarySubTask : public SubTask {
  private:
    bool is_done = false;
    function func_;
    argument1 arg1_;
    argument2 arg2_;
    using return_type = decltype(func_(arg1_, arg2_));
    return_type answer_;
    return_type* answer_pointer_ = &answer_;

  public:
    BinarySubTask(function func, argument1 arg1, argument2 arg2)
        : func_(func), arg1_(arg1), arg2_(arg2) {};

    void execute() override {
        is_done = true;
        answer_ = func_(arg1_, arg2_);
    }

    void* getResult() override {
        if (!is_done) {
            execute();
        }
        return static_cast<void*>(answer_pointer_);
    }
};

class TaskNo {
  private:
    size_t taskNo;
  public:
    explicit TaskNo(int n)
        : taskNo(n) {};

    size_t getNo() const {
        return taskNo;
    }
};

template<typename T>
class FutureResult {
  private:
    SubTask* dependence_;

  public:
    explicit FutureResult(SubTask* dependence)
        : dependence_(dependence) {};

    operator const T&() const {
        const T* temp = reinterpret_cast<const T*>(dependence_->getResult());
        return static_cast<const T&>(*temp);
    }
};

class TTaskScheduler {
  private:
    std::vector<std::unique_ptr<SubTask>> tasks_;

  public:
    template<typename function>
    TaskNo add(function func) {
        auto new_task = std::make_unique<EmptySubTask<function>>(func);
        tasks_.push_back(std::move(new_task));
        return TaskNo(tasks_.size() - 1);
    }

    template<typename function, typename T>
    TaskNo add(function func, T arg) {
        auto new_task = std::make_unique<UnarySubTask<function, T>>(func, arg);
        tasks_.push_back(std::move(new_task));
        return TaskNo(tasks_.size() - 1);
    }

    template<typename function, typename T, typename U>
    TaskNo add(function func, T arg1, U arg2) {
        auto new_task = std::make_unique<BinarySubTask<function, T, U>>(func, arg1, arg2);
        tasks_.push_back(std::move(new_task));
        return TaskNo(tasks_.size() - 1);
    }

    template<typename T>
    FutureResult<T> getFutureResult(TaskNo dependence) {
        if (dependence.getNo() >= tasks_.size()){
            exit(0);
        }
        return FutureResult<T>(tasks_[dependence.getNo()].get());
    }

    template<typename T>
    FutureResult<T> getResult(TaskNo task) {
        return FutureResult<T>(tasks_[task.getNo()].get());
    }

    void executeAll() {
        std::vector<std::thread> threads;

        for (auto& task : tasks_) {
            threads.emplace_back([&task]() { task->execute(); });
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }

    ~TTaskScheduler() {
        tasks_.clear();
    }
};
#endif //LABWORK10_NICRONN_LIB_SCHEDULER_H_
