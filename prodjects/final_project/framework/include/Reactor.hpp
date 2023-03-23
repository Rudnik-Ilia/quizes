#ifndef __ILRD_RD132_REACTOR_HPP__
#define __ILRD_RD132_REACTOR_HPP__

#include <functional>
#include <map>
#include <list>
#include <memory>

namespace ilrd
{
    class IFDListener;

    class Reactor
    {
        public:
            enum class ioMode
            {
                READ,
                WRITE
            };

            using EventCallback = std::function<void()>;

            using EventKey = std::pair<int, ioMode>;
            using ConnectionMap = std::map<EventKey, EventCallback>;

            using ListenerPtr = std::unique_ptr<IFDListener>;

            Reactor(ListenerPtr listener_);
            ~Reactor();

            Reactor(Reactor &&) = delete;
            Reactor(const Reactor &) = delete;
            Reactor &operator=(Reactor &&) = delete;
            Reactor &operator=(const Reactor &) = delete;

            void Register(const EventKey &key_, EventCallback handler_);
            void Unregister(const EventKey &key_);

            void Run();
            void Stop();

        private:
            ConnectionMap m_connections;
            ListenerPtr m_listener;
            bool m_stop_flag{false};
    };

    /***************************************************************************************/

    class IFDListener
    {
        public:
            IFDListener() = default;
            IFDListener(IFDListener &&) = default;
            IFDListener(const IFDListener &) = default;
            IFDListener &operator=(IFDListener &&) = default;
            IFDListener &operator=(const IFDListener &) = default;

            virtual ~IFDListener() = default;
            virtual std::list<Reactor::EventKey> Listen(const Reactor::ConnectionMap &) = 0;
    };
}

#endif /* __ILRD_RD132_REACTOR_HPP__ */
