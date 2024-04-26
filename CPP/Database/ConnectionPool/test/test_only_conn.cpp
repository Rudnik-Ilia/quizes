#include <iostream>
#include <pqxx/pqxx>
#include <unistd.h> 
#include <memory>

// -lstdc++


// -lpqxx -lpq

int main()
{
    try
    {
        pqxx::connection conn("dbname = ilia user = ilia password = 12345 hostaddr = 172.19.0.3 port = 5432");
        // std::shared_ptr<pqxx::connection> conn(new pqxx::connection("dbname = ilia user = ilia password = 12345 hostaddr = 172.19.0.3 port = 5432"));

        // auto conn = std::make_shared<pqxx::connection>("dbname = ilia user = ilia password = 12345 hostaddr = 172.19.0.3 port = 5432");

        // if (conn.get()->is_open())
        if (conn.is_open())
        {
            std::cout << "Opened database successfully: " << conn.dbname() << std::endl;
            // std::cout << "Opened database successfully: " << conn.get()->dbname() << std::endl;
        } 
        else 
        {
            std::cout << "Can't open database" << std::endl;
        }

        // std::string sql = "SELECT * FROM categories;";

        // pqxx::work W(conn);
        // W.exec(sql_change);
        // W.commit();

        // pqxx::nontransaction N(*conn.get());
        // pqxx::result R(N.exec(sql));
        // std::cout << "NUMBER : " << R.columns() << std::endl;

        // for(auto iter : R) 
        // {
        //     std::cout << iter[0].as<int>() << '\t' << iter[1].as<std::string>() << '\t' << iter[2].as<std::string>()<< '\t' << iter[3].as<std::string>() << std::endl;
        // }
        conn.disconnect();
        

    }
    catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return 0;
}