#include "poly.h"
#include <sstream>

/**
 * @brief Construct a new Poly Object
 *
 * @param coefficient
 * @param largestPower
 */
Poly::Poly(int coefficient, int largestPower) : arrSize(largestPower + 1) {
   // had to use calloc instead of new[] because was getting
   // uninitialized value error in the << overload
  coeffPtr = (int *)calloc(arrSize, sizeof(int));
  coeffPtr[arrSize - 1] = coefficient;
}

/**
 * @brief Construct a new Poly object
 *
 * @param coefficient
 */
Poly::Poly(int coefficient) {
  coeffPtr = (int *)calloc(arrSize, sizeof(int));
  coeffPtr[arrSize - 1] = coefficient;
}

/**
 * @brief Copy constructor for a new poly object
 *
 * @param other
 */
Poly::Poly(const Poly &other) {
  arrSize = other.arrSize;
  coeffPtr = (int *)calloc(arrSize, sizeof(int));
  for (int i = 0; i < arrSize; i++) {
    coeffPtr[i] = other.coeffPtr[i];
  }
}

/**
 * @brief Default constructor
 *
 */
Poly::Poly() {
  coeffPtr = (int *)calloc(arrSize, sizeof(int));
  coeffPtr[arrSize - 1] = 0;
}

/**
 * @brief Destructor
 *
 */
Poly::~Poly() { free(coeffPtr); }

/**
 * Helper method for assignment operator
 * swaps the fields of first and second
 *
 * @param first
 * @param second
 */
void Poly::swap(Poly &first, Poly &second) {
  int *temp = first.coeffPtr;
  first.coeffPtr = second.coeffPtr;
  second.coeffPtr = temp;

  int tempArrSize = first.arrSize;
  first.arrSize = second.arrSize;
  second.arrSize = tempArrSize;
}

/**
 * Assignment operator to assign other to this.
 * Other is not passed by reference because the swap method used
 * directly modifies other.
 *
 * @param other
 * @return Poly&
 */
Poly &Poly::operator=(Poly other) {
  swap(*this, other);
  return *this;
}

/**
 * @brief Addition operator overload
 *
 *
 * @param other
 * @return Poly
 */
Poly Poly::operator+(const Poly &other) const {
  // if both array sizes equal, the degrees will be equal so can just add
  // elements directly
  if (this->arrSize == other.arrSize) {
    Poly temp(0, this->arrSize);
    for (int i = 0; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] + other.coeffPtr[i];
    }

    return temp;
  } else if (this->arrSize > other.arrSize) {
    Poly temp(0, this->arrSize);
    // add together like exponents
    for (int i = 0; i < other.arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] + other.coeffPtr[i];
    }

    // "append" the non modified values
    for (int i = other.arrSize; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i];
    }

    return temp;
  } else {
    Poly temp(0, other.arrSize);
    // add together like exponents
    for (int i = 0; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] + other.coeffPtr[i];
    }

    // "append" the non modified values
    for (int i = this->arrSize; i < other.arrSize; i++) {
      temp.coeffPtr[i] = other.coeffPtr[i];
    }

    return temp;
  }
}

/**
 * @brief Addition assignment operator
 *
 * @param other
 * @return Poly&
 */
Poly &Poly::operator+=(const Poly &other) {
  *this = *this + other;
  return *this;
}

/**
 * @brief Subtraction operator
 *
 * @param other
 * @return Poly
 */
Poly Poly::operator-(const Poly &other) const {
  // both polys are same size, just subtract directly
  if (this->arrSize == other.arrSize) {
    Poly temp(0, this->arrSize);
    for (int i = 0; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] - other.coeffPtr[i];
    }

    return temp;
  } else if (this->arrSize > other.arrSize) {
    Poly temp(0, this->arrSize);

    // subtract like terms
    for (int i = 0; i < other.arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] - other.coeffPtr[i];
    }

    // "append" terms from lhs poly, not flipping sign because it is lhs - rhs
    for (int i = other.arrSize; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i];
    }

    return temp;
  } else {
    Poly temp(0, other.arrSize);
    // subtract like terms
    for (int i = 0; i < this->arrSize; i++) {
      temp.coeffPtr[i] = this->coeffPtr[i] - other.coeffPtr[i];
    }

    // "append" terms from rhs poly, flip sign because lhs - rhs
    for (int i = this->arrSize; i < other.arrSize; i++) {
      temp.coeffPtr[i] = other.coeffPtr[i] * -1;
    }

    return temp;
  }
}

/**
 * @brief Subtraction assignment operator
 *
 * @param other
 * @return Poly&
 */
Poly &Poly::operator-=(const Poly &other) {
  *this = *this - other;
  return *this;
}

/**
 * @brief Multiplication operator
 *
 * @param other
 * @return Poly
 */
Poly Poly::operator*(const Poly &other) const {
  // new degree is highest exponents added together
  // arrSize - 1 = degree
  int newDegree = (this->arrSize - 1) + (other.arrSize - 1);
  Poly temp(0, newDegree + 1);

  // essentially FOIL'ing the polys together
  for (int i = 0; i < this->arrSize; i++) {
    for (int j = 0; j < other.arrSize; j++) {
      // coeffPtr[i + j] because adding exponents,
      // += because dont want to overwrite
      temp.coeffPtr[i + j] += this->coeffPtr[i] * other.coeffPtr[j];
    }
  }

  return temp;
}

/**
 * @brief Multiplication assignment operator
 *
 * @param other
 * @return Poly&
 */
Poly &Poly::operator*=(const Poly &other) {
  *this = *this * other;
  return *this;
}

/**
 * @brief == operator to check if 2 polynomials are equal based on values
 *
 * @param other
 * @return true
 * @return false
 */
bool Poly::operator==(const Poly &other) const {
  if (arrSize != other.arrSize) {
    return false;
  }

  for (int i = 0; i < this->arrSize; i++) {
    if (this->coeffPtr[i] != other.coeffPtr[i]) {
      return false;
    }
  }

  return true;
}

/**
 * @brief != operator, just inverse of == operator
 *
 * @param other
 * @return true
 * @return false
 */
bool Poly::operator!=(const Poly &other) const { return !(*this == other); }

/**
 * @brief Returns coefficient associated with an exponent
 *
 *
 * @param power
 * @return int
 * @return INT_LEAST8_MIN if power not valid
 */
int Poly::getCoeff(int power) const {
  if (power < 0 || power >= arrSize) {
    return INT_LEAST8_MIN;
  }
  return coeffPtr[power];
}

/**
 * @brief Setter method to set the coefficient of a power to coeff
 *
 * @param coeff
 * @param power
 */
void Poly::setCoeff(int coeff, int power) {
  if (power >= arrSize) {
    int newArrSize = power + 1;
    int *newCoeffPtr = (int *)calloc(newArrSize, sizeof(int));

    for (int i = 0; i < arrSize; i++) {
      newCoeffPtr[i] = coeffPtr[i];
    }

    free(coeffPtr);
    coeffPtr = newCoeffPtr;
    arrSize = newArrSize;
    newCoeffPtr = nullptr;
  }

  if (power < arrSize && power >= 0) {
    coeffPtr[power] = coeff;
  }
}

/**
 * @brief << operator overload to print a polynomial by it's values
 *
 * @param o
 * @param other
 * @return ostream&
 */
ostream &operator<<(ostream &o, const Poly &other) {
  // if poly doesnt exist
  if (other.coeffPtr == nullptr) {
    o << "0";
  } else {
    bool printed = false;
    // iterate backwards because printing from degree backwards
    for (int i = other.arrSize - 1; i >= 0; i--) {
      if (other.coeffPtr[i] != 0) {
        // if not first value, put a space before
        if (printed) {
          o << " ";
        }

        // put a + if positive
        if (other.coeffPtr[i] > 0) {
          o << "+";
        }

        // if no exponent
        if (i == 0) {
          o << other.coeffPtr[i];
        } else if (i == 1) { // if exponent == 1
          o << other.coeffPtr[i] << "x";
        } else { // if exponent > 1
          o << other.coeffPtr[i] << "x^" << i;
        }

        printed = true;
      }
    }

    // if coeffPtr != nullptr but no non zero values
    if (!printed) {
      o << "0";
    }
  }

  return o;
}

/**
 * @brief >> operator overload that takes either a full string of val exp pairs
 * or takes pairs of val exp individually
 *
 * An inner loop is used to both handle when pairs are input one at a time
 * and when the whole polynomial is input at once
 *
 * @param i
 * @param other
 * @return istream&
 */
istream &operator>>(istream &i, const Poly &other) {
  // bool to keep track of whether inner loop was broken
  bool broken = false;
  while (!broken) {
    int coeff = 0;
    int power = 0;

    string input;
    getline(i, input);

    stringstream s(input);

    // used to tell whether looking at coefficient or exponent
    bool isCoeff = true;

    string number;

    // while there is a number left in input
    while (s >> number) {
      if (isCoeff) {
        coeff = stoi(number);
      } else {
        power = stoi(number);
      }

      if (coeff == -1 && power == -1) {
        broken = true;
        break;
      } else if (power != -1 && !isCoeff) {
        other.coeffPtr[power] = coeff;
      }

      isCoeff = !isCoeff;
    }

    // if broke out of inner while loop due to -1 -1, break out of outer loop
    // too
    if (broken) {
      break;
    }

    if (coeff == -1 && power == -1) {
      return i;
    }

    if (power != -1) {
      other.coeffPtr[power] = coeff;
    }
  }

  return i;
}