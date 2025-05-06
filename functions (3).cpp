#include <climits>
#include <stdexcept>

bool SumIsEven(int a, int b) {
  if((a + b) % 2 == 0) {
    return true;
  }
  return false;
}

int Largest(int a, int b, int c) {
  int d = a;
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}

int BoxesNeeded(int apples) {
  int boxes = apples / 20;
  if(apples % 20 != 0) {
    boxes = 1 + (apples / 20);
  }
  if(apples < 0) {
    boxes = 0;
  }
  return boxes;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  double a_corr = A_correct;
  double atotal = A_total;
  double bcorr = B_correct;
  double btotal = B_total;
  double a_score = a_corr / atotal;
  double b_score = bcorr / btotal;
  if(a_corr > atotal || bcorr > btotal || a_corr < 0 || atotal < 0 || bcorr < 0 || btotal < 0) {
    throw std::invalid_argument("");
  }
  if(a_score > b_score) {
    return true;
  }
  return false;
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10) {
    if(is_weekend == true) {
      return true;
    }
    else if(is_weekend == false && pizzas <= 20) {
      return true;
    }
  }
  return false;
}

long long int SumBetween(long long int low, long long int high) {
  long long int diff = high;
    long long int sum = 0;
    if(low > high) {
        throw std::invalid_argument("invalid");
    }
    if(low < 0 && high > 0) {
        long long int neghigh = -1 * high;
        if(neghigh < low) {
            low = (-1 * low) + 1;
        }
        if(neghigh > low) {
            diff = neghigh - 1;
        }
    }
    for(long long int i = low; i <= diff; i++) {
        if(i > 0 && sum > (LLONG_MAX - i) && sum != 0) {
            throw std::overflow_error("overflow");
        }
        if(i < 0 && sum < (LLONG_MIN - i) && sum != 0) {
            throw std::overflow_error("overflow");
        }
        sum += i;
    }
    return sum;
}

long long int Product(long long int a, long long int b) {
  long long int prod = a * b;
  if((a > 0) && (b > 0)) {
    if(a > (LLONG_MAX / b)) {
      throw std::overflow_error("overflow");
    }
  }
  if((a < 0) && (b < 0)) {
    if(a < (LLONG_MAX / b)) {
      throw std::overflow_error("overflow");
    }
  }
  if(a > 0 && b < 0) {
    if(a > (LLONG_MIN / b)) {
      throw std::overflow_error("overflow");
    }
  }
  if(a < 0 && b > 0) {
    if(b > (LLONG_MIN / a)) {
      throw std::overflow_error("overflow");    
    }
  }
  return prod;
}