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
    tcp_listener.setBlocking(true);
    cout << "TCP Blocking is " << (tcp_listener.isBlocking() ? "True" : "False") << endl;

    m_is_started = true;
}

void server::sync_clients() {

}

void server::tcp_new_connections() {
    int* thread_id = new int(thread_count);
    thread_count++;
    cout << format("Начало потока обработки подключения клиентов #{}\n", *thread_id);

    while (m_server.is_started()) {
        TcpSocket* c = new TcpSocket();

        if (tcp_listener.accept(*c) != sf::Socket::Done) {
            delete c;
            return;
        }

        serverPlayerPeer* peer = new serverPlayerPeer();

        peer->set_tcp_socket(c);
        peer->set_public_hash(utils::hashing::sha256(c->getRemoteAddress().toString() + utils::strings::get_rand_string(32)));
        peer->set_private_hash(utils::hashing::sha256(c->getRemoteAddress().toString() + utils::strings::get_rand_string(64)));
        peer->set_player_name(peer->get_public_hash());
        peer->set_timestamp(time(0));

        bool success = peer->create_player_node(peer->get_public_hash(), peer->get_private_hash(), v2f(0.0, 0.0), true);

        // Если не получилось отправить первый пакет нашему игроку, значит НАХУЙ ЕГО И В ПИЗДУ
        if (!success) {
            delete c;
            delete peer;
            return;
        }

        // ↓ ↓ ↓ Пакет был отправлен успешно, добавляем пир в наш массив и тд и тп ↓ ↓ ↓

        peers.push_back(peer);

        send_msg_to_all(format("{} подключился к серверу", peer->get_public_hash()));

        cout << c->getRemoteAddress().toString() << ":" << c->getLocalPort() << " новое подключение" << endl;
    }
}
void server::process_connected() {
    int* thread_id = new int(thread_count);
    thread_count++;
    cout << format("Начало потока обработки клиентов #{}\n", *thread_id);
    while (m_server.is_started()) {

        sync_clients();
        Sleep(1000); // УБРАТЬ КОГДА НЕ НАДО БУДЕТ
    }
}

void server::add_thread(threadtype type) {
    Thread* t = new Thread(&server::process_connected, &m_server);
    switch (type) {
    case threadtype::new_connections:
        t = new Thread(&server::tcp_new_connections, &m_server);
        break;
    case threadtype::process_connected:
        t = new Thread(&server::process_connected, &m_server);
        break;
    }

    threads.push_back(t);
}
void server::start() {
    for (int i = threads.size() - 1; i >= 0; i--)
        threads[i]->launch();
    cout << "start main thread\n";

    //while (1) { cout << "main thread\n"; Sleep(1000); }

    for (auto t : threads)
        t->wait();
}
bool server::is_started() { return m_is_started; }

void server::send_msg_to_all(string text) {
    for (auto p : peers) {
        bool success = p->send_chat_msg(text);
    }
}