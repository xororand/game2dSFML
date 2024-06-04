#include "server.h"

server m_server;

int main() {
    setlocale(LC_ALL, "ru-RU");

    m_server.add_thread(server::threadtype::new_connections);

    for (int i = 0; i < CPU_THREADS_MAX_COUNT - 1; i++) {
        m_server.add_thread(server::threadtype::process_connected);
    }

    m_server.start();
}

server::server() {
    
    cout << "Starting OUR GREATE server..." << endl;
    

    if (tcp_listener.listen(DEFAULT_TCP_SERVER_PORT) != Socket::Done) {
        cout << "Server is NOT STARTED" << endl;
        return;
    }

    cout << "Server is STARTED on port "<< tcp_listener.getLocalPort() << endl;

    m_is_started = true;
}
bool server::is_started() {
    return m_is_started;
}
void server::accept_connections() {
    cout << "Начало потока новых клиентов\n";
    while (m_server.is_started()) {
        TcpSocket* c = new TcpSocket();

        if (tcp_listener.accept(*c) != sf::Socket::Done) { return; }

        cout << c->getRemoteAddress().toString() << ":" << c->getLocalPort() << " новое подключение" << endl;

        playerPeer* newPeer = new playerPeer();

        newPeer->set_tcp_socket(c);
        newPeer->set_public_hash(utils::hashing::sha256(c->getRemoteAddress().toString() + utils::strings::get_rand_string(32)));
        newPeer->set_private_hash(utils::hashing::sha256(c->getRemoteAddress().toString() + utils::strings::get_rand_string(64)));
        newPeer->set_timestamp(time(0));

        players.push_back(newPeer);
        Sleep(1000); // УБРАТЬ КОГДА НЕ НАДО БУДЕТ
    }
}
void server::process_connected() {
    cout << "Начало потока обработки клиентов\n";
    while (m_server.is_started()) {
        Sleep(1000); // УБРАТЬ КОГДА НЕ НАДО БУДЕТ
    }
}
void server::add_thread(threadtype type) {
    Thread* t;
    switch (type) {
    case threadtype::new_connections:
        t = new Thread(&server::accept_connections, &m_server);
        break;
    case threadtype::process_connected:
        t = new Thread(&server::process_connected, &m_server);
        break;
    }
    
    threads.push_back(t);
}
void server::start() {
    for (auto t : threads)
        t->launch();
    cout << "start main thread\n";

    for (auto t : threads)
        t->wait();

    /*while (1) { Sleep(100); }*/
}