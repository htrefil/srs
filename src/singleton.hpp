#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class singleton {
public:
	static T& get() {
		static T instance; 
	
		return instance;
	}
};

#endif