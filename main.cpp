#include <map>
#include <iostream>


template<typename K, typename V>
class interval_map {
    //region not allowed to be edited
    friend void IntervalMapTest();

    V m_valBegin;
    std::map<K, V> m_map;

public:
    explicit interval_map(V const &val)
            : m_valBegin(val) {}

    V const &operator[](K const &key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }

    void PrintMap() {
        for (auto const &pair: m_map) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }

    void PrintValBegin() {
        std::cout << m_valBegin;
    }
    //endregion

    void assign(K const &keyBegin, K const &keyEnd, V const &val) {

        // if invalid range do nothing
        if (!(keyBegin < keyEnd)) {
            return;
        }

        // store previous value at keyBegin
        V lastValue = operator[](keyBegin);

        // insert value at keyBegin, if not already the same
        if (operator[](keyBegin) != val) {
            m_map[keyBegin] = val;
        }

        // remove every key inside range and store last value to be put at keyEnd
        for (auto it = m_map.upper_bound(keyBegin), next_it = it; it != m_map.cend(); it = next_it) {
            if (keyEnd < it->first) break;
            ++next_it;
            m_map.erase(it);
            lastValue = it->second;
        }

        // put previous value at keyEnd
        if (!(val == lastValue)) {
            m_map[keyEnd] = lastValue;
        }
    }
};

//region Help Functions
void PrintRange(int start, int end, interval_map<int, char> m) {
    for (int i = start; i <= end; i++) {
        std::cout << "Key: " << i << " Value: " << m[i] << std::endl;
    }
}

void Print(interval_map<int, char> m) {
    std::cout << std::endl << "Range" << std::endl;
    PrintRange(-5, 30, m);
    std::cout << std::endl << "Map" << std::endl;
    std::cout << "{ValBegin: ";
    m.PrintValBegin();
    std::cout << "}" << std::endl;
    m.PrintMap();
}
//endregion



void IntervalMapTest() {
    //Initialise m_map
    interval_map m = interval_map<int, char>('A');


    //Testing
    Print(m);
    m.assign(2, 5, 'D');
    Print(m);
    m.assign(-1, 3, 'f');
    Print(m);
    m.assign(4, 20, '2');
    Print(m);
    m.assign(1, 4, 'x');
    Print(m);

    char value = m[23];
    std::cout << value;


}


int main() {
    IntervalMapTest();
}