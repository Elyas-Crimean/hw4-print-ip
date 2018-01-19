#include <limits>
#include <type_traits>
#include <iostream>
#include <string>
#include <type_traits>
#include <tuple>



/// Реализация для целых типов
template<typename T>
std::enable_if_t<std::is_integral<T>::value> print_ip(T ip, std::ostream &s = std::cout, bool eol = true) //void print_ip()
{
    static_assert(std::numeric_limits<T>::digits >= 7,"Bool not supported.");
    static const int N = (std::numeric_limits<T>::digits+1)/8;
    for(int i=0; i<N;++i){
        if(i>0){
            s<<'.';
        }
        s<<((ip >> 8*(N-1-i)) & 0xFF);
    }
    if(eol){
        s<<std::endl;
    }
}

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        std::conditional_t<
            false,
            is_container_helper<
                typename T::value_type,
                typename T::size_type,
                typename T::allocator_type,
                typename T::iterator,
                typename T::const_iterator,
                decltype(std::declval<T>().size()),
                decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                decltype(std::declval<T>().cbegin()),
                decltype(std::declval<T>().cend())
                >,
            void
            >
        > : public std::true_type {};


/// Реализация для контейнерных типов
template<typename T>
std::enable_if_t<is_container<T>::value> print_ip(T &ip, std::ostream &s = std::cout, bool eol = true)
{
    bool dot_skip = true;
    for(auto ip_part : ip) {
        if (dot_skip) {
			dot_skip = false;
        }else{
			s << ".";
		}
        s << (ip_part);
    }
    if(eol){
        s<<std::endl;
    }
};


///  Реализация для строки
void print_ip(std::string &ip, std::ostream &s = std::cout, bool eol = true)
{
    s << ip;
    if(eol){
        s<<std::endl;
    }
}


template <class T, class ... Candidates>
constexpr bool is_all_same() {
    bool pairs[] = {std::is_same<T,Candidates>::value...};
    for(bool p: pairs) if(!p) return false;
    return true;
}

template<int i, typename... Ts>
struct print_tuple
{
    void operator()(std::tuple<Ts...>& t,std::ostream& s){
        constexpr int N = std::tuple_size<std::tuple<Ts...>>::value;
        s << std::get<N-i-1>(t) << ".";
        print_tuple<i-1, Ts...>{}(t,s);
    }
};

template<typename... Ts>
struct print_tuple<0, Ts...>
{
    void operator()(std::tuple<Ts...>& t,std::ostream& s){
        constexpr int N = std::tuple_size<std::tuple<Ts...>>::value;
        s << std::get<N-1>(t);
    }
};


/// Реализация для  tuple
template<typename T,typename ...Args>
void print_ip(std::tuple<T ,T , Args...> &ip,std::ostream &s = std::cout, bool eol = true)
{
    static_assert(is_all_same<T, Args...>(),"same type of tuple elements supported only");
    constexpr int N = std::tuple_size<std::tuple<T ,T , Args...>>::value;
    print_tuple<N-1,T,T, Args...>{}(ip,s);
    if(eol){
        s<<std::endl;
    }
}

template<typename T>
void print_ip(std::tuple<T> &ip, std::ostream &s = std::cout, bool eol = true)
{
    s << std::get<0>(ip);
    if(eol){
        s<<std::endl;
    }
}
