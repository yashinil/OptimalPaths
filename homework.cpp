#include<bits/stdc++.h>
#include<string>
using namespace std;

void BreadthFirstSearch(int **map,int **parent_h,int **parent_w,int target_coordinates[],int number_of_targets, int rows,int columns, int source_w,int source_h,int max_diff){
    bool visited[rows][columns];
    for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             visited[i][j]=false;
         }
     }
    parent_h[source_h][source_w]=-5;
    parent_w[source_h][source_w]=-5;
    visited[source_h][source_w]=true;
    queue <int> qh;
    queue <int> qw;
    qh.push(source_h);
    qw.push(source_w);

    while(!qh.empty() && !qw.empty()){
    int self_h=qh.front();
    int self_w=qw.front();
    //east
    if(self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h][self_w+1])<=max_diff && visited[self_h][self_w+1]==false){
        parent_h[self_h][self_w+1]=self_h;
        parent_w[self_h][self_w+1]=self_w;
        visited[self_h][self_w+1]=true;
        qh.push(self_h);
        qw.push(self_w+1);
    }
    }
    //west
    if(self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h][self_w-1])<=max_diff && visited[self_h][self_w-1]==false){
        parent_h[self_h][self_w-1]=self_h;
        parent_w[self_h][self_w-1]=self_w;
        visited[self_h][self_w-1]=true;
        qh.push(self_h);
        qw.push(self_w-1);
    }
    }
    //north
    if(self_h!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w])<=max_diff && visited[self_h-1][self_w]==false){
        parent_h[self_h-1][self_w]=self_h;
        parent_w[self_h-1][self_w]=self_w;
        visited[self_h-1][self_w]=true;
        qh.push(self_h-1);
        qw.push(self_w);
    }
    }
    //south
    if(self_h!=rows-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w])<=max_diff && visited[self_h+1][self_w]==false){
        parent_h[self_h+1][self_w]=self_h;
        parent_w[self_h+1][self_w]=self_w;
        visited[self_h+1][self_w]=true;
        qh.push(self_h+1);
        qw.push(self_w);
    }
    }
    //northwest
    if(self_h!=0 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w-1])<=max_diff && visited[self_h-1][self_w-1]==false){
        parent_h[self_h-1][self_w-1]=self_h;
        parent_w[self_h-1][self_w-1]=self_w;
        visited[self_h-1][self_w-1]=true;
        qh.push(self_h-1);
        qw.push(self_w-1);
    }
    }
    //northeast
    if(self_h!=0 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w+1])<=max_diff && visited[self_h-1][self_w+1]==false){
        parent_h[self_h-1][self_w+1]=self_h;
        parent_w[self_h-1][self_w+1]=self_w;
        visited[self_h-1][self_w+1]=true;
        qh.push(self_h-1);
        qw.push(self_w+1);
    }
    }
    //southwest
    if(self_h!=rows-1 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w-1])<=max_diff && visited[self_h+1][self_w-1]==false){
        parent_h[self_h+1][self_w-1]=self_h;
        parent_w[self_h+1][self_w-1]=self_w;
        visited[self_h+1][self_w-1]=true;
        qh.push(self_h+1);
        qw.push(self_w-1);
    }
    }
    //southeast
    if(self_h!=rows-1 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w+1])<=max_diff && visited[self_h+1][self_w+1]==false){
        parent_h[self_h+1][self_w+1]=self_h;
        parent_w[self_h+1][self_w+1]=self_w;
        visited[self_h+1][self_w+1]=true;
        qh.push(self_h+1);
        qw.push(self_w+1);
    }
    }
    qh.pop();
    qw.pop();
    }
    /*for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             cout<<parent_h[i][j]<<parent_w[i][j]<<'\t';
        }
        cout<<endl;
    }*/
    ofstream outputFile;
    outputFile.open("output.txt");

    for(int i=0;i<2*number_of_targets;i+=2){
        int temp_h=parent_h[target_coordinates[i+1]][target_coordinates[i]];
        int temp_w=parent_w[target_coordinates[i+1]][target_coordinates[i]];
        if(temp_h==-2 && temp_w==-2)
            outputFile<<"FAIL"<<'\n';
        else{
            vector <int> answer;
            answer.push_back(target_coordinates[i+1]);
            answer.push_back(target_coordinates[i]);
            while(true){
                if(temp_h==-5 && temp_w==-5){
                    break;
                }
                else{
                    answer.push_back(temp_h);
                    answer.push_back(temp_w);
                    int x=temp_h;
                    int y=temp_w;
                    temp_h=parent_h[x][y];
                    temp_w=parent_w[x][y];
                }
            }
            for(int i=answer.size()-1; i>=0;i--){
                if(i==0)
                    outputFile<<answer[i]<<'\n';
                else if(i%2!=0)
                    outputFile<<answer[i]<<',';
                else
                    outputFile<<answer[i]<<' ';
            }
        }
    }
    outputFile.close();
}

void UniformCostSearch(int **map,int **parent_h,int **parent_w,int **cost,int target_coordinates[],int number_of_targets, int rows,int columns, int source_w,int source_h,int max_diff){
    bool visited[rows][columns];
    for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             visited[i][j]=false;
         }
     }
    parent_h[source_h][source_w]=-5;
    parent_w[source_h][source_w]=-5;
    visited[source_h][source_w]=true;

    multimap<int, int> queue;
    int combine=source_h*columns+source_w;
    queue.insert(pair<int,int>(0,combine));

    while(!queue.empty()){
    multimap<int,int>::iterator it=queue.begin();
    int n=it->second;
    int self_h=n/columns;
    int self_w=n%columns;

    //east
    if(self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h][self_w+1])<=max_diff && visited[self_h][self_w+1]==false){
        parent_h[self_h][self_w+1]=self_h;
        parent_w[self_h][self_w+1]=self_w;
        visited[self_h][self_w+1]=true;
        cost[self_h][self_w+1]=cost[self_h][self_w]+10;
        combine=self_h*columns+self_w+1;
        queue.insert(pair<int,int>(cost[self_h][self_w+1],combine));
    }
    }
    //west
    if(self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h][self_w-1])<=max_diff && visited[self_h][self_w-1]==false){
        parent_h[self_h][self_w-1]=self_h;
        parent_w[self_h][self_w-1]=self_w;
        visited[self_h][self_w-1]=true;
        cost[self_h][self_w-1]=cost[self_h][self_w]+10;
        combine=self_h*columns+self_w-1;
        queue.insert(pair<int,int>(cost[self_h][self_w-1],combine));
    }
    }
    //north
    if(self_h!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w])<=max_diff && visited[self_h-1][self_w]==false){
        parent_h[self_h-1][self_w]=self_h;
        parent_w[self_h-1][self_w]=self_w;
        visited[self_h-1][self_w]=true;
        cost[self_h-1][self_w]=cost[self_h][self_w]+10;
        combine=(self_h-1)*columns+self_w;
        queue.insert(pair<int,int>(cost[self_h-1][self_w],combine));
    }
    }
    //south
    if(self_h!=rows-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w])<=max_diff && visited[self_h+1][self_w]==false){
        parent_h[self_h+1][self_w]=self_h;
        parent_w[self_h+1][self_w]=self_w;
        visited[self_h+1][self_w]=true;
        cost[self_h+1][self_w]=cost[self_h][self_w]+10;
        combine=(self_h+1)*columns+self_w;
        queue.insert(pair<int,int>(cost[self_h+1][self_w],combine));
    }
    }
    //northwest
    if(self_h!=0 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w-1])<=max_diff && visited[self_h-1][self_w-1]==false){
        parent_h[self_h-1][self_w-1]=self_h;
        parent_w[self_h-1][self_w-1]=self_w;
        visited[self_h-1][self_w-1]=true;
        cost[self_h-1][self_w-1]=cost[self_h][self_w]+14;
        combine=(self_h-1)*columns+self_w-1;
        queue.insert(pair<int,int>(cost[self_h-1][self_w-1],combine));
    }
    }
    //northeast
    if(self_h!=0 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w+1])<=max_diff && visited[self_h-1][self_w+1]==false){
        parent_h[self_h-1][self_w+1]=self_h;
        parent_w[self_h-1][self_w+1]=self_w;
        visited[self_h-1][self_w+1]=true;
        cost[self_h-1][self_w+1]=cost[self_h][self_w]+14;
        combine=(self_h-1)*columns+self_w+1;
        queue.insert(pair<int,int>(cost[self_h-1][self_w+1],combine));
    }
    }
    //southwest
    if(self_h!=rows-1 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w-1])<=max_diff && visited[self_h+1][self_w-1]==false){
        parent_h[self_h+1][self_w-1]=self_h;
        parent_w[self_h+1][self_w-1]=self_w;
        visited[self_h+1][self_w-1]=true;
        cost[self_h+1][self_w-1]=cost[self_h][self_w]+14;
        combine=(self_h+1)*columns+self_w-1;
        queue.insert(pair<int,int>(cost[self_h+1][self_w-1],combine));
    }
    }
    //southeast
    if(self_h!=rows-1 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w+1])<=max_diff && visited[self_h+1][self_w+1]==false){
        parent_h[self_h+1][self_w+1]=self_h;
        parent_w[self_h+1][self_w+1]=self_w;
        visited[self_h+1][self_w+1]=true;
        cost[self_h+1][self_w+1]=cost[self_h][self_w]+14;
        combine=(self_h+1)*columns+self_w+1;
        queue.insert(pair<int,int>(cost[self_h+1][self_w+1],combine));
    }
    }
    queue.erase(queue.begin());
    /*for (it=queue.begin(); it!=queue.end(); it++)
    cout << it->first << " => " << it->second << '\n';
    cout<<"_______________________"<<endl;*/
    }
    /*for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             cout<<parent_h[i][j]<<parent_w[i][j]<<'\t';
        }
        cout<<endl;
    }*/
    ofstream outputFile;
    outputFile.open("output.txt");

    for(int i=0;i<2*number_of_targets;i+=2){
        int temp_h=parent_h[target_coordinates[i+1]][target_coordinates[i]];
        int temp_w=parent_w[target_coordinates[i+1]][target_coordinates[i]];
        //cout<<temp_h<<temp_w<<endl;
        if(temp_h==-2 && temp_w==-2)
            outputFile<<"FAIL"<<'\n';
        else{
            vector <int> answer;
            cout<<cost[target_coordinates[i+1]][target_coordinates[i]]<<endl;
            answer.push_back(target_coordinates[i+1]);
            answer.push_back(target_coordinates[i]);
            while(true){
                if(temp_h==-5 && temp_w==-5){
                    break;
                }
                else{
                    answer.push_back(temp_h);
                    answer.push_back(temp_w);
                    int x=temp_h;
                    int y=temp_w;
                    temp_h=parent_h[x][y];
                    temp_w=parent_w[x][y];
                }
            }
            for(int i=answer.size()-1; i>=0;i--){
                if(i==0)
                    outputFile<<answer[i]<<'\n';
                else if(i%2!=0)
                    outputFile<<answer[i]<<',';
                else
                    outputFile<<answer[i]<<' ';
            }
        }
    }
    outputFile.close();
}

vector <int> HeuristicSearch(int **map,int **parent_h,int **parent_w,int **cost,int rows,int columns, int source_w,int source_h,int target_w,int target_h,int max_diff){
    bool visited[rows][columns];
    for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             visited[i][j]=false;
         }
     }
    parent_h[source_h][source_w]=-5;
    parent_w[source_h][source_w]=-5;
    visited[source_h][source_w]=true;

    multimap<int, int> queue;
    int combine=source_h*columns+source_w;
    int g=cost[source_h][source_w];
    int h=max(abs(target_h-source_h),abs(target_w-source_w));
    int f=g+h;
    int flag=0;
    queue.insert(pair<int,int>(f,combine));

    while(!queue.empty()){
    multimap<int,int>::iterator it=queue.begin();
    int n=it->second;
    int self_h=n/columns;
    int self_w=n%columns;
    //cout<<self_h<<self_w<<endl;
    if(self_h==target_h && self_w==target_w){
        flag=1;
        break;
    }
    //east
    if(self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h][self_w+1])<=max_diff && visited[self_h][self_w+1]==false){
        parent_h[self_h][self_w+1]=self_h;
        parent_w[self_h][self_w+1]=self_w;
        visited[self_h][self_w+1]=true;
        cost[self_h][self_w+1]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w+1]);
        g=cost[self_h][self_w+1];
        h=max(abs(target_h-self_h),abs(target_w-(self_w+1)));
        f=g+h;
        combine=self_h*columns+self_w+1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h][self_w+1])<=max_diff && visited[self_h][self_w+1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w+1]);
        if(cost_temp<cost[self_h][self_w+1]){
            parent_h[self_h][self_w+1]=self_h;
            parent_w[self_h][self_w+1]=self_w;
            visited[self_h][self_w+1]=true;
            cost[self_h][self_w+1]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w+1]);
            g=cost[self_h][self_w+1];
            h=max(abs(target_h-self_h),abs(target_w-(self_w+1)));
            f=g+h;
            combine=self_h*columns+self_w+1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //west
    if(self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h][self_w-1])<=max_diff && visited[self_h][self_w-1]==false){
        parent_h[self_h][self_w-1]=self_h;
        parent_w[self_h][self_w-1]=self_w;
        visited[self_h][self_w-1]=true;
        cost[self_h][self_w-1]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w-1]);
        g=cost[self_h][self_w-1];
        h=max(abs(target_h-self_h),abs(target_w-(self_w-1)));
        f=g+h;
        combine=self_h*columns+self_w-1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h][self_w-1])<=max_diff && visited[self_h][self_w-1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w-1]);
        if(cost_temp<cost[self_h][self_w-1]){
            parent_h[self_h][self_w-1]=self_h;
            parent_w[self_h][self_w-1]=self_w;
            visited[self_h][self_w-1]=true;
            cost[self_h][self_w-1]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h][self_w-1]);
            g=cost[self_h][self_w-1];
            h=max(abs(target_h-self_h),abs(target_w-(self_w-1)));
            f=g+h;
            combine=self_h*columns+self_w-1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //north
    if(self_h!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w])<=max_diff && visited[self_h-1][self_w]==false){
        parent_h[self_h-1][self_w]=self_h;
        parent_w[self_h-1][self_w]=self_w;
        visited[self_h-1][self_w]=true;
        cost[self_h-1][self_w]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h-1][self_w]);
        g=cost[self_h-1][self_w];
        h=max(abs(target_h-(self_h-1)),abs(target_w-self_w));
        f=g+h;
        combine=(self_h-1)*columns+self_w;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h-1][self_w])<=max_diff && visited[self_h-1][self_w]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h-1][self_w]);
        if(cost_temp<cost[self_h-1][self_w]){
            parent_h[self_h-1][self_w]=self_h;
            parent_w[self_h-1][self_w]=self_w;
            visited[self_h-1][self_w]=true;
            cost[self_h-1][self_w]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h-1][self_w]);
            g=cost[self_h-1][self_w];
            h=max(abs(target_h-(self_h-1)),abs(target_w-(self_w)));
            f=g+h;
            combine=(self_h-1)*columns+self_w;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //south
    if(self_h!=rows-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w])<=max_diff && visited[self_h+1][self_w]==false){
        parent_h[self_h+1][self_w]=self_h;
        parent_w[self_h+1][self_w]=self_w;
        visited[self_h+1][self_w]=true;
        cost[self_h+1][self_w]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h+1][self_w]);
        g=cost[self_h+1][self_w];
        h=max(abs(target_h-(self_h+1)),abs(target_w-self_w));
        f=g+h;
        combine=(self_h+1)*columns+self_w;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h+1][self_w])<=max_diff && visited[self_h+1][self_w]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h+1][self_w]);
        if(cost_temp<cost[self_h+1][self_w]){
            parent_h[self_h+1][self_w]=self_h;
            parent_w[self_h+1][self_w]=self_w;
            visited[self_h+1][self_w]=true;
            cost[self_h+1][self_w]=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h+1][self_w]);
            g=cost[self_h+1][self_w];
            h=max(abs(target_h-(self_h+1)),abs(target_w-(self_w)));
            f=g+h;
            combine=(self_h+1)*columns+self_w;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //northwest
    if(self_h!=0 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w-1])<=max_diff && visited[self_h-1][self_w-1]==false){
        parent_h[self_h-1][self_w-1]=self_h;
        parent_w[self_h-1][self_w-1]=self_w;
        visited[self_h-1][self_w-1]=true;
        cost[self_h-1][self_w-1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h-1][self_w-1]);
        g=cost[self_h-1][self_w-1];
        h=max(abs(target_h-(self_h-1)),abs(target_w-(self_w-1)));
        f=g+h;
        combine=(self_h-1)*columns+self_w-1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h-1][self_w-1])<=max_diff && visited[self_h-1][self_w-1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h-1][self_w-1]);
        if(cost_temp<cost[self_h-1][self_w-1]){
            parent_h[self_h-1][self_w-1]=self_h;
            parent_w[self_h-1][self_w-1]=self_w;
            visited[self_h-1][self_w-1]=true;
            cost[self_h-1][self_w-1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h-1][self_w-1]);
            g=cost[self_h-1][self_w-1];
            h=max(abs(target_h-(self_h-1)),abs(target_w-(self_w-1)));
            f=g+h;
            combine=(self_h-1)*columns+self_w-1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //northeast
    if(self_h!=0 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h-1][self_w+1])<=max_diff && visited[self_h-1][self_w+1]==false){
        parent_h[self_h-1][self_w+1]=self_h;
        parent_w[self_h-1][self_w+1]=self_w;
        visited[self_h-1][self_w+1]=true;
        cost[self_h-1][self_w+1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h-1][self_w+1]);
        g=cost[self_h-1][self_w+1];
        h=max(abs(target_h-(self_h-1)),abs(target_w-(self_w+1)));
        f=g+h;
        combine=(self_h-1)*columns+self_w+1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h-1][self_w+1])<=max_diff && visited[self_h-1][self_w+1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h-1][self_w+1]);
        if(cost_temp<cost[self_h-1][self_w+1]){
            parent_h[self_h-1][self_w+1]=self_h;
            parent_w[self_h-1][self_w+1]=self_w;
            visited[self_h-1][self_w+1]=true;
            cost[self_h-1][self_w+1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h-1][self_w+1]);
            g=cost[self_h-1][self_w+1];
            h=max(abs(target_h-(self_h-1)),abs(target_w-(self_w+1)));
            f=g+h;
            combine=(self_h-1)*columns+self_w+1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //southwest
    if(self_h!=rows-1 && self_w!=0){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w-1])<=max_diff && visited[self_h+1][self_w-1]==false){
        parent_h[self_h+1][self_w-1]=self_h;
        parent_w[self_h+1][self_w-1]=self_w;
        visited[self_h+1][self_w-1]=true;
        cost[self_h+1][self_w-1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h+1][self_w-1]);
        g=cost[self_h+1][self_w-1];
        h=max(abs(target_h-(self_h+1)),abs(target_w-(self_w-1)));
        f=g+h;
        combine=(self_h+1)*columns+self_w-1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h+1][self_w-1])<=max_diff && visited[self_h+1][self_w-1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h+1][self_w-1]);
        if(cost_temp<cost[self_h+1][self_w-1]){
            parent_h[self_h+1][self_w-1]=self_h;
            parent_w[self_h+1][self_w-1]=self_w;
            visited[self_h+1][self_w-1]=true;
            cost[self_h+1][self_w-1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h+1][self_w-1]);
            g=cost[self_h+1][self_w-1];
            h=max(abs(target_h-(self_h+1)),abs(target_w-(self_w-1)));
            f=g+h;
            combine=(self_h+1)*columns+self_w-1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    //southeast
    if(self_h!=rows-1 && self_w!=columns-1){
    if(abs(map[self_h][self_w]-map[self_h+1][self_w+1])<=max_diff && visited[self_h+1][self_w+1]==false){
        parent_h[self_h+1][self_w+1]=self_h;
        parent_w[self_h+1][self_w+1]=self_w;
        visited[self_h+1][self_w+1]=true;
        cost[self_h+1][self_w+1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h+1][self_w+1]);
        g=cost[self_h+1][self_w+1];
        h=max(abs(target_h-(self_h+1)),abs(target_w-(self_w+1)));
        f=g+h;
        combine=(self_h+1)*columns+self_w+1;
        queue.insert(pair<int,int>(f,combine));
    }
    else if(abs(map[self_h][self_w]-map[self_h+1][self_w+1])<=max_diff && visited[self_h+1][self_w+1]==true){
        int cost_temp=cost[self_h][self_w]+10+abs(map[self_h][self_w]-map[self_h+1][self_w+1]);
        if(cost_temp<cost[self_h+1][self_w+1]){
            parent_h[self_h+1][self_w+1]=self_h;
            parent_w[self_h+1][self_w+1]=self_w;
            visited[self_h+1][self_w+1]=true;
            cost[self_h+1][self_w+1]=cost[self_h][self_w]+14+abs(map[self_h][self_w]-map[self_h+1][self_w+1]);
            g=cost[self_h+1][self_w+1];
            h=max(abs(target_h-(self_h+1)),abs(target_w-(self_w+1)));
            f=g+h;
            combine=(self_h+1)*columns+self_w+1;
            queue.insert(pair<int,int>(f,combine));
        }
    }
    }
    queue.erase(queue.begin());
    /*for (it=queue.begin(); it!=queue.end(); it++)
    cout << (it->second)/columns<<" , "<<(it->second)%columns<< " => " << it->first << '\n';
    cout<<"_______________________"<<endl;*/
    }
    /*for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             cout<<parent_h[i][j]<<parent_w[i][j]<<'\t';
        }
        cout<<endl;
    }*/

    /*for(int i = 0; i < rows; i++){
         for(int j = 0; j < columns; j++){
             cout<<cost[i][j]<<'\t';
        }
        cout<<endl;
    }*/

    vector <int> answer;
    int temp_h=parent_h[target_h][target_w];
    int temp_w=parent_w[target_h][target_w];
    if(temp_h==-2 && temp_w==-2 && flag==0)
            answer.push_back(-1);
    else{
        cout<<cost[target_h][target_w]<<endl;
        answer.push_back(target_h);
        answer.push_back(target_w);
        while(true){
            if(temp_h==-5 && temp_w==-5){
                break;
            }
            else{
                answer.push_back(temp_h);
                answer.push_back(temp_w);
                int x=temp_h;
                int y=temp_w;
                temp_h=parent_h[x][y];
                temp_w=parent_w[x][y];
            }
        }
    }
    return answer;
}


int main(){
    string type_of_algorithm;
    int columns,rows,landing_column,landing_row,max_diff_elevation,number_of_targets;
    ifstream inputFile;
    inputFile.open("input004.txt");
    if(inputFile.is_open()){
        inputFile>>type_of_algorithm;
        inputFile>>columns>>rows>>landing_column>>landing_row>>max_diff_elevation>>number_of_targets;
    }
    //target array format is w,h w,h
    int target_coordinates[2*number_of_targets];
    if(inputFile.is_open()){
        for(int i=0; i<2*number_of_targets; i+=2){
            inputFile>>target_coordinates[i]>>target_coordinates[i+1];
        }
    }
    int map[rows][columns];
    if(inputFile.is_open()){
        for(int i=0; i<rows; i++){
            for(int j=0;j<columns;j++){
                inputFile>>map[i][j];
            }
        }
    }
    inputFile.close();
    int *map_pointer[rows];

    int parent_h[rows][columns];
    int *parents_h_pointer[rows];

    int parent_w[rows][columns];
    int *parents_w_pointer[rows];

    int cost[rows][columns];
    int *cost_pointer[rows];
    vector <int> path;

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            parent_h[i][j]=-2;
            parent_w[i][j]=-2;
        }
    }
    for (int i=0;i<rows;i++){
        map_pointer[i] = map[i];
        parents_h_pointer[i]=parent_h[i];
        parents_w_pointer[i]=parent_w[i];
    }

    ofstream outputFile;
    outputFile.open("output.txt");
    switch(type_of_algorithm[0]){
        case 'B':BreadthFirstSearch(map_pointer,parents_h_pointer,parents_w_pointer,target_coordinates,number_of_targets,rows,columns,landing_column,landing_row,max_diff_elevation);
                break;
        case 'U':for(int i=0;i<rows;i++){
                    for(int j=0;j<columns;j++){
                        cost[i][j]=0;
                    }
                }
                for (int i=0;i<rows;i++){
                    cost_pointer[i] = cost[i];
                }
                UniformCostSearch(map_pointer,parents_h_pointer,parents_w_pointer,cost_pointer,target_coordinates,number_of_targets,rows,columns,landing_column,landing_row,max_diff_elevation);
                break;
        case 'A':for(int i=0;i<rows;i++){
                    for(int j=0;j<columns;j++){
                        cost[i][j]=0;
                    }
                }
                for (int i=0;i<rows;i++){
                    cost_pointer[i] = cost[i];
                }
                for(int i=0;i<2*number_of_targets;i+=2){
                    path=HeuristicSearch(map_pointer,parents_h_pointer,parents_w_pointer,cost_pointer,rows,columns,landing_column,landing_row,target_coordinates[i],target_coordinates[i+1],max_diff_elevation);
                    if(path[0]==-1){
                        outputFile<<"FAIL"<<'\n';
                    }
                    else{
                        for(int i=path.size()-1; i>=0;i--){
                            if(i==0)
                                outputFile<<path[i]<<'\n';
                            else if(i%2!=0)
                                outputFile<<path[i]<<',';
                            else
                                outputFile<<path[i]<<' ';
                        }
                    }
                }
                break;
        default: cout<<"Error";break;
    }
    outputFile.close();
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
    return 0;
}
