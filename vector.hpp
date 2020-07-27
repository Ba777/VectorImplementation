


#ifndef LNI_VECTOR
#define LNI_VECTOR

#define LNI_VECTOR_MAX_SZ 1000000000

namespace lni {

    template <typename T>
    class vector {


        public:
            typedef unsigned int                          size_type;
            typedef T *                                   iterator;

            vector() noexcept;
            explicit vector(size_type n);
            vector(size_type n, const T &val);
            vector(typename vector<T>::iterator , typename vector<T>::iterator );
            vector(std::initializer_list<T> lst);

        private:
            size_type rsrv_sz = 4;
            size_type vec_sz = 0;
            T *arr;

    };


    template <typename T>
    vector<T>::vector() noexcept {
        arr = new T[rsrv_sz];
    }

    template <typename T>
    vector<T>::vector(typename vector<T>::size_type n) {
        size_type i;
        rsrv_sz = n << 2;
        arr = new T[rsrv_sz];
        for (i = 0; i < n; ++i) {
            arr[i] = T();
        }
        vec_sz = n;
    }

    template <typename T>
    vector<T>::vector(typename vector<T>::size_type n, const T &value) {
        size_type i;
        rsrv_sz = n << 2;
        arr = new T[rsrv_sz];
        for (i = 0; i < n; ++i) {
            arr[i] = value;
        }
        vec_sz = n;
    }


    template <typename T>
    vector<T>::vector(typename vector<T>::iterator first, typename vector<T>::iterator last) {
        size_type i, count = last - first;
        rsrv_sz = count << 2;
        arr = new T[rsrv_sz];
        for (i=0; i < count ; ++i, ++first) {
            arr[i] = *first;
        }
        vec_sz = count;
    }

    // Initializing a vector with elements.
    template <typename T>
    vector<T>::vector(std::initializer_list<T> lst) {
        rsrv_sz = lst.size() << 2;
        arr = new T[rsrv_sz];
        for (auto &item: lst) {
            arr[vec_sz++] = item;
        }
    }

    // Copying one vector elements to another new vector.
    template <typename T>
    vector<T>::vector(const vector<T> &other) {
        size_type i;
        rsrv_sz = other.rsrv_sz;
        arr = new T[rsrv_sz];
        for (i = 0; i < other.vec_sz; ++i) {
            arr[i] = other.arr[i];
        }
        vec_sz = other.vec_sz;
    }

    template <typename T>
    vector<T>::vector(vector<T> &&other) noexcept {
        size_type i;
        rsrv_sz = other.rsrv_sz;
        arr = new T[rsrv_sz];
        for (i = 0; i < other.vec_sz; ++i) {
            arr[i] = std::move(other.arr[i]);
        }
        vec_sz = other.vec_sz;
    }

    template <typename T>
    vector<T>::~vector() {
        delete [] arr;
    }

    template <typename T>
	vector<T> & vector<T>::operator = (const vector<T> &other) {
		size_type i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
		return *arr;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (vector<T> &&other) {
		size_type i;
		if (rsrv_sz < other.vec_sz) {&
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

}

#endif // LNI_VECTOR

