#include "server.h"

server m_server;

int main() {
    setlocale(LC_ALL, "ru-RU");

    //m_server.add_thread(server::threadtype::new_connections);

    for (int i = 0; i < CPU_THREADS_MAX_COUNT * 2; i++) {
        m_server.add_thread();
    }

    m_server.start();
}

server::server() {  
    cout << "Starting OUR GREATE server..." << endl;

    if (tcp_listener.listen(DEFAULT_TCP_SERVER_PORT) != Socket::Done) {
        cout << "Server is NOT STARTED cause someone USING TCP PORT: " << DEFAULT_TCP_SERVER_PORT << endl;
        return;
    }
    if (udp_socket.bind(DEFAULT_UDP_SERVER_PORT) != Socket::Done) {
        cout << "Server is NOT STARTED cause someone USING UDP PORT: " << DEFAULT_TCP_SERVER_PORT << endl;
        return;
    }

    tcp_listener.setBlocking(false);
    udp_socket.setBlocking(false);
    //cout << "TCP Blocking is " << (tcp_listener.isBlocking() ? "True" : "False") << endl;

    cout << "Server is STARTED on port tcp:"<< tcp_listener.getLocalPort() << " / udp:" << udp_socket.getLocalPort() << endl;

    m_is_started = true;
}

void server::sync_clients() {

}

void server::udp_process_packets() {
    Packet p;
    IpAddress sender_ip;
    unsigned short port;

    if (udp_socket.receive(p, sender_ip, port) != Socket::Done) return;

    // TODO: ОБРАБОТКУ UDP ПОДКЛЮЧЕНИЙ НА ОСНОВЕ ПОДКЛЮЧЕННОГО TCP
    std::string json_string(static_cast<const char*>(p.getData()), p.getDataSize());
    
    if(is_debug)
        std::cout << "FROM CLIENT: " << json_string << std::endl;

    json json_parsed;
    string private_hash;
    try {
        json_parsed = json::parse(utils::encoding::to_wide(json_string));
        private_hash = json_parsed["private_hash"];
    }
    catch (...) {
        if (is_debug)
            wcout << L"ERROR JSON PARSING: " << utils::encoding::to_wide(json_string) << endl;
        return;
    }
    for (serverPlayerPeer* peer : peers) {
        if (peer->get_private_hash() == private_hash) {
            cout << json_string << endl;
            return;
        }
    }
}
void server::tcp_new_connections() {
    TcpSocket* client = new TcpSocket();

    if (tcp_listener.accept(*client) != sf::Socket::Done) {
        delete client;
        return;
    }

    serverPlayerPeer* peer = new serverPlayerPeer();

    peer->set_tcp_socket(client);
    peer->set_public_hash(utils::hashing::sha256(client->getRemoteAddress().toString() + utils::strings::get_rand_string(32)));
    peer->set_private_hash(utils::hashing::sha256(client->getRemoteAddress().toString() + utils::strings::get_rand_string(64)));
    peer->set_player_name(peer->get_public_hash());
    peer->set_timestamp(time(0));

    // отправка пакета игроку о создании его же куклы
    bool success = peer->create_player_node(peer->get_public_hash(), peer->get_private_hash(), v2f(0.0, 0.0), true);

    // Если не получилось отправить первый пакет нашему игроку, значит НАХУЙ ЕГО И В ПИЗДУ
    if (!success) {
        delete client;
        delete peer;
        return;
    }

    // ↓ ↓ ↓ Пакет был отправлен успешно, добавляем пир в наш серверный массив и тд и тп ↓ ↓ ↓

    peers.push_back(peer);

    send_msg_to_all(format("{} подключился к серверу", peer->get_public_hash()));

    cout << client->getRemoteAddress().toString() << ":" << client->getLocalPort() << " новое подключение" << endl;
}

void server::process_connected() {
    int* thread_id = new int(thread_count);
    thread_count++;
    cout << format("Начало потока обработки клиентов #{}\n", *thread_id);
    while (m_server.is_started()) {
        tcp_new_connections();
        udp_process_packets();

        sync_clients();

        Sleep(100); // УБРАТЬ КОГДА НЕ НАДО БУДЕТ
    }
}

void server::add_thread() {
    Thread* t = new Thread(&server::process_connected, &m_server);
    //switch (type) {
    //case threadtype::new_connections:
    //    t = new Thread(&server::tcp_new_connections, &m_server);
    //    break;
    //case threadtype::process_connected:
    //    t = new Thread(&server::process_connected, &m_server);
    //    break;
    //}

    threads.push_back(t);
}
void server::start() {
    for (int i = threads.size() - 1; i >= 0; i--)
        threads[i]->launch();
    cout << "start main thread\n";

    //while (1) { cout << "main thread\n"; Sleep(1000); }

    // Ждем завершения всех потоков
    for (auto t : threads)
        t->wait();

    // Отключаем каждый пир нахуй
    for (auto peer : peers)
        peer->get_tcp_sock()->disconnect();

    // Выключаем жестом доброй воли все серверные сокеты
    tcp_listener.close();
    udp_socket.unbind();
}
bool server::is_started() { return m_is_started; }

void server::send_msg_to_all(string text) {
    for (auto p : peers) {
        bool success = p->send_chat_msg(text);
    }
}