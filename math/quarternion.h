#ifndef MATH_QUARTERNION_H
#define MATH_QUARTERNION_H

#include <string>
#include "absl/strings/str_cat.h"

template <typename Storage>
class Quarternion {
 public:
  static const Quarternion i;
  static const Quarternion j;
  static const Quarternion k;

  // Allow implicit conversion from real value.
 Quarternion(Storage real) : real_(real) {}
 Quarternion(Storage real, Storage i) : real_(real), i_(i) {}
 Quarternion(Storage real, Storage i, Storage j, Storage k)
   : real_(real), i_(i), j_(j), k_(k) {}

  std::string DebugString() const {
    std::string ret;
    if (real_) absl::StrAppend(&ret, real_);
    if (i_) {
      if (!ret.empty()) absl::StrAppend(&ret, "+");
      if (i_ != 1) absl::StrAppend(&ret, i_);
      absl::StrAppend(&ret, "i");
    }
    if (j_) {
      if (!ret.empty()) absl::StrAppend(&ret, "+");
      if (j_ != 1) absl::StrAppend(&ret, j_);
      absl::StrAppend(&ret, "j");
    }
    if (k_) {
      if (!ret.empty()) absl::StrAppend(&ret, "+");
      if (k_ != 1) absl::StrAppend(&ret, k_);
      absl::StrAppend(&ret, "k");
    }
    if (ret.empty()) { ret = "0"; }
    return ret;
  }
  
  bool operator==(const Quarternion& other) const {
    return real_ == other.real_ && i_ == other.i_ && j_ == other.j_ && k_ == other.k_;
  }
  bool operator!=(const Quarternion& other) const {
    return !(*this == other);
  }

 Quarternion& operator+=(const Quarternion& other) {
   real_ += other.real;
   i_ += other.i_;
   j_ += other.j_;
   k_ += other.k_;
   return *this;
 }
 Quarternion operator+(const Quarternion& other) const {
   Quarternion ret = *this;
   return ret += other;
 }
 Quarternion& operator*=(Storage real) {
   real_ *= real;
   i_ *= real;
   j_ *= real;
   k_ *= real;
   return *this;
 }
 Quarternion operator/(Storage real) const {
   Quarternion ret = *this;
   return ret *= real;
 }
 Quarternion& operator/=(Storage real) {
   real_ /= real;
   i_ /= real;
   j_ /= real;
   k_ /= real;
   return *this;
 }
 Quarternion operator/(const Quarternion& other) const {
   return *this * other.inverse();
 }
 Quarternion operator/=(const Quarternion& other) {
   return *this = *this * other.inverse();
 }
 Quarternion operator-() const {
   return Quarternion(-real_, -i_, -j_, -k_);
 }
 Quarternion operator*(const Quarternion& other) const {
   Quarternion ret{
     /*real=*/real_ * other.real_ - i_ * other.i_ - j_ * other.j_ - k_ * other.k_,
     /*i=*/i_ * other.real_ + real_ * other.i_ + j_ * other.k_ - k_ * other.j_,
     /*j=*/j_ * other.real_ + real_ * other.j_ + k_ * other.i_ - i_ * other.k_,
     /*k=*/k_ * other.real_ + real_ * other.k_ + i_ * other.j_ - j_ * other.i_
   };
   return ret;
 }
 Quarternion& operator*=(const Quarternion& other) {
   return *this = *this * other;
 }
 Quarternion& operator-=(const Quarternion& other) {
   return *this += -other;
 }

 private:
  Quarternion inverse() const {
    Quarternion ret{
      real_, -i_, -j_, -k_
    };
    ret /= norm();
    return ret;
  }
  Storage norm() const {
    return real_ * real_ + i_ * i_ + j_ * j_ + k_ * k_;
  }
  Storage real_{};
  Storage i_{};
  Storage j_{};
  Storage k_{};
};

template <typename Storage>
Quarternion<Storage> const Quarternion<Storage>::i = {0, 1, 0, 0};

template <typename Storage>
Quarternion<Storage> const Quarternion<Storage>::j = {0, 0, 1, 0};

template <typename Storage>
Quarternion<Storage> const Quarternion<Storage>::k = {0, 0, 0, 1};

template <typename Storage>
std::ostream& operator<<(std::ostream& out, const Quarternion<Storage>& q) {
  return out << q.DebugString();
}

#endif  // MATH_QUARTERNION_H
