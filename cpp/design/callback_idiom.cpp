#include <atomic>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>

using namespace std;

typedef std::vector<std::string> AdminCallbackArgs;
typedef std::function<std::string(std::string const&, AdminCallbackArgs const&)> TAdminCallback;

struct AdminCallback {
    AdminCallback(TAdminCallback const& callback_ = TAdminCallback(), std::string const& description_ = std::string(),
                  std::string const& detail_ = std::string())
        : callback(callback_), description(description_), detail(detail_) {}

    TAdminCallback callback;
    std::string description;
    std::string detail;
};

class AdminChannel {
public:
    std::map<std::string, AdminCallback> adminCallbacks;
    std::mutex mutex_;
    std::string data{"hello admin."};

public:
    AdminChannel() {
        add("call1", std::bind(&AdminChannel::call1, this), "call1", "call1");
        add("call2", std::bind(&AdminChannel::call2, this, std::placeholders::_1), "call2", "call2");
    }

    ~AdminChannel() = default;

    AdminChannel(AdminChannel const&) = delete;

    AdminChannel& operator=(AdminChannel const&) = delete;

    void add(std::string const& command, const TAdminCallback& callback, std::string const& description,
             std::string const& detail) {
        std::lock_guard<std::mutex> guard(mutex_);
        adminCallbacks[command] = AdminCallback(callback, description, detail);
    }

    AdminCallback& commandCallback(const std::string& command) { return adminCallbacks[command]; }

    void dispatch_command(const std::string& cmd, const AdminCallbackArgs& cmdArgs) {
        AdminCallback currentCB = commandCallback(cmd);
        cout << "response for this callback is " << currentCB.callback(cmd, cmdArgs) << endl;
    }

    string call1() {
        cout << "AdminChannel::call1()" << endl;
        return "call1";
    }

    string call2(string param) {
        cout << "AdminChannel::call2(　" << param << " ) " << data << endl;
        return "call2";
    }

    void test() {
        dispatch_command("call1", {});
        dispatch_command("call2", {"test"});
    }
};

int main() {
    AdminChannel adminChannel;
    adminChannel.test();
    return 0;
}
