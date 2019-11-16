#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class SingleTon{
private:
    SingleTon(){}
    SingleTon(const SingleTon& singleTon)=delete;

    static SingleTon* instance;
    T singleTon;
public:
    static T* getInstance(){
        if(instance == nullptr) instance = new SingleTon;
        return &(instance->singleTon);
    }
    static T& getReference(){
        return *getInstance();
    }
};

template<class T>
SingleTon<T>* SingleTon<T>::instance = nullptr;

#endif // SINGLETON_H
