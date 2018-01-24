#include <google/protobuf/util/time_util.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same file.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is compatible
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::AddressBook address_book;

    const char* addressBookPath = "/tmp/address.book";

    {
        // Read the existing address book.
        fstream input(addressBookPath, ios::in | ios::binary);
        if (!input) {
            cout << addressBookPath << ": File not found.  Creating a new file." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Add an address.
    tutorial::Person* person = address_book.add_people();
    int id = 42;
    string name{"kun"};
    string email{"fake@126.com"};
    vector<string> phones{"123", "456"};
    person->set_id(42);
    person->set_name(name);
    person->set_email(email);

    for (const auto& number : phones) {
        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);
        phone_number->set_type(tutorial::Person::MOBILE);
    }
    *person->mutable_last_updated() = TimeUtil::SecondsToTimestamp(time(NULL));

    {
        // Write the new address book back to disk.
        fstream output(addressBookPath, ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
