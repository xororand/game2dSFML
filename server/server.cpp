#include "server.h"

server m_server = server();

int main() {
    while (m_server.is_started()) {
        m_server.accept_connections();
    }
}

server::server() {
    if (tcp_listener.listen(DEFAULT_TCP_SERVER_PORT) != Socket::Done)
        return;

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