//
// Tomás Oliveira e Silva, AED, November 2021
//
// Generic stack (First In Last Out) implementation based on an array
//

#ifndef _AED_aStack_
#define _AED_aStack_

#include <cassert>

template <typename T> class aStack {

  private:
    int max_size; // maximum stack size
    int cur_size; // current stack size
    T *data;      // the stack data (stored in an array)

    int growStack() {
      T *newData = new T[cur_size + 100];
      for (int i = 0; i < max_size; i++) {
        newData[i] = data[i];
      }

      data = newData;
      return 0;
    }

  public:
    aStack(int n = 100) {
        assert(n >= 10 && n <= 1000000);
        max_size = n;
        cur_size = 0;
        data = new T[n];
    }

    ~aStack(void) { delete[] data; }

    void clear(void) { cur_size = 0; }

    int size(void) const { return cur_size; }

    int is_full(void) const { return (cur_size == max_size) ? 1 : 0; }

    int is_empty(void) const { return (cur_size == 0) ? 1 : 0; }

    T top(void) const {
        assert(cur_size > 0);
        return data[cur_size - 1];
    }

    void push(T &v) {
        if(is_full()) { growStack(); };
        data[cur_size++] = v;
    }

    T pop(void) {
        assert(cur_size > 0);
        return data[--cur_size];
    }
};

#endif
