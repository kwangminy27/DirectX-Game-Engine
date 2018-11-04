#pragma once

using namespace std;
using namespace DG;

template <typename T>
unique_ptr<T, function<void(T*)>> Singleton_Temp<T>::singleton_;
template <typename T>
once_flag Singleton_Temp<T>::once_flag_;

template <typename T>
unique_ptr<T, function<void(T*)>>& Singleton_Temp<T>::singleton()
{
	call_once(once_flag_, []() {
		singleton_ = unique_ptr<T, function<void(T*)>>{ new T, [](T* _p) {
			_p->_Release();
			delete _p;
		} };
		singleton_->Initialize();
	});

	return singleton_;
}