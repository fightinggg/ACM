#include<bits/stdc++.h>
#include<dirent.h>

using namespace std;

string workspace = "/Users/s/Documents/GitHub/ACM/blog/";
string head1 = "<!DOCTYPE html>\n<html>\n\n<head>\n    <meta charset=\"utf-8\">\n    <script type=\"text/javascript\" src=\"/ACM/js/link.js\"></script>\n    <title>";
string head2 = "</title>\n</head>\n\n<script type=\"text/javascript\" src=\"/ACM/js/web_begin.js\"></script>\n<div>\n";
string tail3 = "\n\n</div>\n<script type=\"text/javascript\" src=\"/ACM/js/web_end.js\"></script>\n</html>\n";

char op[20] = {' ', '+', '-', '*', '/', '&', '|', '!', '~', '%', '=', '(', ')', '[', ']', '{', '}', '?', '<', '>'};
int opflag[256];
map<string, bool> mp;

void ini() {
    for (int i = 0; i < 20; i++) opflag[128 + op[i]] = 1;
    mp["int"] = true;
    mp["char"] = true;
    mp["ll"] = true;
    mp["typedef"] = true;
    mp["for"] = true;
    mp["break"] = true;
    mp["continue"] = true;
    mp["struct"] = true;
    mp["class"] = true;
    mp["return"] = true;
    mp["string"] = true;
    mp["vector"] = true;
    mp["map"] = true;
    mp["list"] = true;
    mp["true"] = true;
    mp["false"] = true;
    mp["long"] = true;
    mp["double"] = true;
}

struct input {
    string s;
    int idx;

    input(string s) : s(s) { idx = 0; }

    bool havenext() { return idx < s.size(); }

    string read() {
        string ret;
        if (s[idx] == '/' && idx + 1 < s.size() && s[idx + 1] == '/') {
            ret = s.substr(idx);
            idx = s.size();
            return ret;
        }
        ret.push_back(s[idx]);
        if (!opflag[128 + s[idx]]) {
            while (havenext() && !opflag[128 + s[idx + 1]]) ret.push_back(s[++idx]);
        }
        idx++;
        return ret;
    }
};

struct blog {
    string link;// 题目链接
    string time;// 更新时间
    string name;// 题目名字
    vector<string> tag;
    string context;// 部分html5

    string build_head() { return head1 + name + head2 + '\n'; }

    string build_tail() { return tail3; }

    string build_time() { return "<span style=\"float:right\">此文更新于" + time + "</span>\n"; }

    string build_link() {
        if (link == "") return "<h1><center>" + name + "<center><h1>";
        return "    <h1><center><a href=\"" + link + "\" target=\"_blank\">" + name + "</a></center></h1>\n\n";
    }

    string build_code(const string &where) {
        cout << "looking for " + workspace + "cpp/" + where << endl;
        ifstream in(workspace + "cpp/" + where);
        string s = "    <script type=\"text/javascript\" src=\"/ACM/js/code_begin.js\"></script>\n    <div>\n";
        while (true) {
            if (in.eof()) break;
            string buf;
            getline(in, buf);
            input fin(buf);
            buf.clear();
            s += "            ";
            while (fin.havenext()) {
                string word = fin.read();
                if (word.size() == 1 && opflag[128 + word[0]]) {
                    if (word == " ")s += "&nbsp;";
                    else if (word == "<")s += "&lt;";
                    else if (word == ">")s += "&gt;";
                    else if (word[0] == '[' || word[0] == ']' || word[0] == '{' || word[0] == '}' || word[0] == '(' ||
                             word[0] == ')') {
                        s += word;
                    } else s += "<span style=\"color:red;\">" + word + "</span>";
                } else if (word.size() >= 2 && word[0] == '/' && word[1] == '/') {
                    s += "<span style=\"color:grey;\">" + word + "</span>";
                } else if (mp.find(word) != mp.end()) {
                    s += "<span style=\"color:black;\">" + word + "</span>";
                } else {
                    long long x = 0;
                    int siz = word.size();
                    for (int i = 0; i < siz; i++) {
                        x *= 47;
                        x += word[i];
                        x %= int(1e9 + 7);
                    }
                    x %= 3;
                    if (x == 0) s += "<span style=\"color:#3CBDD0;\">" + word + "</span>";
                    else if (x == 1) s += "<span style=\"color:#5a64aa;\">" + word + "</span>";
                    else if (x == 2)s += "<span style=\"color:#22CC8D;\">" + word + "</span>";
                }
            }
            s += "<br>\n";
        }
        s += "    </div>\n    <script type=\"text/javascript\" src=\"/ACM/js/code_end.js\"></script>\n\n";
        return s;
    }

    string txttohtml(string txt) {
        string s;
        for (int i = 0; i < txt.size(); i++) {
            if (txt[i] == ' ')s += "&nbsp;";
            else if (txt[i] == '>')s += "&gt;";
            else if (txt[i] == '<')s += "&lt;";
            else s += txt[i];
        }
        return s;
    }

    string build_txt(vector<string> &txt) {
        string s;
        s = "    <div id=\"text\">\n";
        for (int i = 0; i < txt.size(); i++) {
            s += "            " + txttohtml(txt[i]) + "<br>\n";
        }
        s += "    </div>\n\n";
        return s;
    }

    string build_othersblog(vector<string> othersblog) {
        string s;
        return s;
    }

    string build_tag(vector<string> &read_tag) {
        tag = read_tag;
        string s;
        if (tag.empty()) return s;
        s += "            <span>此文标签</span><br>\n";
        for (int i = 0; i < tag.size(); i++) {
            s += "                <a href=\"" + tag[i] + ".html\"> " + tag[i] + " </a>";
        }
        s += "<br>\n";
        return s;
    }

    string build_solve(vector<string> &solve) {
        string s = "    <script type=\"text/javascript\" src=\"/ACM/js/solve_begin.js\"></script>\n    <div>\n";
        for (int i = 0; i < solve.size(); i++) {
            s += "            " + solve[i] + "<br>\n";
        }
        s += "    </div>\n    <script type=\"text/javascript\" src=\"/ACM/js/solve_end.js\"></script>\n\n";
        return s;
    }

    blog(string s) {// file name
        cout << "lookint for " << s << endl;
        ifstream in(s);
        string buf;
        vector<string> reading;
        while (true) {
            if (in.eof()) break;
            getline(in, buf);
            if (buf.empty()) continue;
            if (buf == "###link") {
                getline(in, link);
                getline(in, buf);
                assert(buf == "###link");
            } else if (buf == "###time") {
                getline(in, time);
                getline(in, buf);
                assert(buf == "###time");
            } else if (buf == "###name") {
                getline(in, name);
                getline(in, buf);
                assert(buf == "###name");
            } else if (buf == "###code") {
                getline(in, buf);
                context += build_code(buf);
                getline(in, buf);
                assert(buf == "###code");
            } else if (buf == "###txt") {
                reading.clear();
                while (true) {
                    getline(in, buf);
                    if (buf == "###txt")break;
                    else reading.push_back(buf);
                }
                context += build_txt(reading);
            } else if (buf == "###othersblog") {
                reading.clear();
                while (true) {
                    getline(in, buf);
                    if (buf == "###othersblog")break;
                    else reading.push_back(buf);
                }
                context += build_othersblog(reading);
            } else if (buf == "###tag") {
                reading.clear();
                while (true) {
                    getline(in, buf);
                    if (buf == "###tag")break;
                    else reading.push_back(buf);
                }
                context += build_tag(reading);
            } else if (buf == "###solve") {
                reading.clear();
                while (true) {
                    getline(in, buf);
                    if (buf == "###solve")break;
                    else reading.push_back(buf);
                }
                context += build_solve(reading);
            }
        }
    }

    void write() {
        cout << "writing to  " << workspace + "span/" + name + ".html" << endl;
        ofstream out(workspace + "span/" + name + ".html");
        out << build_head() << build_link() << build_time() << context << build_tail();
        out.close();
    }
};


char *auto_cpy(string str) {
    const int maxn = 1e6;
    static char s[maxn], idx = 0;
    if (idx > maxn * 0.8)idx = 0;
    char *ret = s + idx;
    str.copy(ret, str.size(), 0);
    ret[str.size()] = 0;
    idx += str.size() * 4;
    return ret;
}


void build_index(vector<blog> myblog) {
    map<string, vector<string>> index;
    for (int i = 0; i < myblog.size(); i++) {
        for (int j = 0; j < myblog[i].tag.size(); j++) {
            index[myblog[i].tag[j]].push_back(myblog[i].name);
        }
    }

    ofstream out1(workspace + "span/index.html");
    out1<<head1<<"生成博客总揽"<<head2;

    for (pair<string, vector<string>> x:index) {
        string name = x.first;
        vector<string> web = x.second;

        out1 << "            <div id=\"index\">\n";
        out1 << "                <a href=\"" + name + ".html\">" + name + "</a> </br>\n";
        out1 << "            </div>\n";

        ofstream out2(workspace + "span/" + name + ".html");

        out2 << head1 << name << head2;
        for (int i = 0; i < web.size(); i++) {
            out2 << "            <div id=\"index\">\n";
            out2 << "                <a href=\"" + web[i] + ".html\">" + web[i] + "</a> </br>\n";
            out2 << "            </div>\n";
        }
        out2 << tail3 << endl;
    }

    out1<<tail3<<endl;
}

int main() {
    cout << endl;
    ini();
    vector<blog> myblog;
    DIR *dir = opendir(auto_cpy(workspace + "txt/"));
    while (true) {
        dirent *dirp = readdir(dir);
        if (dirp == nullptr) break;
        if (dirp->d_name[0] == '.')continue;
        if (dirp->d_type == DT_DIR) continue;
        blog a_new_blog(workspace + "txt/" + string(dirp->d_name));
        myblog.push_back(a_new_blog);
    }
    for (blog &b:myblog) b.write();
    build_index(myblog);
}





