#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Ebook {
public:
    Ebook() {
        page_on_user_.reserve(100001);
        users_on_page_.reserve(1001);
        page_on_user_.push_back(0);
        users_on_page_.push_back(0);
    }

    double ProceedCheerRequest(int&& user) {
        if (page_on_user_.size() - 1 < user || page_on_user_[user] == 0) {
            return .0;
        } else if (registered_users == 1) {
            return 1.0;
        }
        int lt_users = accumulate(users_on_page_.begin(), users_on_page_.begin() + page_on_user_[user], 0);

        return static_cast<double>(lt_users) / (registered_users - 1);
    };
    void ProceedReadRequest(int&& user, int&& page) {
        /* В условиях задачи не сказано, увеличиваются ли id пользователя в запросах READ последовательно, т.е. 1, 2, 3... Поэтому исходим
         * из того, что необходимо обрабатывать случаи, когда id пользователя значительно за пределами размера текущего вектора. То же и с
         * номерами страниц.
         */
        int size_u = page_on_user_.size() - 1; // размер вектора без нулевого элемента
        if (user > size_u) {
            for (int i = 0; i < user - (size_u + 1); ++i) {
                page_on_user_.push_back(0);
            }
            page_on_user_.push_back(move(page));
            ++registered_users;
        } else {
            if (page_on_user_[user] > 0) {
                --users_on_page_[page_on_user_[user]];
            } else {
                ++registered_users;
            }
            page_on_user_[user] = page;
        }

        int size_p = users_on_page_.size() - 1; // размер вектора без нулевого элемента
        if (page > size_p) {
            for (int i = 0; i < page - size_p; ++i) {
                users_on_page_.push_back(0);
            }
        }
        ++users_on_page_[page];
    };

private:
    vector<int> page_on_user_;  // кол-во страниц у каждого читателя
    vector<int> users_on_page_; // кол-во читателей на каждой странице
    int registered_users = 0;   // кол-во читающих книгу
};

int main() {

    Ebook ebook;
        int request_number, user, page;
        string request_type;
        cin >> request_number;

        for (int i = 0; i < request_number; ++i) {
            cin >> request_type;
            if (request_type == "CHEER"s) {
                cin >> user;
                cout << setprecision(6) << ebook.ProceedCheerRequest(move(user)) << endl;
            } else if (request_type == "READ"s) {
                cin >> user >> page;
                ebook.ProceedReadRequest(move(user), move(page));
            } else {
                cout << "Wrong request type "s << request_type << " found!"s << endl;
                break;
            }
        }
}