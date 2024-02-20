#pragma once
#include <vector>
#include <stdexcept>

namespace console_cpp {
    template<class ValueType, class ContainerType = std::vector<ValueType>>
    class TwoDimArrWrapper {
    public:
        explicit TwoDimArrWrapper()
            : TwoDimArrWrapper(0, 0) {

        }

        explicit TwoDimArrWrapper(size_t rows, size_t cols)
            : TwoDimArrWrapper(rows, cols, ValueType{}) {

        }

        explicit TwoDimArrWrapper(size_t rows, size_t cols, ValueType value)
            : rows_(rows), cols_(cols), arr_(rows * cols, value) {

        }

        TwoDimArrWrapper(const TwoDimArrWrapper&) = default;

        TwoDimArrWrapper(TwoDimArrWrapper&&) noexcept = default;

        TwoDimArrWrapper& operator=(const TwoDimArrWrapper&) = default;

        TwoDimArrWrapper& operator=(TwoDimArrWrapper&&) noexcept = default;

        friend bool operator==(const TwoDimArrWrapper& first, const TwoDimArrWrapper& second) {
            return first.rows_ == second.rows_ && first.cols_ == second.cols_ && first.arr_ == second.arr_;
        }

        friend bool operator!=(const TwoDimArrWrapper& first, const TwoDimArrWrapper& second) {
            return !(first == second);
        }

        ~TwoDimArrWrapper() = default;

        auto GetRows() const -> size_t {
            return this->rows_;
        }

        auto GetCols() const -> size_t {
            return this->cols_;
        }

        auto GetRawContainer() const -> const ContainerType& {
            return this->arr_;
        }

        auto At(size_t row, size_t col) const -> const ValueType& {
            const size_t index = col + row * this->cols_;

            if (index >= this->arr_.size()) {
                throw std::runtime_error("Out of bounds error");
            }

            return this->arr_[index];
        }

        auto At(size_t row, size_t col) -> ValueType& {
            const size_t index = col + row * this->cols_;

            if (index >= this->arr_.size()) {
                throw std::runtime_error("Out of bounds error");
            }

            return this->arr_[index];
        }

    private:
        size_t rows_{};
        size_t cols_{};
        ContainerType arr_{};
    };
}