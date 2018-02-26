#pragma once

template <typename T, typename Parameter>
class StrongType
{
public:
    constexpr explicit StrongType(T const& value) : value_(value) {}
    constexpr explicit StrongType(T&& value) : value_(std::move(value)) {}
    T& get() { return value_; }
    T const& get() const { return value_; }
    T const& operator*() const { return get(); }

    bool operator < (const StrongType &rhs)
    {
        return get() < rhs.get();
    }
    bool operator > (const StrongType &rhs)
    {
        return rhs < *this;
    }
    bool operator <= (const StrongType &rhs)
    {
        return !(*this > rhs);
    }
    bool operator >= (const StrongType &rhs)
    {
        return !(*this < rhs);
    }

    friend bool operator < (const StrongType &lhs, const StrongType &rhs)
    {
        return lhs.get() < rhs.get();
    }
    friend bool operator > (const StrongType &lhs, const StrongType &rhs)
    {
        return rhs < lhs;
    }
    friend bool operator <= (const StrongType &lhs, const StrongType &rhs)
    {
        return !(lhs > rhs);
    }
    friend bool operator >= (const StrongType &lhs, const StrongType &rhs)
    {
        return !(lhs < rhs);
    }

    friend StrongType operator * (const StrongType &lhs, const StrongType &rhs)
    {
        return StrongType{ lhs.get() * rhs.get() };
    }

    friend double operator * (const StrongType &lhs, const double &rhs)
    {
        return lhs.get() * rhs;
    }

    friend double operator * (const double &lhs, const StrongType &rhs)
    {
        return rhs * lhs;
    }

private:
    T value_;
};
