#include <FRAME.hpp>

namespace ilrd
{
    FRAME::FRAME(NBDServer& nbd): m_nbd(nbd) , m_reactor(std::move(std::unique_ptr<Listener>(new Listener()))), m_pool(6), m_factory(), m_transmitter()
    {
        m_nbd.Start();
        m_reactor.Register({STDIN_FILENO, Reactor::ioMode::READ}, std::bind(&FRAME::StopFunc, this));
        m_reactor.Register({m_nbd.GetDescriptor(), Reactor::ioMode::READ}, std::bind(&FRAME::Run_NBD, this));
    };

    FRAME::~FRAME()
    {

    }

    void FRAME::Run_NBD()
    {
        if(m_nbd.Serve() == EXIT_FAILURE)
        {
            fprintf(stderr, "m_nbd.Serve(). errno: %d\n", errno);
            return;
        }

        if(m_nbd.GetArguments().get()->m_type == NBD_CMD_READ)
        {
            auto task = m_factory.Create(Reactor::ioMode::READ, *(m_nbd.GetArguments().get()));
            m_pool.AddTask(task, ThreadPool::PRIORITY_HIGH);
            return;
        }
        if(m_nbd.GetArguments().get()->m_type == NBD_CMD_WRITE)
        {
            auto task = m_factory.Create(Reactor::ioMode::WRITE, *(m_nbd.GetArguments().get()));
            m_pool.AddTask(task, ThreadPool::PRIORITY_HIGH);
            return;
        }

    }

    void FRAME::Run_Reactor()
    {
        m_reactor.Run();
    }

    void FRAME::Register(const Reactor::ioMode& key, std::function<std::shared_ptr<ITask> (FactoryArgs&)> creator)
    {
        m_factory.Register(key, creator);
    }

}