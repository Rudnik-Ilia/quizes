#ifndef __ILRD_RD132_DISPATCHER_HPP__
#define __ILRD_RD132_DISPATCHER_HPP__

#include <iostream>
#include <functional>
#include <set>

// gp11 test_dispatcher.cpp -I ../include

namespace ilrd
{
    template <typename... EventArgs>
    class Dispatcher;

    template <typename... EventArgs>
    class Callback
    {
        public:
            using Handler = std::function<void(const EventArgs&...)>;

            explicit Callback(Handler function);
        
            Callback(Callback &&) = default;
            Callback(const Callback &) = default;
            Callback &operator=(Callback &&) = default;
            Callback &operator=(const Callback &) = default;
            ~Callback() = default;
            

            bool operator<(const Callback &rhs_) const;

        private:
            Handler m_function;
            friend class Dispatcher<EventArgs...>;
            void Notify(const EventArgs &...) const;
            virtual void Death() const;
        }; 

        template <typename... EventArgs>
        class Dispatcher
        {
        public:
            Dispatcher(): dispatcher_alive(true){};
            Dispatcher(Dispatcher &&) = default;
            Dispatcher(const Dispatcher &) = default;
            Dispatcher &operator=(Dispatcher &&) = default;
            Dispatcher &operator=(const Dispatcher &) = default;


            ~Dispatcher();
            void Subscribe(const Callback<EventArgs...> &callback_);
            void Unsubscribe(const Callback<EventArgs...> &callback_);
            void Dispatch(const EventArgs &...args_) const;

        private:
            std::set<const Callback<EventArgs...> *> m_subscribers;
            bool dispatcher_alive;
        };

        /*****************************************************************************************/
        template <typename... EventArgs>
        Callback<EventArgs...>::Callback(Handler function) : m_function(function){}

        template <typename... EventArgs>
        bool Callback<EventArgs...>::operator<(const Callback &rhs_) const
        {
            return &(this->m_function) < &rhs_.m_function;
        }

        template <typename... EventArgs>
        void Callback<EventArgs...>::Notify(const EventArgs &... arg_) const
        {
            m_function(arg_...);
        }

        /*****************************************************************************************/
        template <typename... EventArgs>
        void Dispatcher<EventArgs...>::Subscribe(const Callback<EventArgs...> &callback_)
        {
            m_subscribers.insert(&callback_);
        }

        template <typename... EventArgs>
        void Callback<EventArgs...>::Death() const
        {
            std::cout << "The DISPATCHER is OVER!!!" << std::endl;
        }

        template <typename... EventArgs>
        Dispatcher<EventArgs...>::~Dispatcher()
        {
            dispatcher_alive = false;

            for (auto iter : m_subscribers)
            {
                iter->Death();
            }
        }

        template <typename... EventArgs>
        void Dispatcher<EventArgs...>::Unsubscribe(const Callback<EventArgs...> &callback_)
        {
            #ifdef NDEBUG
            std::cout << m_subscribers.size() << std::endl;
            #endif 
            m_subscribers.erase(&callback_);
             #ifdef NDEBUG
            std::cout << m_subscribers.size() << std::endl;
            #endif

        }

        template <typename... EventArgs>
        void Dispatcher<EventArgs...>::Dispatch(const EventArgs &...args_) const
        {
            for(auto iter: m_subscribers)
            {
                iter->Notify(args_...);
            }
        }
} // namespace ilrd

#endif /* __ILRD_RD132_DISPATCHER_HPP__ */
