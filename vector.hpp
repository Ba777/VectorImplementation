#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>


#ifndef LNI_VECTOR
#define LNI_VECTOR

#define LNI_VECTOR_MAX_SZ 1000000000

namespace lni {

    template <typename T>
    class vector {


        public:
            typedef unsigned int                          size_type;
            typedef T *                                   iterator;
            typedef const T *                             const_iterator;
            typedef std::reverse_iterator<iterator>       reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

            vector() noexcept;
            explicit vector(size_type n);
            vector(size_type n, const T &val);
            vector(typename vector<T>::iterator , typename vector<T>::iterator );
            vector(std::initializer_list<T> lst);
            vector(const vector<T> &);
            vector(vector<T> &&) noexcept;

            ~vector();

            vector<T> & operator = (const vector<T> &);
            vector<T> & operator = (vector<T> &&);
            vector<T> & operator = (std::initializer_list<T>);

            void assign(typename vector<T>::size_type, const T &);
            void assign(typename vector<T>::iterator, typename vector<T>::iterator);
            void assign(std::initializer_list<T>);

            // iterators:
			iterator begin() noexcept;
			const_iterator cbegin() const noexcept;
			iterator end() noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator crbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator crend() const noexcept;

            bool empty() const noexcept;
			size_type size() const noexcept;
			size_type max_size() const noexcept;
			size_type capacity() const noexcept;

			void resize(size_type);

        private:
            size_type rsrv_sz = 4;
            size_type vec_sz = 0;
            T *arr;

            inline void reallocate();

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
			// I think this should be called off and have
			//another function where we could direcly write other.arr into arr..
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
		return *arr;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (vector<T> &&other) {
		size_type i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
        if(rsrv_sz < lst.size()) {
            rsrv_sz = lst.size() << 2;
            reallocate();
        }
        vec_sz = 0;
        for (auto &item: lst) {
            arr[vec_sz++] = item;
        }
	}

    template <typename T>
    void vector<T>::assign(typename vector<T>::size_type count, const T &value) {
        size_type i;
        if (count > rsrv_sz) {
                rsrv_sz = count << 2;
                reallocate();
        }
        for (i = 0; i < count; ++i) {
            arr[i] = value;
        }
        vec_sz = count;
    }

    template <typename T>
    void vector<T>::assign(typename vector<T>::iterator first, typename vector<T>::iterator last) {
        size_type i, count = last - first;
        if (count > rsrv_sz) {
            rsrv_sz = count << 2;
            reallocate();
        }
        for (i = 0; i < count; ++i, ++first) {
            arr[i] = *first;
        }
        vec_sz = count;
    }

    template <typename T>
    void vector<T>::assign(std::initializer_list<T> lst) {
        size_type i, count = lst.size();
        if (count > rsrv_sz) {
            rsrv_sz = count << 2;
            reallocate();
        }
        i = 0;
        for (auto &item: lst) {
            arr[i++] = item;
        }
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::begin() noexcept {
        return arr;
    }

    template <typename T>
    typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
        return arr;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::end() noexcept {
        return arr + vec_sz;
    }

    template <typename T>
    typename vector<T>::const_iterator vector<T>::cend() const noexcept {
        return arr + vec_sz;
    }

    template <typename T>
    typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
        return reverse_iterator(arr + vec_sz);
    }

    template <typename  T>
    typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
        return reverse_iterator(arr);
    }

    template  <typename T>
    typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
        return reverse_iterator(arr + vec_sz);
    }

    template <typename T>
    typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
        return reverse_iterator(arr);
    }


    template <typename T>
    inline void vector<T>::reallocate() {
        T *tarr = new T[rsrv_sz];
        memcpy(tarr, arr, vec_sz * sizeof(T));
        delete [] arr;
        arr = tarr;
    }

    template <typename T>
	typename vector<T>::size_type vector<T>::size() const noexcept{
		return vec_sz;
	}

	template <typename T>
	bool vector<T>::empty() const noexcept {
        return vec_sz == 0;
	}

    template <typename T>
    typename vector<T>::size_type vector<T>::max_size() const noexcept {
        return LNI_VECTOR_MAX_SZ;
    }

    template <typename T>
    typename vector<T>::size_type vector<T>::capacity() const noexcept {
        return rsrv_sz;
    }

    template <typename T>
    void vector<T>::resize(typename vector<T>::size_type sz) {
        if(sz > vec_sz) {
           if(sz > rsrv_sz) {
                rsrv_sz = sz;
                reallocate();
           }
        } else {
            size_type i;
            for (i = vec_sz; i > sz; --i) {
                arr[i].~T();
            }
        }
        vec_sz = sz;
    }

    template <typename T>
    void vector<T>::resize(typename vector<T>::size_type sz, const T &c) {
        if (sz > vec_sz) {
            if (sz > rsrv_sz) {
                rsrv_sz = sz;
                reallocate();
            }
            size_type i;
            for (i = vec_sz; i < sz; ++i) {
                arr[i] = c;
            }
        } else {
            size_type i;
            for (i = vec_sz; i > sz; --i) {
                arr[i].~T();
            }
            vec_sz = sz;
        }
    }

    template <typename T>
    void vector<T>::reserve(typename vector<T>::size_type _sz) {
        if (_sz > rsrv_sz) {
            rsrv_sz = _sz;
            reallocate();
        }
    }

    template <typename T>
    void vector<T>::shrink_to_fit() {
        rsrv_sz = vec_sz;
        reallocate();
    }
}

#endif // LNI_VECTOR

