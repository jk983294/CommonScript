#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class order {
public:
    long long price;
    long long qty;
    long long filled;
    bool is_buy;
    long long time;
    bool is_gfd;
    string order_id;
    string cmd;

    order(long long _price, long long _qty, bool _is_buy, long long _time, bool _is_gfd, string _order_id, string _cmd){
        this->price = _price;
        this->qty = _qty;
        this->is_buy = _is_buy;
        this->time = _time;
        this->is_gfd = _is_gfd;
        this->order_id = _order_id;
        this->filled = 0;
        this->cmd = _cmd;
    }
    order(string _cmd){
        this->cmd = _cmd;
    }
    order(string _order_id, string _cmd){
        this->cmd = _cmd;
        this->order_id = _order_id;
    }

    long long remain_qty(){
        return qty - filled;
    }
};

bool compare_order_low_first (const order& first, const order& second){
    if(first.price < second.price){
        return true;
    } else if(first.price > second.price){
        return false;
    } else {
        return first.time < second.time;
    }
}
bool compare_order_high_first (const order& first, const order& second){
    if(first.price > second.price){
        return true;
    } else if(first.price < second.price){
        return false;
    } else {
        return first.time < second.time;
    }
}

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while(it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
int count_space(const string& s){
	return count(s.begin(), s.end(), ' ');
}


string process_str(const string& str){
	if(str.empty()) return "";
	int i = 0, j = str.size() - 1;
	while(i <= j && str[i] == ' ') i++;
	while(j >= 0 && str[j] == ' ') j--;
	if(i > j) return "";
	string result = "";
	int len = 0;
	for(int k = i; k <= j; k++){
		if(str[k] == ' ' && result[result.size() - 1] == ' ') continue;
		result += str[k];
	}
	return result;
}

class match_system {
public:
    list<order> buy;    // from high to low
    list<order> sell;       // from low to high
    long long time;

    void trade(){
        string t1 = "", t2 = "", order_id = "", line = "", price_str = "", qty_str = "";
		stringstream ss;
        long long price = 0, qty = 0;
        long long time = 0;
        while (getline(cin,line)){
			if(line.empty()) continue;
			line = process_str(line);
			ss.clear();
			ss<<line;
			ss>>t1;
            if(t1 == "BUY" || t1 == "SELL"){
				if(count_space(line) == 4){
					ss>>t2>>price_str>>qty_str>>order_id;
					if(is_number(price_str) && is_number(qty_str) && (t2 == "GFD" || t2 == "IOC")){
						ss.clear();
						ss<<price_str<<" "<<qty_str;
						ss>>price>>qty;
						deal_order(order(price, qty, t1 == "BUY", time++, t2 == "GFD", order_id, t1));
					}
				}    
            } else if(t1 == "CANCEL"){
				if(count_space(line) == 1){
					ss>>order_id;
					deal_order(order(order_id, t1));
				}
            } else if(t1 == "PRINT"){
				if(count_space(line) == 0){
					deal_order(order(t1));
				}
            } else if(t1 == "MODIFY"){
				if(count_space(line) == 4){
					ss>>order_id>>t2>>price_str>>qty_str;
					if(is_number(price_str) && is_number(qty_str) && (t2 == "BUY" || t2 == "SELL")){
						ss.clear();
						ss<<price_str<<" "<<qty_str;
						ss>>price>>qty;
						deal_order(order(price, qty, t2 == "BUY", time++, true, order_id, t1));
					}
				}
            }
        }
    }

    void simulate(){
        
        deal_order(order(10, 10, true, 1, true, "order1", "BUY"));
        deal_order(order(9, 10, true, 2, true, "order2", "BUY"));
        deal_order(order(11, 10, true, 3, true, "order3", "BUY"));
        deal_order(order(10, 10, true, 4, true, "order4", "BUY"));
        deal_order(order(20, 10, false, 5, true, "order5", "SELL"));
        deal_order(order(19, 10, false, 6, true, "order6", "SELL"));
        deal_order(order(21, 10, false, 7, true, "order7", "SELL"));
        deal_order(order(20, 10, false, 8, true, "order8", "SELL"));
		//deal_order(order("order8", "CANCEL"));
		
        deal_order(order("PRINT"));
		/*
        deal_order(order(1000, 10, true, 1, true, "order1", "BUY"));
        deal_order(order(900, 20, false, 8, true, "order9", "SELL"));
		*/
		deal_order(order(10, 22, false, 9, false, "order9", "SELL"));
		deal_order(order("order4", "CANCEL"));
		deal_order(order("order1", "CANCEL"));



        deal_order(order("PRINT"));
    }

    void deal_order(order o){
        if(o.cmd == "PRINT"){
            print_book();
        } else if(o.cmd == "BUY" || o.cmd == "SELL"){
            add_order(o);
        } else if(o.cmd == "CANCEL"){
            cancel_order(o);
        } else if(o.cmd == "MODIFY"){
            if(cancel_order(o)){
                add_order(o);
            }
        }
    }

    bool cancel_order(order &o){
        list<order>::iterator i = find_order(buy, o.order_id);
        if(i != buy.end()){
            buy.erase(i);
            return true;
        }
        else {
            i = find_order(sell, o.order_id);
            if(i != sell.end()){
                sell.erase(i);
                return true;
            }
        }
        return false;
    }

    list<order>::iterator find_order(list<order> &orders, string id){
        for (list<order>::iterator i = orders.begin(); i != orders.end(); ++i){
            if(i->order_id == id) return i;
        }
        return orders.end();
    }

    void print_book(){
        long long p = -1, q = -1;
        cout<<"SELL:"<<endl;
        for (list<order>::reverse_iterator i = sell.rbegin(); i != sell.rend(); ++i){
            if(p < 0){
                p = i->price;
                q = i->remain_qty();
            } else if(p == i->price){
                q += i->remain_qty();
            } else {
                cout <<p<<" "<<q<<endl;
                p = i->price;
                q = i->remain_qty();
            }
        }
        if(p > 0) cout <<p<<" "<<q<<endl;
        p = -1, q = -1;

        cout<<"BUY:"<<endl;
        for (list<order>::iterator i = buy.begin(); i != buy.end(); ++i){
            if(p < 0){
                p = i->price;
                q = i->remain_qty();
            } else if(p == i->price){
                q += i->remain_qty();
            } else {
                cout <<p<<" "<<q<<endl;
                p = i->price;
                q = i->remain_qty();
            }
        }
        if(p > 0) cout <<p<<" "<<q<<endl;
    }

    void add_order(order &o){
        long long fill_count = 0;
        if(o.price > 0 && o.qty > 0){
            if(o.is_buy){
                while(o.remain_qty() > 0 && !sell.empty()){
                   order& s = sell.front();
                   if(s.price <= o.price){
                       if(s.remain_qty() >= o.remain_qty()){
                           fill_count = o.remain_qty();
                       } else {
                           fill_count = s.remain_qty();
                       }
                       print_trade(o, s, fill_count);
                       if(s.remain_qty() <= 0){
                           sell.pop_front();
                       }
                   } else {
                       break;
                   }
                }// end while

                if(o.remain_qty() > 0 && o.is_gfd){
                    add_buy_list(o);
                }
            } else {    // sell
                while(o.remain_qty() > 0 && !buy.empty()){
                    order& b = buy.front();
                    if(o.price <= b.price){
                        if(b.remain_qty() >= o.remain_qty()){
                            fill_count = o.remain_qty();
                        } else {
                            fill_count = b.remain_qty();
                        }
                        print_trade(o, b, fill_count);
                        if(b.remain_qty() <= 0){
                            buy.pop_front();
                        }
                    } else {
                        break;
                    }
                }// end while

                if(o.remain_qty() > 0 && o.is_gfd){
                    add_sell_list(o);
                }
            }
        }
    }

    void add_buy_list(order o){
        buy.push_back(o);
        buy.sort(compare_order_high_first);
    }

    void add_sell_list(order o){
        sell.push_back(o);
        sell.sort(compare_order_low_first);
    }


    void print_trade(order &o1, order &o2, long long count){
        if(o1.time > o2.time){
            cout<<"TRADE "<<o2.order_id<<" "<<o2.price<<" "<<count<<" "<<o1.order_id<<" "<<o1.price<<" "<<count<<endl;
        } else {
            cout<<"TRADE "<<o1.order_id<<" "<<o1.price<<" "<<count<<" "<<o2.order_id<<" "<<o2.price<<" "<<count<<endl;
        }
        o2.filled += count;
        o1.filled += count;
    }
};

int main() {
    match_system s;
    //s.simulate();
    s.trade();

    return 0;
}
