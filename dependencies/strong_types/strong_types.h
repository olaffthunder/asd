#pragma once

template <typename T, typename Parameter>
class StrongType
{
public:
    constexpr explicit StrongType(T const& value) : value_(value) {}
    constexpr explicit StrongType(T&& value) : value_(std::move(value)) {}
    T& get() { return value_; }
    T const& get() const { return value_; }
private:
    T value_;
};
