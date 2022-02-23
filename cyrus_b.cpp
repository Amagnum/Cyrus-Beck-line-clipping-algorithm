// 	Sirusbeck algo

#include <bits/stdc++.h>
#include <Eigen>

/*
g++ -I ./lib/eigen-3.3.9/Eigen 3dTransf.cpp -o 3d.exp
./3d.exp < 3d.in
*/

using namespace Eigen;
using namespace std;

int main(){
	
    string mode;
    int k = 4, // no of boundaries
    	nlines = 1; // no of lines
    
    cin >> mode;

    map<string,string> name;
    name["01"]="B";
    name["-10"]="R";
    name["0-1"]="T";
    name["10"]="L";
    

	vector<Vector2d> bnd_points = vector<Vector2d>(k,Vector2d()); // 4 boundaries , 2 dimensions

    if(mode=="win"){
    	double Xmin,Xmax, Ymin, Ymax;
    	cin >> Xmin >> Xmax >> Ymin >> Ymax;
    	bnd_points[0](0) = bnd_points[3](0) = Xmin;
    	bnd_points[0](1) = bnd_points[1](1) = Ymin;
    	bnd_points[2](0) = bnd_points[1](0) = Xmax;
    	bnd_points[2](1) = bnd_points[3](1) = Ymax;
    	for(auto i: bnd_points)
    		cout<<i.transpose()<<endl;
    }
    else if(mode=="poi"){
	   	cin>>k;
	   	// Definfing Boundary

	   	cout<<"Boundary Points: (Always take ACKW rotation)"<<endl;
	   	for(int i=0; i<k; i++){
	   		double temp;
	   		cin >> temp;
	   		bnd_points[i](0) = temp; // X coord
	   		cin >> temp;
	   		bnd_points[i](1) = temp; // Y coord
	   		cout<<bnd_points[i].transpose()<<endl;
	   	}
   }

   	// Calculating Normals

   	cout<<"Noraml Vectors: (Pointing Inside)"<<endl;
    vector<Vector2d> norms = vector<Vector2d>(k,Vector2d());

    // Always take ACKW rotation
    for(int i=1; i<k+1; i++){
    	Vector2d bnd_vec = bnd_points[i%k] - bnd_points[i-1];
    	norms[i-1](0) = -1*bnd_vec(1);
    	norms[i-1](1) = bnd_vec(0);
    	norms[i-1].normalize();
    	cout<<right<<setw(5)<<norms[i-1].transpose()<<endl;
    }

    cin >> nlines;

   	while(nlines--){
   		cout<<"\n------- New Line --------\n";
   		Vector2d p1(2), p2(2);
    	double X,Y;

   		cin >> X >> Y;
   		p1(0) = X; // P1 X
	   	p1(1) = Y; // P1 Y

	   	cin >> X >> Y;
	   	p2(0) = X; // P2 X
	   	p2(1) = Y; // P2 Y

	   	cout<<" P1: ("<<p1.transpose()<<") ->  P2: ("<<p2.transpose()<<")"<<endl<<endl;

	   	Vector2d d(1,2);
   		d = p2-p1;
   		
   		cout<<" Wi = P1 - Qi"<<endl;
	   	cout<<" t = - Wi.Ni / D.Ni"<<endl;
   		cout<<" D (P2-P1): "<<d.transpose()<<endl<<endl;
   		
	   	cout << right;
   		cout << "P_  D [   Nx Ny ]   [   Qx Qy ]   [   Wx Wy ] |   N.W |   N.D |  Tmin |  Tmax |"<<endl;
   		cout << " -------------------------------------------------------------------------- "<<endl;

   		double ftmin=0.0, ftmax=1.0;
	    for(int i=0; i<k; i++){
	    	Vector2d w(2);
	    	double tmin = 0.0, tmax = 1.0, stmin=0, stmax=0;
	    	if(d.dot(norms[i])==0){
	    		cout<<"Removed Line (d.n=0)\n";
	    		break;	
	    	}else{
	    		w = p1 - bnd_points[i];
	    		//cout << "w:" << w.transpose()<<endl;
	    		double t = -1.0*(w.dot(norms[i]))/(d.dot(norms[i]));
	    		if(d.dot(norms[i])>0){
	    			cout<<"PE ";
	    			if(t<1)
	    				if(t>tmin) tmin=t; 
	    			stmin = t;
	    		}
	    		else if(t>0){
	    			cout<<"PL ";
	    			if(t<tmax) tmax = t;
	    			stmax =t;
	    		}
	    	}

	    	cout<<" "<<name[to_string((int)norms[i](0))+to_string((int)norms[i](1))];
	    	cout << right;
	    	cout << " [ " << setw(2) << norms[i].transpose() << " ]"<< setw(5) <<"[ "<< setw(2) << bnd_points[i].transpose() 
	    		 << " ]"<< setw(5) <<"[ "<< setw(2)<< w.transpose()
	    		 << " ] | " << setw(5) << norms[i].dot(w) << " | " << setw(5)
	    		 << norms[i].dot(d) << " | "<< setw(5) << stmin << " | "<< setw(5) <<stmax;//<<endl;
	    	cout << " | ( Tmin Tmax ) = " << tmin << " "<< tmax << endl;// << endl;
	    	ftmax = min(tmax,ftmax);
	    	ftmin = max(tmin,ftmin);
	    }

	    if(ftmax<=ftmin){ 
	    	cout<<"Removed Line (tmax<tmin)\n\n";
	    }else{
	    	cout<<" tmin: ("<<(p1+(p2-p1)*ftmin).transpose()<<") t: "<<ftmin<<endl;
	    	cout<<" tmax: ("<<(p1+(p2-p1)*ftmax).transpose()<<") t: "<<ftmax<<endl;
	    }
	    // else compute the visible part 
	}

	return 0;
}