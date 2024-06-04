#include "server.h"

server m_server;

int main() {
    setlocale(LC_ALL, "ru-RU");
    
    while (m_server.is_started()) {
        m_server.accept_connections();
    }
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
    sf::TcpSocket c;
    if (tcp_listener.accept(c) != sf::Socket::Done) { return; }

    cout << c.getRemoteAddress().toString() << ":"<< c.getLocalPort() << " новое подключение" << endl;
}