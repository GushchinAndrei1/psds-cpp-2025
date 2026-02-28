#include <cmath>
#include <iostream>
#include <iomanip>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};


class Phasor {
public:
    Phasor() : real_(0.0), imag_(0.0) {}

    Phasor(double magnitude, double phase_rad) {
        SetPolar(magnitude, phase_rad);
    }

    Phasor(double magnitude, double phase_rad, ExpTag)
        : Phasor(magnitude, phase_rad) {}

    Phasor(double magnitude, double phase_deg, DegTag) {
        SetPolar(magnitude, DegToRad(phase_deg));
    }

    Phasor(double real, double imag, AlgTag)
        : real_(real), imag_(imag) {}

    void SetPolar(double magnitude, double phase_rad) {
        if (magnitude < 0) {
            magnitude = -magnitude;
            phase_rad += M_PI;
        }
        real_ = magnitude * std::cos(phase_rad);
        imag_ = magnitude * std::sin(phase_rad);
    }

    void SetCartesian(double real, double imag) {
        real_ = real;
        imag_ = imag;
    }

    double Real() const { return real_; }
    double Imag() const { return imag_; }

    double Magnitude() const {
        return std::hypot(real_, imag_);
    }

    double Abs() const { return Magnitude(); }

    double Phase() const {
        return NormalizeRad(std::atan2(imag_, real_));
    }

    double Angle() const { return Phase(); }

    double PhaseDeg() const {
        return NormalizeDeg(RadToDeg(Phase()));
    }

    double AngleDeg() const { return PhaseDeg(); }

    Phasor Conj() const {
        return Phasor(real_, -imag_, AlgTag{});
    }

    Phasor Inv() const {
        double d = real_ * real_ + imag_ * imag_;
        return Phasor(real_ / d, -imag_ / d, AlgTag{});
    }

    Phasor& operator+=(const Phasor& rhs) {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }

    Phasor& operator-=(const Phasor& rhs) {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }

    Phasor& operator*=(const Phasor& rhs) {
        double mag = Magnitude() * rhs.Magnitude();
        double phase = Phase() + rhs.Phase();
        SetPolar(mag, phase);
        return *this;
    }

    Phasor& operator/=(const Phasor& rhs) {
        double mag = Magnitude() / rhs.Magnitude();
        double phase = Phase() - rhs.Phase();
        SetPolar(mag, phase);
        return *this;
    }

    Phasor& operator+=(double x) { return *this += Phasor(x, 0.0, AlgTag{}); }
    Phasor& operator-=(double x) { return *this -= Phasor(x, 0.0, AlgTag{}); }
    Phasor& operator*=(double x) { return *this *= Phasor(x, 0.0); }
    Phasor& operator/=(double x) { return *this /= Phasor(x, 0.0); }

    Phasor operator-() const {
        return Phasor(-real_, -imag_, AlgTag{});
    }

    bool operator==(const Phasor& rhs) const {
        return NearlyEqual(real_, rhs.real_) &&
               NearlyEqual(imag_, rhs.imag_);
    }

    bool operator!=(const Phasor& rhs) const {
        return !(*this == rhs);
    }

private:
    double real_;
    double imag_;

    static bool NearlyEqual(double a, double b, double eps = 1e-12) {
        return std::fabs(a - b) < eps;
    }

    static double NormalizeRad(double x) {
        while (x <= -M_PI) x += 2 * M_PI;
        while (x > M_PI) x -= 2 * M_PI;
        return x;
    }

    static double NormalizeDeg(double x) {
        while (x <= -180.0) x += 360.0;
        while (x > 180.0) x -= 360.0;
        return x;
    }

    static double DegToRad(double d) {
        return d * M_PI / 180.0;
    }

    static double RadToDeg(double r) {
        return r * 180.0 / M_PI;
    }
};

inline Phasor operator+(Phasor lhs, const Phasor& rhs) { return lhs += rhs; }
inline Phasor operator-(Phasor lhs, const Phasor& rhs) { return lhs -= rhs; }
inline Phasor operator*(Phasor lhs, const Phasor& rhs) { return lhs *= rhs; }
inline Phasor operator/(Phasor lhs, const Phasor& rhs) { return lhs /= rhs; }

inline Phasor operator+(Phasor p, double x) { return p += x; }
inline Phasor operator-(Phasor p, double x) { return p -= x; }
inline Phasor operator*(Phasor p, double x) { return p *= x; }
inline Phasor operator/(Phasor p, double x) { return p /= x; }

inline Phasor operator+(double x, Phasor p) { return p + x; }
inline Phasor operator-(double x, Phasor p) { return Phasor(x, 0.0, AlgTag{}) - p; }
inline Phasor operator*(double x, Phasor p) { return p * x; }
inline Phasor operator/(double x, Phasor p) { return Phasor(x, 0.0) / p; }

inline Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

inline Phasor MakePhasorPolar(double mag, double phase_rad) {
    return Phasor(mag, phase_rad);
}

inline Phasor MakePhasorPolarDeg(double mag, double phase_deg) {
    return Phasor(mag, phase_deg, DegTag{});
}

inline std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    os << std::fixed << std::setprecision(3)
       << p.Magnitude()
       << "*e(j*" << p.PhaseDeg() << ") "
       << "[" << p.Real() << " + j*" << p.Imag() << "]";
    return os;
}