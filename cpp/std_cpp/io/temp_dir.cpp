#include <ftw.h>
#include <unistd.h>
#include <array>
#include <cstdlib>
#include <iostream>

using namespace std;

/* Call-back to the 'remove()' function called by nftw() */
static int remove_callback(const char *pathname, __attribute__((unused)) const struct stat *sbuf,
                           __attribute__((unused)) int type, __attribute__((unused)) struct FTW *ftwb) {
    return remove(pathname);
}

static bool my_exec(const char *cmd, std::string &out) {
    std::array<char, 128> buffer{};
    auto pipe = popen(cmd, "r");
    if (!pipe) {
        return false;
    }
    while (!feof(pipe)) {
        if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) out += buffer.data();
    }
    return pclose(pipe) == EXIT_SUCCESS;
}

int main() {
    char template_dir[] = "/tmp/tmpdir.XXXXXX";
    char *dir_name = mkdtemp(template_dir);

    if (dir_name == nullptr) {
        perror("mkdtemp failed: ");
        return 0;
    }

    /* Use it here */
    printf("use %s\n", dir_name);
    string my_cmd = std::string("cd ") + dir_name;
    my_cmd += " && touch a.txt && ls ";
    my_cmd += " 2>&1";  // collect error msg

    string output;
    bool success = my_exec(my_cmd.c_str(), output);
    if (not success) {
        printf("cmd failed due to\n%s\n", output.c_str());
    } else {
        printf("cmd success in %s\noutput:\n%s\n", dir_name, output.c_str());
    }

    /* Delete the temporary directory */
    if (nftw(dir_name, remove_callback, FOPEN_MAX, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) == -1) {
        perror("tempdir: error: ");
        exit(EXIT_FAILURE);
    }
    return 0;
}