#ifndef __ILRD_RD132_FACTORY_HPP__
#define __ILRD_RD132_FACTORY_HPP__

#include <functional>
#include <memory>
#include <unordered_map>
    
namespace ilrd
{

// any arguments that user wants to pass to creator_ should be publicly inherited from FactoryArgs
    struct FactoryArgs 
    {
        inline virtual ~FactoryArgs() = default;
    };


    template <class Base, class Key>
    class Factory
    {
    public:
        typedef std::function<std::shared_ptr<Base> (FactoryArgs&)> Value;

        Factory() = default;
        Factory(Factory &&) = delete;
        Factory(const Factory &) = delete;
        Factory &operator=(Factory &&) = delete;
        Factory &operator=(const Factory &) = delete;
        ~Factory() = default;

        void Register(const Key& key_, Value creator_);

        std::shared_ptr<Base> Create(const Key& key_, FactoryArgs& args_);

    private:
        std::unordered_map<Key, Value> m_creators;
        
    };

    template <class Base, class Key>
    void Factory<Base, Key>::Register(const Key& key_, Value creator_)
    {
        m_creators.insert({key_, creator_});
    }

    template <class Base, class Key>
    std::shared_ptr<Base> Factory<Base, Key>::Create(const Key& key_, FactoryArgs& args)
    {
        return ((m_creators.find(key_))->second)(args);
    }



} // namespace ilrd

#endif // __ILRD_RD132_FACTORY_HPP__
