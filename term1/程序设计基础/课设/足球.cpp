#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;

class team {
private:
	string name;
	int game;
	int score;
	int win;
	int draw;
	int lose;
	int GF;
	int GA;
	int GD;
	//依次为队名, 场次，积分，胜场，平局数，负场，进球，失球，净胜球
public:
	team(string n="...", int game = 0, int s = 0,int w = 0, int dr = 0, int l = 0, int f = 0, int a = 0, int d = 0);
	//team构造函数 
	void getname(string x="0"){
		this->name=x;
	}
	//创建队名 
	void thename(){
		cout<<name<<endl;
	}
	//显示队名 
	void put(){
		cout<<name<<" "<<game<<" "<<score<<" "<<win<<" "<<draw<<" "<<lose<<" "<<GF<<" "<<GA<<" "<<GD<<endl;
	}
	//用于积分表的显示 
	int putscore(){
		return score;
	}
	int putGD(){
		return GD;
	}
	int putGF(){
		return GF;
	}
	//用于排序时取得私有成员的值 
	string putname(){
		return name;
	}
	int putgame(){
		return game;
	}
	int putwin(){
		return win;
	}
	int putlose(){
		return lose;
	}
	int putdraw(){
		return draw;
	}
	int putGA(){
		return GA;
	}
    void add(int g = 0 ,int s = 0,int w = 0, int dr = 0, int l = 0, int f = 0, int a = 0, int d = 0 );
    //修改各项数据 函数add 
    void copy(team obj);
 	//用于复制
};
team::team(string n,int g , int s ,int w , int dr , int l , int f , int a , int d ) {
	this->game = g;
	this->name = n;
	this->score = s;
	this->win = w;
	this->draw = dr;
	this->lose = l;
	this->GF = f;
	this->GA = a;
	this->GD = d;
}
//team构造函数 
void team::copy(team obj){
	this->game = obj.putgame();
	this->name = obj.putname();
	this->score = obj.putscore();
	this->win = obj.putwin();
	this->draw = obj.putdraw();
	this->lose = obj.putlose();
	this->GF = obj.putGF();
	this->GA = obj.putGA();
	this->GD = obj.putGD();
}  
//copy函数
void team::add(int g , int s ,int w , int dr , int l , int f , int a , int d ){
	this->game+=g;
	this->score+=s;
	this->win+=w;
	this->draw+=dr;
	this->lose+=l;
	this->GF+=f;
	this->GA+=a;
	this->GD+=d;
}
//成员函数add 
class league{
	private:
		int round;
		int num;
	public:
		team lt[100];
		league(){}; 
		void create();
		void get();
		void search();
		void begin();
		//begin整合了get和search
		//在主函数中直接调用 
		int getround(){
			return round;
		}
		int getnum(){
			return num;
		} 
		//用于create后取得round的值 
};
void league::create(){
	int numf;
	int roundf;
	cout<<"输入联赛队伍数量";
	cin>>numf;
	roundf=2*(numf-1);
	if(numf<=0||numf%2==1){
		cout<<"...error..."<<endl;
		cout<<"...end..."<<endl;
	} 
	else{
		round=roundf;
		num=numf;
		
	for(int i=0;i<numf;i++){
			cout<<"录入第"<<i+1<<"个球队"<<endl;
			string xxx;
			cin>>xxx;
			lt[i].getname(xxx);
			cout<<"-----------"<<endl;		
		}
		cout<<"录入成功";
		cout<<"-----------"<<endl;	
	}

}
void league::get(){
	cout<<"以下是各队对应的号码列表"<<endl;
	for(int t=0;t<getnum();t++){
		cout<<t;
		lt[t].thename();
	} 
	cout<<"-----------"<<endl;	
	cout<<"下面录入这一轮比赛情况"<<endl;
	int vs1;
	int vs2;
	//对应主客场球队 
	int score1,score2;
	int goal1,goal2;
	for(int u=0;u<getnum()/2;u++){
		cout<<"第"<<u+1<<"场"<<endl;
		cout<<"主队编号:";
		cin>>vs1;
		cout<<"客队编号:";
		cin>>vs2;
		cout<<"主队进球数:";
		cin>>goal1;
		cout<<"客队进球数:";
		cin>>goal2;
		cout<<"完成录入"<<"本场结果为"<<endl;
		cout<<lt[vs1].putname() <<"(主)"<<goal1<<":"<<goal2<<lt[vs2].putname()<<"(客)"<<endl;
		if(goal1>goal2){
			lt[vs1].add(1,3,1,0,0,goal1,goal2,goal1-goal2);
			lt[vs2].add(1,0,0,0,1,goal2,goal1,goal2-goal1);
		} 
		if(goal1<goal2){
			lt[vs2].add(1,3,1,0,0,goal2,goal1,goal2-goal1);
			lt[vs1].add(1,0,0,0,1,goal1,goal2,goal1-goal2);
		} 
		if(goal1==goal2){
			lt[vs1].add(1,1,0,1,0,goal1,goal2,0);
			lt[vs2].add(1,1,0,1,0,goal2,goal1,0);
		}
		cout<<"-----------"<<endl;
	}
	for(int o=0;o<getnum()-1;o++){
		for(int p=o+1;p<getnum();p++){
				team temp;
				//在这里卡了很久
				//原因是之前在team类构造函数中，没用给string类name提供缺省值
				//以至于下面的if中temp无法使用 
				if(lt[o].putscore()<lt[p].putscore()){
					temp.copy(lt[o]);
					lt[o].copy(lt[p]);
					lt[p].copy(temp);
				}
				if(lt[o].putscore()==lt[p].putscore()&&lt[o].putGD()<lt[p].putGD()){
					temp.copy(lt[o]);
					lt[o].copy(lt[p]);
					lt[p].copy(temp);
				} 
				if(lt[o].putscore()==lt[p].putscore()&&lt[o].putGD()==lt[p].putGD()&&lt[o].putGF()<lt[p].putGF()){
					temp.copy(lt[o]);
					lt[o].copy(lt[p]);
					lt[p].copy(temp);
				}
		}
	
	}
}
void league::search() {
	cout<<"联赛积分榜"<<endl;
	cout<<"排名，队名, 场次，积分，胜场，平局数，负场，进球，失球，净胜球" <<endl;
 	cout<<"-----------"<<endl;
	for(int c=0;c<getnum();c++){
		cout<<c+1<<" "; 
		lt[c].put();
	}
	cout<<"-----------"<<endl; 
	cout<<"-----------"<<endl; 	
}
void league::begin(){
	if(num>0&&num%2==0){
		for(int a=0;a<getround();a++){
			cout<<"第"<<a+1<<"轮"<<endl; 
			cout<<"-----------"<<endl;
			get();
			cout<<"-----------"<<endl;
			search();
		}
		for(int o=0;o<getnum()-1;o++){
			int p=o+1;
			if(lt[o].putscore()==lt[p].putscore()&&lt[o].putGD()==lt[p].putGD()&&lt[o].putGF()==lt[p].putGF()){
				cout<<round<<"轮联赛后"<<endl; 
				cout<<lt[o].putname()<<"与"<<lt[p].putname()<<"同分，且净胜球相同，进球数相同"<<endl;
				cout<<"进行附加赛"<<endl; 
				cout<<lt[o].putname()<<"vs"<<lt[p].putname()<<endl;
				int goala;
				int goalb;
				do{
				cout<<lt[o].putname()<<"进球数:";
				cin>>goala;
				cout<<lt[p].putname()<<"进球数:";
				cin>>goalb;
			    }while(goala==goalb);
				if(goala>goalb){
					lt[o].add(1,0,1,0,0,goala,goalb,goala-goalb);
					lt[p].add(1,0,0,0,1,goalb,goala,goalb-goala);  
				}
				if(goala<goalb){
					lt[o].add(1,0,0,0,1,goala,goalb,goala-goalb);
					lt[p].add(1,0,1,0,0,goalb,goala,goalb-goala);  
					team tempab;//交换两队排名
					tempab.copy(lt[o]);
					lt[o].copy(lt[p]);
					lt[p].copy(tempab); 
				}
			}
		}
		cout<<"最终排名如下" <<endl;
		search();
		cout<<lt[0].putname()<<"是冠军"<<endl;
	} 
}
int main(){
	league football;
	football.create(); 
	football.begin() ;
	cout<<"再见";
	return 0;
}

