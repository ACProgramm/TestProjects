#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

struct Event {
    string time;
    int id;
    string body;
    string raw;
};

struct Client {
    string name;
    bool inClub = false;
    bool inQueue = false;
    int table = 0;
    string startTime;
};

int toMinutes(const string& t) {
    int h = stoi(t.substr(0, 2));
    int m = stoi(t.substr(3, 2));
    return h * 60 + m;
}

string toTime(int mins) {
    stringstream ss;
    ss << setw(2) << setfill('0') << (mins / 60) << ":"
       << setw(2) << setfill('0') << (mins % 60);
    return ss.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./task input.txt" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "File error" << endl;
        return 1;
    }

    int numTables, price;
    string workStart, workEnd;
    if (!(fin >> numTables)) {
        cout << "1" << endl;
        return 0;
    }
    if (!(fin >> workStart >> workEnd)) {
        cout << "2" << endl;
        return 0;
    }
    if (!(fin >> price)) {
        cout << "3" << endl;
        return 0;
    }

    vector<Event> events;
    string line;
    getline(fin, line); // съесть оставшийся перевод строки

    while (getline(fin, line)) {
        istringstream iss(line);
        string time;
        int id;
        string rest;
        if (!(iss >> time >> id)) {
            cout << line << endl;
            return 0;
        }
        getline(iss, rest);
        rest = rest.substr(1); // убрать пробел
        events.push_back({time, id, rest, line});
    }

    map<string, Client> clients;
    vector<string> tables(numTables + 1, "");
    vector<int> revenue(numTables + 1, 0);
    vector<int> busyTime(numTables + 1, 0);
    queue<string> waitQueue;
    vector<string> output;

    output.push_back(workStart);

    int openTime = toMinutes(workStart);
    int closeTime = toMinutes(workEnd);

    for (const auto& e : events) {
        output.push_back(e.raw);
        int currTime = toMinutes(e.time);
        auto& client = clients[e.body.substr(0, e.body.find(' '))];
        client.name = client.name.empty() ? e.body.substr(0, e.body.find(' ')) : client.name;

        if (e.id == 1) {
            if (client.inClub) {
                output.push_back(e.time + " 13 YouShallNotPass");
            } else if (currTime < openTime) {
                output.push_back(e.time + " 13 NotOpenYet");
            } else {
                client.inClub = true;
            }
        }
        else if (e.id == 2) {
            istringstream ss(e.body);
            string name; int table;
            ss >> name >> table;

            if (!client.inClub) {
                output.push_back(e.time + " 13 ClientUnknown");
            } else if (tables[table] != "" && tables[table] != name) {
                output.push_back(e.time + " 13 PlaceIsBusy");
            } else {
                if (client.table != 0) {
                    int t1 = toMinutes(client.startTime);
                    int t2 = currTime;
                    int hours = ceil((t2 - t1) / 60.0);
                    revenue[client.table] += hours * price;
                    busyTime[client.table] += t2 - t1;
                    tables[client.table] = "";
                }
                tables[table] = name;
                client.table = table;
                client.startTime = e.time;
            }
        }
        else if (e.id == 3) {
            bool free = false;
            for (int i = 1; i <= numTables; ++i)
                if (tables[i] == "") free = true;
            if (free) {
                output.push_back(e.time + " 13 ICanWaitNoLonger!");
            } else if (waitQueue.size() >= numTables) {
                output.push_back(e.time + " 11 " + client.name);
                client.inClub = false;
            } else {
                waitQueue.push(client.name);
                client.inQueue = true;
            }
        }
        else if (e.id == 4) {
            if (!client.inClub) {
                output.push_back(e.time + " 13 ClientUnknown");
            } else {
                if (client.table != 0) {
                    int t1 = toMinutes(client.startTime);
                    int t2 = currTime;
                    int hours = ceil((t2 - t1) / 60.0);
                    revenue[client.table] += hours * price;
                    busyTime[client.table] += t2 - t1;
                    tables[client.table] = "";
                    client.table = 0;
                }
                client.inClub = false;

                if (!waitQueue.empty()) {
                    string next = waitQueue.front(); waitQueue.pop();
                    clients[next].table = 0;
                    clients[next].startTime = e.time;
                    clients[next].inQueue = false;
                    for (int i = 1; i <= numTables; ++i) {
                        if (tables[i] == "") {
                            tables[i] = next;
                            clients[next].table = i;
                            break;
                        }
                    }
                    output.push_back(e.time + " 12 " + next + " " + to_string(clients[next].table));
                }
            }
        }
    }

    // Закрытие клуба
    for (auto& [name, client] : clients) {
        if (client.inClub) {
            output.push_back(workEnd + " 11 " + name);
            if (client.table != 0) {
                int t1 = toMinutes(client.startTime);
                int t2 = closeTime;
                int hours = ceil((t2 - t1) / 60.0);
                revenue[client.table] += hours * price;
                busyTime[client.table] += t2 - t1;
            }
        }
    }

    output.push_back(workEnd);

    for (const auto& line : output) {
        cout << line << endl;
    }

    for (int i = 1; i <= numTables; ++i) {
        cout << i << " " << revenue[i] << " " << toTime(busyTime[i]) << endl;
    }

    return 0;
}
