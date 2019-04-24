#include <bits/stdc++.h>
#include <dirent.h>
using namespace std;

char* auto_cpy(string str){
    const int maxn=1e6;
    static char s[maxn],idx=0;
    if(idx>maxn*0.8)idx=0;
    char*ret=s+idx;
    str.copy(ret,str.size(),0);
    ret[str.size()]=0;
    idx+=str.size()*4;
    return ret;
}

struct blog{
    string name,link;
    vector<string> problem,solve;
    set<string> tag;


    void make_blog(string&str){
        
        int found = -1;
        while(true){
            found=str.find("&",found+1);
            if(found==string::npos)break;
            str.replace(found,1,"&amp");
        }

        while(true){
            size_t found=str.find("\"");
            if(found==string::npos)break;
            str.replace(found,1,"&quot;");
        }
        while(true){
            size_t found=str.find(" ");
            if(found==string::npos)break;
            str.replace(found,1,"&nbsp;");
        }
        while(true){
            size_t found=str.find("<");
            if(found==string::npos)break;
            str.replace(found,1,"&lt;");
        }
        while(true){
            size_t found=str.find(">");
            if(found==string::npos)break;
            str.replace(found,1,"&gt;");
        }
    }
    void make_blog(){
        for(int i=0;i<problem.size();i++)make_blog(problem[i]);
        for(int i=0;i<solve.size();i++)make_blog(solve[i]);
    }


    blog(string s){//file name
        if(s.size()>=4&&s.substr(s.size()-4)==".txt"){
            cout<<s<<endl;
            ifstream in(s);
            string buf;
            in>>buf;assert(buf=="####");
            
            in>>name;
            
            in>>buf;assert(buf=="####");

            while(in>>buf){
                if(buf=="####")break;
                else tag.insert(buf);
            }assert(buf=="####");

            in>>link;

            in>>buf;assert(buf=="####");

            getline(in,buf);//read \n
            while(getline(in,buf)){
                if(buf=="####")break;
                else problem.push_back(buf);
            }assert(buf=="####");

            while(getline(in,buf)){
                if(buf=="####")break;
                else solve.push_back(buf);
            }assert(buf=="####");

            in>>link;assert(buf=="####");

            make_blog();
        }
    }

    void write(string s){//file name
        ofstream out(s);
        // cout<<"write: "<<s<<endl;
        out<<"<!DOCTYPE html>"<<endl;
        out<<"<html>"<<endl;
        out<<""<<endl;
        out<<""<<endl;
        out<<"<head>"<<endl;
        out<<"    <meta charset=\"utf-8\">"<<endl;
        out<<"    <script type=\"text/javascript\" src=\"/ACM/js/link.js\"></script>"<<endl;
        out<<"    <title>"+name+"</title>"<<endl;
        out<<"</head>"<<endl;
        out<<""<<endl;
        out<<""<<endl;
        out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_begin.js\"></script>"<<endl;
        out<<"<div>"<<endl;
        out<<"    <center><h1>"+name+"</h1></center>"<<endl;
        //do it
        out<<"    <div id=\"text\">"<<endl;

        out<<"    <h2>链接</h2>"<<endl;
        out<<"        <div id=\"normal_href\">"<<endl;
        out<<"            <a href=\""+link+"\" target=\"_blank\">"+link+"</a><br>"<<endl;
        out<<"        </div>"<<endl;
        
        out<<"    <h2>题意</h2>"<<endl;
        out<<"        <span style=\"color:red\">"<<endl;
        for(int i=0;i<problem.size();i++)out<<"            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"<<problem[i]<<"<br>"<<endl;
        out<<"        </span>"<<endl;

        out<<"    <h2>题解</h2>"<<endl;
        for(int i=0;i<solve.size();  i++)out<<"            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"<<solve[i]<<"<br>"<<endl;
        out<<"    </div>"<<endl;
        //
        out<<"</div>"<<endl;
        out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_end.js\"></script>"<<endl;
        out<<"</html>"<<endl;
    }
};

vector<blog>myblog;



void get_index1(){
    set<string> se;
    for (vector<blog>::iterator it = myblog.begin(); it != myblog.end(); ++it){
        for (set<string>::iterator i = it->tag.begin(); i != it->tag.end(); ++i){
            se.insert(*i);
        }
    }
    ofstream out("/Users/s/Documents/GitHub/ACM/reading_problem/indexs/reading_index.html");
    out<<"<!DOCTYPE html>"<<endl;
    out<<"<html>"<<endl;
    out<<""<<endl;
    out<<""<<endl;
    out<<"<head>"<<endl;
    out<<"    <meta charset=\"utf-8\">"<<endl;
    out<<"    <script type=\"text/javascript\" src=\"/ACM/js/link.js\"></script>"<<endl;
    out<<"    <title>reading_index</title>"<<endl;
    out<<"</head>"<<endl;
    out<<""<<endl;
    out<<""<<endl;
    out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_begin.js\"></script>"<<endl;
    out<<"<div>"<<endl;
    out<<"    <center><h1>reading_index</h1></center>"<<endl;
    out<<""<<endl;
    for (set<string>::iterator itse = se.begin(); itse != se.end(); ++itse){
        out<<"    <div id=\"normal_index\">"<<endl;
        out<<string("        <a href=\"")+"http://fightinggg.github.io/ACM/reading_problem/indexs/"+*itse+".html"+"\">"+*itse+"</a><br>"<<endl;
        out<<"    </div>"<<endl;
        out<<""<<endl;           
    }
    out<<"</div>"<<endl;
    out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_end.js\"></script>"<<endl;
    out<<"</html>"<<endl;
}






void get_index2(){
    set<string> se;
    for (vector<blog>::iterator it = myblog.begin(); it != myblog.end(); ++it){
        for (set<string>::iterator i = it->tag.begin(); i != it->tag.end(); ++i){
            se.insert(*i);
        }
    }
    for (set<string>::iterator itse = se.begin(); itse != se.end(); ++itse){
        ofstream out("/Users/s/Documents/GitHub/ACM/reading_problem/indexs/"+*itse+".html");
        out<<"<!DOCTYPE html>"<<endl;
        out<<"<html>"<<endl;
        out<<""<<endl;
        out<<""<<endl;
        out<<"<head>"<<endl;
        out<<"    <meta charset=\"utf-8\">"<<endl;
        out<<"    <script type=\"text/javascript\" src=\"/ACM/js/link.js\"></script>"<<endl;
        out<<"    <title>"+*itse+"</title>"<<endl;
        out<<"</head>"<<endl;
        out<<""<<endl;
        out<<""<<endl;
        out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_begin.js\"></script>"<<endl;
        out<<"<div>"<<endl;
        out<<"    <center><h1>"+*itse+"</h1></center>"<<endl;
        out<<""<<endl;
        for (std::vector<blog>::iterator itv = myblog.begin(); itv != myblog.end(); ++itv){
            if(itv->tag.find(*itse)!=itv->tag.end()){//O(n) n<10 故O(1)
                out<<"    <div id=\"normal_index\">"<<endl;
                out<<string("        <a href=\"")+"http://fightinggg.github.io/ACM/reading_problem/"+itv->name+".html"+"\">"+itv->name+"</a><br>"<<endl;
                out<<"    </div>"<<endl;
                out<<""<<endl;
            }
        }
        out<<"</div>"<<endl;
        out<<"<script type=\"text/javascript\" src=\"/ACM/js/web_end.js\"></script>"<<endl;
        out<<"</html>"<<endl;
    }
}

void dfs(string name){
    cout<<name<<endl;
    DIR* dir=opendir(auto_cpy(name));

    while(true){
        dirent *dirp = readdir(dir);
        if(dirp == nullptr)break;
        if(dirp->d_name[0]=='.')continue;

        if (dirp->d_type == DT_DIR)dfs(name+string(dirp->d_name)+"/");
        else if (dirp->d_type == DT_REG) {
            string path=name+string(dirp->d_name);
            blog a_new_blog(path);
            
            if(path.size()>=4&&path.substr(path.size()-4)==".txt"){
                string name=string(dirp->d_name);
                name.pop_back();name.pop_back();name.pop_back();name.pop_back();
                name+=".html";
                a_new_blog.write("/Users/s/Documents/GitHub/ACM/reading_problem/"+name);
                myblog.push_back(a_new_blog);
            }
        }
    }
    closedir(dir);
}




int main() {
    string name="/Users/s/Documents/GitHub/ACM/reading_problem_txt/";
    dfs(name);
    get_index1();
    get_index2();
}



















