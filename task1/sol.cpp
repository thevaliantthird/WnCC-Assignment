#include <bits/stdc++.h>
#define pbi pair<bool,int>

using namespace std;

struct GroundWork {
  int start;
  int dur;
  int end;
};

struct Available_GroundWorks {
  int n;
  GroundWork *works;
};

Available_GroundWorks* initialize(int start_time[], int duration[], int n) {
  Available_GroundWorks *work = new Available_GroundWorks;
  work->n = n;
  work->works = new GroundWork[n];
  for(int i = 0;i<n;i++){
    work->works[i].start = start_time[i];
    work->works[i].dur = duration[i];
    work->works[i].end = start_time[i]+duration[i];
  }
  return work;
}

int *dp;
int N;
map<int,int> indi;
vector<pbi > *wh;

int DP(int i, GroundWork * ptr, int *endsi) {

  if (dp[i]!=-1) {return dp[i];}
  else {

    int maxi = -1;
    for(int j = 0;j<wh[i].size();j++) {
      if(wh[i][j].first==1){
        maxi = max(maxi, DP(indi[ptr[wh[i][j].second].start],ptr,endsi)+1);
      }
    }
    maxi = max(maxi,DP(endsi[i],ptr,endsi));
    dp[i] = maxi;
    return dp[i];
  }
}

int CalculateMaxGroundworks(Available_GroundWorks* ptr) {
  set<int> ind;
  set<int> endi;
  for(int i = 0;i<ptr->n;i++){
    ind.insert(ptr->works[i].start);
    ind.insert(ptr->works[i].end);
  }
  N = ind.size();

  set<int>::iterator it = ind.begin();
  for(int i = 0;i<ind.size();i++){
    indi[*it] = i;
    ++it;
  }
  dp = new int[N];
  for(int i = 0;i<N;i++) {
    dp[i] = -1;
  }
  dp[0] = 0;

  wh = new vector<pbi >[N];
  int *endsis = new int[N];

  for(int i = 0;i<ptr->n;i++) {
    wh[indi[ptr->works[i].start]].push_back(make_pair(0,i));
    wh[indi[ptr->works[i].end]].push_back(make_pair(1,i));
    endi.insert(indi[ptr->works[i].end]);
  }

  int j = 0;
  for(int i = 0;i<N;i++) {
    endsis[i] = j;
    if(endi.find(i)!=endi.end()) {
      j = i;
    }
  }
  return DP(N-1,ptr->works,endsis);
}

int main () {
  int i,j,k;
  ifstream inf("Schedule.txt",ios::in);
  int start[500000];
  int duration[500000];
  i = 0;
  string s;
  map<int, map<int,bool> > ifs;
  while(inf>>s>>j>>k) {
    if( !ifs[j][k]){
      start[i] = j;
      duration[i] = k;
      ifs[j][k] = 1;
      i++;
    }
  }
  Available_GroundWorks *myWork = initialize(start,duration,i);
  cout<<CalculateMaxGroundworks(myWork)<<endl;
}
