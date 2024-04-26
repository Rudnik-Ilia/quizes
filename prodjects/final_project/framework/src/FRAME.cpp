#include <FRAME.hpp>

namespace ilrd
{
    FRAME::FRAME(NBDServer& nbd): m_nbd(nbd) , m_reactor(std::move(std::unique_ptr<Listener>(new Listener()))), m_pool(6), m_factory(), m_transmit(new Transmitter(1234)), m_static_listen()
    {
        m_nbd.Start();
        m_reactor.Register({STDIN_FILENO, Reactor::ioMode::READ}, std::bind(&FRAME::StopFunc, this));
        m_reactor.Register({m_nbd.GetDescriptor(), Reactor::ioMode::READ}, std::bind(&FRAME::Run_NBD, this));
        m_reactor.Register({m_static_listen.GetFD(), Reactor::ioMode::READ}, std::bind(&FRAME::AddReadTask, this));

        Register(Reactor::ioMode::READ, Creator::Get_Read_Task);
        Register(Reactor::ioMode::WRITE, Creator::Get_Write_Task);
    };

    FRAME::~FRAME(){}

    void FRAME::Run_NBD()
    {
        if(m_nbd.Serve() == EXIT_FAILURE)
        {
            fprintf(stderr, "m_nbd.Serve(). errno: %d\n", errno);
            return;
        }

        m_nbd.GetArguments().get()->m_utils = m_transmit;
    
        if(m_nbd.GetArguments().get()->m_type == 33)
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
        if(m_nbd.GetArguments().get()->m_type == 3)
        {
            std::cout << "FLUSH" << std::endl; 
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

    void FRAME::AddReadTask()
    {
        std::cout << "REACTOR EVENT" << std::endl;
        // usleep(10000);
        m_static_listen.Receiver(m_nbd.GetDescriptor());
    }

}