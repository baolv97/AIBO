#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

struct B_O {
	float time;
	float open ;
	float close ;
	float diff;
};

B_O B[200000];

long readB(){
	ifstream f;
	f.open("Bo.txt",ios::out);
	
	long count =0;
	
	while (!f.eof()){
		f>>B[count].time;
		f>>B[count].open;
		f>>B[count].close;
		B[count].diff=0;
		count++;
	}
	return count-1;
}

main(){
	// Bao -Bao dep trai.
	long k=readB();
	
	float M=500;
	// von banau la 500$
	for (int i=1;i<k;i++){
		B[i].diff=B[i].close*100000-B[i-1].close*100000;
		//cout<<B[i].diff<<endl;
	}
	cout <<"tong so giao dich "<<k<<endl;
	long i= 1;
	float win = 0;
	float lose =0 ;
	float maxM=-1;
	float minM= 1000000;
	while(i < k){
		//cout<<i<<endl;
		if (abs(B[i].diff) <=3 && B[i].time >= 13.0 && B[i].time <= 15.0  ){
			if (B[i+1].diff*B[i].diff < 0){
				if (M/100*6 < 3){
					M=M-3;
				}else {
					M=M-M/100*6;
				}
				
			 	lose++;
			}else {
				if (M/100*6 < 3){
					M=M+3*0.8;
				}else {
					M=M+M/100*6*0.8;
				}
				win ++;
			}
			i+=2;
		}
		
		if (M > maxM) maxM=M;
		//cout<<M<<endl;
		
		if (M < minM){
			cout<<i<<"	"<<M<<endl;
			minM=M;	
		} 
		//cout<<M<<endl;
		
		if (M< 0) {
			cout <<"Pha san"<<endl;
			break;
		}
		i++;
	}
	
	cout<<"Tong hien tai:"<<M<<endl;
	cout<<"Thoi gian so tien cao nhat:"<<maxM<<endl;
	cout<<"Thoi gian so tien xuong thap nhat:"<<minM<<endl;
	cout <<"tong so tran choi:"<< win +lose <<endl;
	cout<<win/(win+lose); // voi ty le win nay minh danh ve nau dai minh se thang. kelly =0.060175 ddang danh k/4=1.5%
}
