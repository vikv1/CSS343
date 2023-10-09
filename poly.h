#ifndef POLY_H
#define POLY_H

#include <iostream>

using namespace std;

class Poly {
  // Output operator overload
  friend ostream &operator<<(ostream &o, const Poly &other);

  // Input operator overload
  friend istream &operator>>(istream &i, const Poly &other);

public:
  // Constructor that takes coefficient and degree
  Poly(int coefficient, int largestPower);

  // Constructor that only takes coefficient
  Poly(int coefficient);

  // Deep Copy constructor
  Poly(const Poly &other);

  // Default constructor
  Poly();

  // Destructor
  virtual ~Poly();

  // Addition operator
  Poly operator+(const Poly &other) const;

  // Addition Assignment operator
  Poly &operator+=(const Poly &other);

  // Subtraction operator
  Poly operator-(const Poly &other) const;

  // Subtraction Assignment operator
  Poly &operator-=(const Poly &other);

  // Multiplication Operator
  Poly operator*(const Poly &other) const;

  // Multiplication Assignment operator
  Poly &operator*=(const Poly &other);

  // Assignment Operator
  Poly &operator=(Poly other);

  // == Operator
  bool operator==(const Poly &other) const;

  // != Operator
  bool operator!=(const Poly &other) const;

  // Getter that retrieves coefficients by power
  int getCoeff(int power) const;

  // Setter that sets coefficients by power
  void setCoeff(int coeff, int power);

private:
  // Array to hold values
  int *coeffPtr = nullptr;

  // Default array size
  int arrSize = 1;

  // swap helper method for Assignment operator
  void swap(Poly &first, Poly &second);
};

#endif