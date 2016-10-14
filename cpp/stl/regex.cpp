#include <iostream>
#include <string>
#include <regex>

using namespace std;

/**
 * returns whether the target sequence matches the regular expression
 */
void regex_match_demo(){
    cout << regex_match ("subject", regex("(sub)(.*)") ) << endl;

    const char cstr[] = "subject";
    string s ("subject");
    regex e ("(sub)(.*)");
    cout << regex_match ( s, e ) << endl;
    cout << regex_match ( s.begin(), s.end(), e ) << endl;

    cmatch cm;                                                                  // same as match_results<const char*> cm;
    regex_match (cstr, cm, e);
    cout << "string literal with " << cm.size() << " matches" << endl;

    smatch sm;                                                                  // same as match_results<string::const_iterator> sm;
    regex_match (s, sm, e);
    cout << "string object with " << sm.size() << " matches" << endl;

    regex_match ( s.cbegin(), s.cend(), sm, e);
    cout << "range with " << sm.size() << " matches" << endl;

    // using explicit flags:
    regex_match ( cstr, cm, e, regex_constants::match_default );

    cout << "the matches were: ";
    for (unsigned i = 0; i < cm.size(); ++i) {
        cout << "[" << cm[i] << "] ";
    }
    cout << endl;
}

/**
 * returns whether some sub-sequence in the target sequence (the subject) matches the regular expression
 */
void regex_search_demo(){
    string s ("this subject has a submarine as a subsequence");
    smatch m;
    regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    cout << "Target sequence: " << s << endl;
    cout << "Regular expression: /\\b(sub)([^ ]*)/" << endl;
    cout << "The following matches and submatches were found:" << endl;

    while (regex_search (s, m, e)) {
        for (auto x : m)
            cout << x << " ";
        cout << endl;
        s = m.suffix().str();
        cout << "next to search: " << s << endl;
    }
}

void regex_replace_demo(){
    string s ("there is a subsequence in the string");
    regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    // $0 is whole regex
    cout << regex_replace ( s, e, "sub-$2" ) << endl;

    string result;
    regex_replace (back_inserter(result), s.begin(), s.end(), e, "$2");     // replace $0 with $2
    cout << result << endl;

    // with flags:
    cout << regex_replace (s, e, "$1 and $2", regex_constants::format_no_copy) << endl;
}

void format_demo(){
    string s = string("call 110-119-911 to police!");
    regex r("((\\d{3})-(\\d{3})-(\\d{3}))" );
    smatch m = smatch {};
    cout << "empty " << m.empty() << endl;
    regex_search(s, m, r);
    cout << "empty " << m.empty() << endl;
    cout << m.format("result is [$1] [$2] [$3] [$4]") << endl;
}

int main() {
    cout << boolalpha;

    regex_match_demo();

    regex_search_demo();

    regex_replace_demo();

    format_demo();

    return 0;
}