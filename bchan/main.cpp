//
//  main.cpp
//  bchan
//
//  Created by 尹航 on 16/2/6.
//  Copyright © 2016年 zjubank. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <vector>

using namespace std;

const char * T_20150626_5 = "112416";
const char * T_20150626_7 = "140543";
const char * T_20150727_5 = "141942";
const char * T_20150727_7 = "143556";
const char * T_20150824_5 = "093509";
const char * T_20150824_7 = "095035";
const char * T_20160104_5 = "131241";
const char * T_20160104_7 = "133428";
const char * T_20160107_5 = "094233";
const char * T_20160107_7 = "095911";
const char * T_5;
const char * T_7;

double IMBAL, IMBAL_pre5, IMBAL_57, IMBAL_post7;
double Volatility, Volatility_pre5, Volatility_57, Volatility_post7;

typedef struct line
{
    string time;
    double latest_price;
    double buy_total;
    double buy_and_sell_total;
}csvline;

void init_T(const char * dir);
int timecmp(const char * time1C, const char * time2C);
csvline calline(string line);
void printresult();
void dealcsv(vector<csvline> csvlines);
void readcsv(char* filename);
void readdir(const char * dir);

int main(int argc, const char * argv[]) {
    const char * dir;
    if( argc >= 2 )
    {
        dir = argv[1];
    }
    else
    {
        dir = "20150626/";
    }

    if( argc >= 4)
    {
        T_5 = argv[2];
        T_7 = argv[3];
    }
    else
    {
        init_T(dir);
    }
    
    cout << "Ticker,Daily-IMBAL,pre5-IMBAL,57-IMBAL,post7-IMBAL,Daily-Volatility,pre5-Volatility,57-Volatility,post7-Volatility" << endl;
    readdir(dir);

    return 0;
}

void init_T(const char* dir)
{
    if( !strcmp(dir, "20160107/") )
    {
        T_5 = T_20160107_5;
        T_7 = T_20160107_7;
        return;
    }
    if( !strcmp(dir, "20160104/") )
    {
        T_5 = T_20160104_5;
        T_7 = T_20160104_7;
        return;
    }
    if( !strcmp(dir, "20150824/") )
    {
        T_5 = T_20150824_5;
        T_7 = T_20150824_7;
        return;
    }
    if( !strcmp(dir, "20150727/") )
    {
        T_5 = T_20150727_5;
        T_7 = T_20150727_7;
        return;
    }
    if( !strcmp(dir, "20150626/") )
    {
        T_5 = T_20150626_5;
        T_7 = T_20150626_7;
        return;
    }
}

int timecmp(const char * time1C, const char * time2C)
{
    int time1 = atoi(time1C);
    int time2 = atoi(time2C);
    return time1-time2;
}

csvline calline(string line)
{
    csvline thisline;
    
    string stime;
    stime = line.substr( line.find(' ') + 1, 8 );
    stime = stime.erase(2,1);
    stime = stime.erase(4,1);
    thisline.time = stime;

    line = line.substr(line.find(' ') + 1);
    line = line.substr(line.find(',') + 1);
    string slprice = line.substr(0, line.find(','));
    thisline.latest_price = atof(slprice.c_str());
    
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    line = line.substr(line.find(',') + 1);
    string sbuy1 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string sbuy2 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string sbuy3 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string sbuy4 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string sbuy5 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string ssell1 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string ssell2 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string ssell3 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string ssell4 = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    string ssell5 = line.substr(0, line.find(','));
    thisline.buy_total = atof(sbuy1.c_str()) + atof(sbuy2.c_str()) + atof(sbuy3.c_str()) + atof(sbuy4.c_str()) + atof(sbuy5.c_str());
    thisline.buy_and_sell_total = thisline.buy_total + atof(ssell1.c_str()) + atof(ssell2.c_str()) + atof(ssell3.c_str()) + atof(ssell4.c_str()) + atof(ssell5.c_str());
    
    return thisline;
}

void printresult()
{
    cout << "," << IMBAL << "," << IMBAL_pre5 << "," << IMBAL_57 << "," << IMBAL_post7 << "," << Volatility << "," << Volatility_pre5 << "," << Volatility_57 << "," << Volatility_post7 << endl;
}

void dealcsv(vector<csvline> csvlines)
{
    double total_buy_total = 0, total_buy_sell_total = 0;
    double total_buy_total_pre5 = 0, total_buy_sell_total_pre5 = 0;
    double total_buy_total_57 = 0, total_buy_sell_total_57 = 0;
    double total_buy_total_post7 = 0, total_buy_sell_total_post7 = 0;
    
    double total_latest_price = 0;
    double total_latest_price_pre5 = 0;
    double total_latest_price_57 = 0;
    double total_latest_price_post7 = 0;
    
    double square_total_latest_price = 0;
    double square_total_latest_price_pre5 = 0;
    double square_total_latest_price_57 = 0;
    double square_total_latest_price_post7 = 0;
    
    int count = 0;
    int count_pre5 = 0, count_57 = 0, count_post7 = 0;
    
    vector<csvline>::iterator it;
    for(it = csvlines.begin(); it != csvlines.end(); it++)
    {
        count++;
        
        total_buy_total += it->buy_total;
        total_buy_sell_total += it->buy_and_sell_total;
        
        total_latest_price += it->latest_price;
        square_total_latest_price += it->latest_price * it->latest_price;
        
        if( timecmp(it->time.c_str(), T_5) <= 0 )
        {
            count_pre5++;
            
            total_buy_total_pre5 += it->buy_total;
            total_buy_sell_total_pre5 += it->buy_and_sell_total;
            
            total_latest_price_pre5 += it->latest_price;
            square_total_latest_price_pre5 += it->latest_price * it->latest_price;
        }
        else if( timecmp(it->time.c_str(), T_7) <= 0 )
        {
            count_57++;
            
            total_buy_total_57 += it->buy_total;
            total_buy_sell_total_57 += it->buy_and_sell_total;
            
            total_latest_price_57 += it->latest_price;
            square_total_latest_price_57 += it->latest_price * it->latest_price;
        }
        else
        {
            count_post7++;
            
            total_buy_total_post7 += it->buy_total;
            total_buy_sell_total_post7 += it->buy_and_sell_total;
            
            total_latest_price_post7 += it->latest_price;
            square_total_latest_price_post7 += it->latest_price * it->latest_price;
        }
    }
    IMBAL = total_buy_total / total_buy_sell_total;
    IMBAL_pre5  = total_buy_total_pre5  / total_buy_sell_total_pre5;
    IMBAL_57    = total_buy_total_57    / total_buy_sell_total_57;
    IMBAL_post7 = total_buy_total_post7 / total_buy_sell_total_post7;
    
    double mean_tlpp = total_latest_price / count;
    double mean_tlpp_pre5  = total_latest_price_pre5   / count_pre5;
    double mean_tlpp_57    = total_latest_price_57     / count_57;
    double mean_tlpp_post7 = total_latest_price_post7  / count_post7;
    
    Volatility = sqrt( square_total_latest_price / count - mean_tlpp * mean_tlpp );
    Volatility_pre5     = sqrt( square_total_latest_price_pre5 / count_pre5 - mean_tlpp_pre5 * mean_tlpp_pre5 );
    Volatility_57       = sqrt( square_total_latest_price_57 / count_57 - mean_tlpp_57 * mean_tlpp_57 );
    Volatility_post7    = sqrt( square_total_latest_price_post7 / count_post7 - mean_tlpp_post7 * mean_tlpp_post7 );
    
    printresult();
}

void readcsv(char* filename)
{
    char buffer[256];
    ifstream in(filename);
    vector<csvline> csvlines;
    csvlines.clear();
    int cnt = 0;
    
    if (! in.is_open())
    {
        cout << "Cannot open the file" << endl;
        exit(1);
    }
    while (!in.eof())
    {
        in.getline(buffer, 256);
        if(cnt == 0)
        {
            cnt++;
            continue;
        }
        if(strcmp(buffer, "") != 0)
        {
            string sbuf = buffer;
            csvline thisline = calline(sbuf);
            csvlines.push_back(thisline);
            cnt++;
        }
    }
    dealcsv(csvlines);
    return;
}

void readdir(const char * dir)
{
    DIR *dp;
    struct  dirent  *entry;
    struct  stat    statbuf;
    
    //先遍历一次目录，添加所有图片
    if ((dp = opendir(dir)) == NULL)
    {
        printf("Cannot open the dir.\n");
        return ;
    }
    //如果不能打开用户所给目录，程序退出
    else
    {
        chdir(dir);
        while ( (entry = readdir(dp)) != NULL )
        {
            lstat( entry->d_name, &statbuf );
            if ( S_ISDIR(statbuf.st_mode) )
            {
                if ( strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0 )
                {
                    continue;
                }
                //排除Linux系统下的隐藏文件和上级目录
            }
            else
            {
                char filename[] = "";
                strcat(filename, entry->d_name);
                
                string key = filename;
                key = key.substr(0, key.find('_'));
                cout << key ;
                readcsv(filename);
            }
        }
        chdir("..");
        closedir(dp);
    }

}